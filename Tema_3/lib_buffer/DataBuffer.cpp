#include "DataBuffer.h"

//initializare cu 0 date din constructor 
DataBuffer::DataBuffer(size_t bufferSize) : size(bufferSize), data(new int[bufferSize]) {
    std::cout << "[Constructor] Am alocat buffer de dim. " << size << " pe heap. \n";
    for(size_t i = 0; i < size; ++i) {
        data[i] = 0; 
    }
}

// suprascrierea Copy Constructorului - deep copy
DataBuffer::DataBuffer(const DataBuffer &other) : size(other.size), data(new int[other.size]) {
    std::cout << "[Copy Constructor] Deep copy pentru buffer de dim " << size << " \n";
    for(size_t i = 0; i < size; ++i) {
        data[i] = other.data[i]; 
    }
}

//move constructor
DataBuffer::DataBuffer(DataBuffer &&other) noexcept : size(other.size), data(other.data) {
    std::cout << "[Move Constructor] Mutare date. Furt de pointer \n";
    //golim obiectul sursa pentru destructorul sasu sa nu stearga memoria preluata
    other.data = nullptr;
    other.size = 0;
}

//eliberarea heap-ului in cadrul destructorului
DataBuffer::~DataBuffer() {
    if(data != nullptr) {
        std::cout << " [Destructor] Eliberarea memorie heap pt buffer de dim " << size << ".\n";
        delete[] data;
    } else {
        std::cout << " [Destructor] Buffer gol, nu e nevoie de eliberare.\n";
    }
}

void DataBuffer::setValue(size_t index, int value)
{
    if(index < size)
    {
        data[index] = value;
    }
}

int DataBuffer::getValue(size_t index) const {
    if(index < size) 
    {
        return data[index];
    }
    return -1;
}

void DataBuffer::print() const {
    std::cout << "Buffer data: ";
    for(size_t i = 0; i<size; ++i)
    {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";
}