#ifndef MUTEX_H
#define MUTEX_H

// =============================================================================
//  Mutex simulat (în carte: o resursă de tip C, cu lock/unlock).
//  unlock() pe un mutex deja deblocat afișează o EROARE în loc să crape.
// =============================================================================

#include <string>

class Mutex
{
public:
    explicit Mutex(const std::string& nume);

    Mutex(const Mutex&)            = delete;
    Mutex& operator=(const Mutex&) = delete;

    bool               esteBlocat() const { return m_blocat; }
    const std::string& nume()       const { return m_nume; }

private:
    friend void lock(Mutex* pm);
    friend void unlock(Mutex* pm);

    std::string m_nume;
    bool        m_blocat;
};

void lock(Mutex* pm);
void unlock(Mutex* pm);

#endif // MUTEX_H