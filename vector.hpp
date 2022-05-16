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

    // Default constructor
    Vector() { create(); }

    explicit Vector(size_type n, const T &val = T{}) { create(n, val); }

    Vector(const Vector &vector) {
        create(vector.begin(), vector.end());
    }

    // Destructor
    ~Vector() { uncreate(); }

    size_type size() const { return limit - data; }

    T &operator[](size_type i) { return data[i]; }

    const T &operator[](size_type i) const { return data[i]; }

    iterator begin() { return data; };

    const_iterator begin() const { return data; }

    iterator end() { return limit; }

    const_iterator end() const { return limit; }


    Vector &operator=(const Vector &x) {
        if (&x != this) {
            uncreate();
            create(x.begin(), x.end());
        }

        return *this;
    }

    void push(const T &val) {
        if (avail == limit)
            grow();
        unchecked_append(val);
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
        iterator new_available = uninitialized_copy(data, avail, new_data);

        uncreate();

        data = new_data;
        avail = new_available;
        limit = new_data + new_size;
    }

    void unchecked_append(const T &value) {
        alloc.construct(avail++, value);
    }

};