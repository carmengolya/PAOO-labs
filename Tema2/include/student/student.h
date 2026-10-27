#ifndef STUDENT_H
#define STUDENT_H

#include <cstddef>
#include <string>

// CORRECT class: has a destructor, copy constructor, and move constructor.
class Student
{
public:
    // 3. constructor with an initialization list
    Student(int id, const std::string& nume, std::size_t capacitate);

    // 4. destructor - releases the heap memory
    ~Student();

    // 5. copy constructor - DEEP copy
    Student(const Student& other);

    // 6. move constructor - "steals" the memory without a new allocation
    Student(Student&& other) noexcept;

    // Assignment is not required for this topic -> explicitly forbid it so
    // that an implicit (shallow) version cannot be used by mistake.
    Student& operator=(const Student&) = delete;
    Student& operator=(Student&&)      = delete;

    // 2. encapsulation: the only way to modify grades, with validation
    bool adaugaNota(int nota);
    void modificaNota(std::size_t index, int notaNoua);

    // getters (read-only)
    int                id()     const { return m_id; }
    const std::string& nume()   const { return m_nume; }
    std::size_t        nrNote() const { return m_nrNote; }
    double             medie()  const;
    const int*         adresaNote() const { return m_note; }

    void afiseaza(const char* eticheta) const;

private:
    // 2. encapsulation: data is private and cannot be corrupted from outside
    const int    m_id;          // const -> CAN only be set in the initialization list
    std::string  m_nume;
    std::size_t  m_capacitate;
    std::size_t  m_nrNote;
    int*         m_note;        // vector allocated on the HEAP
};

#endif // STUDENT_H
