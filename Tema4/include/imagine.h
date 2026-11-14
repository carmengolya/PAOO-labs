#ifndef IMAGINE_H
#define IMAGINE_H

#include <string>

// =============================================================================
//  Imagine = resursa alocată pe heap (în carte: Bitmap).
//  Ține evidența imaginilor "în viață", ca să putem DETECTA și afișa
//  când cineva folosește o imagine deja ștearsă (în loc să crape programul).
// =============================================================================
class Imagine
{
public:
    explicit Imagine(const std::string& nume);
    Imagine(const Imagine& other);   // aruncă excepție dacă sursa e "uriasa"
    ~Imagine();

    Imagine& operator=(const Imagine&) = delete;   // nu avem nevoie de ea

    const std::string& nume() const { return m_nume; }

    // true dacă p arată spre o imagine care încă există
    static bool esteValida(const Imagine* p);

private:
    static std::string numeDin(const Imagine& other);

    std::string m_nume;
    bool        m_preaMare;    // true pentru "uriasa": copierea ei aruncă excepție
};

#endif // IMAGINE_H