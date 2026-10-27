#include <student/student_gresit.h>
#include <student/heap_contor.h>

#include <iostream>

StudentGresit::StudentGresit(std::size_t nrNote)
    : m_nrNote(nrNote)
    , m_note(new int[nrNote]())
{
    heap::alocat();
    std::cout << "  [ctor]  StudentGresit -> new int[" << m_nrNote << "] la " << m_note << "\n";
}

#ifdef DEMO_DOUBLE_FREE
StudentGresit::~StudentGresit()
{
    std::cout << "  [dtor]  StudentGresit -> delete[] " << m_note << "\n";
    delete[] m_note;
    heap::eliberat();
}
#endif

void StudentGresit::setNota(std::size_t index, int nota)
{
    if (index < m_nrNote) {
        m_note[index] = nota;
    }
}

int StudentGresit::nota(std::size_t index) const
{
    return index < m_nrNote ? m_note[index] : 0;
}
