#include <imagine.h>

#include <iostream>
#include <new>
#include <set>

namespace {
// adresele imaginilor care există acum
std::set<const Imagine*>& imaginiVii()
{
    static std::set<const Imagine*> vii;   // static local (Item 4)
    return vii;
}
} // namespace

bool Imagine::esteValida(const Imagine* p)
{
#ifdef DEMO_ASAN
    (void)p;
    return true;         // fără detector: lăsăm AddressSanitizer să prindă eroarea
#else
    return p != nullptr && imaginiVii().count(p) == 1;
#endif
}

Imagine::Imagine(const std::string& nume)
    : m_nume(nume)
    , m_preaMare(nume == "uriasa")
{
    imaginiVii().insert(this);
    std::cout << "      + Imagine(\"" << m_nume << "\")\n";
}

// Verificările se fac ÎNAINTE de a citi ceva din other
std::string Imagine::numeDin(const Imagine& other)
{
    if (!esteValida(&other)) {
        std::cout << "      !!! copiez dintr-o imagine DEJA STEARSA (use-after-free)\n";
        return "<GUNOI>";
    }
    if (other.m_preaMare) {
        std::cout << "      !!! nu e destula memorie pentru copie -> exceptie\n";
        throw std::bad_alloc();
    }
    return other.m_nume;
}

Imagine::Imagine(const Imagine& other)
    : m_nume(numeDin(other))
    , m_preaMare(false)
{
    imaginiVii().insert(this);
    std::cout << "      + Imagine(copie \"" << m_nume << "\")\n";
}

Imagine::~Imagine()
{
    std::cout << "      - ~Imagine(\"" << m_nume << "\")\n";
    imaginiVii().erase(this);
}