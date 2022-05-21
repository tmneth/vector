#include <iostream>
#include "vector.hpp"
#include "timer.hpp"

using namespace std;

int main() {
    // initialize custom vector class
//    Vector<int> myVector1(20);
    Vector<int> myVector;
//    myVector = {1,2,3};
    cout << "Push elements into the vector:\n";
    for (int i = 0; i < 20; ++i)
        myVector.push(i);

    for (auto i: myVector)
        cout << i << " ";

    cout << "\nPop elements out of the vector\n";
    for (int i = 0; i < 5; ++i)
        myVector.pop();

    for (auto i: myVector)
        cout << i << " ";


    cout << "\nVector size is: " << myVector.size() << endl;

    return 0;
}
