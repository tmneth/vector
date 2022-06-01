# Custom Vector Class

MyVector is a feature-complete, generic and customizable resizable array implementation in C++ that supports almost the
entire C++ std::vector API.

## Features

- Measurement of the execution time difference between std::vector and custom vector class
- Doxygen documentation describing each and every implemented method
- Unit testing (using <a href="https://github.com/google/googletest">googletest</a>)

## Execution time

Difference in the execution time between `std::vector` and `MyVector` using `.push_back()`

| Data Structure | 10000 | 100000    | 1000000    | 10000000   |  100000000  | Total |
|----------------|-------|-----|-----|-----|-----|-------|
| std::vector    | 0.000174602s |  0.00123856s  | 0.0125634s   |   0.144284s |  1.37746s   |    1.53572s   |
| MyVector       |  0.000134863s  | 0.00139039s    |  0.0136582s  |  0.166781s   |  1.58274s  |    1.76471s   |


# Examples

## .push_back()

Appends the given element value to the end of the container

### Method

```cpp 
void push_back(const T &val) {
    if (avail == limit)
        grow();
    unchecked_append(val);
}
```

### Usage example

```cpp
MyVector<int> example;

for(int i = 0; i < 5; ++i)
    example.push_back(i);

std::cout << "Vector elements: "; // 0  1  2  3  4
for (int i: example) 
    std::cout << i << ' ';


std::cout << "Vector size: " << example.size() << std::endl; // 5
std::cout << "Vector capacity: " << example.capacity() << std::endl; // 8

```

###             

## .pop_back()

Removes the last element of the container

### Method

```cpp 
void pop_back() {
    iterator new_avail = avail;
    alloc.destroy(--new_avail);
    avail = new_avail;
}
```

### Usage example

```cpp
MyVector<int> example {1,2,3,4,5};

example.pop_back();

std::cout << "Vector size: " << example.size() << std::endl; // 4
std::cout << "Vector capacity: " << example.capacity() << std::endl; // 5

```

###             

## .shrink_to_fit()

Requests the removal of unused capacity

### Method

```cpp 
void shrink_to_fit() { 
    if (limit > avail) 
        limit = avail; 
}
```

### Usage example

```cpp
MyVector<int> example {1,2,3,4,5};

example.reserve(500);

std::cout << "Vector size: " << example.size() << std::endl; // 5
std::cout << "Vector capacity: " << example.capacity() << std::endl; // 500

example.shrink_to_fit();

std::cout << "Vector size: " << example.size() << std::endl; // 5
std::cout << "Vector capacity: " << example.capacity() << std::endl; // 5

```

###             

### Project Setup

Navigate to the directory of choice and clone the project

```zsh
git clone https://github.com/tmneth/vector.git
```

Initialise and update google test submodules

```zsh
git submodule init
git submodule update
```

Compile the program

```zsh
cd vector/src && g++ 'main.cpp' -o 'main' && ./main
```

