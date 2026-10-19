#include <iostream>
#include "math_utils.h"

int main() {
    int a=6;
    int b=7;

    std::cout << "Suma dintre " << a << " si " << b << " este " << MathUtils::add(a,b) << std::endl;
    std::cout << "produsul dintre " << a << " si " << b << " este " << MathUtils::multiply(a,b) << std::endl;

    return 0;
}