#pragma once

#include <iostream>
#include <memory>
#include <exception>
#include <limits>
#include <cmath>

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

    /**
     * @brief Construct a new Vector object.
     */
    MyVector() { create(); }

    /**
     * @brief Destroy the Vector object.
     */
    ~MyVector() { uncreate(); }

    /**
     * @brief Construct a new Vector object
     *
     * @param n
     * @param val
     */
    explicit MyVector(size_type n, const T &val = T{}) { create(n, val); }

    /**
     * @brief List initializer.
     *
     * @param list
     */
    MyVector(const std::initializer_list<T> list) {
        create(list.begin(), list.end());
    }

    /**
     * @brief Copy constructor.
     *
     * @param v Source object.
     */
    MyVector(const MyVector &v) {
        create(v.begin(), v.end());
    }

    /**
     * @brief Move constructor.
     *
     * @param v
     */
    MyVector(MyVector &&v) noexcept {
        create(v.begin(), v.end());
        v.swap(*this);
    }

    /**
     * @brief Copy assignment operator. Replaces the contents with a copy of the
     * contents of other.
     *
     * @param rhs Container to use as a data source.
     * @return MyVector&
     */
    MyVector &operator=(const MyVector &rhs) {
        if (&rhs != this) {
            uncreate();
            create(rhs.begin(), rhs.end());
        }
        return *this;
    }

    /**
    * @brief Replaces the contents with count copies of value value.
    *
    * @param n
    * @param val
    */
    void assign(size_type n, const T &val = T{}) {
        uncreate();
        create(n, val);
    }

    /**
    * @brief Replaces the contents with the elements from the initializer list.
    *
    * @param list
    */
    void assign(std::initializer_list<value_type> list) {
        uncreate();
        create(list.begin(), list.end());
    }

    /**
    * @brief Returns the allocator associated with the container.
    *
    * @return allocator_type Returns allocator object.
    */
    allocator_type get_allocator() const { return alloc; };

    // Element access  functions.

    /**
    * @brief Returns a reference to the element at specified location pos, with bounds checking.
    *
    * @param index
    * @return data[index]
    */
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

    /**
    * @brief Returns a reference to the element at specified location pos, with bounds checking.
    *
    * @param index
    * @return data[index]
    */
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

    /**
    * @brief Returns a reference to the first element in the container.
    *
    * @return *data
    */
    reference front() { return *data; }

    const_reference front() const { return *data; }

    /**
    * @brief Returns a reference to the last element in the container.
    *
    * @return *(avail - 1)
    */
    reference back() { return *(avail - 1); }

    const_reference back() const { return *(avail - 1); }

    // Iterators.

    iterator begin() { return data; };

    const_iterator begin() const { return data; };

    const_iterator cbegin() const { return data; }

    iterator end() { return avail; }

    const_iterator end() const { return avail; };

    const_iterator cend() const { return avail; }

    reverse_iterator rbegin() { return reverse_iterator(avail); }

    const_reverse_iterator rbegin() const { return reverse_iterator(avail); }

    const_reverse_iterator crbegin() const { return reverse_iterator(avail); }

    reverse_iterator rend() { return reverse_iterator(data); }

    const_reverse_iterator rend() const { return reverse_iterator(data); }

    const_reverse_iterator crend() const { return reverse_iterator(data); }

    //  Capacity.

    /**
    * @brief Checks if the container has no elements, i.e. whether begin() == end().
    *
   * @return true
   * @return false
    */
    bool empty() { return begin() == end(); }

    /**
    * @brief Returns the number of elements in the container, i.e. std::distance(begin(), end()).
    *
   * @return size_type
    */
    size_type size() const { return avail - data; }

    /**
    * @brief Returns the maximum number of elements the container is able to hold due to system or library implementation limitations.
    *
    * @return size_type
    */
    size_type max_size() const {
        return pow(2, sizeof(void *) * 8) / sizeof(T) - 1;
    }

    /**
    * @brief Increase the capacity of the vector (the total number of elements that the vector can hold without requiring reallocation).
    *
    * @param new_cap
    */
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

    /**
    * @brief Returns the number of elements that the container has currently allocated space for.
    *
    * @return size_type
    */
    size_type capacity() const { return limit - data; }

    /**
    * @brief Requests the removal of unused capacity.
    *
    * @return size_type
    */
    void shrink_to_fit() {
        if (limit > avail)
            limit = avail;
    }

    /**
     * @brief Return pointer to the underlying array.
     *
     * @return T*
     */
    T *access_data() {
        return data;
    }


    // Modifiers.

    /**
     * @brief Erases all elements from the container. After this call, size() returns zero.
     */
    void clear() {
        iterator it = avail;
        while (it != data)
            alloc.destroy(--it);
        avail = data;
    }

    /**
     * @brief Appends the given element value to the end of the container. The new
     * element is initialized as a copy of value.
     *
     * @param val Value to append.
     */
    void push_back(const T &val) {
        if (avail == limit)
            grow();
        unchecked_append(val);
    }

    /**
    * @brief Appends the given element value to the end of the container. Value
    * is moved into the new element.
    *
    * @param val
    */
    void push_back(T &&val) {
        if (avail == limit)
            grow();
        unchecked_append(val);
    }

    /**
    * @brief Removes the last element of the container.
    */
    void pop_back() {
        iterator new_avail = avail;
        alloc.destroy(--new_avail);
        avail = new_avail;
    }

    /**
     * @brief Removes the element at pos.
     *
     * @param pos
     *
     * @return iterator
     */
    iterator erase(iterator pos) {
        if (pos < data || pos > avail) {
            throw std::out_of_range("Index out of range");
        }
        iterator new_available = std::uninitialized_copy(pos + 1, avail, pos);
        alloc.destroy(avail + 1);

        avail = new_available;

        return pos;
    }

    /**
    * @brief Removes the elements in the range [first, last).
    *
    * @param first
    * @param last
    *
    * @return iterator
    */
    iterator erase(iterator first, iterator last) {
        if (first < data || last > avail) {
            throw std::out_of_range("Index out of range");
        }

        iterator new_available = std::uninitialized_copy(last, avail, first);

        iterator it = avail;
        while (it != new_available) {
            alloc.destroy(--it);
        }

        avail = new_available;
        return last;
    }

    /**
     * @brief Inserts n copies of the val before position.
     *
     * @param position Iterator before which the content will be inserted.
     * @param n Number of elements to insert
     * @param val Element value to insert
     * @return iterator
     */
    iterator insert(iterator position, size_type n, const value_type &val) {
        if (position < begin() || position >= end()) {
            throw std::out_of_range("Index out of range");
        }

        if (avail + n >= limit) {
            size_type index = position - begin();
            grow();
            position = begin() + index;
        }

        int i = 0;
        for (iterator it(avail + n - 1); it != (position + n - 1); it--, i++) {
            *it = data[size() - i - 1];
        }

        std::uninitialized_fill(position, position + n, val);
        avail += n;

        return position;
    }

    /**
     * @brief Insert a single element.
     *
     * @param position Iterator before which the content will be inserted.
     * @param val Element value to insert.
     * @return iterator.
     */
    iterator insert(iterator position, const value_type &val) {
        return insert(position, 1, val);
    }

    /**
     * @brief Exchanges the contents of the container with those of other.
      Does not invoke any move, copy, or swap operations on individual elements.
     *
     * @param other
     */
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

    /**
     * @brief Resizes the container to contain n elements.
     *
     * @param n
     */
    void resize(size_type n) {
        if (n < size()) {
            avail = data + n;
            iterator it = limit;
            while (it != avail) {
                alloc.destroy(--it);
            }
        } else if (n > capacity()) {
            grow();
            resize(n);
        } else if (n > size()) {
            avail += n - size();
        }
    }


    bool operator==(const MyVector<T> &rhs) const {
        return size() == rhs.size() && std::equal(begin(), end(), rhs.begin());
    }

    bool operator!=(const MyVector<T> &rhs) { return !(*this == rhs); }

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

    void unchecked_append(const T &value) {
        alloc.construct(avail++, value);
    }

};