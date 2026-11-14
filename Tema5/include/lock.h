#ifndef LOCK_H
#define LOCK_H

// =============================================================================
//  Item 14: Think carefully about copying behavior in resource-managing classes.
//  Lock = clasă RAII: blochează mutex-ul în constructor, îl deblochează în
//  destructor. Întrebarea e: ce se întâmplă când un Lock e COPIAT?
//  Variantele din carte: interzici copierea, numeri referințele,
//  copiezi resursa (deep copy, vezi text.h) sau transferi proprietatea.
// =============================================================================

#include <mutex.h>

#include <memory>

// ---- 14.1 GREȘIT: copierea implicită -> două obiecte deblochează același mutex
class LockNaiv
{
public:
    explicit LockNaiv(Mutex* pm);
    ~LockNaiv();
private:
    Mutex* m_mutex;
};

// ---- 14.2 Varianta 1: INTERZICI copierea (cea mai des folosită)
class LockNecopiabil
{
public:
    explicit LockNecopiabil(Mutex* pm);
    ~LockNecopiabil();

    LockNecopiabil(const LockNecopiabil&)            = delete;
    LockNecopiabil& operator=(const LockNecopiabil&) = delete;
private:
    Mutex* m_mutex;
};

// ---- 14.3 Varianta 2: NUMERI REFERINȚELE (shared_ptr cu "deleter" = unlock)
//      Mutex-ul se deblochează o singură dată, când dispare ultima copie.
//      Nu e nevoie de destructor: îl generează compilatorul (Item 5)
//      și el distruge shared_ptr-ul, care apelează unlock.
class LockPartajat
{
public:
    explicit LockPartajat(Mutex* pm);
    long copii() const { return m_mutex.use_count(); }
private:
    std::shared_ptr<Mutex> m_mutex;
};

// ---- 14.4 Varianta 4: TRANSFERI PROPRIETATEA (copiere interzisă, mutare permisă)
class LockTransferabil
{
public:
    explicit LockTransferabil(Mutex* pm);
    ~LockTransferabil();

    LockTransferabil(const LockTransferabil&)            = delete;
    LockTransferabil& operator=(const LockTransferabil&) = delete;

    LockTransferabil(LockTransferabil&& other) noexcept;
    LockTransferabil& operator=(LockTransferabil&&)      = delete;

    bool detineMutex() const { return m_mutex != nullptr; }
private:
    Mutex* m_mutex;
};

void demoItem14();

#endif // LOCK_H