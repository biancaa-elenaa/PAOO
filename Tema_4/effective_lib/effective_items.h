#pragma once
#include <string>
#include <iostream>
#include <vector>

// --- ITEM 4: 1. Ordinea de inițializare a membrilor ---
// Regulă din Effective C++: Membrii unei clase sunt întotdeauna inițializați în 
// ordinea în care sunt DECLARAȚI în clasă, nu în ordinea în care apar în lista constructorului[cite: 21].
class SensorReading {
public:
    int rawValue;
    int processedValue;

    // Chiar dacă în listă am pus processedValue primul, rawValue se va inițializa primul
    // deoarece este declarat primul în clasă.
    SensorReading(int val) : rawValue(val), processedValue(rawValue * 2) {
        std::cout << "[Item 4 - Ordine] SensorReading creat. rawValue: " << rawValue 
                  << ", processedValue: " << processedValue << "\n";
    }
};

// --- ITEM 4: 2. Lista de inițializare vs Atribuire în corp ---
class AdvancedSensor {
    std::string sensorName;
    int calibrationCode;
public:
    // Corect: Folosirea listei de inițializare construiește membrul direct din argument (1 singur pas).
    // Dacă am fi atribuit în corp, membrul ar fi fost mai întâi creat gol, apoi suprascris (2 pași)[cite: 20].
    AdvancedSensor(const std::string& name, int code) 
        : sensorName(name), calibrationCode(code) {
        //sensorName = name; - gresit - Membrul clasei ar fi fost mai întâi creați gol, (prin constructorul lor implicit),
        //  iar abia apoi li s-ar fi dat valoarea în corpul constructorului (însemnând doi pași / dublă operațiune).
        std::cout << "[Item 4 - Lista] AdvancedSensor inițializat corect prin lista de inițializare.\n";
    }
};

// ==========================================
// ITEM 5: Funcțiile generate silențios de C++
// ==========================================

// Clasa goală pe care C++ o umple automat cu funcții implicite
class EmptySignalBox {
    // Dacă nu scrii nimic, C++ generează în mod silențios (dacă sunt folosite):
    // 1. Constructor implicit (Default constructor)
    // 2. Destructor
    // 3. Constructor de copiere (Copy constructor - face shallow copy / bit-cu-bit)
    // 4. Operator de atribuire prin copiere (Copy assignment operator)[cite: 22]
};

// Exemplu unde C++ REFUZĂ să genereze operatorul de atribuire (operator=)
class NetworkConfiguration {
    std::string& serverIp; // Referință: o dată legată, nu mai poate fi schimbată
    const int portNumber;  // Membru const: nu poate primi altă valoare prin atribuire
public:
    NetworkConfiguration(std::string& ip, int port) 
        : serverIp(ip), portNumber(port) {
        std::cout << "[Item 5] NetworkConfiguration creat cu IP și port " << portNumber << "\n";
    }

    void display() const {
        std::cout << "[Item 5] Configurație rețea -> Port: " << portNumber << "\n";
    }

    // DE CE NU GENEREAZĂ C++ operator= AICI?
    // Conform Item 5: Dacă o clasă conține referințe (&) sau membri constanți (const), 
    // compilatorul marchează operatorul de atribuire prin copiere ca fiind ȘTERS (= delete).
    // Motivul: O referință nu poate fi reatribuită către un alt obiect, iar un const nu poate fi suprascris[cite: 23].
};

// --- ITEM 6: Interzicerea explicita a copierii (= delete) ---
class UniqueDatabaseConnection {
    std::string connectionString;
public:
    UniqueDatabaseConnection(const std::string& connStr) : connectionString(connStr) {
        std::cout << "[Item 6] Conexiunea la baza de date deschisa pentru: " << connectionString << "\n";
    }

    ~UniqueDatabaseConnection() {
        std::cout << "[Item 6] Conexiunea inchisa.\n";
    }

    // --- ABORDAREA MODERNĂ (C++11 și ulterior) ---
    // Folosirea lui '= delete' blochează copierea direct la nivelul compilatorului.
    UniqueDatabaseConnection(const UniqueDatabaseConnection&) = delete;
    UniqueDatabaseConnection& operator=(const UniqueDatabaseConnection&) = delete;

    /* 
       --- ABORDAREA ISTORICĂ (C++98 / din cartea originală Effective C++) ---
       Dacă ai folosi standardul vechi, blocarea copierii s-ar face mutând 
       funcțiile în zona 'private' și fără a le scrie corpul (implementarea)[cite: 24]:
       
       private:
           UniqueDatabaseConnection(const UniqueDatabaseConnection&);
           UniqueDatabaseConnection& operator=(const UniqueDatabaseConnection&);
    */
    void executeQuery(const std::string& query) const {
        std::cout << "[Item 6 Executare] " << query << " pe conexiunea " << connectionString << "\n";
    }
};