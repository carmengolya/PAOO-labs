#include <mutex.h>

#include <iostream>

Mutex::Mutex(const std::string& nume)
    : m_nume(nume)
    , m_blocat(false)
{
}

void lock(Mutex* pm)
{
    pm->m_blocat = true;
    std::cout << "      [lock]   " << pm->m_nume << " BLOCAT\n";
}

void unlock(Mutex* pm)
{
    if (!pm->m_blocat) {
        std::cout << "      [unlock] !!! EROARE: " << pm->m_nume
                  << " era deja deblocat (deblocare dubla)\n";
        return;
    }
    pm->m_blocat = false;
    std::cout << "      [unlock] " << pm->m_nume << " deblocat\n";
}