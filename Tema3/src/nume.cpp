#include <nume.h>

#include <iostream>

Nume::Nume()
    : m_text("<gol>")
{
    std::cout << "      Nume()            implicit -> \"" << m_text << "\"\n";
}

Nume::Nume(const char* text)
    : m_text(text)
{
    std::cout << "      Nume(text)        -> \"" << m_text << "\"\n";
}

Nume::Nume(const Nume& other)
    : m_text(other.m_text)
{
    std::cout << "      Nume(copy)        -> \"" << m_text << "\"\n";
}

Nume& Nume::operator=(const Nume& other)
{
    std::cout << "      Nume::operator=   \"" << m_text << "\" = \"" << other.m_text << "\"\n";
    m_text = other.m_text;
    return *this;
}

Nume::~Nume()
{
    std::cout << "      ~Nume()           \"" << m_text << "\"\n";
}
