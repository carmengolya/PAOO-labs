#ifndef NUME_H
#define NUME_H

#include <string>

// Clasă ajutătoare: un text care AFIȘEAZĂ fiecare funcție specială apelată.
// O folosim ca membru în celelalte clase, ca să vedem ce apelează compilatorul.
class Nume
{
public:
    Nume();                               // constructor implicit
    Nume(const char* text);               // constructor din text
    Nume(const Nume& other);              // copy constructor
    Nume& operator=(const Nume& other);   // copy assignment
    ~Nume();                              // destructor

    const std::string& text() const { return m_text; }

private:
    std::string m_text;
};

#endif // NUME_H
