#include <iostream>
#include <vector>
#include "vector.hpp"
#include "timer.hpp"

template<typename Container>
void benchmark(bool customVector) {

    Container v;
    Timer clock;

    double duration, totalDuration = 0;

    int vectorSize[5] = {10000, 100000, 1000000, 10000000, 100000000};

    std::cout << "Filling " << (customVector ? "custom vector class" : "std::vector") << "...\n";

    for (int currentSize: vectorSize) {

        for (int i = 0; i < currentSize; ++i)
            v.push_back(i);

        duration = clock.elapsed();
        totalDuration += duration;

        std::cout << "To push_back() " << currentSize << " elements it takes: " << duration << "s.\n";
        clock.reset();
        v.clear();

    }
    std::cout << "Total time: " << totalDuration << "s.\n";

}

int main() {

    benchmark<std::vector<int>>(false);
    benchmark<myVector<int>>(true);

    return 0;
}
