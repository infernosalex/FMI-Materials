#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cassert>
#include <ostream>

// Vector class declaration with template
template<class type>
class vector {
public:
    vector();
    vector(const unsigned int size);
    vector(const unsigned int size, const type& default_value);
    vector(const vector<type>& other);
    ~vector();

    //  assignment operator
    vector<type>& operator=(const vector<type>& other);

    unsigned int size() const;
    unsigned int capacity() const;
    bool empty() const;
    void resize(const unsigned int size, const type& default_value = type());
    // make capacity at least the given capacity
    void reserve(const unsigned int capacity);
    void shrink_to_fit();

    type& front();
    const type& front() const;
    type& back();
    const type& back() const;
    type& operator [](const int pos);
    const type& operator [](const int pos) const;
    type * begin();
    type * end();

    // Const versions for template compatibility
    const type * begin() const;
    const type * end() const;

    void push_back(const type& value);
    void pop_back();
    void clear();

    // not yet implemented
    void erase(type* begin, type* end);

    // extra
    void swap(vector<type>& other);
    type *at(const int pos);
    void remove_duplicates();
    void sort();

private:
    static constexpr unsigned int kMinCapacity = 1;

    // modifies capacity_ => reallocation
    // size_ <= capacity_
    unsigned int size_ = 0;
    unsigned int capacity_ = 0;
    type * contents_;
};

// Non-member functions
template<class type>
std::ostream& operator<< (std::ostream& out, const vector<type>& to_print);

// Include the implementation at the end of the header
#include "vector.cpp"

#endif // VECTOR_H