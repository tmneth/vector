#include "vector.hpp"
#include "gtest/gtest.h"
#include <vector>
using namespace std;

TEST(VectorClassTest, MemberFunctions) {
    myVector<int> myVector(10, 20), myVector2{1, 2, 3, 4, 5, 6, 7, 8}, myVectorCopy(myVector);
    vector<int> cppVector(10, 20), cppVector2{1, 2, 3, 4, 5, 6, 7, 8}, cppVectorCopy(cppVector);

    EXPECT_EQ(myVector.size(), cppVector.size());
    EXPECT_EQ(myVector2.size(), cppVector2.size());
    EXPECT_EQ(myVectorCopy.size(), cppVectorCopy.size());
    EXPECT_EQ(myVector.get_allocator(), cppVector.get_allocator());
}

TEST(VectorClassTest, ElementAccess) {

    myVector<int> myVector{1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> cppVector{1, 2, 3, 4, 5, 6, 7, 8};

    EXPECT_EQ(cppVector[5], myVector[5]);
    EXPECT_EQ(cppVector.at(5), myVector.at(5));
    EXPECT_EQ(cppVector.front(), myVector.front());
    EXPECT_EQ(cppVector.back(), myVector.back());
}

TEST(VectorClassTest, Iterators) {

    myVector<int> myVector{1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> cppVector{1, 2, 3, 4, 5, 6, 7, 8};

    EXPECT_EQ(*cppVector.begin(), *myVector.begin());
    EXPECT_EQ(*cppVector.rbegin(), *myVector.rbegin());
    EXPECT_EQ(*cppVector.end(), *myVector.end());
    EXPECT_EQ(*cppVector.rend(), *myVector.rend());
}


TEST(VectorClassTest, Capacity) {

    myVector<int> myVector{1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> cppVector{1, 2, 3, 4, 5, 6, 7, 8};

    EXPECT_EQ(cppVector.empty(), myVector.empty());
    EXPECT_EQ(cppVector.size(), myVector.size());
    EXPECT_EQ(cppVector.capacity(), myVector.capacity());
    cppVector.shrink_to_fit();
    myVector.shrink_to_fit();
    EXPECT_EQ(cppVector.capacity(), myVector.capacity());
}

TEST(VectorClassTest, Reserve) {

    int size = 20;
    myVector<int> myVector(size, 5);

    myVector.reserve(600);
    EXPECT_EQ(myVector.capacity(), 600);
    myVector.shrink_to_fit();
    EXPECT_EQ(myVector.capacity(), size);
}


TEST(VectorClassTest, Modifiers) {

    myVector<int> myVector;
    vector<int> cppVector;
    int size = 25;

    for (int i = 0; i <= size; ++i) {
        myVector.push_back(i);
        cppVector.push_back(i);
    }

    EXPECT_EQ(myVector.size(), cppVector.size());

    myVector.pop_back();
    EXPECT_EQ(myVector.back(), size-1);
    myVector.clear();
    EXPECT_EQ(myVector.size(), 0);
}



