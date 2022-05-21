#include "vector.hpp"
#include "gtest/gtest.h"


TEST(VectorClassTest, customSizeMethod) {

    Vector<int> myVector;
    vector<int> cppVector;

    for (int i = 0; i < 25; ++i) {
        myVector.push(i);
        cppVector.push_back(i);
    }
    EXPECT_EQ(myVector.size(), cppVector.size());
}


TEST(VectorClassTest, customPushMethod) {

    Vector<int> myVector;
    vector<int> cppVector;

    for (int i = 0; i < 25; ++i) {
        myVector.push(i);
        cppVector.push_back(i);
    }


    EXPECT_EQ(myVector[0], cppVector[0]);

}


TEST(VectorClassTest, customPopMethod) {

    Vector<int> myVector;
    vector<int> cppVector;

    for (int i = 0; i < 25; ++i) {
        myVector.push(i);
        cppVector.push_back(i);
    }

    EXPECT_EQ(myVector.size(), cppVector.size());
    EXPECT_EQ(myVector[0], cppVector[0]);

    myVector.pop();
    cppVector.pop_back();
    EXPECT_EQ(myVector.size(), cppVector.size());
}