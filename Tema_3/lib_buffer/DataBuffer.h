#ifndef DATABUFFER_H
#define DATABUFFER_H

#include <iostream>

class DataBuffer {

    private:
    //Incapsulare: datele membre sunt private
    int* data;
    size_t size;
    
    public:
    DataBuffer(size_t bufferSize); //constructorul normal

    DataBuffer(const DataBuffer &other); //copy constructor

    DataBuffer(DataBuffer &&other) noexcept; // move constructor

    ~DataBuffer(); //destructor

    void setValue(size_t index, int value);
    int getValue(size_t index) const;
    void print() const;
};

#endif