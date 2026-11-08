#ifndef ITEM5_H
#define ITEM5_H

// =============================================================================
//  Item 5: Know what functions C++ silently writes and calls.
//  Pentru o clasă fără funcții speciale, compilatorul scrie singur:
//    constructor implicit, copy constructor, copy assignment, destructor
//    (+ din C++11: move constructor, move assignment)
// =============================================================================

#include <nume.h>

// ---- 5.1 Clasă GOALĂ de funcții speciale: totul e generat de compilator.
//          Funcțiile generate apelează funcțiile membrilor (Nume).
class Carte
{
public:
    // nimic declarat: Carte(), Carte(const Carte&), operator=, ~Carte()
    // sunt scrise de compilator
    Nume titlu;
    Nume autor;
};

// ---- 5.2 Dacă declari ORICE constructor, compilatorul NU mai scrie Carte()
class CarteCuTitlu
{
public:
    explicit CarteCuTitlu(const Nume& titlu) : m_titlu(titlu) {}
private:
    Nume m_titlu;
};

// ---- 5.3 Cu membru referință sau const, compilatorul REFUZĂ operator=
//          (nu poate re-lega o referință și nu poate modifica un const)
class Imprumut
{
public:
    Imprumut(Carte& carte, int id) : m_carte(carte), m_id(id) {}
private:
    Carte&    m_carte;
    const int m_id;
};

void demoItem5();

#endif // ITEM5_H
