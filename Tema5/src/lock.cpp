#include <lock.h>
#include <text.h>

#include <iostream>
#include <stdexcept>
#include <utility>

// ================================ 14.1 LockNaiv =============================
LockNaiv::LockNaiv(Mutex* pm)
    : m_mutex(pm)
{
    lock(m_mutex);
}

LockNaiv::~LockNaiv()
{
    unlock(m_mutex);
}

// ============================= 14.2 LockNecopiabil ==========================
LockNecopiabil::LockNecopiabil(Mutex* pm)
    : m_mutex(pm)
{
    lock(m_mutex);
}

LockNecopiabil::~LockNecopiabil()
{
    unlock(m_mutex);
}

// ============================== 14.3 LockPartajat ===========================
LockPartajat::LockPartajat(Mutex* pm)
    : m_mutex(pm, unlock)        // al doilea argument = ce se face la final (în loc de delete)
{
    lock(pm);
}

// ============================ 14.4 LockTransferabil =========================
LockTransferabil::LockTransferabil(Mutex* pm)
    : m_mutex(pm)
{
    lock(m_mutex);
}

LockTransferabil::LockTransferabil(LockTransferabil&& other) noexcept
    : m_mutex(other.m_mutex)
{
    other.m_mutex = nullptr;     // sursa nu mai deține mutex-ul
    std::cout << "      (proprietatea asupra mutex-ului a fost transferata)\n";
}

LockTransferabil::~LockTransferabil()
{
    if (m_mutex != nullptr) {
        unlock(m_mutex);
    }
}

// ================================== DEMO ====================================
void demoItem14()
{
    Mutex m("mutex");

    std::cout << "\n--- 14.0 RAII: mutex-ul se deblocheaza si la exceptie ---\n";
    try {
        LockNecopiabil l(&m);
        std::cout << "    lucrez in sectiunea critica... exceptie!\n";
        throw std::runtime_error("eroare");
    } catch (const std::exception&) {
        std::cout << "    exceptie prinsa, mutex blocat? "
                  << (m.esteBlocat() ? "DA (problema!)" : "nu") << "\n";
    }

    std::cout << "\n--- 14.1 GRESIT: copiere implicita ---\n";
    {
        LockNaiv l1(&m);
        LockNaiv l2(l1);         // copiază doar pointerul: 2 obiecte, 1 mutex
        std::cout << "  iesire din scope (ambele obiecte apeleaza unlock):\n";
    }

    std::cout << "\n--- 14.2 Varianta 1: copiere interzisa (= delete) ---\n";
    {
        LockNecopiabil l1(&m);
#ifdef DEMO_COPIERE_INTERZISA
        LockNecopiabil l2(l1);   // EROARE: use of deleted function
#else
        std::cout << "    LockNecopiabil l2(l1); NU compileaza (vezi -DDEMO_COPIERE_INTERZISA=ON)\n";
#endif
    }

    std::cout << "\n--- 14.3 Varianta 2: numarare de referinte (shared_ptr) ---\n";
    {
        LockPartajat l1(&m);
        std::cout << "    copii: " << l1.copii() << "\n";
        {
            LockPartajat l2(l1);
            std::cout << "    dupa copiere: " << l1.copii() << " copii\n";
        }
        std::cout << "    l2 distrus -> " << l1.copii() << " copie, mutex blocat? "
                  << (m.esteBlocat() ? "DA (corect, l1 inca il foloseste)" : "nu") << "\n";
        std::cout << "  iesire din scope (ultima copie deblocheaza):\n";
    }

    std::cout << "\n--- 14.4 Varianta 3: copiere profunda a resursei (Text) ---\n";
    {
        Text a("salut");
        Text b(a);
        a.afiseaza("a");
        b.afiseaza("b");
        std::cout << "    -> fiecare obiect are propria copie a resursei (adrese diferite)\n";
    }

    std::cout << "\n--- 14.5 Varianta 4: transfer de proprietate (move) ---\n";
    {
        LockTransferabil l1(&m);
        LockTransferabil l2(std::move(l1));
        std::cout << "    l1 detine mutex? " << (l1.detineMutex() ? "DA" : "nu")
                  << " | l2 detine mutex? " << (l2.detineMutex() ? "DA" : "nu") << "\n";
        std::cout << "  iesire din scope (doar l2 deblocheaza):\n";
    }
}