# Tema 3 – clasa `Student` (C++14 + CMake)

Aplicatie simpla (proof of life): clasa `Student` tine notele intr-un vector
alocat pe **heap** (`int* m_note`). Fiecare constructor si destructor afiseaza
un mesaj, iar un contor arata cate blocuri de heap nu au fost inca eliberate.

## Structura

```
tema3/
├── CMakeLists.txt
├── include/student/
│   ├── student.h          # clasa CORECTA
│   ├── student_gresit.h   # contra-exemplu (fara copy ctor / destructor)
│   └── heap_contor.h      # contor de alocari
└── src/
    ├── student.cpp
    ├── student_gresit.cpp
    ├── heap_contor.cpp
    └── main.cpp           # demonstratiile, pe sectiuni
```

## Build si rulare

```bash
cmake -S . -B build
cmake --build build
./build/tema3
```

## Demonstratii optionale

```bash
# Double free intentionat: programul se opreste cu eroare.
cmake -S . -B build_df -DDEMO_DOUBLE_FREE=ON
cmake --build build_df
./build_df/tema3
```

Pentru a vedea eroarea de compilare cauzata de lipsa listei de initializare:

```bash
cmake -S . -B build_init -DDEMO_EROARE_INIT=ON
cmake --build build_init
```

## Clean

```bash
rm -rf build build_df build_init
```

Comenzile de mai sus pot fi rulate din directorul `Tema2`.

## Cerinte → unde se vad

| # | Cerinta | Unde | Ce demonstreaza |
|---|---|---|---|
| 1 | CMake | `CMakeLists.txt` | `inc/` + `src/`, C++14, `target_include_directories`, optiuni |
| 2 | Incapsulare | `student.h`, `adaugaNota` | date `private`; nota 15 e respinsa; `ana.m_note[0] = 100` nu compileaza |
| 3 | Lista de initializare | constructorul `Student(...)` | `m_id` e `const` → se poate seta **doar** acolo; cu `-DDEMO_EROARE_INIT=ON`: `assignment of read-only member 'Student::m_id'` |
| 4 | Destructor | `~Student()` | `Student` iese din scope → `delete[]`, contorul scade; `StudentGresit` nu are destructor → contorul ramane > 0 (leak) |
| 5 | Copy constructor | `Student(const Student&)` | **fara** el: copia si originalul au *aceeasi adresa*, modificarea copiei strica originalul, iar la distrugere → double free / crash. **Cu** el: adrese diferite, originalul ramane neatins |
| 6 | Move constructor | `Student(Student&&) noexcept` | copierea face `new int[1000]` (+1 alocare); mutarea doar preia pointerul (+0); sursa ramane cu `nullptr` |

## De ce e nevoie de fiecare (pe scurt)

* **Lista de initializare** – membrii `const` si referintele *nu pot* fi atribuiti
  in corpul constructorului, doar initializati. In plus, membrii sunt construiti
  direct cu valoarea corecta, nu intai implicit si apoi suprascrisi.
* **Destructor** – memoria luata cu `new[]` nu se elibereaza singura. Fara
  `delete[]`, fiecare obiect lasa un bloc ocupat (memory leak).
* **Copy constructor** – cel generat de compilator copiaza doar pointerul
  (*shallow copy*): doua obiecte ajung sa imparta acelasi vector. Modificarea
  unuia il afecteaza pe celalalt, iar la final ambele fac `delete[]` pe aceeasi
  adresa → *double free* (comportament nedefinit, de obicei crash).
* **Move constructor** – cand sursa nu mai e folosita (temporar, `std::move`,
  inserare in `std::vector`), nu are sens sa alocam si sa copiem tot vectorul:
  il „furam” si punem `nullptr` in sursa, ca destructorul ei sa nu-l elibereze.
  E marcat `noexcept` ca `std::vector` sa-l foloseasca la realocare.

> Operatorii de atribuire (`operator=`) nu sunt ceruti in tema, asa ca sunt
> marcati `= delete`: astfel nu ramane activa varianta implicita (shallow),
> care ar avea exact problema de la punctul 5 (regula celor 3/5).
