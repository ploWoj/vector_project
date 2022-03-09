#pragma once 

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>


namespace nstd 
{

template <typename T, typename U>
concept SameType = std::is_same_v<std::remove_cvref<T>, std::remove_cvref_t<U>>;

template <typename T, typename Allocator = std::allocator<T>> 
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
    if(front_) {
        std::destroy_n(front_,size_);
        all
    }
}


vector& operator= (const vector<T>& copy)
{
    swap(*this, copy);
    return *this;
}


vector& operator= (vector<T>&& move) noexcept
{
    swap(*this, move);
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

T& operator[](size_t index)                 {   return data_[index]; }
const T& operator[](size_t index) const     {   return data_[index]; }
T& front()                                  {   return data_[0]; }
const T& front() const                      {   return data_[0]; }
T& back()                                   {   return data_[size_ -1]; }
const T& back() const                       {   return data_[size_ -1]; }
T* data() noexcept                          {   return data_; }
const T* data() const noexcept              {   return data_; }


// Capacity
size_t size() const                         { return size_;};
size_t capacity() const                     { return capacity_; };
bool empty() const                          { return begin() == end(); }

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
    
    reserveCapacity(capacity_);
}


// Modifiers
void clear()
{
    for(T* it = data_; it != data_+size_; ++it)
    {
        it->~T();
    }
    size_ = 0;
}

T* insert(T* pos, const T& value)
{
    emplace(pos, value);

}
T* insert(const T* pos, const T& value)
{
    emplace(pos, value);
}
T* insert(const T* pos, T&& value)
{
    emplace(pos, std::move(value));
}
void insert(T* pos, size_t count, const T& value);


T* erase(const T* pos);
T* erase(const T* first, const T* last);


template <typename... Args> 
T& emplace_back(Args&&... args)
{
    if (size_ >= capacity_ )
    {
        resizeIfRequire();
    }
    
    data_[size_] = T(std::forward<Args>(args)...);
    return data_[size_++];
}

template <typename... ARGS>
T* emplace(const T* position, ARGS&&... args)
{   
    const auto distance = position - cbegin();
    if (distance  == capacity_)
    {
        emplace_back(T(std::forward<ARGS>(args)...));
    }
    
    if (size_  == capacity_)
    {
        resizeIfRequire();
    }

    std::move_backward(begin() + distance, end(), end() + 1);
    

    auto iter = &data_[distance];

    *iter = T(std::forward<ARGS>(args)...);
    size_++;
    return iter;
}

void push_back(const T& value)
{
    resizeIfRequire();
    new (data_ + size_) T(value);
    ++size_;
}

// void push_back(T&& value);

void pop_back()
{
    if (this->empty()) {
        throw   std::out_of_range("Out of Range");
    }
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
        reserveCapacity(newSize);
    }
    size_ = newSize;
    
}


private: 
Allocator alloc_;
size_t size_ {0};
size_t capacity_{0};
T* front_ {nullptr};

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
        size_t newCapacity = capacity_ * 1.5 + 1;
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