#ifndef INVESTITIE_H
#define INVESTITIE_H

// =============================================================================
//  Item 13: Use objects to manage resources.
//  Resursa (în carte: Investment) e creată cu new de o funcție fabrică.
//  Cine o primește trebuie să o șteargă -> ușor de uitat sau de sărit.
//  Soluția: pune resursa IMEDIAT într-un obiect (RAII) care o șterge
//  în destructor: std::unique_ptr sau std::shared_ptr.
// =============================================================================

#include <string>

class Investitie
{
public:
    explicit Investitie(const std::string& nume);
    ~Investitie();

    Investitie(const Investitie&)            = delete;
    Investitie& operator=(const Investitie&) = delete;

    const std::string& nume() const { return m_nume; }

    // câte investiții există acum (dacă rămân > 0 la final => memory leak)
    static int existente() { return s_existente; }

private:
    std::string m_nume;
    static int  s_existente;
};

// Funcția fabrică din carte: returnează un obiect alocat pe heap,
// apelantul are responsabilitatea să facă delete.
Investitie* creeazaInvestitie(const std::string& nume);

void demoItem13();

#endif // INVESTITIE_H