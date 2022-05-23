#pragma once

#include <memory>
#include <exception>
#include <limits>
#include <iostream>

template<class T>

class MyVector {

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

    // Constructor. Constructs an empty MyVector container
    MyVector() { create(); }

    // Destructor. Deallocates memory and do other cleanup when the object is destroyed
    ~MyVector() { uncreate(); }

    // Fills empty Vector container with the 'size' number of 'val' copies
    explicit MyVector(size_type container_size, const T &val = T{}) { create(container_size, val); }

    // Initializes Vector from an array
    MyVector(const std::initializer_list<T> list) {
        create(list.begin(), list.end());
    }

    // Copies Constructor
    MyVector(const MyVector &v) {
        create(v.begin(), v.end());
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



    // Returns a reference to the element at specified location pos. Bounds checking is performed.
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

    // Returns a reference to the element at specified location pos. Bounds checking is performed.
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

    const_iterator begin() const { return data; };

    const_iterator cbegin() const { return data; }

    // Returns an iterator to the element following the last element of the vector.
    iterator end() { return avail; }

    const_iterator end() const { return avail; };

    const_iterator cend() const { return avail; }

    // Returns a reverse iterator to the first element of the reversed vector.
    // It corresponds to the last element of the non-reversed vector.
    reverse_iterator rbegin() { return reverse_iterator(avail); }

    const_reverse_iterator rbegin() const { return reverse_iterator(avail); }

    const_reverse_iterator crbegin() const { return reverse_iterator(avail); }

    // Returns a reverse iterator to the element following the last element of the reversed vector.
    // It corresponds to the element preceding the first element of the non-reversed vector.
    reverse_iterator rend() { return reverse_iterator(data); }

    const_reverse_iterator rend() const { return reverse_iterator(data); }

    const_reverse_iterator crend() const { return reverse_iterator(data); }



    //  Capacity (empty, size, max_size, reserve, capacity, shrink_to_fit)



    // Checks if the container has no elements, i.e. whether begin() == end(), !size.
    bool empty() { return begin() == end(); }

    // Returns the number of elements in the container, i.e. std::distance(begin(), end()).
    size_type size() const { return avail - data; }

    // Returns the maximum number of elements the container is able to hold.
    // https://stackoverflow.com/questions/7949486/how-is-max-size-calculated-in-the-function-max-size-in-stdlist
    size_type max_size() const {
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
    void shrink_to_fit() {
        if (limit > avail)
            limit = avail;
    }

    value_type *access_data() {
        return data;
    }


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

    // Erases the specified elements from the container.
    iterator erase(iterator pos) {
        try {
            if (pos < data || pos > avail)
                throw std::out_of_range("index is out of range");

            iterator new_avail = std::uninitialized_copy(pos + 1, avail, pos);
            alloc.destroy(avail + 1);

            avail = new_avail;

            return pos;
        } catch (std::domain_error &e) {
            std::cerr << "Terminate called after: " << e.what() << std::endl;
        }
    }

    // Inserts elements at the specified location in the container.
    void insert(const_iterator pos, const T &value) {
        try {
            if (pos < data || pos >= avail)
                throw std::out_of_range{"insert is out of range"};
            int pos_integer = 0;
            for (iterator i = data; i < pos; i++)
                pos_integer++;

            size_type new_size = size() + 1;
            iterator new_data = alloc.allocate(new_size);
            iterator new_avail = std::uninitialized_copy(data, avail + 1, new_data);

            new_data[pos_integer] = value;
            int after_pos = pos_integer + 1;
            int new_last = size() + 1;

            for (int i = after_pos; i < new_last; i++)
                new_data[i] = data[i - 1];

            uncreate();
            data = new_data;
            avail = new_avail;
            limit = data + new_size;

        } catch (std::domain_error &e) {
            std::cerr << "Terminate called after: " << e.what() << std::endl;
        };
    }


    // Exchanges the contents of the container with those of other.
    void swap(MyVector<T> &other) {
        iterator temp = data;
        data = other.data;
        other.data = temp;

        temp = avail;
        avail = other.avail;
        other.avail = temp;

        temp = limit;
        limit = other.limit;
        other.limit = temp;
    }

    // Checks if the contents of lhs and rhs are equal, that is, they have the same number of elements and each element
    // in lhs compares equal with the element in rhs at the same position.

    bool operator==(const MyVector<T> &rhs) const {
        return size() == rhs.size() && std::equal(begin(), end(), rhs.begin());
    }

    bool operator!=(const MyVector<T> &rhs) { return !(*this == rhs); }

    // Compares the contents of lhs and rhs lexicographically. The comparison is performed by a function equivalent to std::lexicographical_compare.

    bool operator<(const MyVector<T> &rhs) {
        return std::lexicographical_compare(begin(), end(), rhs.begin(), rhs.end());
    }

    bool operator>(const MyVector<T> &rhs) {
        return std::lexicographical_compare(rhs.begin(), rhs.end(), begin(), end());
    }

    bool operator<=(const MyVector<T> &rhs) { return !(*this > rhs); }

    bool operator>=(const MyVector<T> &rhs) { return !(*this < rhs); }


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