#include <iostream>
#include "effective_items.h"

int main() {
    //----------------------------------------------------------
    // TEST ITEM 13: RAII (unique_ptr si shared_ptr)
    // ---------------------------------------------------------
    std::cout << "--- 1. ITEM 13: Use objects to manage resources ---\n";
    demoItem13UniquePtr(true); // Chiar cu return prematur, memoria se elibereaza!
    std::cout << "\n";
    demoItem13SharedPtr();

    // ---------------------------------------------------------
    // TEST ITEM 14: Comportamentul de copiere in clase RAII
    // ---------------------------------------------------------
    std::cout << "\n--- 2. ITEM 14 (Strategia 1): Interzicerea copierii ---\n";
    FakeMutex m1{"Mutex-A"};
    {
        UncopyableLock lock1(&m1);
        // UncopyableLock lock2(lock1); // EROARE de compilare: copiere interzisa!
        std::cout << "[Item 14] Lucram in zona critica cu UncopyableLock...\n";
    } // lock1 iese din scop -> m1 este deblocat automat

    std::cout << "\n--- 3. ITEM 14 (Strategia 2): Reference Counting cu Custom Deleter ---\n";
    FakeMutex m2{"Mutex-B"};
    {
        SharedLock sLock1(&m2);
        std::cout << "[Item 14] Owneri activi: " << sLock1.getOwnerCount() << "\n";
        {
            SharedLock sLock2(sLock1); // Copiere PERMISA!
            std::cout << "[Item 14] Dupa copiere, owneri activi: " << sLock1.getOwnerCount() << "\n";
        } // sLock2 moare, dar m2 RAMANE BLOCAT (mai exista sLock1)
        std::cout << "[Item 14] sLock2 a iesit din scop. Owneri ramasi: " << sLock1.getOwnerCount() << "\n";
    } // sLock1 moare -> count ajunge la 0 -> shared_ptr apeleaza automat unlock(&m2)!

    std::cout << "\n=== SFARSIT DEMONSTRATIE ===\n";
    return 0;
}