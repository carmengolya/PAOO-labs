#include <student/student.h>
#include <student/heap_contor.h>

#include <iostream>

// ---------------------------------------------------------------------------
// 3. Constructor with an INITIALIZATION LIST
//    m_id is const: it cannot be assigned in the constructor body,
//    only initialized here. (see the DEMO_EROARE_INIT variant below)
// ---------------------------------------------------------------------------
#ifndef DEMO_EROARE_INIT
Student::Student(int id, const std::string& nume, std::size_t capacitate)
    : m_id(id)
    , m_nume(nume)
    , m_capacitate(capacitate)
    , m_nrNote(0)
    , m_note(new int[capacitate])
{
    heap::alocat();
    std::cout << "  [ctor]  Student #" << m_id << " " << m_nume
              << " -> new int[" << m_capacitate << "] la " << m_note << "\n";
}
#else
// WRONG variant: assignment in the body instead of initialization.
// Does not compile: "assignment of read-only member 'Student::m_id'"
// (and because m_id is not initialized: "uninitialized const member").
Student::Student(int id, const std::string& nume, std::size_t capacitate)
{
    m_id = id;
    m_nume = nume;
    m_capacitate = capacitate;
    m_nrNote = 0;
    m_note = new int[capacitate];
}
#endif

// ---------------------------------------------------------------------------
// 4. DESTRUCTOR: releases what the constructor allocated.
//    Without it, each Student would leave a memory block behind (leak).
// ---------------------------------------------------------------------------
Student::~Student()
{
    std::cout << "  [dtor]  Student #" << m_id << " " << m_nume;
    if (m_note != nullptr) {
        std::cout << " -> delete[] " << m_note << "\n";
        delete[] m_note;
        heap::eliberat();
    } else {
        std::cout << " -> nimic de eliberat (a fost mutat)\n";
    }
}

// ---------------------------------------------------------------------------
// 5. COPY CONSTRUCTOR: DEEP copy.
//    Allocate a NEW vector and copy the values -> each object has its own memory.
// ---------------------------------------------------------------------------
Student::Student(const Student& other)
    : m_id(other.m_id)
    , m_nume(other.m_nume + " (copie)")
    , m_capacitate(other.m_capacitate)
    , m_nrNote(other.m_nrNote)
    , m_note(new int[other.m_capacitate])
{
    for (std::size_t i = 0; i < m_nrNote; ++i) {
        m_note[i] = other.m_note[i];
    }
    heap::alocat();
    std::cout << "  [copy]  Student #" << m_id << " -> new int[" << m_capacitate
              << "] la " << m_note << " (originalul e la " << other.m_note << ")\n";
}

// ---------------------------------------------------------------------------
// 6. MOVE CONSTRUCTOR: takes the pointer without allocation or copying.
//    The source remains "empty" (nullptr), so its destructor does not release
//    the memory that now belongs to us.
// ---------------------------------------------------------------------------
Student::Student(Student&& other) noexcept
    : m_id(other.m_id)
    , m_nume(std::move(other.m_nume))
    , m_capacitate(other.m_capacitate)
    , m_nrNote(other.m_nrNote)
    , m_note(other.m_note)              // steal the pointer
{
    other.m_note       = nullptr;       // the source no longer owns the memory
    other.m_nrNote     = 0;
    other.m_capacitate = 0;
    std::cout << "  [move]  Student #" << m_id << " " << m_nume
              << " -> preia " << m_note << ", fara new\n";
}

// ---------------------------------------------------------------------------
// 2. Encapsulation: input validation
// ---------------------------------------------------------------------------
bool Student::adaugaNota(int nota)
{
    if (nota < 1 || nota > 10) {
        std::cout << "  ! nota " << nota << " respinsa (trebuie 1..10)\n";
        return false;
    }
    if (m_nrNote >= m_capacitate) {
        std::cout << "  ! nu mai e loc pentru nota " << nota << "\n";
        return false;
    }
    m_note[m_nrNote++] = nota;
    return true;
}

void Student::modificaNota(std::size_t index, int notaNoua)
{
    if (index < m_nrNote && notaNoua >= 1 && notaNoua <= 10) {
        m_note[index] = notaNoua;
    }
}

double Student::medie() const
{
    if (m_nrNote == 0) {
        return 0.0;
    }
    int suma = 0;
    for (std::size_t i = 0; i < m_nrNote; ++i) {
        suma += m_note[i];
    }
    return static_cast<double>(suma) / m_nrNote;
}

void Student::afiseaza(const char* eticheta) const
{
    std::cout << "  " << eticheta << ": #" << m_id << " " << m_nume << " note=[";
    for (std::size_t i = 0; i < m_nrNote; ++i) {
        std::cout << m_note[i] << (i + 1 < m_nrNote ? " " : "");
    }
    std::cout << "] medie=" << medie() << " (vector la " << m_note << ")\n";
}
