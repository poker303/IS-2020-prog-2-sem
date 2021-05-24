#pragma once
#include <iterator>
#include <stdexcept>

using namespace std;

template <class T>
class Iterator
{
public:

    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;

private:

    pointer data;
    size_t capacity_size, beginning, index;

public:

    Iterator(pointer data_x, size_t capacity_size_x, size_t index_x, size_t head_x): 

        data{ data_x }, 
        capacity_size{ capacity_size_x }, 
        index{ index_x }, 
        beginning{ head_x }{}

    pointer location() { 
        return locationof(data[(beginning + index) % capacity_size]);
    }

    bool operator==(const Iterator& right_side) const { 
        return index == right_side.index; 
    }

    bool operator!=(const Iterator& right_side) const { 
        return !operator==(right_side); 
    }

    reference operator*() { 
        return data[(beginning + index) % capacity_size];
    }

    pointer operator->() { 
        return  data + (beginning + index) % capacity_size;
    }


    Iterator& operator++()
    {
        index++; return *this;
    }
    Iterator& operator--()
    {
        index--; return *this;
    }


    Iterator  operator++(int) { 
        Iterator temp = *this; 
          ++(*this); 
        return temp; 
    }
    Iterator  operator--(int) { 
        Iterator temp = *this; 
          --(*this); 
        return temp; 
    }


    Iterator operator+(difference_type n) const {
        Iterator temp = *this; 
        return temp.operator+=(n); 
    }
    Iterator operator-(difference_type n) const {
        Iterator temp = *this; 
        return temp.operator-=(n); 
    }

    friend Iterator operator+(difference_type n, const Iterator& it) { return it.operator+(n); }
    difference_type operator-(const Iterator& right_side) const { return index - right_side.index; }

    bool operator< (const Iterator& right_side) const { return index < right_side.index; }
    bool operator> (const Iterator& right_side) const { return index > right_side.index; }
    bool operator<=(const Iterator& right_side) const { return index <= right_side.index; }
    bool operator>=(const Iterator& right_side) const { return index >= right_side.index; }

    Iterator& operator+=(difference_type n)
    {
        operator-=(-n);
        return *this;
    }

    Iterator& operator-=(difference_type n)
    {
        index -= n;
        return *this;
    }

    reference operator[](difference_type n) { return *(Iterator{ *this }.operator+=(n)); }
};

template<class T>
class CircularBuffer
{
private:

    size_t temp_buf_size;         
    size_t head_x;         
    size_t tail_x;         
    size_t cap_buf;     
    T* elements;

public:

    CircularBuffer(const CircularBuffer&);
    CircularBuffer(size_t capacity = 10);
    ~CircularBuffer();

    CircularBuffer& operator=(const CircularBuffer&);
    T operator[](size_t) const;
    T& operator[](size_t);

    void changeCapacity(size_t);
    void addLast(const T&);
    void delLast();
    void addFirst(const T&);
    void delFirst();
    const T& first() const;
    const T& last() const;
    size_t size() const;

    Iterator<T> begin();
    Iterator<T> end();
    Iterator<const T> begin() const;
    Iterator<const T> end() const;
};


template<typename T>
CircularBuffer<T>::CircularBuffer(size_t capacity) :
    temp_buf_size{0},
    head_x{0},
    tail_x{0},
    cap_buf{ capacity + 1 },
    elements{ new T[capacity + 1] } {}


template<typename T>
CircularBuffer<T>::CircularBuffer(const CircularBuffer& another) :
    temp_buf_size{ another.temp_buf_size },
    head_x{ another.head_x },
    tail_x{0},
    cap_buf{ another.cap_buf },
    elements{ new T[temp_buf_size] }
{
    for (size_t i = 0; i < temp_buf_size; i++) { (*this)[i] = another[i]; }
}

template<typename T>
CircularBuffer<T>::~CircularBuffer() { delete[] elements; }

template<typename T>
CircularBuffer<T>& CircularBuffer<T>::operator=(const CircularBuffer<T>& another)
{
    if (this == &another) return *this;

    delete[] elements;
    temp_buf_size = another.size;
    head_x = another.head_x;
    elements = new T[temp_buf_size];
    for (size_t i = 0; i < temp_buf_size; i++) { (*this)[i] = another[i]; }

    return *this;
}

template<typename T>
T CircularBuffer<T>::operator[](size_t index) const
{
        if (temp_buf_size == 0)
            throw std::out_of_range("trying to work with an empty container");
        if (index >= temp_buf_size)
            throw std::out_of_range("given index is out of range");
        return elements[(head_x + (index % temp_buf_size)) % cap_buf];
}

template<typename T>
T& CircularBuffer<T>::operator[](size_t index)
{
    if (temp_buf_size == 0)
        throw std::out_of_range("trying to work with an empty container");
    if (index >= temp_buf_size)
        throw std::out_of_range("given index is out of range");
    return elements[(head_x + (index % temp_buf_size)) % cap_buf];
}

template<typename T>
void CircularBuffer<T>::changeCapacity(size_t capacity)
{
    if (capacity + 1 < cap_buf)
        throw std::length_error("cap_buf cann\'t be less");

    T* temp = new T[capacity + 1];

    for (size_t i = 0; i < temp_buf_size; i++) {
        temp[i] = (*this)[i];
    }
    delete[] elements;
    elements = temp;
    cap_buf = capacity + 1;
    head_x = 0;
    tail_x = temp_buf_size % cap_buf;
}

template<typename T>
void CircularBuffer<T>::addFirst(const T& first_element)
{
    head_x = (cap_buf + head_x - 1) % cap_buf;
    elements[head_x] = first_element;

    if (temp_buf_size == cap_buf - 1) {
        tail_x = (tail_x - 1 + cap_buf) % cap_buf;
    }
    else {
        temp_buf_size++;
    }
}

template<typename T>
void CircularBuffer<T>::addLast(const T& last_element)
{
    elements[tail_x] = last_element;
    tail_x = (tail_x + 1) % cap_buf;

    if (temp_buf_size == cap_buf - 1) {
        head_x = (head_x + 1) % cap_buf;
    }
    else {
        temp_buf_size++;
    }
}

template<typename T>
void CircularBuffer<T>::delFirst()
{
    if (temp_buf_size > 0) {
        temp_buf_size--;
        head_x = (head_x + 1) % cap_buf;
    }
}

template<typename T>
void CircularBuffer<T>::delLast()
{
    if (temp_buf_size > 0) {
        temp_buf_size--;
        tail_x = (tail_x + cap_buf - 1) % cap_buf;
    }
}

template<typename T>
const T& CircularBuffer<T>::first() const
{ return elements[head_x]; }

template<typename T>
const T& CircularBuffer<T>::last() const
{ return elements[(head_x + temp_buf_size - 1) % cap_buf]; }

template<typename T>
size_t CircularBuffer<T>::size() const
{ return temp_buf_size; }

template<typename T>
Iterator<const T> CircularBuffer<T>::begin() const
{ return Iterator<const T>{ elements, cap_buf, 0, head_x }; }

template<typename T>
Iterator<const T> CircularBuffer<T>::end() const
{ return Iterator<const T>{ elements, cap_buf, temp_buf_size, head_x }; }

template<typename T>
Iterator<T> CircularBuffer<T>::begin()
{ return Iterator<T>{ elements, cap_buf, 0, head_x }; }

template<typename T>
Iterator<T> CircularBuffer<T>::end()
{ return Iterator<T>{ elements, cap_buf, temp_buf_size, head_x }; }
