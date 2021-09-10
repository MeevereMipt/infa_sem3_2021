#include <iostream>

#include "containers/set.h"
using containers::set::Set;

int main() {
    std::cout << "Hello, World!" << std::endl;

    Set<int> test(1);
    std::cout << test;

    return 0;
}
