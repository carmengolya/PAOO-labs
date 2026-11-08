#include <item5.h>

#include <iostream>
#include <type_traits>

namespace {

const char* dn(bool b) { return b ? "DA" : "nu"; }

// Întreabă compilatorul ce funcții există pentru tipul T
template <typename T>
void tabel(const char* nume)
{
    std::cout << "    " << nume
              << " | implicit: "  << dn(std::is_default_constructible<T>::value)
              << " | copy ctor: " << dn(std::is_copy_constructible<T>::value)
              << " | operator=: " << dn(std::is_copy_assignable<T>::value)
              << " | move ctor: " << dn(std::is_move_constructible<T>::value)
              << "\n";
}

} // namespace

void demoItem5()
{
    std::cout << "\n--- 5.1 functii scrise de compilator pentru Carte ---\n";
    Nume ion("Ion");
    Nume rebreanu("Rebreanu");

    std::cout << "  Carte a;            -> constructor implicit generat:\n";
    Carte a;
    a.titlu = ion;
    a.autor = rebreanu;

    std::cout << "  Carte b(a);         -> copy constructor generat:\n";
    Carte b(a);

    std::cout << "  Carte c; c = a;     -> copy assignment generat:\n";
    Carte c;
    c = a;

    std::cout << "\n--- 5.2 / 5.3 ce a generat (sau nu) compilatorul ---\n";
    tabel<Carte>       ("Carte        ");
    tabel<CarteCuTitlu>("CarteCuTitlu ");
    tabel<Imprumut>    ("Imprumut     ");
    std::cout << "    -> CarteCuTitlu: are constructor propriu => fara constructor implicit\n";
    std::cout << "    -> Imprumut: are referinta + const => fara operator=\n";

    Imprumut i1(a, 1);
    Imprumut i2(i1);                 // copy constructor: MERGE (se inițializează referința)
    (void)i2;
#ifdef DEMO_ATRIBUIRE_REFERINTA
    Imprumut i3(b, 2);
    i3 = i1;                         // EROARE: operator= e "implicitly deleted"
#endif

    std::cout << "\n  la iesirea din functie -> destructori generati (~Carte apeleaza ~Nume):\n";
}
