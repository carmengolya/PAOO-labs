#include <fereastra.h>

#include <iostream>
#include <new>
#include <utility>

namespace {

void afiseazaImagine(const char* nume, const Imagine* img)
{
    std::cout << "    " << nume << " -> ";
    if (Imagine::esteValida(img)) {
        std::cout << "imagine \"" << img->nume() << "\"\n";
    } else {
        std::cout << "POINTER AGATAT (imaginea a fost stearsa!)\n";
    }
}

void elibereaza(Imagine* img)
{
    if (img != nullptr && !Imagine::esteValida(img)) {
        std::cout << "      !!! destructorul ar face delete pe o imagine deja stearsa"
                     " (double free) -> sar peste\n";
        return;
    }
    delete img;
}

} // namespace

// =============================== 11.1 NAIV ==================================
FereastraNaiva::FereastraNaiva(const std::string& imagine) : m_img(new Imagine(imagine)) {}
FereastraNaiva::~FereastraNaiva() { elibereaza(m_img); }
void FereastraNaiva::afiseaza(const char* n) const { afiseazaImagine(n, m_img); }

FereastraNaiva& FereastraNaiva::operator=(const FereastraNaiva& rhs)
{
    delete m_img;                        // 1. ștergem imaginea NOASTRĂ
    m_img = new Imagine(*rhs.m_img);     // 2. copiem imaginea lui rhs
    return *this;                        //    dacă rhs e chiar *this, la pasul 2
}                                        //    copiem din imaginea ștearsă la pasul 1

// ========================== 11.2 TEST DE IDENTITATE =========================
FereastraTest::FereastraTest(const std::string& imagine) : m_img(new Imagine(imagine)) {}
FereastraTest::~FereastraTest() { elibereaza(m_img); }
void FereastraTest::afiseaza(const char* n) const { afiseazaImagine(n, m_img); }

FereastraTest& FereastraTest::operator=(const FereastraTest& rhs)
{
    if (this == &rhs) {                  // test de identitate
        std::cout << "      (auto-atribuire detectata -> nu fac nimic)\n";
        return *this;
    }
    delete m_img;                        // dacă new de mai jos aruncă excepție,
    m_img = new Imagine(*rhs.m_img);     // m_img rămâne spre imaginea ȘTEARSĂ
    return *this;
}

// ============================ 11.3 ORDINE ATENTĂ ============================
FereastraOrdine::FereastraOrdine(const std::string& imagine) : m_img(new Imagine(imagine)) {}
FereastraOrdine::~FereastraOrdine() { elibereaza(m_img); }
void FereastraOrdine::afiseaza(const char* n) const { afiseazaImagine(n, m_img); }

FereastraOrdine& FereastraOrdine::operator=(const FereastraOrdine& rhs)
{
    Imagine* original = m_img;           // 1. ținem minte imaginea veche
    m_img = new Imagine(*rhs.m_img);     // 2. facem copia (dacă aruncă, nimic nu s-a schimbat)
    delete original;                     // 3. abia acum ștergem imaginea veche
    return *this;
}

// ============================= 11.4 COPY-AND-SWAP ===========================
FereastraSwap::FereastraSwap(const std::string& imagine) : m_img(new Imagine(imagine)) {}
FereastraSwap::FereastraSwap(const FereastraSwap& other) : m_img(new Imagine(*other.m_img)) {}
FereastraSwap::~FereastraSwap() { elibereaza(m_img); }
void FereastraSwap::afiseaza(const char* n) const { afiseazaImagine(n, m_img); }

void FereastraSwap::swap(FereastraSwap& other) noexcept
{
    std::swap(m_img, other.m_img);       // schimbăm doar pointerii
}

FereastraSwap& FereastraSwap::operator=(const FereastraSwap& rhs)
{
    FereastraSwap temp(rhs);             // 1. copie a lui rhs (dacă aruncă, *this e neatins)
    swap(temp);                          // 2. *this primește copia, temp primește vechea imagine
    return *this;                        // 3. temp e distrus -> șterge vechea imagine
}

// ================================== DEMO ====================================
void demoItem11()
{
    std::cout << "\n--- 11.1 NAIV ---\n";
    {
        FereastraNaiva a("munte"), b("mare");
        std::cout << "  a = b;   (obiecte diferite -> merge)\n";
        a = b;
        a.afiseaza("a");

        std::cout << "  a = a;   (auto-atribuire)\n";
        a = a;
        a.afiseaza("a");
        std::cout << "    -> a si-a pierdut imaginea: a copiat din memoria pe care tocmai a sters-o\n";
        std::cout << "  iesire din scope:\n";
    }

    std::cout << "\n--- auto-atribuirea nu e mereu evidenta ---\n";
    {
        FereastraTest a("munte");

        FereastraTest* px = &a;              // în carte: a[i] = a[j] cu i == j,
        FereastraTest* py = &a;              // sau *px = *py cu px == py
        std::cout << "  *px = *py;   px si py arata spre acelasi obiect\n";
        *px = *py;

        FereastraTest& alias = a;
        std::cout << "  a = alias;   alias e o referinta la a\n";
        a = alias;
        std::cout << "  iesire din scope:\n";
    }

    std::cout << "\n--- 11.2 TEST DE IDENTITATE ---\n";
    {
        FereastraTest a("munte"), mare("uriasa");
        std::cout << "  a = a;\n";
        a = a;
        a.afiseaza("a");

        std::cout << "  a = mare;   (copierea imaginii arunca exceptie)\n";
        try {
            a = mare;
        } catch (const std::bad_alloc&) {
            std::cout << "    exceptie prinsa\n";
        }
        a.afiseaza("a");
        std::cout << "    -> a = a e rezolvat, dar dupa exceptie a ramane cu pointer agatat\n";
        std::cout << "  iesire din scope:\n";
    }

    std::cout << "\n--- 11.3 ORDINE ATENTA ---\n";
    {
        FereastraOrdine a("munte"), mare("uriasa");
        std::cout << "  a = a;   (fara test de identitate, dar corect)\n";
        a = a;
        a.afiseaza("a");

        std::cout << "  a = mare;\n";
        try {
            a = mare;
        } catch (const std::bad_alloc&) {
            std::cout << "    exceptie prinsa\n";
        }
        a.afiseaza("a");
        std::cout << "    -> a si-a pastrat imaginea veche: nimic nu s-a stricat\n";
        std::cout << "  iesire din scope:\n";
    }

    std::cout << "\n--- 11.4 COPY-AND-SWAP ---\n";
    {
        FereastraSwap a("munte"), b("mare"), mare("uriasa");
        std::cout << "  a = a;\n";
        a = a;
        a.afiseaza("a");

        std::cout << "  a = b;\n";
        a = b;
        a.afiseaza("a");

        std::cout << "  a = mare;\n";
        try {
            a = mare;
        } catch (const std::bad_alloc&) {
            std::cout << "    exceptie prinsa\n";
        }
        a.afiseaza("a");
        std::cout << "  iesire din scope:\n";
    }
}