#include <iostream>
#include "effective_items.h"

int main() {
    std::cout << "=== PROIECT COMPLEX: EFFECTIVE C++ (ITEMS 4, 5, 6) ===\n\n";

    // ----------------------------------------------------
    // EXEMPLE SI COMENTARII PENTRU ITEM 4:
    // ----------------------------------------------------
    std::cout << "--- DEMO ITEM 4: Initializare vs Atribuire ---\n";
    std::string primaryLocation = "/etc/sensors.conf";
    SensorDevice sensor("Termometru-Lab", 402, 10);
    // Explicație: Membrii sunt construiti direct din argumente prin lista de initializare,
    // evitand dubla initializare (creare goala + suprascriere ulterioara), obligatorie pentru const/referinte.


    // ----------------------------------------------------
    // EXEMPLE SI COMENTARII PENTRU ITEM 5:
    // ----------------------------------------------------
    std::cout << "\n--- DEMO ITEM 5: Functii generate tacit si limitari ---\n";
    std::string path1 = "config_v1.json";
    std::string path2 = "config_v2.json";
    
    ConfigurationManager cfg1(path1, 3);
    ConfigurationManager cfg2(path2, 5);
    cfg1.showConfig();
    cfg2.showConfig();

    //cfg1=cfg2;

    std::cout << "[Item 5 Detaliu]: Daca am incerca 'cfg1 = cfg2;', codul nu ar compila.\n"
              << "Motivul: Clasa contine referinte si membri const, fortand compilatorul\n"
              << "sa marcheze operatorul de atribuire (=) ca fiind sters implicit.\n";


    // ----------------------------------------------------
    // EXEMPLE SI COMENTARII PENTRU ITEM 6:
    // ----------------------------------------------------
    std::cout << "\n--- DEMO ITEM 6: Interzicerea explicita a copierii ---\n";
    UniqueDatabaseConnection dbConn("postgresql://localhost:5432/prod");
    dbConn.executeQuery("SELECT * FROM users;");

    std::cout << "[Item 6 Detaliu]: Incercarea de a face 'UniqueDatabaseConnection dbCopy = dbConn;' \n"
              << "sau 'dbConn2 = dbConn;' va opri compilarea imediat datorita clauzei '= delete'.\n"
              << "Astfel evitam bug-uri critice generate de copierea accidentali a unor entitati unice.\n\n";

    std::cout << "=== FINALUL DEMONSTRATIEI COMPLEXE ===\n";
    return 0;
}