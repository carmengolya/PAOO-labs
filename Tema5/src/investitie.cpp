#include <investitie.h>

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

int Investitie::s_existente = 0;

Investitie::Investitie(const std::string& nume)
    : m_nume(nume)
{
    ++s_existente;
    std::cout << "      + Investitie(\"" << m_nume << "\")\n";
}

Investitie::~Investitie()
{
    --s_existente;
    std::cout << "      - ~Investitie(\"" << m_nume << "\")\n";
}

Investitie* creeazaInvestitie(const std::string& nume)
{
    return new Investitie(nume);
}

namespace {

void contor()
{
    std::cout << "    >> investitii neeliberate: " << Investitie::existente() << "\n";
}

// ------------------------- 13.1 GREȘIT: delete manual -----------------------
void analizaManuala(bool iesireDevreme)
{
    Investitie* p = creeazaInvestitie("actiuni");
    if (iesireDevreme) {
        std::cout << "    return inainte de delete\n";
        return;                          // delete p nu se mai execută -> LEAK
    }
    delete p;
}

void analizaManualaCuExceptie()
{
    Investitie* p = creeazaInvestitie("obligatiuni");
    std::cout << "    exceptie inainte de delete\n";
    throw std::runtime_error("eroare in analiza");
    delete p;                            // nu se ajunge niciodată aici -> LEAK
}

// ------------------------- 13.2 CORECT: unique_ptr --------------------------
void analizaRAII(bool iesireDevreme)
{
    std::unique_ptr<Investitie> p(creeazaInvestitie("actiuni"));   // resursa intră IMEDIAT în obiect
    if (iesireDevreme) {
        std::cout << "    return devreme\n";
        return;                          // destructorul lui p face delete
    }
}                                        // ...sau aici

void analizaRAIICuExceptie()
{
    std::unique_ptr<Investitie> p(creeazaInvestitie("obligatiuni"));
    std::cout << "    exceptie\n";
    throw std::runtime_error("eroare in analiza");   // p e distrus la "stack unwinding"
}

} // namespace

void demoItem13()
{
    std::cout << "\n--- 13.1 GRESIT: pointer simplu + delete manual ---\n";
    analizaManuala(false);
    contor();
    analizaManuala(true);
    contor();
    try {
        analizaManualaCuExceptie();
    } catch (const std::exception& e) {
        std::cout << "    prins: " << e.what() << "\n";
    }
    contor();
    std::cout << "    -> 2 investitii pierdute: nimeni nu le mai poate sterge\n";

    std::cout << "\n--- 13.2 CORECT: resursa gestionata de un obiect (unique_ptr) ---\n";
    analizaRAII(false);
    analizaRAII(true);
    try {
        analizaRAIICuExceptie();
    } catch (const std::exception& e) {
        std::cout << "    prins: " << e.what() << "\n";
    }
    contor();
    std::cout << "    -> tot 2: cu RAII nu s-a mai pierdut nimic\n";

    std::cout << "\n--- 13.3 unique_ptr: un singur proprietar ---\n";
    {
        std::unique_ptr<Investitie> p1(creeazaInvestitie("aur"));
#ifdef DEMO_COPIERE_INTERZISA
        std::unique_ptr<Investitie> copie(p1);        // EROARE: copierea e interzisă
#endif
        std::unique_ptr<Investitie> p2(std::move(p1)); // transfer de proprietate
        std::cout << "    dupa move: p1 = " << (p1 ? "are obiect" : "nullptr")
                  << ", p2 = \"" << p2->nume() << "\"\n";
        std::cout << "  iesire din scope (o singura stergere):\n";
    }

    std::cout << "\n--- 13.4 shared_ptr: mai multi proprietari, numarare de referinte ---\n";
    {
        std::shared_ptr<Investitie> p1(creeazaInvestitie("imobiliare"));
        std::cout << "    proprietari: " << p1.use_count() << "\n";
        {
            std::shared_ptr<Investitie> p2 = p1;      // copiere permisă
            std::cout << "    dupa copiere: " << p1.use_count() << " proprietari\n";
        }
        std::cout << "    p2 distrus: " << p1.use_count() << " proprietar (obiectul inca exista)\n";
        std::cout << "  iesire din scope (ultimul proprietar sterge):\n";
    }

    std::cout << "\n--- 13.5 tablouri ---\n";
    {
        // GREȘIT: std::shared_ptr<int> p(new int[10]);  -> face delete, nu delete[]
        std::unique_ptr<int[]> numere(new int[5]{1, 2, 3, 4, 5});   // face delete[]
        std::vector<int> mai_bine{1, 2, 3, 4, 5};                    // recomandat
        std::cout << "    unique_ptr<int[]>: " << numere[4]
                  << ", vector: " << mai_bine.size() << " elemente\n";
    }

    contor();
    std::cout << "    (cele 2 ramase sunt leak-urile intentionate din 13.1)\n";
}