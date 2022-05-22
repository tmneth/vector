#pragma once

#include <memory>
#include <exception>
#include <limits>
#include <iostream>

template<class T>

class myVector {

public:
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef const size_t size_type;
    typedef T value_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef std::allocator<T> allocator_type;

    // Member functions (constructor, destructor, operator=, assign, get_allocator)

    // Constructor. Constructs an empty myVector container
    myVector() { create(); }

    // Destructor. Deallocates memory and do other cleanup when the object is destroyed
    ~myVector() { uncreate(); }

    // Fills empty Vector container with the 'size' number of 'val' copies
    explicit myVector(size_type container_size, const T &val = T{}) { create(container_size, val); }

    // Initializes Vector from an array
    myVector(const std::initializer_list<T> list) {
        create(list.begin(), list.end());
    }

    // Copies Constructor
    myVector(const myVector &myVector) {
        create(myVector.begin(), myVector.end());
    }


    // Assignment operators
    void assign(size_type container_size, const T &val = T{}) {
        uncreate();
        create(container_size, val);
    }

    void assign(std::initializer_list<value_type> list) {
        uncreate();
        create(list.begin(), list.end());
    }


    // Returns the allocator associated with the container.
    allocator_type get_allocator() const { return alloc; };



    // Element access  functions (at, operator[], front, back)



    // Returns a reference to the element at specified location position. Bounds checking is performed.
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

    // Returns a reference to the element at specified location position. Bounds checking is performed.
    const_reference at(size_type index) const {
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

    // Returns a reference to the element at specified location pos. Bounds checking is performed.
    T &operator[](size_type index) {
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

    // Returns a reference to the element at specified location pos. Bounds checking is performed.
    const T &operator[](size_type index) const {
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

    // Returns a reference to the first element in the container.
    reference front() { return *data; }

    const_reference front() const { return *data; }

    // Returns a reference to the last element in the container.
    reference back() { return *(avail - 1); }

    const_reference back() const { return *(avail - 1); }



    // Iterators (begin, end, rbegin, rend)



    // Returns an iterator to the first element of the vector.
    iterator begin() { return data; };
    const_iterator begin() const { return data; }

    // Returns an iterator to the element following the last element of the vector.
    iterator end() { return avail; }
    const_iterator end() const { return avail; }

    // Returns a reverse iterator to the first element of the reversed vector.
    // It corresponds to the last element of the non-reversed vector.
    reverse_iterator rbegin() { return reverse_iterator(avail); }
    const_reverse_iterator rbegin() const { return reverse_iterator(avail); }

    // Returns a reverse iterator to the element following the last element of the reversed vector.
    // It corresponds to the element preceding the first element of the non-reversed vector.
    reverse_iterator rend() { return reverse_iterator(data); }
    const_reverse_iterator rend() const { return reverse_iterator(data); }



    //  Capacity (empty, size, max_size, reserve, capacity, shrink_to_fit)



    // Checks if the container has no elements, i.e. whether begin() == end().
    bool empty() { return !size(); }

    // Returns the number of elements in the container, i.e. std::distance(begin(), end()).
    size_type size() const { return avail - data; }

    // Returns the maximum number of elements the container is able to hold
    // https://stackoverflow.com/questions/7949486/how-is-max-size-calculated-in-the-function-max-size-in-stdlist
    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max();
    }

    // Increases the capacity of the vector.
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

    // Returns the number of elements that the container has currently allocated space for.
    size_type capacity() const { return limit - data; }

    // Requests the removal of unused capacity.
    void shrink_to_fit() { if (limit > avail) limit = avail; }



    // Modifiers (clear, insert, erase, push_back, pop_back, resize, swap)



    // Erases all elements from the container. After this call, size() returns zero.
    void clear() { uncreate(); }

    // Appends the given element value to the end of the container.
    void push_back(const T &val) {
        if (avail == limit)
            grow();
        unchecked_append(val);
    }

    // Removes the last element of the container.
    void pop_back() {
        iterator new_avail = avail;
        alloc.destroy(--new_avail);
        avail = new_avail;
    }

private:
    iterator data;
    iterator limit;
    iterator avail;
    std::allocator<T> alloc;

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
        limit = avail = std::uninitialized_copy(i, j, data);
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

    void grow(size_type n = 1) {
        size_type new_size = std::max(2 * (limit - data), ptrdiff_t(n));
        iterator new_data = alloc.allocate(new_size);
        iterator new_avail = std::uninitialized_copy(data, avail, new_data);

        uncreate();

        data = new_data;
        avail = new_avail;
        limit = new_data + new_size;
    }

    // Insert new element at the end
    void unchecked_append(const T &value) {
        alloc.construct(avail++, value);
    }

};