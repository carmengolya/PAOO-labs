#include <item4.h>

#include <cstring>
#include <iostream>
#include <new>

// ---------------------------------------------------------------------------
// 4.2 Atribuire în corp: Nume e construit ÎNTÂI implicit, APOI suprascris
// ---------------------------------------------------------------------------
PersoanaAtribuire::PersoanaAtribuire(const Nume& nume)
{                                   // aici m_nume a fost deja creat cu Nume()
    m_nume = nume;                  // ...și abia acum primește valoarea (operator=)
}

// Listă de inițializare: Nume e construit DIRECT cu valoarea corectă (o singură operație)
PersoanaInitializare::PersoanaInitializare(const Nume& nume)
    : m_nume(nume)
{
}

// ---------------------------------------------------------------------------
// 4.3 const și referință: singurul loc posibil este lista de inițializare
// ---------------------------------------------------------------------------
Angajat::Angajat(int id, const Nume& departament)
    : m_id(id)
    , m_departament(departament)
{
    // m_id = id;                   // NU compilează: assignment of read-only member
    std::cout << "    Angajat #" << m_id << " din " << m_departament.text() << "\n";
}

// ---------------------------------------------------------------------------
// 4.4 Lista e scrisă invers, dar ordinea reală e cea din declarația clasei
//     (compilatorul avertizează cu -Wall: "will be initialized after")
// ---------------------------------------------------------------------------
Ordine::Ordine()
    : m_al_doilea("al doilea")      // scris primul în listă...
    , m_primul("primul")            // ...dar m_primul e construit primul
{
}

// ---------------------------------------------------------------------------
// 4.5 Static local: obiectul e creat la PRIMUL apel al funcției
// ---------------------------------------------------------------------------
Jurnal::Jurnal()
    : m_nrMesaje(0)
{
    std::cout << "  [Jurnal] creat la prima folosire\n";
}

void Jurnal::scrie(const char* mesaj)
{
    ++m_nrMesaje;
    std::cout << "  [Jurnal #" << m_nrMesaje << "] " << mesaj << "\n";
}

Jurnal& jurnal()
{
    static Jurnal instanta;          // construit o singură dată, la primul apel
    return instanta;
}

// Obiect GLOBAL, construit ÎNAINTEA lui main(). Constructorul lui folosește
// jurnalul. Dacă jurnalul ar fi fost tot un obiect global, definit în alt
// fișier .cpp, ordinea dintre ele ar fi nedefinită -> l-am putea folosi
// înainte să fie construit. Cu jurnal() problema dispare.
namespace {
struct PornireAplicatie
{
    PornireAplicatie() { jurnal().scrie("obiect global construit inainte de main()"); }
};
PornireAplicatie g_pornire;
} // namespace

// ---------------------------------------------------------------------------
void demoItem4()
{
    std::cout << "\n--- 4.1 int-uri neinitializate ---\n";
    {
        // Umplem o zonă de memorie cu 0xAB, ca să vedem clar "gunoiul"
        // pe care îl preia un obiect neinițializat (în practică poate fi orice).
        alignas(ContGresit) unsigned char memorie[sizeof(ContGresit)];
        std::memset(memorie, 0xAB, sizeof(memorie));

        ContGresit* gresit = new (memorie) ContGresit();
        std::cout << "    ContGresit: sold=" << gresit->sold()
                  << ", nrTranzactii=" << gresit->nrTranzactii() << "   <- GUNOI\n";
        gresit->~ContGresit();

        std::memset(memorie, 0xAB, sizeof(memorie));
        ContCorect* corect = new (memorie) ContCorect();
        std::cout << "    ContCorect: sold=" << corect->sold()
                  << ", nrTranzactii=" << corect->nrTranzactii() << "   <- corect\n";
        corect->~ContCorect();
    }

    std::cout << "\n--- 4.2 atribuire in corp vs. lista de initializare ---\n";
    Nume ion("Ion");
    std::cout << "  PersoanaAtribuire(ion):      (2 operatii: Nume() + operator=)\n";
    { PersoanaAtribuire p(ion); }
    std::cout << "  PersoanaInitializare(ion):   (1 operatie: Nume(copy))\n";
    { PersoanaInitializare p(ion); }

    std::cout << "\n--- 4.3 membri const si referinta ---\n";
    Nume it("IT");
    { Angajat a(7, it); }

    std::cout << "\n--- 4.4 ordinea de initializare ---\n";
    std::cout << "  lista: m_al_doilea, m_primul | declaratie: m_primul, m_al_doilea\n";
    { Ordine o; }

    std::cout << "\n--- 4.5 static local (jurnal deja creat inainte de main) ---\n";
    jurnal().scrie("folosit din demoItem4()");
}
