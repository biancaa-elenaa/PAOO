#pragma once
#include <iostream>
#include <cstring>
#include <algorithm>

// ============================================================================
// ITEM 10: Have assignment operators return a reference to *this
// ============================================================================

class ScoreTracker {
    int points;

public:
    ScoreTracker(int p=0) : points(p) {}

    // Operatorul de atribuire returneaza o REFERINTA la *this (ScoreTracker&)
    // Daca ar fi returnat 'void', inlantuirea (s1 = s2 = s3) ar da eroare de compilare.
    ScoreTracker& operator=(const ScoreTracker& rhs) {
        points = rhs.points;
        return *this; // <--- ESENTIAL conform Item 10
    }

    // Regula se aplica si operatorilor compusi (+=, -=, *=, etc.)
    //Trebuie definit separat fiecare tip de operator care urmeaza sa fie folosit
    ScoreTracker& operator+=(const ScoreTracker& rhs) {
        points += rhs.points;
        return *this; // <--- Returnam *this pentru a permite (s1 += s2) += s3
    }

    int getPoints() const { return points; }
};

//============================================================================
// ITEM 11: Handle assignment to self in operator=
// ============================================================================

class DynamicBuffer {
    char* data;
    size_t size;

public:
    DynamicBuffer(const char* text = "") {
        size = std::strlen(text);
        data = new char[size + 1];
        std::strcpy(data, text);
    }

    // Constructor de copiere (Deep Copy - aloca memorie separata)
    DynamicBuffer(const DynamicBuffer& other) : size(other.size) {
        data = new char[size + 1];
        std::strcpy(data, other.data);
    }

    ~DynamicBuffer() {
        delete[] data;
    }

    // METODA 1 (Clasica + Exception Safe): Verificare identitate + salvare pointer vechi
    //fara aceasta regula, daca facem buf = buf, se va sterge memoria si se va incerca copierea dintr-un pointer invalid.
    DynamicBuffer& operator=(const DynamicBuffer& rhs) {
        // 1. Test de identitate: daca atribuim obiectul lui insusi (buf = buf), iesim imediat.
        if (this == &rhs) {
            std::cout << "[Item 11] Auto-atribuire detectata si prevenita!\n";
            return *this;
        }

        // 2. Alocam mai intai noua memorie (daca 'new' arunca exceptie, 'data' vechi ramane intact!)
        char* pOrig = data; // Salvam adresa veche
        size_t newSize = rhs.size;
        data = new char[newSize + 1];
        std::strcpy(data, rhs.data);
        size = newSize;

        // 3. Abia dupa ce copia a reusit, eliberam memoria veche
        delete[] pOrig;

        return *this; // Respectam si Item 10
    }

    const char* getText() const { return data; }
};

// ============================================================================
// ITEM 12: Copy all parts of an object
// ============================================================================

class Customer {
    std::string name;
    int customerId;

public:
    Customer(const std::string& n = "Anonim", int id = 0) 
        : name(n), customerId(id) {}

    // Constructor de copiere: copiem TOTI membruu locali
    Customer(const Customer& other) 
        : name(other.name), customerId(other.customerId) {
        std::cout << "[Item 12] Constructor de copiere apelat pentru Customer: " << name << "\n";
        }
    
    // Operatorul de atribuire: copiem TOTI membrii locali
    Customer& operator=(const Customer& rhs) {
        if (this == &rhs) {
            std::cout << "[Item 12] Auto-atribuire detectata si prevenita pentru Customer: " << name << "\n";
            return *this;
        }
        name = rhs.name;
        customerId = rhs.customerId;
        std::cout << "[Item 12] Operator de atribuire apelat pentru Customer: " << name << "\n";
        return *this;
    }

    std::string getName() const { return name; }
    int getId() const { return customerId; }

};

class PriorityCustomer : public Customer {
    int priorityLevel;

public:
    PriorityCustomer(const std::string& n, int id, int prio)
        : Customer(n, id), priorityLevel(prio) {}

    // CORECT (Item 12): Apelam EXPLICIT constructorul de copiere al clasei de baza!
    // Daca am omite ': Customer(rhs)', partea de baza ar primi valori default ("Anonim", 0).
    PriorityCustomer(const PriorityCustomer& rhs)
        : Customer(rhs), priorityLevel(rhs.priorityLevel) {
        std::cout << "[Item 12 - Derived] PriorityCustomer copy constructor apelat.\n";
    }

    // CORECT (Item 12): Apelam EXPLICIT operator= al clasei de baza!
    PriorityCustomer& operator=(const PriorityCustomer& rhs) {
        std::cout << "[Item 12 - Derived] PriorityCustomer operator= apelat.\n";
        if (this == &rhs) return *this; // Item 11

        Customer::operator=(rhs);       // <--- ESENTIAL: copiaza partea clasei de baza
        priorityLevel = rhs.priorityLevel; // Copiaza membrii proprii

        return *this; // Item 10
    }

    void display() const {
        std::cout << "   Client: " << getName()
                  << " | ID: " << getId()
                  << " | Prioritate: " << priorityLevel << "\n";
    }

};