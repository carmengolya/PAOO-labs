#include <client.h>

#include <iostream>

// ============================ 12.1 ClientIncomplet ==========================
ClientIncomplet::ClientIncomplet(const std::string& nume)
    : m_nume(nume)
    , m_ultimaTranzactie("-")
{
}

ClientIncomplet::ClientIncomplet(const ClientIncomplet& rhs)
    : m_nume(rhs.m_nume)                 // m_ultimaTranzactie UITAT -> rămâne ""
{
}

ClientIncomplet& ClientIncomplet::operator=(const ClientIncomplet& rhs)
{
    m_nume = rhs.m_nume;                 // m_ultimaTranzactie UITAT -> rămâne vechea valoare
    return *this;
}

void ClientIncomplet::afiseaza(const char* eticheta) const
{
    std::cout << "    " << eticheta << ": nume=\"" << m_nume
              << "\", ultima tranzactie=\"" << m_ultimaTranzactie << "\"\n";
}

// ================================ 12.2 Client ===============================
Client::Client()
    : m_nume("<fara nume>")
    , m_ultimaTranzactie("-")
{
    std::cout << "      Client() implicit   <- partea de baza NU a fost copiata\n";
}

Client::Client(const std::string& nume)
    : m_nume(nume)
    , m_ultimaTranzactie("-")
{
}

Client::Client(const Client& rhs)
    : m_nume(rhs.m_nume)
    , m_ultimaTranzactie(rhs.m_ultimaTranzactie)   // TOȚI membrii
{
    jurnal("Client copy constructor");
}

Client& Client::operator=(const Client& rhs)
{
    jurnal("Client::operator=");
    m_nume = rhs.m_nume;
    m_ultimaTranzactie = rhs.m_ultimaTranzactie;   // TOȚI membrii
    return *this;
}

void Client::jurnal(const char* operatie) const
{
    std::cout << "      " << operatie << "\n";
}

void Client::afiseaza(const char* eticheta) const
{
    std::cout << "    " << eticheta << ": nume=\"" << m_nume
              << "\", ultima tranzactie=\"" << m_ultimaTranzactie << "\"";
}

// ========================= 12.3 ClientPremiumGresit =========================
ClientPremiumGresit::ClientPremiumGresit(const std::string& nume, int prioritate)
    : Client(nume)
    , m_prioritate(prioritate)
{
}

ClientPremiumGresit::ClientPremiumGresit(const ClientPremiumGresit& rhs)
    : m_prioritate(rhs.m_prioritate)     // lipsește Client(rhs)
{                                        // -> se apelează Client() implicit
}

ClientPremiumGresit& ClientPremiumGresit::operator=(const ClientPremiumGresit& rhs)
{
    m_prioritate = rhs.m_prioritate;     // lipsește Client::operator=(rhs)
    return *this;                        // -> partea de Client rămâne neschimbată
}

void ClientPremiumGresit::afiseaza(const char* eticheta) const
{
    Client::afiseaza(eticheta);
    std::cout << ", prioritate=" << m_prioritate << "\n";
}

// ============================ 12.4 ClientPremium ============================
ClientPremium::ClientPremium(const std::string& nume, int prioritate)
    : Client(nume)
    , m_prioritate(prioritate)
{
}

ClientPremium::ClientPremium(const ClientPremium& rhs)
    : Client(rhs)                        // copiem partea de bază
    , m_prioritate(rhs.m_prioritate)     // și membrii proprii
{
}

ClientPremium& ClientPremium::operator=(const ClientPremium& rhs)
{
    Client::operator=(rhs);              // atribuim partea de bază
    m_prioritate = rhs.m_prioritate;     // și membrii proprii
    return *this;
}

void ClientPremium::afiseaza(const char* eticheta) const
{
    Client::afiseaza(eticheta);
    std::cout << ", prioritate=" << m_prioritate << "\n";
}

// ================================== DEMO ====================================
void demoItem12()
{
    std::cout << "\n--- 12.1 GRESIT: membru nou uitat la copiere ---\n";
    {
        ClientIncomplet ana("Ana");
        ana.seteazaTranzactie("14.11.2026");
        ana.afiseaza("ana   ");

        ClientIncomplet copie(ana);
        copie.afiseaza("copie ");

        ClientIncomplet bogdan("Bogdan");
        bogdan.seteazaTranzactie("01.01.2020");
        bogdan = ana;
        bogdan.afiseaza("bogdan");
        std::cout << "    -> numele s-a copiat, data NU: copia are \"\", bogdan are data lui veche\n";
    }

    std::cout << "\n--- 12.2 CORECT: toti membrii copiati ---\n";
    {
        Client ana("Ana");
        ana.seteazaTranzactie("14.11.2026");

        Client copie(ana);
        ana.afiseaza("ana  ");   std::cout << "\n";
        copie.afiseaza("copie"); std::cout << "\n";
    }

    std::cout << "\n--- 12.3 GRESIT: clasa derivata uita partea de baza ---\n";
    {
        ClientPremiumGresit vip("Cristina", 1);
        vip.seteazaTranzactie("14.11.2026");
        vip.afiseaza("vip  ");

        std::cout << "  copy constructor:\n";
        ClientPremiumGresit copie(vip);
        copie.afiseaza("copie");

        std::cout << "  operator=:\n";
        ClientPremiumGresit altul("Dan", 5);
        altul = vip;
        altul.afiseaza("altul");
        std::cout << "    -> s-a copiat doar prioritatea; numele si data sunt gresite\n";
    }

    std::cout << "\n--- 12.4 CORECT: clasa derivata apeleaza functiile bazei ---\n";
    {
        ClientPremium vip("Cristina", 1);
        vip.seteazaTranzactie("14.11.2026");
        vip.afiseaza("vip  ");

        std::cout << "  copy constructor:\n";
        ClientPremium copie(vip);
        copie.afiseaza("copie");

        std::cout << "  operator=:\n";
        ClientPremium altul("Dan", 5);
        altul = vip;
        altul.afiseaza("altul");
        std::cout << "    -> toate partile copiate: nume, data si prioritate\n";
    }
}