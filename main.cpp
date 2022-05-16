#include <iostream>
#include "vector.hpp"
#include "timer.hpp"

using namespace std;

int main() {
    // initialize custom vector class
    Vector<int> customVector;
    cout << "Methods in question:\n";
    for (int i = 0; i < 10; ++i)
        customVector.push(i);

    for (auto i: customVector)
        cout << i << " ";

    cout << "\nVector size is: " << customVector.size() << endl;

    return 0;
}
