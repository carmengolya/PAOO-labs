#ifndef STUDENT_GRESIT_H
#define STUDENT_GRESIT_H

#include <cstddef>

// INCORRECT class, used only as a counterexample:
//  - Has NO custom copy constructor -> the compiler generates one that
//    copies only the pointer (shallow copy): two objects, the SAME vector.
//  - By default, it has NO destructor to release memory -> memory leak.
//  - With -DDEMO_DOUBLE_FREE=ON it gets a destructor -> both objects
//    release the same address -> double free -> the program crashes.
class StudentGresit
{
public:
    explicit StudentGresit(std::size_t nrNote);

#ifdef DEMO_DOUBLE_FREE
    ~StudentGresit();
#endif

    void setNota(std::size_t index, int nota);
    int  nota(std::size_t index) const;
    const int* adresaNote() const { return m_note; }

private:
    std::size_t m_nrNote;
    int*        m_note;
};

#endif // STUDENT_GRESIT_H
