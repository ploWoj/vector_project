// #include "vector.hpp"

// template <typename T>
// nstd::vector<T>::vector(size_t capacity)
//     : capacity_(capacity)
//     , size_(0)
//     , data_ (static_cast<T*>(::operator new(sizeof(T)* capacity_)))
//     {}

// template <typename T>
// nstd::vector<T>::vector(const vector& copy)
//     : capacity_(copy.capacity_)
//     , size_(copy.size_)
//     , data_(static_cast<T*>(::operator new(sizeof(T)* capacity_)))
// {

//     for (size_t i = 0; i < size_; ++i)
//     {
//         data_[i] = copy.data_[i];
//     }
// }


// template <typename T>
// nstd::vector<T>::vector(vector&& move) noexcept
//     : capacity_(0)
//     , size_(0)
//     , data_(nullptr)
//     {
//         move.swap(*this, move);
//     }

// template <typename T>
// nstd::vector<T>::vector(const std::initializer_list<T>& list)
//     : size_(list.size())
//     , capacity_(list.size())
//     , data_(static_cast<T*>(::operator new(sizeof(T)* capacity_)))
// {
//     for (auto iter = list.begin(), i = 0; iter != list.end(); ++i, ++iter)
//     {
//         data_[i] = *iter;
//     }
// }

// template <typename T>
// nstd::vector<T>::~vector()
// {
//     std::unique_ptr<T, Deleter> deleter(data_, Deleter());

//     for (size_t loop = 0; loop < size_; loop++)
//     {
//         data_[size_ - 1 - loop].~T(); 
//     }   
// }


// // Element access
// template <typename T>
// T& nstd::vector<T>::at(size_t index)
// {
//     validatIndex(index);
//     return data_[index];
// }

// template <typename T>
// const T& nstd::vector<T>::at(size_t index) const
// {  
//     validatIndex(index);
//     return data_[index];
// }




// // Modifiers


// template <typename T>
// void nstd::vector<T>::clear() 
// {
//     for(T* it = data_; it != data_+size_; ++it)
//     {
//         it->~T();
//     }
//     size_ = 0;
// }



// template <typename T>
// void nstd::vector<T>::push_back(const T& value)
// {
//     resizeIfRequire();
//     new (data_ + size_) T(value);
//     ++size_;
// }


// template <typename T>
// void nstd::vector<T>::pop_back()
// {
//     if (this->empty()) {
//         throw   std::out_of_range("Out of Range");
//     }
//     --size_;
//     data_[size_].~T();
// }


// template <typename T>
// void nstd::vector<T>::resize(size_t newSize)
// {
//     if ( newSize > capacity_)
//     {
//         reserveCapacity(newSize);
//     }
//     size_ = newSize;
    
// }


// template <typename T>
// void nstd::vector<T>::validatIndex(size_t index)
// {
//     if(index < 0 ||index >= size_)
//     {
//        throw std::out_of_range("Out of Range");
//     }
// }

// // template <typename T>
// // void nstd::vector<T>::reserveCapacity(size_t newCapacity)
// // {
// //     vector<T> tmpData(newCapacity);

// //     std::for_each(data_, data_ + size_, [&tmpData] 
// //                                         (const T& elemtent)
// //                                         { return tmpData.push_back(elemtent);});
    
// //     swap(*this, tmpData);
// // }

// // template <typename T>
// // void nstd::vector<T>::resizeIfRequire()
// // {
// //     if ( size_ == capacity_)
// //     {
// //         size_t newCapacity = capacity_ * 1.5;
// //         reserveCapacity(newCapacity);
// //     }
// // }