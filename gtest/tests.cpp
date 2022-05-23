#include "vector.hpp"
#include "gtest/gtest.h"
#include <vector>

using namespace std;

TEST(VectorClassTest, MemberFunctions) {
MyVector<int> MyVector(10, 20), MyVector2{1, 2, 3, 4, 5, 6, 7, 8}, MyVectorCopy(MyVector);
vector<int> cppVector(10, 20), cppVector2{1, 2, 3, 4, 5, 6, 7, 8}, cppVectorCopy(cppVector);

EXPECT_EQ(MyVector.size(), cppVector.size());
EXPECT_EQ(MyVector2.size(), cppVector2.size());
EXPECT_EQ(MyVectorCopy.size(), cppVectorCopy.size());
EXPECT_EQ(MyVector.get_allocator(), cppVector.get_allocator());
}

TEST(VectorClassTest, ElementAccess) {

MyVector<int> MyVector{1, 2, 3, 4, 5, 6, 7, 8};
vector<int> cppVector{1, 2, 3, 4, 5, 6, 7, 8};

EXPECT_EQ(cppVector[5], MyVector[5]);
EXPECT_EQ(cppVector.at(5), MyVector.at(5));
EXPECT_EQ(cppVector.front(), MyVector.front());
EXPECT_EQ(cppVector.back(), MyVector.back());
}

TEST(VectorClassTest, Iterators) {

MyVector<int> MyVector{1, 2, 3, 4, 5, 6, 7, 8};
vector<int> cppVector{1, 2, 3, 4, 5, 6, 7, 8};

EXPECT_EQ(*cppVector.begin(), *MyVector.begin());
EXPECT_EQ(*cppVector.rbegin(), *MyVector.rbegin());
}


TEST(VectorClassTest, Capacity) {

MyVector<int> MyVector{1, 2, 3, 4, 5, 6, 7, 8};
vector<int> cppVector{1, 2, 3, 4, 5, 6, 7, 8};

EXPECT_EQ(cppVector.empty(), MyVector.empty());
EXPECT_EQ(cppVector.size(), MyVector.size());
EXPECT_EQ(cppVector.capacity(), MyVector.capacity());
cppVector.shrink_to_fit();
MyVector.shrink_to_fit();
EXPECT_EQ(cppVector.capacity(), MyVector.capacity());
}

TEST(VectorClassTest, Reserve) {

int size = 20;
MyVector<int> MyVector(size, 5);

MyVector.reserve(600);
EXPECT_EQ(MyVector.capacity(), 600);
MyVector.shrink_to_fit();
EXPECT_EQ(MyVector.capacity(), size);
}


TEST(VectorClassTest, Modifiers) {

MyVector<int> MyVector;
vector<int> cppVector;
int size = 25;

for (int i = 0; i <= size; ++i) {
MyVector.push_back(i);
cppVector.push_back(i);
}

EXPECT_EQ(MyVector.size(), cppVector.size());

MyVector.pop_back();
EXPECT_EQ(MyVector.back(), size - 1);
MyVector.clear();
EXPECT_EQ(MyVector.size(), 0);
}


TEST(VectorClassTest, Insert) {

MyVector<int> MyVector{1, 2, 3, 4, 5};

MyVector.insert(MyVector.begin() + 1, 27);

EXPECT_EQ(MyVector.at(1), 27);
}


TEST(VectorClassTest, Compare) {


MyVector<int> my_v1{1, 2, 3};
MyVector<int> my_v2{7, 8, 9, 10};


EXPECT_EQ(my_v1 == my_v2, false);
EXPECT_EQ(my_v1 != my_v2, true);
EXPECT_EQ(my_v1 < my_v2, true);
EXPECT_EQ(my_v1 <= my_v2, true);
EXPECT_EQ(my_v1 > my_v2, false);
EXPECT_EQ(my_v1 >= my_v2, false);

}

