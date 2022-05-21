#pragma once
#include <memory>

using namespace std;

template<class T>

class Vector {

public:
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef const size_t size_type;
    typedef T value_type;

    // Constructor. Constructs an empty Vector container
    Vector() { create(); }

    // Use rule of three. Copy Constructor, Copy Assignment Operator, Destructor

    // Fill empty Vector container with the 'size' number of 'val' copies
    explicit Vector(size_type container_size, const T &val = T{}) { create (container_size, val); }

    //  Copy Constructor
    Vector(const Vector &vector) {
        create(vector.begin(), vector.end());
    }

    // Destructor. Deallocates memory and do other cleanup for a class object and its class members when the object is destroyed.
    ~Vector() { uncreate(); }


    T &operator[](size_type i) { return data[i]; }
    const T &operator[](size_type i) const { return data[i]; }

    // Iterator pointing at the beginning of the Vector
    iterator begin() { return data; };
    const_iterator begin() const { return data; }

    // Iterator pointing at the end of the Vector
    iterator end() { return avail; }
    const_iterator end() const { return avail; }

    // Space allocated for the Vector class
    size_type capacity() const { return limit - data; }

    // Alternative to std::vector size() method
    size_type size() const { return avail - data; }

    // Alternative to std::vector push_back() method
    void push(const T &val) {
        if (avail == limit)
            grow();
        unchecked_append(val);
    }

    // Alternative to std::vector pop_back() method
    void pop() {
        iterator new_avail = avail;
        alloc.destroy(--new_avail);
        avail = new_avail;
    }

private:
    iterator data;
    iterator limit;
    iterator avail;
    allocator<T> alloc;

    void create() {
        data = avail = limit = nullptr;
    }


    void create(size_type size, const T &value) {
        data = alloc.allocate(size);
        limit = avail = data + size;
        std::uninitialized_fill(data, limit, value);
    }

    void create(const_iterator i, const_iterator j) {
        data = alloc.allocate(j - i);
        limit = avail = uninitialized_copy(i, j, data);
    }


    void uncreate() {
        if (data) {
            iterator it = avail;
            while (it != data) {
                alloc.destroy(--it);
            }
            alloc.deallocate(data, limit - data);
        }
        data = limit = avail = nullptr;
    }

    void grow() {
        size_type new_size = max(2 * (limit - data), ptrdiff_t(1));
        iterator new_data = alloc.allocate(new_size);
        iterator new_avail = uninitialized_copy(data, avail, new_data);

        uncreate();

        data = new_data;
        avail = new_avail;
        limit = new_data + new_size;
    }

    void unchecked_append(const T &value) {
        alloc.construct(avail++, value);
    }

};