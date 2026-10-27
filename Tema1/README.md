# Tema 1 — Biblioteca statica C++

## Obiectiv

Se vor realiza doua proiecte C++ independente, configurate cu ajutorul
fisierelor `CMakeLists.txt`. Primul proiect va furniza o biblioteca statica,
iar cel de-al doilea proiect va utiliza functionalitatile oferite de aceasta.

## Cerinte

- configurarea celor doua proiecte C++ folosind fisierele `CMakeLists.txt`
  aferente;
- implementarea, in primul proiect, a unei biblioteci statice;
- expunerea functionalitatilor bibliotecii printr-un fisier header cu extensia
  `.h`;
- utilizarea bibliotecii statice create in primul proiect de catre cel de-al
  doilea proiect.

## Rezultatul asteptat

La final, al doilea proiect trebuie sa poata fi compilat si rulat folosind
biblioteca statica generata de primul proiect.

## Rulare

Executa comenzile de mai jos din directorul `Tema1`.

### Biblioteca: compilare si export in `install/`

```bash
cmake -S hello_lib -B build_lib
cmake --build build_lib
cmake --install build_lib --prefix install
```

### Aplicatia: folosirea bibliotecii instalate

```bash
cmake -S hello_app -B build_app -DCMAKE_PREFIX_PATH=$PWD/install
cmake --build build_app
./build_app/hello_app
```

Aplicatia poate primi si un argument:

```bash
./build_app/hello_app Timisoara
```

Alternativ, ambele proiecte pot fi configurate si construite din directorul
`Tema1`:

```bash
cmake -S . -B build
cmake --build build
./build/hello_app/hello_app
```

### Clean

```bash
rm -rf build build_lib build_app install
```