#pragma once
#include <iterator>
#include <stdexcept>

using namespace std;

//fixed warnings
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
    size_t capacity_size;
    size_t index;
    size_t beginning;

public:

    Iterator(pointer _data, size_t _capacity_size, size_t _index, size_t _head) 
        : data{ _data }, capacity_size{ _capacity_size }, index{ _index }, beginning{ _head }
    {}

    pointer address() {
        return std::addressof(data[(beginning + index) % capacity_size]);
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
        index++; 
        return *this;
    }
    Iterator& operator--()
    {
        index--; 
        return *this;
    }


    Iterator operator++(int) {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }
    Iterator operator--(int) {
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

    reference operator[](difference_type n) { 
        return *(Iterator{ *this }.operator+=(n)); 
    }
};

template<class T>
class CircularBuffer
{
public:

    CircularBuffer(const CircularBuffer&);
    CircularBuffer(size_t capacity = 10);
    ~CircularBuffer();

    CircularBuffer& operator=(const CircularBuffer&);
    T operator[](size_t) const;
    T& operator[](size_t);

    void changeCapacity(size_t);
    void addFirst(const T&);
    void addLast(const T&);
    void delFirst();
    void delLast();
    const T& first() const;
    const T& last() const;
    size_t size() const;

    Iterator<T> begin();
    Iterator<T> end();
    Iterator<const T> begin() const;
    Iterator<const T> end() const;
private:

    size_t temp_buf_size;
    size_t _head;
    size_t tail_x;
    size_t _capacity;
    T* _elements;
};


template<typename T>
CircularBuffer<T>::CircularBuffer(size_t capacity) :
    temp_buf_size{ 0 },
    _head{ 0 },
    tail_x{ 0 },
    _capacity{ capacity + 1 },
    _elements{ new T[capacity + 1] } {}


template<typename T>
CircularBuffer<T>::CircularBuffer(const CircularBuffer& another) :
    temp_buf_size{ another.temp_buf_size },
    _head{ another._head },
    tail_x{ 0 },
    _capacity{ another._capacity },
    _elements{ new T[temp_buf_size] }
{
    for (size_t i = 0; i < temp_buf_size; i++) { (*this)[i] = another[i]; }
}

template<typename T>
CircularBuffer<T>::~CircularBuffer() { delete[] _elements; }

template<typename T>
CircularBuffer<T>& CircularBuffer<T>::operator=(const CircularBuffer<T>& another)
{
    if (this == &another) return *this;

    delete[] _elements;
    temp_buf_size = another.size;
    _head = another._head;
    _elements = new T[temp_buf_size];
    for (size_t i = 0; i < temp_buf_size; i++) { (*this)[i] = another[i]; }

    return *this;
}

template<typename T>
T CircularBuffer<T>::operator[](size_t index) const
{
    if (temp_buf_size == 0)
        throw std::out_of_range("trying to work with an empty container");
    if (index >= temp_buf_size)
        throw std::range_error("given index is out of range, index range from 0 to " + std::to_string(this->temp_buf_size-1) +
        "but input index is" + std::to_string(index));
    return _elements[(_head + (index % temp_buf_size)) % _capacity];
}

//fixed more information in exceptions
template<typename T>
T& CircularBuffer<T>::operator[](size_t index)
{
    if (temp_buf_size == 0)
        throw std::out_of_range("trying to work with an empty container");
    if (index >= temp_buf_size)
        throw std::range_error("given index is out of range, index range from 0 to " + std::to_string(this->temp_buf_size - 1) +
            " but input index is " + std::to_string(index));
    return _elements[(_head + (index % temp_buf_size)) % _capacity];
}

template<typename T>
void CircularBuffer<T>::changeCapacity(size_t capacity)
{
    if (capacity + 1 < _capacity)
        throw std::length_error("_capacity can\'t be less");

    T* temp = new T[capacity + 1];

    for (size_t i = 0; i < temp_buf_size; i++) {
        temp[i] = (*this)[i];
    }
    delete[] _elements;
    _elements = temp;
    _capacity = capacity + 1;
    _head = 0;
    tail_x = temp_buf_size % _capacity;
}

template<typename T>
void CircularBuffer<T>::addFirst(const T& first_element)
{
    _head = (_capacity + _head - 1) % _capacity;
    _elements[_head] = first_element;

    if (temp_buf_size == _capacity - 1) {
        tail_x = (tail_x - 1 + _capacity) % _capacity;
    }
    else {
        temp_buf_size++;
    }
}

template<typename T>
void CircularBuffer<T>::addLast(const T& last_element)
{
    _elements[tail_x] = last_element;
    tail_x = (tail_x + 1) % _capacity;

    if (temp_buf_size == _capacity - 1) {
        _head = (_head + 1) % _capacity;
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
        _head = (_head + 1) % _capacity;
    }
}

template<typename T>
void CircularBuffer<T>::delLast()
{
    if (temp_buf_size > 0) {
        temp_buf_size--;
        tail_x = (tail_x + _capacity - 1) % _capacity;
    }
}

template<typename T>
const T& CircularBuffer<T>::first() const
{
    return _elements[_head];
}

template<typename T>
const T& CircularBuffer<T>::last() const
{
    return _elements[(_head + temp_buf_size - 1) % _capacity];
}

template<typename T>
size_t CircularBuffer<T>::size() const
{
    return temp_buf_size;
}

template<typename T>
Iterator<const T> CircularBuffer<T>::begin() const
{
    return Iterator<const T>{ _elements, _capacity, 0, _head };
}

template<typename T>
Iterator<const T> CircularBuffer<T>::end() const
{
    return Iterator<const T>{ _elements, _capacity, temp_buf_size, _head };
}

template<typename T>
Iterator<T> CircularBuffer<T>::begin()
{
    return Iterator<T>{ _elements, _capacity, 0, _head };
}

template<typename T>
Iterator<T> CircularBuffer<T>::end()
{
    return Iterator<T>{ _elements, _capacity, temp_buf_size, _head };
}