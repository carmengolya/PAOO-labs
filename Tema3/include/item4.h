#ifndef ITEM4_H
#define ITEM4_H

// =============================================================================
//  Item 4: Make sure that objects are initialized before they're used.
// =============================================================================

#include <nume.h>

// ---- 4.1 Tipurile de bază (int, double, pointeri) NU se inițializează singure
class ContGresit
{
public:
    ContGresit() {}              // constructor gol: m_sold și m_nrTranzactii rămân cu "gunoi"
    int sold()          const { return m_sold; }
    int nrTranzactii()  const { return m_nrTranzactii; }
private:
    int m_sold;
    int m_nrTranzactii;
};

class ContCorect
{
public:
    ContCorect() : m_sold(0), m_nrTranzactii(0) {}   // inițializate explicit
    int sold()          const { return m_sold; }
    int nrTranzactii()  const { return m_nrTranzactii; }
private:
    int m_sold;
    int m_nrTranzactii;
};

// ---- 4.2 Atribuire în corp vs. listă de inițializare
class PersoanaAtribuire
{
public:
    PersoanaAtribuire(const Nume& nume);     // m_nume = nume; în CORP
private:
    Nume m_nume;
};

class PersoanaInitializare
{
public:
    PersoanaInitializare(const Nume& nume);  // : m_nume(nume) în LISTĂ
private:
    Nume m_nume;
};

// ---- 4.3 Membrii const și referințele POT fi doar inițializați, nu atribuiți
class Angajat
{
public:
    Angajat(int id, const Nume& departament);
private:
    const int   m_id;            // const      -> obligatoriu în lista de inițializare
    const Nume& m_departament;   // referință  -> obligatoriu în lista de inițializare
};

// ---- 4.4 Ordinea de inițializare = ordinea DECLARĂRII, nu ordinea din listă
class Ordine
{
public:
    Ordine();                    // lista scrie: m_al_doilea, apoi m_primul
private:
    Nume m_primul;               // declarat PRIMUL  -> inițializat primul
    Nume m_al_doilea;            // declarat AL DOILEA
};

// ---- 4.5 Obiecte statice din fișiere diferite: folosim un static LOCAL
//          (funcția creează obiectul la primul apel -> sigur e inițializat)
class Jurnal
{
public:
    Jurnal();
    void scrie(const char* mesaj);
private:
    int m_nrMesaje;
};

Jurnal& jurnal();                // returnează Jurnal-ul unic (static local)

void demoItem4();

#endif // ITEM4_H
