# Tema 4 – Effective C++: Item 4, 5, 6

Aplicație simplă (C++14 + CMake), câte o secțiune pentru fiecare item.
Clasa ajutătoare `Nume` afișează fiecare funcție specială apelată
(`Nume()`, `Nume(copy)`, `operator=`, `~Nume()`), ca să se vadă ce face compilatorul.

## Structura

```
tema4/
├── CMakeLists.txt
├── include/tema4/
│   ├── nume.h      # clasa care afișează ce funcții i se apelează
│   ├── item4.h
│   ├── item5.h
│   └── item6.h
└── src/
    ├── nume.cpp
    ├── item4.cpp
    ├── item5.cpp
    ├── item6.cpp
    └── main.cpp    # apelează demoItem4/5/6
```

## Build și rulare

```bash
cmake -S . -B build
cmake --build build
./build/tema4
```

Demonstrații de erori de compilare (fiecare în alt folder de build):

```bash
# Item 6: încercare de copiere a obiectelor necopiabile
cmake -S . -B build_copy -DDEMO_COPIERE_INTERZISA=ON && cmake --build build_copy

# Item 5: operator= pe o clasă cu membru referință + const
cmake -S . -B build_ref -DDEMO_ATRIBUIRE_REFERINTA=ON && cmake --build build_ref
```

Clean: `rm -rf build build_copy build_ref`

---

## Item 4 – Make sure that objects are initialized before they're used

Fișiere: `item4.h`, `item4.cpp`

| # | Problema | Exemplu | Ce se vede |
|---|---|---|---|
| 4.1 | `int`, `double` și pointerii **nu** se inițializează singuri | `ContGresit` (constructor gol) vs. `ContCorect` (`: m_sold(0)`) | `sold=-1414812757` (gunoi) vs. `sold=0` |
| 4.2 | Atribuirea în corp face **două** operații | `PersoanaAtribuire` vs. `PersoanaInitializare` | `Nume()` + `operator=` vs. doar `Nume(copy)` |
| 4.3 | `const` și referințele **pot fi doar** inițializate | `Angajat` (`const int m_id`, `const Nume& m_departament`) | merge doar cu lista de inițializare |
| 4.4 | Ordinea reală = **ordinea declarării** în clasă | `Ordine`: lista e scrisă invers | se construiește „primul”, apoi „al doilea” |
| 4.5 | Obiectele statice din fișiere diferite au ordine de inițializare **nedefinită** | `jurnal()` cu `static Jurnal instanta;` | Jurnalul e creat la primul apel, chiar și înainte de `main()` |

**Reguli:** inițializează manual tipurile de bază, folosește mereu lista de
inițializare (în ordinea declarării) și înlocuiește obiectele statice globale
cu statice locale în funcții.

## Item 5 – Know what functions C++ silently writes and calls

Fișiere: `item5.h`, `item5.cpp`

Dacă nu le declari tu, compilatorul scrie singur: **constructorul implicit,
copy constructorul, copy assignment (`operator=`) și destructorul**
(din C++11 și pe cele de mutare). Le scrie doar dacă sunt folosite.

| # | Exemplu | Ce se vede |
|---|---|---|
| 5.1 | `Carte` (nicio funcție declarată) | `Carte a;`, `Carte b(a);`, `c = a;` și distrugerea apelează funcțiile membrilor `Nume` |
| 5.2 | `CarteCuTitlu` (are un constructor propriu) | **nu** mai are constructor implicit |
| 5.3 | `Imprumut` (membru referință + `const`) | copy constructorul merge, dar **`operator=` nu e generat**; cu `-DDEMO_ATRIBUIRE_REFERINTA=ON` apare eroarea `use of deleted function` |

Tabelul din program e calculat de compilator cu `std::is_default_constructible`,
`std::is_copy_constructible` și `std::is_copy_assignable` din `<type_traits>`.

## Item 6 – Explicitly disallow the use of compiler-generated functions you do not want

Fișiere: `item6.h`, `item6.cpp`

Exemplu: o **cheie de acces unică** nu trebuie să poată fi copiată.

| # | Variantă | Cum | Eroare la copiere |
|---|---|---|---|
| 6.1 | din carte (C++98) | copy ctor + `operator=` **private și nedefinite** | `is private within this context` (iar din clasă/friend: eroare de link) |
| 6.2 | din carte (C++98) | moștenire din clasa de bază **`Uncopyable`** | `Uncopyable(const Uncopyable&) is private` (mereu la compilare) |
| 6.3 | modern (C++11) | `= delete` | `use of deleted function` (cea mai clară) |

`CheieModerna` interzice copierea, dar permite **mutarea**: cheia își poate
schimba proprietarul, dar nu poate fi duplicată (la fel ca `std::unique_ptr`).
