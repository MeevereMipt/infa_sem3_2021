#include <iostream>

#include "containers/set.h"
using containers::set::Set;

using std::cout;
using std::endl;

int main() {
    cout << "Hello, World!" << endl;

    Set<int> test(1);
    cout << test << endl;

    List<int> test2;
    test2.push_bottom(2);
    cout << test2 << endl;

    test2 = test.to_list();
    cout << test2 << endl;

    cout << test.to_list() << endl;

    return 0;
}
