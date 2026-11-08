#ifndef ITEM6_H
#define ITEM6_H

// =============================================================================
//  Item 6: Explicitly disallow the use of compiler-generated functions
//          you do not want.
//  Exemplu: o cheie de acces unică NU trebuie să poată fi copiată.
//  Trei variante: cea din carte (C++98, două forme) și cea modernă (C++11).
// =============================================================================

#include <string>

// ---- 6.1 Varianta din carte: declarate PRIVATE și NEDEFINITE
//          - din afara clasei: eroare de compilare (sunt private)
//          - din interiorul clasei / friend: eroare de LINK (nu au corp)
class CheieVeche
{
public:
    explicit CheieVeche(const std::string& cod);
    const std::string& cod() const { return m_cod; }
private:
    CheieVeche(const CheieVeche&);              // doar declarat, fără definiție
    CheieVeche& operator=(const CheieVeche&);   // doar declarat, fără definiție
    std::string m_cod;
};

// ---- 6.2 Varianta din carte: clasa de bază Uncopyable
//          Orice clasă care moștenește din ea devine necopiabilă,
//          iar eroarea apare la compilare (nu la link).
class Uncopyable
{
protected:
    Uncopyable()  {}                            // se poate construi/distruge
    ~Uncopyable() {}                            // ...din clasele derivate
private:
    Uncopyable(const Uncopyable&);              // dar NU se poate copia
    Uncopyable& operator=(const Uncopyable&);
};

class CheieMostenita : private Uncopyable
{
public:
    explicit CheieMostenita(const std::string& cod);
    const std::string& cod() const { return m_cod; }
private:
    std::string m_cod;
};

// ---- 6.3 Varianta modernă (C++11): = delete
//          Eroare clară la compilare: "use of deleted function".
//          Bonus: copierea e interzisă, dar MUTAREA e permisă
//          (cheia își poate schimba proprietarul, dar nu poate fi duplicată).
class CheieModerna
{
public:
    explicit CheieModerna(const std::string& cod);
    ~CheieModerna();

    CheieModerna(const CheieModerna&)            = delete;   // fără copiere
    CheieModerna& operator=(const CheieModerna&) = delete;

    CheieModerna(CheieModerna&& other) noexcept;              // mutarea e permisă
    CheieModerna& operator=(CheieModerna&&)      = delete;

    const std::string& cod() const { return m_cod; }
private:
    std::string m_cod;
};

void demoItem6();

#endif // ITEM6_H
