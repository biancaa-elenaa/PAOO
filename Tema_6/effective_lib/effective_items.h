#pragma once
#include <iostream>
#include <memory>   // pentru std::unique_ptr, std::shared_ptr
#include <string>

// ============================================================================
// ITEM 13: Use objects to manage resources (RAII)
// ============================================================================

// O resursa simulata (ex: o conexiune sau un fisier alocat pe heap)
class Investment {
    std::string name;
public:
    Investment(const std::string& n) : name(n) {
        std::cout << "[Item 13] Resursa '" << name << "' a fost ALOCATA.\n";
    }
    ~Investment() {
        std::cout << "[Item 13] Resursa '" << name << "' a fost ELIBERATA automat!\n";
    }
    void use() const {
        std::cout << "[Item 13] Folosim resursa: " << name << "\n";
    }
};

// Functie factory care returneaza un obiect alocat dinamic
inline Investment* createInvestment(const std::string& name) {
    return new Investment(name);
}

// DEMONSTRATIE RAII cu std::unique_ptr (inlocuitorul modern pentru std::auto_ptr din carte)
inline void demoItem13UniquePtr(bool simulateEarlyReturn) {
    // Punem resursa IMEDIAT intr-un obiect manager (RAII)
    std::unique_ptr<Investment> pInv(createInvestment("Actiuni-Tech"));
    pInv->use();

    if (simulateEarlyReturn) {
        std::cout << "[Item 13] Return prematur! Nu apelam 'delete' manual...\n";
        return; // <--- Destructorul lui unique_ptr elibereaza memoria automat aici!
    }
}

// DEMONSTRATIE RAII cu std::shared_ptr (Reference Counting)
inline void demoItem13SharedPtr() {
    std::shared_ptr<Investment> pInv1(createInvestment("Obligatiuni-Stat"));
    {
        std::shared_ptr<Investment> pInv2 = pInv1; // Ambele pointeaza la aceeasi resursa (count = 2)
        std::cout << "[Item 13] Numar referinte (use_count): " << pInv1.use_count() << "\n";
    } // pInv2 iese din scop (count scade la 1, resursa NU se sterge inca)

    std::cout << "[Item 13] Dupa iesirea lui pInv2, use_count: " << pInv1.use_count() << "\n";
} // pInv1 iese din scop (count devine 0 -> resursa se elibereaza automat)

// ============================================================================
// ITEM 14: Think carefully about copying behavior in resource-managing classes
// ============================================================================

// Resursa non-heap simulata: un Mutex (lacat pentru sincronizare)
struct FakeMutex {
    std::string id;
    bool isLocked = false;
};

inline void lock(FakeMutex* pm) {
    pm->isLocked = true;
    std::cout << "[Item 14] Mutex '" << pm->id << "' BLOCAT (locked).\n";
}

inline void unlock(FakeMutex* pm) {
    pm->isLocked = false;
    std::cout << "[Item 14] Mutex '" << pm->id << "' DEBLOCAT (unlocked).\n";
}

// --- STRATEGIA 1: Interzicem copierea (Prohibit copying) ---
// Are sens pentru un lock: nu vrei ca doua obiecte sa deblocheze acelasi mutex de doua ori.
class UncopyableLock {
    FakeMutex* mutexPtr;
public:
    explicit UncopyableLock(FakeMutex* pm) : mutexPtr(pm) {
        lock(mutexPtr); // Achizitionam resursa in constructor (RAII)
    }
    ~UncopyableLock() {
        unlock(mutexPtr); // Eliberam resursa in destructor
    }

    // Interzicem copierea conform Item 14 (Strategia 1) + Item 6
    UncopyableLock(const UncopyableLock&) = delete;
    UncopyableLock& operator=(const UncopyableLock&) = delete;
};

// --- STRATEGIA 2: Reference-counting cu Custom Deleter (std::shared_ptr) ---
// Vrem sa putem copia obiectul Lock, iar mutex-ul sa se deblocheze ABIA cand
// ultimul obiect care il detine este distrus.
class SharedLock {
    std::shared_ptr<FakeMutex> mutexPtr;
public:
    // Folosim 'unlock' ca si CUSTOM DELETER in locul lui 'delete'!
    explicit SharedLock(FakeMutex* pm)
        : mutexPtr(pm, unlock) {
        lock(mutexPtr.get());
    }

    // Nu avem nevoie de destructor manual: cand use_count ajunge la 0,
    // shared_ptr va apela automat functia 'unlock(pm)'!
    long getOwnerCount() const { return mutexPtr.use_count(); }
};