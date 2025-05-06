#ifndef VECTOR_CPP
#define VECTOR_CPP

#include <iostream>
#include <cassert>

template<class type>
vector<type>::vector() {
    capacity_ = kMinCapacity;
    contents_ = new type[capacity_];
}

template<class type>
vector<type>::vector(const unsigned int size) {
    size_ = capacity_ = size;
    contents_ = new type[capacity_]();
}

template<class type>
vector<type>::vector(const unsigned int size, const type& default_value) {
    size_ = capacity_ = size;
    contents_ = new type[capacity_];
    for (unsigned int i = 0; i < size_; i++) {
        contents_[i] = default_value;
    }
}

template<class type>
vector<type>::vector(const vector<type>& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    contents_ = new type[capacity_];
    for (unsigned int i = 0; i < size_; i++) {
        contents_[i] = other.contents_[i];
    }
}

template<class type>
vector<type>::~vector() {
    size_ = capacity_ = 0;
    delete[] contents_;
}

template<class type>
unsigned int vector<type>::size() const {
    return size_;
}

template<class type>
unsigned int vector<type>::capacity() const {
    return capacity_;
}

template<class type>
bool vector<type>::empty() const {
    return (size_ == 0);
}

template<class type>
void vector<type>::resize(const unsigned int size, const type& default_value) {
    if (size > capacity_) {
        reserve(size);
    }
    if (size > size_) {
        for (unsigned int i = size_; i < size; i++) {
            contents_[i] = default_value;
        }
    }
    size_ = size;
}

template<class type>
void vector<type>::reserve(const unsigned int capacity) {
    if (capacity > capacity_) {
        type * new_contents = new type[capacity];
        for (unsigned int i = 0; i < size_; i++) {
            new_contents[i] = contents_[i];
        }
        delete[] contents_;
        contents_ = new_contents;
        capacity_ = capacity;
    }
}

template<class type>
void vector<type>::shrink_to_fit() {
    if (size_ < capacity_) {
        type * new_contents = new type[size_];
        for (unsigned int i = 0; i < size_; i++) {
            new_contents[i] = contents_[i];
        }
        delete[] contents_;
        contents_ = new_contents;
        capacity_ = size_;
    }
}

template<class type>
void vector<type>::swap(vector<type>& other) {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(contents_, other.contents_);
}

template<class type>
void vector<type>::push_back(const type& x) {
    if (size_ == capacity_) {
        reserve(capacity_ * 2);
    }
    contents_[size_] = x;
    size_++;
}

template<class type>
void vector<type>::pop_back() {
    if (size_ <= capacity_ / 3) {
        reserve(capacity_ / 2);
    }
    size_--;
}

template<class type>
void vector<type>::clear() {
    size_ = 0;
}

template<class type>
type& vector<type>::operator [](const int pos) {
    assert(0 <= pos && pos < size_);
    return contents_[pos];
}

template<class type>
const type& vector<type>:: operator [](const int pos) const {
    assert(0 <= pos && pos < size_);
    return contents_[pos];
}

template<class type>
type& vector<type>::front() {
    assert(!empty());
    return contents_[0];    
}

template<class type>
const type& vector<type>::front() const {
    assert(!empty());
    return contents_[0];
}

template<class type>
type& vector<type>::back() {
    assert(!empty());
    return contents_[size_ - 1];
}

template<class type>
const type& vector<type>::back() const {
    assert(!empty());
    return contents_[size_ - 1];
}

template<class type>
type * vector<type>::begin() {
    assert(!empty());
    return contents_;
}

template<class type>
type * vector<type>::end() {
    assert(!empty());
    return contents_ + size_;
}

template<class type>
void vector<type>::erase(type* begin, type* end) {
    assert(begin >= contents_ && begin < contents_ + size_);
    assert(end >= contents_ && end < contents_ + size_);

    unsigned int new_size = size_ - (end - begin);
    for (type* it = begin; it != contents_ + new_size; it++) {
        *it = *(it + (end - begin));
    }
    size_ = new_size;
}

template<class type>
type * vector<type>::at(const int pos) {
    assert(!empty());
    if (0 <= pos && pos < size_) {
        return contents_ + pos;
    }
    return nullptr;
}

template<class type>
void vector<type>::sort() {
    // bubble sort
    for (unsigned int i = 0; i < size_ - 1; i++) {
        for (unsigned int j = i + 1; j < size_; j++) {
            if (contents_[i] > contents_[j]) {
                std::swap(contents_[i], contents_[j]);
            }
        }
    }
}

template<class type>
void vector<type>::remove_duplicates() {
    for (unsigned int i = 0; i < size_; i++) {
        for (unsigned int j = i + 1; j < size_; j++) {
            if (contents_[i] == contents_[j]) {
                erase(contents_ + j, contents_ + j + 1);
                j--;
            }
        }
    }
}

template<class type>
vector<type>& vector<type>::operator=(const vector<type>& other) {
    if (this != &other) {  // to avoid memory corruption
        delete[] contents_;
        
        size_ = other.size_;
        capacity_ = other.capacity_;
        contents_ = new type[capacity_];
        for (unsigned int i = 0; i < size_; i++) {
            contents_[i] = other.contents_[i];
        }
    }
    return *this;
}

template<class type>
std::ostream& operator<< (std::ostream& out, const vector<type>& to_print) {
    for (int i = 0; i < to_print.size(); i++) {
        out << to_print[i] << " ";
    }
    return out;
}

#endif // VECTOR_CPP