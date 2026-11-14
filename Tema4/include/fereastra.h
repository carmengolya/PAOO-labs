#ifndef FEREASTRA_H
#define FEREASTRA_H

// =============================================================================
//  Item 11: Handle assignment to self in operator=.
//  Fereastra (în carte: Widget) deține o Imagine pe heap.
//  Patru variante de operator=, de la greșit la corect.
//
//  Copy constructorul nu e subiectul acestui item: la primele trei variante
//  e interzis (= delete, Item 6), ca să nu existe unul implicit (shallow).
// =============================================================================

#include <imagine.h>

#include <string>

// ---- 11.1 NAIV: șterge întâi, copiază apoi -> la a = a copiază din ce a șters
class FereastraNaiva
{
public:
    explicit FereastraNaiva(const std::string& imagine);
    ~FereastraNaiva();
    FereastraNaiva(const FereastraNaiva&) = delete;
    FereastraNaiva& operator=(const FereastraNaiva& rhs);
    void afiseaza(const char* nume) const;
private:
    Imagine* m_img;
};

// ---- 11.2 TEST DE IDENTITATE: if (this == &rhs) return *this;
//      rezolvă a = a, dar NU e sigur la excepții
class FereastraTest
{
public:
    explicit FereastraTest(const std::string& imagine);
    ~FereastraTest();
    FereastraTest(const FereastraTest&) = delete;
    FereastraTest& operator=(const FereastraTest& rhs);
    void afiseaza(const char* nume) const;
private:
    Imagine* m_img;
};

// ---- 11.3 ORDINE ATENTĂ: copiază întâi, șterge apoi
//      sigur și la a = a, și la excepții (fără test de identitate)
class FereastraOrdine
{
public:
    explicit FereastraOrdine(const std::string& imagine);
    ~FereastraOrdine();
    FereastraOrdine(const FereastraOrdine&) = delete;
    FereastraOrdine& operator=(const FereastraOrdine& rhs);
    void afiseaza(const char* nume) const;
private:
    Imagine* m_img;
};

// ---- 11.4 COPY-AND-SWAP: fă o copie, apoi schimbă conținutul cu ea
class FereastraSwap
{
public:
    explicit FereastraSwap(const std::string& imagine);
    FereastraSwap(const FereastraSwap& other);
    ~FereastraSwap();
    FereastraSwap& operator=(const FereastraSwap& rhs);
    void swap(FereastraSwap& other) noexcept;
    void afiseaza(const char* nume) const;
private:
    Imagine* m_img;
};

void demoItem11();

#endif // FEREASTRA_H