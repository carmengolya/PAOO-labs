#include <text.h>

#include <cstring>
#include <iostream>

namespace {
char* copiaza(const char* sursa)
{
    char* nou = new char[std::strlen(sursa) + 1];
    std::strcpy(nou, sursa);
    return nou;
}
} // namespace

Text::Text(const char* text)
    : m_date(copiaza(text))
{
}

Text::Text(const Text& other)
    : m_date(copiaza(other.m_date))       // memorie NOUĂ, nu același pointer
{
    std::cout << "      Text(copy): resursa copiata la o adresa noua\n";
}

Text& Text::operator=(const Text& other)
{
    char* nou = copiaza(other.m_date);    // întâi copiem...
    delete[] m_date;                      // ...apoi ștergem resursa veche
    m_date = nou;
    return *this;
}

Text::~Text()
{
    delete[] m_date;
}

void Text::afiseaza(const char* nume) const
{
    std::cout << "    " << nume << " = \"" << m_date << "\" (la "
              << static_cast<const void*>(m_date) << ")\n";
}