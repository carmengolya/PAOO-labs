#include <student/student.h>
#include <student/student_gresit.h>
#include <student/heap_contor.h>

#include <iostream>
#include <utility>
#include <vector>

static void titlu(const char* text)
{
    std::cout << "\n==================== " << text << " ====================\n";
}

static void contor(const char* moment)
{
    std::cout << "  >> blocuri heap neeliberate " << moment << ": "
              << heap::blocuriNeeliberate() << "\n";
}

int main()
{
    // Flush every message immediately (otherwise it could be lost in a crash).
    std::cout << std::unitbuf;

    // -----------------------------------------------------------------------
    titlu("2+3. Incapsulare + lista de initializare");
    // -----------------------------------------------------------------------
    {
        Student ana(1, "Ana", 4);
        ana.adaugaNota(9);
        ana.adaugaNota(10);
        ana.adaugaNota(15);      // rejected: class validation protects the data
        ana.adaugaNota(8);
        // ana.m_note[0] = 100;  // DOES NOT compile: m_note is private
        // ana.m_id = 7;         // DOES NOT compile: private + const
        ana.afiseaza("ana");
    }   // <- the destructor is called automatically here
    contor("dupa ce ana a iesit din scope");

    // -----------------------------------------------------------------------
    titlu("4. Destructor: cu el vs. fara el");
    // -----------------------------------------------------------------------
    {
        Student s(2, "Bogdan", 3);           // has a destructor -> releases memory
#ifndef DEMO_DOUBLE_FREE
        StudentGresit g(3);                  // has NO destructor -> leak
#endif
    }
    contor("dupa scope (Student a eliberat, StudentGresit NU)");

    // -----------------------------------------------------------------------
    titlu("5. De ce e nevoie de copy constructor");
    // -----------------------------------------------------------------------
    std::cout << "\n  --- A) FARA copy constructor (StudentGresit) ---\n";
    {
        StudentGresit original(2);
        original.setNota(0, 10);

        StudentGresit copie = original;      // IMPLICIT copy ctor -> copies only the pointer
        std::cout << "  adresa original: " << original.adresaNote()
                  << " | adresa copie: " << copie.adresaNote()
                  << "  <- ACEEASI adresa!\n";

        copie.setNota(0, 2);                 // modify ONLY the copy...
        std::cout << "  dupa copie.setNota(0, 2): original.nota(0) = "
                  << original.nota(0) << "  <- originalul s-a stricat!\n";
#ifdef DEMO_DOUBLE_FREE
        std::cout << "  la iesirea din scope ambii destructori fac delete[] pe "
                  << original.adresaNote() << " -> DOUBLE FREE:\n";
#else
        std::cout << "  (cu destructor, ambele obiecte ar face delete[] pe aceeasi "
                     "adresa -> double free / crash; vezi -DDEMO_DOUBLE_FREE=ON)\n";
#endif
    }

    std::cout << "\n  --- B) CU copy constructor (Student) ---\n";
    {
        Student original(4, "Cristina", 3);
        original.adaugaNota(10);
        original.adaugaNota(9);

        Student copie = original;            // calls our copy ctor (deep copy)
        copie.modificaNota(0, 5);            // modify only the copy

        original.afiseaza("original");
        copie.afiseaza("copie   ");
        std::cout << "  -> adrese diferite, originalul a ramas neatins\n";
    }   // each releases its own vector -> no double free
    contor("dupa partea 5 (Student-ii s-au eliberat; cele 2 ramase sunt StudentGresit)");

    // -----------------------------------------------------------------------
    titlu("6. Move constructor");
    // -----------------------------------------------------------------------
    {
        Student dan(5, "Dan", 1000);         // "large" vector
        dan.adaugaNota(7);
        dan.adaugaNota(8);
        contor("dupa crearea lui dan");

        std::cout << "\n  Student copiat = dan;   (copy)\n";
        Student copiat = dan;
        contor("dupa copiere (+1 alocare, 1000 de int copiati)");

        std::cout << "\n  Student mutat = std::move(dan);   (move)\n";
        Student mutat = std::move(dan);
        contor("dupa mutare (nicio alocare noua)");

        mutat.afiseaza("mutat");
        std::cout << "  dan dupa mutare: nrNote=" << dan.nrNote()
                  << ", vector la " << dan.adresaNote() << " (gol)\n";

        std::cout << "\n  Mutare intr-un std::vector:\n";
        std::vector<Student> grupa;
        grupa.reserve(2);
        grupa.push_back(Student(6, "Elena", 5));   // temporary object -> move, not copy
        grupa.push_back(std::move(mutat));         // explicit move
        contor("cu grupa populata");
        std::cout << "\n  Iesire din scope (se distrug toti):\n";
    }
    contor("LA FINAL (toti Student-ii eliberati; cele 2 = StudentGresit fara destructor -> leak)");

    return 0;
}
