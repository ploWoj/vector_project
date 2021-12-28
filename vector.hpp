#pragma once 

#include <algorithm>
#include <iterator>
#include <iostream>
#include <exception>
#include <memory>


namespace nstd 
{


template <typename T> 
class vector
{
public:

    using reference                 = T&;
    using const_reference           = T const&;
    using pointer                   = T*;
    using const_pointer             = T* const; 
    using iterator                  = T*;
    using const_iterator            = T* const;
    using riterator                 = std::reverse_iterator<iterator>;
    using const_riterator           = std::reverse_iterator<const_iterator>;



vector() noexcept = default;

vector(size_t capacity) 
    : capacity_(capacity)
    , size_(0)
    , data_ (static_cast<T*>(::operator new(sizeof(T)* capacity_)))
    {}

vector(const vector& copy)
    : capacity_(copy.capacity_)
    , size_(copy.size_)
    , data_(static_cast<T*>(::operator new(sizeof(T)* capacity_)))
{

    for (size_t i = 0; i < size_; ++i)
    {
        data_[i] = copy.data_[i];
    }
}

vector(vector&& move) noexcept
    : capacity_(0)
    , size_(0)
    , data_(nullptr)
    {
        move.swap(*this, move);
    }

vector(const std::initializer_list<T>& list)
    : size_(list.size())
    , capacity_(list.size())
    , data_(static_cast<T*>(::operator new(sizeof(T)* capacity_)))
{
    for (auto iter = list.begin(), i = 0; iter != list.end(); ++i, ++iter)
    {
        data_[i] = *iter;
    }
}

~vector()
{
    std::unique_ptr<T, Deleter> deleter(data_, Deleter());

    for (size_t loop = 0; loop < size_; loop++)
    {
        data_[size_ - 1 - loop].~T(); 
    }
    
}


vector& operator= (const vector& copy) 
{
    swap(*this, copy);
    return *this;
}


vector& operator= (vector&& copy) 
{
    swap(*this, copy);
    return *this;
}

// Iterators

iterator begin()                    { return data_; }
riterator rbegin()                  { return riterator(end()); }
const_iterator begin() const        { return data_; }
const_riterator rbegin() const      { return const_riterator(end()); }

iterator end()                      { return data_ + size_; }
riterator rend()                    { return riterator(begin()); }
const_iterator end() const          { return data_ + size_; }
const_riterator rend() const        { return const_riterator(begin()); }

const_iterator cbegin() const       { return begin(); }
const_riterator crbegin() const     { return rbegin(); }
const_iterator cend() const         { return end(); }
const_riterator crend() const       { return rend(); }



T& at(size_t index)
{
    validatIndex(index);
    return data_[index];
}

const T& at(size_t index) const 
{
    validatIndex(index);
    return data_[index];
}

T& operator[](size_t index)
{
    return data_[index];
}

const T& operator[](size_t index) const
{
    return data_[index];
}

T& front()
{
    return data_[0];
}

const T& front() const
{
    return data_[0];
}

T& back()
{
    return data_[size_ -1];
}

const T& back() const
{
    return data_[size_ -1];
}

T* data() noexcept
{
    return data_;
}

const T* data() const noexcept 
{
    return data_;
}


// Capacity
size_t size() const        { return size_;};
size_t capacity() const    { return capacity_; };
bool empty() const         { return begin() == end(); }

void reserve(size_t n)   
{
    if (n > capacity_)
    {
        capacity_ = n;
        reserveCapacity(n);
    }
}

void shrink_to_fit()
{
    if ( capacity_ == size_)
    {
        return;
    }

    capacity_ = size_;
    
    T* temp = new T[capacity_];

    for (size_t loop = 0; loop < size_; loop++)
    {
        temp[loop] = data_[loop];
    }
    delete[] data_;
    data_ = temp;
}


// Modifiers
void clear() 
{
    for(T* it = data_; it != data_+size_; ++it)
    {
        it->~T();
    }

    // std::destroy(data_, data_+size_);
    size_ = 0;
}


void push_back(const T& value)
{
    resizeIfRequire();
    pushBackInternal(value);
}

void pop_back()
{
    --size_;
    data_[size_].~T();
}


friend void swap(vector& first, vector& second) noexcept
{   using std::swap;
    swap(first.capacity_,     second.capacity_);
    swap(first.size_,         second.size_);
    swap(first.data_,         second.data_);
}

void resize(size_t newSize)
{
    if ( newSize > capacity_)
    {
        capacity_ = newSize;
            
        T* temp = new T[capacity_];

        for (size_t loop = 0; loop < size_; loop++)
        {
            temp[loop] = data_[loop];
        }
        delete[] data_;
        data_ = temp;
    }
    size_ = newSize;
    
}


private: 
size_t size_ {0};
size_t capacity_{0};
T* data_ {nullptr};

struct Deleter
{
    void operator()(T* data_) const
    {
        ::operator delete(data_);
    }
};

void resizeIfRequire()
{
    if ( size_ == capacity_)
    {
        size_t newCapacity = capacity_ * 1.5;
        reserveCapacity(newCapacity);
    }
}

void reserveCapacity(size_t newCapacity)
{
    vector<T> tmpData(newCapacity);

    std::for_each(data_, data_ + size_, [&tmpData] 
                                        (const T& elemtent)
                                        { return tmpData.push_back(elemtent);});
    
    swap(*this, tmpData);
}

void pushBackInternal(const T& value)
{
    new (data_ + size_) T(value);
    ++size_;
}

void validatIndex(size_t index)
{
    if(index < 0 ||index >= size_)
    {
       throw std::out_of_range("Out of Range");
    }
}
};

}