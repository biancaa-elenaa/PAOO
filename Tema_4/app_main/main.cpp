#include <iostream>
#include "effective_items.h"

int main() {
    
    // ----------------------------------------------------
    // ITEM 4:
    // ----------------------------------------------------
    std::cout << "--- ITEM 4: Initializare vs Atribuire ---\n";
    // --- REGULA 1: Inițializarea tipurilor primitive ---
    // Regula din Item 4: Tipurile built-in (int, double, pointeri) locale nu sunt 
    // inițializate automat de C++ și conțin "garbage values".Trebuie initializate manual.
    int localCounter = 0; 
    double thresholdLimit = 25.5;
    std::cout << "1. Tipurile primitive locale au fost inițializate manual:\n"
              << "   - counter = " << localCounter << "\n"
              << "   - threshold = " << thresholdLimit << "\n\n";

    // --- REGULA 2: Lista de inițializare a membrilor ---
    std::cout << "2. Testare membrii prin lista de inițializare:\n";
    AdvancedSensor sensor("Sensor-Alpha", 99);

    // --- REGULA 3: Ordinea de inițializare în clasă ---
    std::cout << "\n3. Testare ordinea de inițializare (bazată pe declarare):\n";
    SensorReading reading(50);

    // ----------------------------------------------------
    // EXEMPLE SI COMENTARII PENTRU ITEM 5:
    // ----------------------------------------------------
    std::cout << "\n--- ITEM 5: Ce scrie C++ în tăcere ---\n";
    
    // C++ generează constructorul implicit și destructorul pentru această clasă goală:
    EmptySignalBox box1; 
    
    // C++ generează constructorul de copiere silențios (copiere membru cu membru):
    EmptySignalBox box2 = box1; 
    std::cout << "[Item 5] Obiectul box2 a fost copiat folosind constructorul generat automat de C++.\n";

    // Testare limitare operator= (Item 5):
    std::string ip1 = "192.168.1.10";
    std::string ip2 = "10.0.0.5";
    
    NetworkConfiguration net1(ip1, 8080);
    NetworkConfiguration net2(ip2, 9090);
    
    net1.display();
    net2.display();
    
    //net1 = net2;
    std::cout << "\n[Item 5 Notă importantă]: Dacă ai încerca să scrii 'net1 = net2;',\n"
              << "compilatorul ar da eroare pentru că operatorul= este șters automat\n"
              << "datorită prezenței referinței și a membrului const[cite: 23].\n";

    // ----------------------------------------------------
    // EXEMPLE SI COMENTARII PENTRU ITEM 6:
    // ----------------------------------------------------
    std::cout << "\n---ITEM 6: Interzicerea explicita a copierii ---\n";
    UniqueDatabaseConnection dbConn("postgresql://localhost:5432/prod_db");
    dbConn.executeQuery("SELECT * FROM sensors;");

    /* 
       DACĂ AI DECOMENTA URMĂTOARELE LINII, PROGRAMUL NU AR COMPILA:
       
       UniqueDatabaseConnection dbCopy = dbConn; // Eroare: constructorul de copiere este șters!
       dbConn = dbCopy;                         // Eroare: operatorul= este șters!
       
       Motivul (Item 6): 
       - Abordarea modernă (C++11): Folosirea clauzei '= delete' blochează copierea de la compilare[cite: 24].
       - Abordarea istorică (C++98): Declararea constructorului de copiere în zona 'private' (fără implementare)[cite: 24].
    */

    std::cout << "[Item 6 Notă]: Încercarea de a copia obiectul UniqueDatabaseConnection\n"
              << "ar fi oprită instant de compilator datorită clauzelor '= delete'.\n";

    return 0;
}