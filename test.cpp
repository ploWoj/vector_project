#include <gtest/gtest.h>
#include "vector.hpp"


TEST(Vector, vectorCtor)
{
    nstd::vector<int> vec;
    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(0, vec.capacity());
}

TEST(Vector, pushBack)
{
    nstd::vector<int> vec;
    EXPECT_EQ(0, vec.size());
    
    vec.push_back(12);
    EXPECT_EQ(1, vec.size());
}

TEST(Vector, vectorCopyConstructor)
{
    nstd::vector<char> charVector;
    charVector.push_back('W');
    charVector.push_back('o');
    charVector.push_back('j');
    charVector.push_back('t');
    charVector.push_back('e');
    charVector.push_back('k');

    nstd::vector<char> copy(charVector);
    EXPECT_EQ(copy.size(), charVector.size());
    EXPECT_EQ(copy[0], charVector[0]);
    EXPECT_EQ(copy[2], charVector[2]);
    EXPECT_EQ(copy[5], charVector[5]);
}

TEST(Vector, vectorAssigneOperator)
{
    nstd::vector<char> charVector;
    charVector.push_back('W');
    charVector.push_back('o');
    charVector.push_back('j');
    charVector.push_back('t');
    charVector.push_back('e');
    charVector.push_back('k');

    nstd::vector<char> copy = charVector;
    EXPECT_EQ(copy.size(), charVector.size());
    EXPECT_EQ(copy[0], charVector[0]);
    EXPECT_EQ(copy[2], charVector[2]);
    EXPECT_EQ(copy[5], charVector[5]);
}

TEST(Vector, initializerListConstructor)
{
    nstd::vector<int> vector{1, 2, 3, 4};

    EXPECT_EQ(1, vector.at(0));
    EXPECT_EQ(2, vector.at(1));
    EXPECT_EQ(3, vector.at(2));
    EXPECT_EQ(4, vector.at(3));
}

TEST(Vector, vectorShouldReturnAt)
{
    nstd::vector<int> Vector;

    EXPECT_THROW(Vector.at(0), std::out_of_range);
    EXPECT_THROW(Vector.at(10), std::out_of_range);
    EXPECT_THROW(Vector.at(-5), std::out_of_range);

    Vector.push_back(5);
    Vector.push_back(10);
    Vector.push_back(20);
    Vector.push_back(-19);
    Vector.push_back(44);

    EXPECT_EQ(5, Vector.at(0));
    EXPECT_EQ(10, Vector.at(1));
    EXPECT_EQ(20, Vector.at(2));
    

    EXPECT_THROW(Vector.at(5), std::out_of_range);
}

TEST(Vector, accessFront)
{
    nstd::vector<double> Vector;

    Vector.push_back(3.2);
    Vector.push_back(3.4);
    Vector.push_back(2.1);

    EXPECT_EQ(3.2, Vector.front());
}

TEST(Vector, accessBack)
{
    nstd::vector<double> Vector;

    Vector.push_back(3.2);
    Vector.push_back(3.4);
    Vector.push_back(2.1);

    EXPECT_EQ(2.1, Vector.back());
}

TEST(Vector, checkPopBack)
{
    nstd::vector<double> Vector;
    Vector.push_back(3.2);
    Vector.push_back(3.4);
    Vector.push_back(2.1);

    EXPECT_EQ(2.1, Vector.back());

    Vector.pop_back();
    EXPECT_EQ(2, Vector.size());
    EXPECT_EQ(3.4, Vector.back());
    
}
// ITERATOR

TEST(Vector, iteratorBegin) 
{
    nstd::vector<double> vector{1.2, 3.4, 5.5, 5.1};
    EXPECT_EQ(1.2, *vector.begin());
}

TEST(Vector, iteratorEnd) 
{
    nstd::vector<double> vector{1.2, 3.4, 5.5, 5.1};
    EXPECT_EQ(5.1, *(vector.end() - 1));
}

TEST(Vector, accessData) 
{
    nstd::vector<double> vector{1.2, 3.4, 5.5, 5.1};

    double* ptrDouble = vector.data();

    EXPECT_EQ(*ptrDouble, vector.front());
    EXPECT_EQ(*(ptrDouble + 1), vector.at(1));
    EXPECT_EQ(*(ptrDouble + 2), vector.at(2));
    EXPECT_EQ(*(ptrDouble + 3), vector.at(3));
}

TEST(Vector, reserveCapacity)
{
    nstd::vector<double> vector{1.2, 3.4, 5.5, 5.1};

    size_t vectorCapacity = vector.capacity();
    EXPECT_EQ(vector.capacity(), vectorCapacity);

    constexpr size_t newCapacity = 10;
    vector.reserve(newCapacity);

    EXPECT_EQ(vector.capacity(), newCapacity);
}

TEST(Vector, shrinkToFit)
{
    nstd::vector<double> vector{1.2, 3.4, 5.5, 5.1};
    constexpr size_t newCapacity = 10;
    vector.reserve(newCapacity);

    EXPECT_EQ(vector.capacity(), newCapacity);

    vector.shrink_to_fit();
    EXPECT_EQ(vector.capacity(), vector.size());
}

TEST(Vector, shouldCheckIsEmpty)
{
    nstd::vector<double> vector{1.2, 3.4, 5.5, 5.1};
    EXPECT_FALSE(vector.empty());
}