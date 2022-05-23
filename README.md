# Custom Vector Class

## Execution time

Difference in the execution time between `std::vector` and `custom vector class` using `.push_back()`

| Data Structure | 10000 | 100000    | 1000000    | 10000000   |  100000000   | Total |
|----------------|-------|-----|-----|-----|-----|-------|
| std::vector    | 0.000168177s |  0.00106654s   |  0.0110924s   |   0.11851s  |  1.10713s   |    1.23796s   |
| MyVector       | 0.000121105s  | 0.00114462s    |  0.0110208s   |  0.136773s   |  1.27128s   |    1.42034s   |

Number of times .size() was equal to .capacity() 

| Data Structure | 10000        | 100000      | 1000000    | 10000000  | 100000000 | Total |
|----------------|--------------|-------------|------------|-----------|-----------|-------|
| std::vector    | 14           | 3           | 3          | 4         | 3         | 27    |
| MyVector       | 14 |  17| 20 | 24 | 27| 102   |

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

## .at()

Returns a reference to the element at specified location position. Bounds checking is performed

### Method

```cpp 
reference at(size_type index) {
    try {
        if (index >= size() || index < 0)
            throw std::domain_error("specified index is out of range");
        else
            return data[index];
    }
    catch (std::domain_error &e) {
        std::cerr << "Terminate called after: " << e.what() << std::endl;
     };
}
```

### Usage example

```cpp
MyVector<int> example (10, 20);

std::cout << "Element at 5th index is: " << MyVector.at(5) << std::endl; // 10
```

###        

## .reserve()

Increases the capacity of the vector

### Method

```cpp 
void reserve(size_type new_cap) {
    try {
        if (new_cap > max_size())
            throw std::length_error("new capacity exceeds maximum vector size");
        else if (capacity() < new_cap) grow(new_cap);
    }
    catch (std::length_error &e) {
        std::cerr << "Terminate called after: " << e.what() << std::endl;
    };
}
```

### Usage example

```cpp
MyVector<int> example (10, 5);

std::cout << "The capacity of the vector is: " << example.capacity() << std::endl; // 10

example.reserve(80);

std::cout << "The capacity of the vector is: " << example.capacity() << std::endl; // 80
```

### Project Setup

Navigate to the directory of choice and clone the project

```bash
git clone https://github.com/tmneth/vector.git
```

Compile the program

```bash
cd vector/src && g++ 'main.cpp' -o 'main' && ./main
```

