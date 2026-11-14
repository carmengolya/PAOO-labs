#include <punct.h>

#include <iostream>

// ============================== Punct (corect) ==============================
Punct::Punct(int x, int y)
    : m_x(x), m_y(y)
{
}

Punct::Punct(const Punct& other)
    : m_x(other.m_x), m_y(other.m_y)
{
    std::cout << "    [Punct] copy ctor (s-a facut o copie)\n";
}

Punct& Punct::operator=(const Punct& other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    return *this;            // returnăm OBIECTUL ÎNSUȘI, prin referință
}

Punct& Punct::operator+=(const Punct& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    return *this;
}

void Punct::afiseaza(const char* nume) const
{
    std::cout << "    " << nume << " = (" << m_x << ", " << m_y << ")\n";
}

// ========================= PunctValoare (greșit 1) ==========================
PunctValoare::PunctValoare(int x, int y)
    : m_x(x), m_y(y)
{
}

PunctValoare::PunctValoare(const PunctValoare& other)
    : m_x(other.m_x), m_y(other.m_y)
{
    std::cout << "    [PunctValoare] copy ctor (copie inutila!)\n";
}

PunctValoare PunctValoare::operator=(const PunctValoare& other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    return *this;            // se returnează o COPIE a lui *this
}

void PunctValoare::afiseaza(const char* nume) const
{
    std::cout << "    " << nume << " = (" << m_x << ", " << m_y << ")\n";
}

// =========================== PunctVoid (greșit 2) ===========================
PunctVoid::PunctVoid(int x, int y)
    : m_x(x), m_y(y)
{
}

void PunctVoid::operator=(const PunctVoid& other)
{
    m_x = other.m_x;
    m_y = other.m_y;         // nu returnează nimic
}

void PunctVoid::afiseaza(const char* nume) const
{
    std::cout << "    " << nume << " = (" << m_x << ", " << m_y << ")\n";
}

// ================================== DEMO ====================================
void demoItem10()
{
    std::cout << "\n--- 10.1 atribuire in lant: a = b = c ---\n";
    {
        Punct a(1, 1), b(2, 2), c(3, 3);
        a = b = c;           // se citește: a = (b = c)
        a.afiseaza("a");
        b.afiseaza("b");
        std::cout << "    -> ambele au primit valoarea lui c, fara nicio copie\n";
    }

    std::cout << "\n--- 10.2 operator+= in lant: (a += b) += c ---\n";
    {
        Punct a(1, 1), b(10, 10), c(100, 100);
        (a += b) += c;
        a.afiseaza("a");
        std::cout << "    -> a = 1 + 10 + 100 = 111\n";
    }

    std::cout << "\n--- 10.3 GRESIT: operator= returneaza prin valoare ---\n";
    {
        PunctValoare a(1, 1), b(2, 2), c(3, 3);
        std::cout << "  a = b = c:\n";
        a = b = c;           // merge, dar face copii inutile
        a.afiseaza("a");

        std::cout << "  (d = e) = f:   (vrem ca d sa devina f)\n";
        PunctValoare d(4, 4), e(5, 5), f(6, 6);
        (d = e) = f;         // al doilea = se aplică pe o COPIE temporară
        d.afiseaza("d");
        std::cout << "    -> d a ramas (5, 5), nu (6, 6): modificarea s-a pierdut!\n";

        std::cout << "  la fel, cu Punct (corect):\n";
        Punct g(4, 4), h(5, 5), i(6, 6);
        (g = h) = i;
        g.afiseaza("g");
        std::cout << "    -> g = (6, 6), cum ne asteptam\n";
    }

    std::cout << "\n--- 10.4 GRESIT: operator= returneaza void ---\n";
    {
        PunctVoid a(1, 1), b(2, 2), c(3, 3);
        a = b;               // atribuirea simplă merge
        a.afiseaza("a");
#ifdef DEMO_ITEM10_VOID
        a = b = c;           // EROARE: b = c returnează void
#else
        (void)c;
        std::cout << "    a = b = c NU compileaza (vezi -DDEMO_ITEM10_VOID=ON)\n";
#endif
    }
}