#ifndef CLIENT_H
#define CLIENT_H

// =============================================================================
//  Item 12: Copy all parts of an object.
//  Funcțiile de copiere (copy constructor și operator=) trebuie să copieze:
//    1. TOȚI membrii clasei (inclusiv cei adăugați mai târziu)
//    2. partea din CLASA DE BAZĂ, la clasele derivate
//  Compilatorul NU te avertizează dacă uiți ceva.
// =============================================================================

#include <string>

// ---- 12.1 GREȘIT: am adăugat m_ultimaTranzactie, dar am uitat
//      să actualizăm funcțiile de copiere
class ClientIncomplet
{
public:
    explicit ClientIncomplet(const std::string& nume);
    ClientIncomplet(const ClientIncomplet& rhs);
    ClientIncomplet& operator=(const ClientIncomplet& rhs);

    void seteazaTranzactie(const std::string& data) { m_ultimaTranzactie = data; }
    void afiseaza(const char* eticheta) const;

private:
    std::string m_nume;
    std::string m_ultimaTranzactie;    // membru NOU, uitat la copiere
};

// ---- 12.2 CORECT: clasa de bază copiază toți membrii
class Client
{
public:
    Client();                                    // constructor implicit
    explicit Client(const std::string& nume);
    Client(const Client& rhs);
    Client& operator=(const Client& rhs);
    virtual ~Client() = default;

    void seteazaTranzactie(const std::string& data) { m_ultimaTranzactie = data; }
    void afiseaza(const char* eticheta) const;

private:
    // cod comun pentru ambele funcții de copiere (în carte: logCall)
    // -> NU apelăm o funcție de copiere din cealaltă
    void jurnal(const char* operatie) const;

    std::string m_nume;
    std::string m_ultimaTranzactie;
};

// ---- 12.3 GREȘIT: clasa derivată copiază doar membrii ei,
//      uită partea de Client
class ClientPremiumGresit : public Client
{
public:
    ClientPremiumGresit(const std::string& nume, int prioritate);
    ClientPremiumGresit(const ClientPremiumGresit& rhs);
    ClientPremiumGresit& operator=(const ClientPremiumGresit& rhs);

    void afiseaza(const char* eticheta) const;

private:
    int m_prioritate;
};

// ---- 12.4 CORECT: clasa derivată apelează funcțiile de copiere ale bazei
class ClientPremium : public Client
{
public:
    ClientPremium(const std::string& nume, int prioritate);
    ClientPremium(const ClientPremium& rhs);
    ClientPremium& operator=(const ClientPremium& rhs);

    void afiseaza(const char* eticheta) const;

private:
    int m_prioritate;
};

void demoItem12();

#endif // CLIENT_H