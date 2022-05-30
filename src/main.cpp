#include <iostream>
#include <vector>
#include "vector.hpp"
#include "timer.hpp"

template<typename Container>
void benchmark() {

    Timer clock;

    double duration, totalDuration = 0;

    int vectorSize[5] = {10000, 100000, 1000000, 10000000, 100000000};

    for (int currentSize: vectorSize) {
        Container v;
        int capacitySize = 0;
        for (int i = 0; i < currentSize; ++i) {
            v.push_back(i);
            if (v.size() == v.capacity()) {
                capacitySize++;
            }
        }
        duration = clock.elapsed();
        totalDuration += duration;

        std::cout << "To push_back() " << currentSize << " elements it takes: " << duration << "s.\n";
        std::cout << "Number of times .capacity() = .size(): " << capacitySize << "\n";
        clock.reset();
    }
    std::cout << "Total time: " << totalDuration << "s.\n";

}

int main() {

    std::cout << "Filling std::vector...\n";
    benchmark<std::vector<int>>();
    std::cout << "Filling custom vector class...\n";
    benchmark<MyVector<int>>();

    return 0;
}
