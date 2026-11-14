#ifndef PUNCT_H
#define PUNCT_H

// =============================================================================
//  Item 10: Have assignment operators return a reference to *this.
// =============================================================================

// ---- Varianta CORECTĂ: operatorii de atribuire returnează Punct&
class Punct
{
public:
    Punct(int x = 0, int y = 0);
    Punct(const Punct& other);

    Punct& operator=(const Punct& other);    // returnează referință la *this
    Punct& operator+=(const Punct& other);   // la fel și +=, -=, *= ...

    void afiseaza(const char* nume) const;

private:
    int m_x;
    int m_y;
};

// ---- Varianta GREȘITĂ 1: returnează prin VALOARE (o copie)
//      compilează, dar (a = b) = c modifică o copie temporară, nu pe a
class PunctValoare
{
public:
    PunctValoare(int x = 0, int y = 0);
    PunctValoare(const PunctValoare& other);

    PunctValoare operator=(const PunctValoare& other);   // fără &

    void afiseaza(const char* nume) const;

private:
    int m_x;
    int m_y;
};

// ---- Varianta GREȘITĂ 2: returnează void
//      a = b = c nici nu compilează
class PunctVoid
{
public:
    PunctVoid(int x = 0, int y = 0);

    void operator=(const PunctVoid& other);

    void afiseaza(const char* nume) const;

private:
    int m_x;
    int m_y;
};

void demoItem10();

#endif // PUNCT_H