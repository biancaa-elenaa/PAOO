#pragma once
#include <string>
#include <iostream>
#include <vector>

// --- ITEM 4: Initializarea corecta si ordinea membrilor ---
class SensorDevice {
    std::string deviceName;
    int sensorId;
    double* readings; // Resursa alocata pe heap
public:
    // Corect: Folosirea listei de initializare (Member Initialization List).
    // Ordinea de initializare este data de ordinea declararii in clasa (deviceName, apoi sensorId, apoi readings).
    SensorDevice(const std::string& name, int id, size_t poolSize)
        : deviceName(name), sensorId(id), readings(new double[poolSize]{0.0}) {
        std::cout << "[Item 4] SensorDevice '" << deviceName << "' initializat corect prin lista.\n";
    }

    ~SensorDevice() {
        delete[] readings;
    }
};

// --- ITEM 5: Functii generate de compilator & Operatorul = sters ---
class ConfigurationManager {
    std::string& configPath; // Referinta (nu poate fi reatribuita dupa constructie)
    const int maxRetries;    // Membru constant (nu poate fi modificat prin atribuire)
public:
    ConfigurationManager(std::string& path, int retries)
        : configPath(path), maxRetries(retries) {}

    void showConfig() const {
        std::cout << "[Item 5] Config path: " << configPath << ", Retries: " << maxRetries << "\n";
    }

    // NOTA EXPLICATIVA: 
    // Din cauza prezentei unei referinte si a unui membru const, compilatorul 
    // defineste automat operatorul de atribuire (operator=) ca fiind STERS (= delete).
    // Incercarea de a face 'config1 = config2;' va genera o eroare directa de compilare.
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

    // O conexiune la baza de date este unica; copierea nu are sens (ar duce la dubla inchidere/conflict).
    // Prin urmare, interzicem explicit constructorul de copiere si operatorul de atribuire folosind C++11.
    UniqueDatabaseConnection(const UniqueDatabaseConnection&) = delete;
    UniqueDatabaseConnection& operator=(const UniqueDatabaseConnection&) = delete;

    void executeQuery(const std::string& query) const {
        std::cout << "[Item 6 Executare] " << query << " pe conexiunea " << connectionString << "\n";
    }
};