# Tema 5 – Effective C++: Item 13, 14

Aplicație simplă în C++14, construită cu CMake. Fiecare problemă are un
exemplu **greșit** și unul **corect**, iar mesajele afișate arată diferența.

## Structura

```
tema5/
├── CMakeLists.txt
├── README.md
├── include/
│   ├── investitie.h   # Item 13 – resursa (Investment în carte)
│   ├── mutex.h        # Item 14 – mutex simulat (lock / unlock)
│   ├── lock.h         # Item 14 – clasele RAII Lock
│   └── text.h         # Item 14 – varianta deep copy
└── src/
    ├── investitie.cpp
    ├── mutex.cpp
    ├── lock.cpp
    ├── text.cpp
    └── main.cpp       # apelează demoItem13/14
```

## Build și rulare

```bash
cmake -S . -B build
cmake --build build
./build/tema5
```

Demonstrația cu erori de compilare: copierea unui `unique_ptr` și a unui
`LockNecopiabil`. Opțiunea `-- -k` continuă build-ul după primul fișier
care pică, așa că apar ambele erori:

```bash
cmake -S . -B build_copy -DDEMO_COPIERE_INTERZISA=ON && cmake --build build_copy -- -k
```

Clean: `rm -rf build build_copy`

---

## Item 13 – Use objects to manage resources

Fișiere: `investitie.h`, `investitie.cpp`

Funcția fabrică `creeazaInvestitie()` returnează un obiect alocat cu `new`,
iar apelantul trebuie să facă `delete`. Un `return` devreme sau o excepție
sar peste `delete`, iar resursa se pierde.

**RAII** (*Resource Acquisition Is Initialization*): resursa intră **imediat**
într-un obiect, iar destructorul acelui obiect o eliberează. Destructorul se
apelează garantat la ieșirea din scope, inclusiv la `return` și la excepții.

| # | Exemplu | Ce se vede |
|---|---|---|
| 13.1 | pointer simplu + `delete` manual, cu `return` devreme și cu excepție | contorul ajunge la **2 investiții neeliberate** (memory leak) |
| 13.2 | aceleași funcții cu `std::unique_ptr` | apare `~Investitie` în toate cazurile, iar contorul nu mai crește |
| 13.3 | `unique_ptr`: un singur proprietar | copierea nu compilează; după `std::move`, `p1` devine `nullptr` |
| 13.4 | `shared_ptr`: numărare de referințe | `use_count` 1 → 2 → 1; obiectul e șters de ultimul proprietar |
| 13.5 | tablouri | `shared_ptr<int>(new int[10])` e greșit (face `delete`, nu `delete[]`); se folosește `unique_ptr<int[]>` sau, mai bine, `std::vector` |

> În carte apare `std::auto_ptr`. A fost eliminat în C++17, iar înlocuitorul
> lui modern este `std::unique_ptr`.

## Item 14 – Think carefully about copying behavior in resource-managing classes

Fișiere: `mutex.h`, `mutex.cpp`, `lock.h`, `lock.cpp`, `text.h`, `text.cpp`

`Lock` e o clasă RAII: blochează mutex-ul în constructor și îl deblochează în
destructor. Mutex-ul se deblochează și dacă apare o excepție (14.0). Problema
e ce se întâmplă când un `Lock` este **copiat**.

| # | Clasa | Comportament la copiere | Ce se vede |
|---|---|---|---|
| 14.1 | `LockNaiv` | implicit: copiază pointerul | **deblocare dublă**: `!!! EROARE: mutex era deja deblocat` |
| 14.2 | `LockNecopiabil` | **interzis** (`= delete`) | `use of deleted function` la compilare |
| 14.3 | `LockPartajat` | **numărare de referințe**: `shared_ptr<Mutex>(pm, unlock)` | mutex-ul rămâne blocat cât timp există o copie și e deblocat o singură dată |
| 14.4 | `Text` | **copiere profundă** a resursei | fiecare copie are memoria ei (adrese diferite) |
| 14.5 | `LockTransferabil` | **transfer de proprietate** (`move`) | sursa rămâne goală, iar mutex-ul e deblocat o singură dată |

La 14.3, al doilea argument al `shared_ptr` e un **deleter**: funcția apelată
la final în locul lui `delete`. Aici e `unlock`. Clasa nu are nevoie de
destructor propriu: destructorul generat de compilator distruge
`shared_ptr`-ul, care apelează `unlock` (vezi Item 5).