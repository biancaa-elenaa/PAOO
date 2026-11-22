#include <iostream>
#include "effective_items.h"

int main() {
    
    // ---------------------------------------------------------
    // TEST ITEM 10: Returnarea *this pentru inlantuire
    // ---------------------------------------------------------

    std::cout << "--- 1. ITEM 10: Return reference to *this ---\n";
    ScoreTracker s1(10), s2(20), s3(30);

    // Atribuire inlantuita: s1 = (s2 = s3)
    s1 = s2 = s3;
    std::cout << "Dupa s1 = s2 = s3 -> s1: " << s1.getPoints()
              << ", s2: " << s2.getPoints() << ", s3: " << s3.getPoints() << "\n";

    // Operator compus inlantuit
    (s1 += s2) += s3;
    std::cout << "Dupa (s1 += s2) += s3 -> s1: " << s1.getPoints() << "\n\n";

    // ---------------------------------------------------------
    // TEST ITEM 11: Tratarea auto-atribuirii (assignment to self)
    // ---------------------------------------------------------
    std::cout << "--- 2. ITEM 11: Handle assignment to self ---\n";
    DynamicBuffer buf1("Mesaj important pe heap");
    DynamicBuffer buf2("Alt mesaj");

    // Auto-atribuire directa (folosim o referinta pentru a evita warning-ul -Wself-assign)
    DynamicBuffer& refBuf = buf1;
    buf1 = refBuf; // Fara verificarea din Item 11, 'buf1' si-ar fi sters propriul text!
    std::cout << "Textul lui buf1 dupa auto-atribuire: " << buf1.getText() << "\n";

    // Atribuire normala intre doua obiecte diferite
    buf2 = buf1;
    std::cout << "Textul lui buf2 dupa buf2 = buf1: " << buf2.getText() << "\n\n";

    // ---------------------------------------------------------
    // TEST ITEM 12: Copierea tuturor partilor unui obiect
    // ---------------------------------------------------------
    std::cout << "--- 3. ITEM 12: Copy all parts of an object ---\n";
    PriorityCustomer vip1("Bianca", 101, 5);
    std::cout << "Original vip1:\n";
    vip1.display();

    // Testare Copy Constructor (copiaza atat partea Customer, cat si priorityLevel)
    PriorityCustomer vip2(vip1);
    std::cout << "Copie vip2 (via copy constructor):\n";
    vip2.display();

    // Testare Copy Assignment Operator
    PriorityCustomer vip3("Temp", 0, 1);
    vip3 = vip1;
    std::cout << "Copie vip3 (via operator=):\n";
    vip3.display();

    return 0;
}