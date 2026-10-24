#include <iostream>
#include <utility>
#include "DataBuffer.h"

int main()
{
    std::cout << "--Creare obiect nou---\n";
    DataBuffer buf1(5);
    buf1.setValue(0,50);
    buf1.setValue(1,100);
    buf1.print();

    std::cout <<"\n---Copy Constructor---\n";
    DataBuffer buf2 = buf1;
    buf2.setValue(0, 999);
    std::cout << "Buf1 dupa modificarea Buf2 ";
    buf1.print();
    std::cout << "Buf2 modificat";
    buf2.print();

    std::cout << "\n--- Move Constructor---\n";
    DataBuffer buf3 = std::move(buf1);
    std::cout<< "Buf3 - preluat de la buf1";
    buf3.print();

    std::cout << "\n---Iesire din program (apelare destructor)--\n";
    return 0;
}