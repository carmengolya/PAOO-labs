#include <item6.h>

#include <iostream>
#include <type_traits>
#include <utility>

CheieVeche::CheieVeche(const std::string& cod)
    : m_cod(cod)
{
    std::cout << "    CheieVeche(\"" << m_cod << "\")\n";
}

CheieMostenita::CheieMostenita(const std::string& cod)
    : m_cod(cod)
{
    std::cout << "    CheieMostenita(\"" << m_cod << "\")\n";
}

CheieModerna::CheieModerna(const std::string& cod)
    : m_cod(cod)
{
    std::cout << "    CheieModerna(\"" << m_cod << "\")\n";
}

CheieModerna::CheieModerna(CheieModerna&& other) noexcept
    : m_cod(std::move(other.m_cod))
{
    other.m_cod = "<mutata>";
    std::cout << "    CheieModerna(move) -> preia \"" << m_cod << "\"\n";
}

CheieModerna::~CheieModerna()
{
    std::cout << "    ~CheieModerna(\"" << m_cod << "\")\n";
}

namespace {
const char* dn(bool b) { return b ? "DA" : "nu"; }

template <typename T>
void poateFiCopiata(const char* nume)
{
    std::cout << "    " << nume
              << " | copy ctor: " << dn(std::is_copy_constructible<T>::value)
              << " | operator=: " << dn(std::is_copy_assignable<T>::value)
              << " | move ctor: " << dn(std::is_move_constructible<T>::value)
              << "\n";
}
} // namespace

void demoItem6()
{
    std::cout << "\n--- 6.1 / 6.2 / 6.3 crearea cheilor ---\n";
    CheieVeche     k1("A-111");
    CheieMostenita k2("B-222");
    CheieModerna   k3("C-333");

    std::cout << "\n--- ce permite compilatorul ---\n";
    poateFiCopiata<CheieVeche>    ("CheieVeche     (private)   ");
    poateFiCopiata<CheieMostenita>("CheieMostenita (Uncopyable)");
    poateFiCopiata<CheieModerna>  ("CheieModerna   (= delete)  ");

#ifdef DEMO_COPIERE_INTERZISA
    CheieVeche     c1(k1);         // eroare: constructor PRIVAT
    CheieMostenita c2(k2);         // eroare: copy ctor-ul din Uncopyable e privat
    CheieModerna   c3(k3);         // eroare: use of deleted function
#endif

    std::cout << "\n--- mutarea cheii moderne (permisa) ---\n";
    CheieModerna k4(std::move(k3));
    std::cout << "    k3 = \"" << k3.cod() << "\", k4 = \"" << k4.cod() << "\"\n";
    std::cout << "\n  iesire din functie:\n";
}
