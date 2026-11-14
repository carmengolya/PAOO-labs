# Tema – Effective C++: Item 10, 11, 12

Aplicație simplă în C++14, construită cu CMake. Fiecare item are fișierele lui
și câte un exemplu **greșit** pus lângă unul **corect**. Mesajele afișate arată
diferența dintre ele.

## Structura

```
effective_10_12/
├── CMakeLists.txt
├── README.md
├── include/
│   ├── punct.h       # Item 10
│   ├── imagine.h     # Item 11 – resursa de pe heap (Bitmap în carte)
│   ├── fereastra.h   # Item 11 – Widget în carte
│   └── client.h      # Item 12 – Customer / PriorityCustomer în carte
└── src/
    ├── punct.cpp
    ├── imagine.cpp
    ├── fereastra.cpp
    ├── client.cpp
    └── main.cpp      # apelează demoItem10/11/12
```

## Build și rulare

```bash
cmake -S . -B build
cmake --build build
./build/tema
```

Demonstrații opționale:

```bash
# Item 10: operator= care returnează void -> a = b = c nu compilează
cmake -S . -B build_void -DDEMO_ITEM10_VOID=ON && cmake --build build_void

# Item 11: eroarea reală de memorie, prinsă de AddressSanitizer
cmake -S . -B build_asan -DDEMO_ASAN=ON && cmake --build build_asan && ./build_asan/tema
```

Clean: `rm -rf build build_void build_asan`

---

## Item 10 – Have assignment operators return a reference to `*this`

Fișiere: `punct.h`, `punct.cpp`

`operator=` (și `+=`, `-=` etc.) trebuie să returneze `T&`, adică `*this`.
Așa funcționează atribuirea în lanț, `a = b = c`, adică `a = (b = c)`, la fel
ca la tipurile predefinite.

| Clasa | Returnează | Rezultat |
|---|---|---|
| `Punct` | `Punct&` | corect: `a = b = c` și `(a += b) += c` funcționează, fără copii |
| `PunctValoare` | `PunctValoare` (copie) | compilează, dar face copii inutile, iar `(d = e) = f` **pierde modificarea**: `d` rămâne `(5, 5)` |
| `PunctVoid` | `void` | `a = b = c` **nu compilează**: `no match for 'operator=' (operand types are 'PunctVoid' and 'void')` |

## Item 11 – Handle assignment to self in `operator=`

Fișiere: `imagine.h`, `imagine.cpp`, `fereastra.h`, `fereastra.cpp`

Auto-atribuirea (`a = a`) apare și ascuns: `v[i] = v[j]` cu `i == j`,
`*px = *py` cu `px == py` sau printr-o referință. Dacă `operator=` șterge
resursa înainte s-o copieze, la auto-atribuire copiază din memorie deja
eliberată.

`Imagine` ține evidența imaginilor existente, așa că programul **afișează**
eroarea în loc să crape. Copierea imaginii `"uriasa"` aruncă excepție, ca să
simuleze lipsa de memorie.

| Clasa | `operator=` | `a = a` | excepție la copiere |
|---|---|---|---|
| `FereastraNaiva` | `delete`, apoi `new` | ❌ use-after-free (`<GUNOI>`) | ❌ |
| `FereastraTest` | `if (this == &rhs) return *this;` | ✅ | ❌ pointer agățat |
| `FereastraOrdine` | păstrează originalul, `new`, apoi `delete` | ✅ | ✅ obiectul rămâne neatins |
| `FereastraSwap` | copy-and-swap | ✅ | ✅ obiectul rămâne neatins |

Cu `-DDEMO_ASAN=ON` detectorul e oprit, iar AddressSanitizer raportează
`heap-use-after-free` exact în `FereastraNaiva::operator=`.

## Item 12 – Copy all parts of an object

Fișiere: `client.h`, `client.cpp`

Funcțiile de copiere trebuie să copieze **toți membrii** și **partea din clasa
de bază**. Compilatorul nu te avertizează dacă uiți: pentru copy constructor
doar cu `-Wextra`, iar pentru `operator=` deloc.

| Clasa | Problema | Ce se vede |
|---|---|---|
| `ClientIncomplet` | membrul nou `m_ultimaTranzactie` a fost uitat în copy ctor și în `operator=` | copia are data `""`, iar destinația atribuirii își păstrează data veche |
| `Client` | corect: copiază toți membrii | copia e identică |
| `ClientPremiumGresit` | copy ctor fără `Client(rhs)`, `operator=` fără `Client::operator=(rhs)` | copy ctor → `Client()` implicit (`"<fara nume>"`); `operator=` → numele și data rămân vechi |
| `ClientPremium` | corect: `: Client(rhs)` și `Client::operator=(rhs);` | toate părțile copiate |

**Regulă din carte:** nu implementa o funcție de copiere apelând-o pe cealaltă.
Codul comun se pune într-o a treia funcție, privată, pe care o apelează
amândouă. În program, aceasta este `Client::jurnal()`, echivalentul lui
`logCall` din carte.