#include <gtest/gtest.h>
#include "../Vector.h"
#include <string>
#include <sstream>
#include <vector>

TEST(VectorConstructorTests, DefaultConstructorTest) {
    Vector<int> v;

    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorConstructorTests, CountConstructorTest) {
    Vector<int> v(5);

    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v.capacity(), 5);
}

TEST(VectorConstructorTests, CountValueConstructorTest) {
    Vector<int> v(4, 7);

    EXPECT_EQ(v.size(), 4);

    for (size_t i = 0; i < v.size(); i++) {
        EXPECT_EQ(v[i], 7);
    }
}

TEST(VectorConstructorTests, InitializerListConstructorTest) {
    Vector<int> v = { 1, 2, 3, 4 };

    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
}

TEST(VectorElementAccessTests, AtTest) {
    Vector<int> v = { 10, 20, 30 };

    EXPECT_EQ(v.at(0), 10);
    EXPECT_EQ(v.at(1), 20);
    EXPECT_EQ(v.at(2), 30);
}

TEST(VectorElementAccessTests, AtOutOfRangeTest) {
    Vector<int> v = { 1, 2, 3 };

    EXPECT_THROW(v.at(5), std::out_of_range);
}

TEST(VectorElementAccessTests, FrontTest) {
    Vector<int> v = { 5, 10, 15 };

    EXPECT_EQ(v.front(), 5);
}

TEST(VectorElementAccessTests, BackTest) {
    Vector<int> v = { 5, 10, 15 };

    EXPECT_EQ(v.back(), 15);
}

TEST(VectorElementAccessTests, DataTest) {
    Vector<int> v = { 1, 2, 3 };

    EXPECT_EQ(v.data()[0], 1);
    EXPECT_EQ(v.data()[1], 2);
    EXPECT_EQ(v.data()[2], 3);
}

TEST(VectorModifierTests, PushBackTest) {
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);

    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
}

TEST(VectorModifierTests, PopBackTest) {
    Vector<int> v = { 1, 2, 3 };

    v.pop_back();

    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.back(), 2);
}

TEST(VectorModifierTests, ClearTest) {
    Vector<int> v = { 1, 2, 3 };

    v.clear();

    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
}


TEST(VectorInsertTests, InsertSingleValueTest) {
    Vector<int> v = { 1, 2, 4 };

    v.insert(v.begin() + 2, 3);

    EXPECT_EQ(v.size(), 4);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
}

TEST(VectorInsertTests, InsertInitializerListTest) {
    Vector<int> v = { 1, 5 };

    v.insert(v.begin() + 1, { 2, 3, 4 });

    EXPECT_EQ(v.size(), 5);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
    EXPECT_EQ(v[4], 5);
}

TEST(VectorInsertTests, InsertRangeTest) {
    Vector<int> v = { 1, 5 };
    int arr[] = { 2, 3, 4 };

    v.insert(v.begin() + 1, arr, arr + 3);

    EXPECT_EQ(v.size(), 5);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
    EXPECT_EQ(v[4], 5);
}

TEST(VectorEraseTests, EraseSingleTest) {
    Vector<int> v = { 1, 2, 3, 4 };

    v.erase(v.begin() + 1);

    EXPECT_EQ(v.size(), 3);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 4);
}

TEST(VectorEraseTests, EraseRangeTest) {
    Vector<int> v = { 1, 2, 3, 4, 5 };

    v.erase(v.begin() + 1, v.begin() + 4);

    EXPECT_EQ(v.size(), 2);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 5);
}

TEST(VectorCapacityTests, ReserveTest) {
    Vector<int> v;

    v.reserve(20);

    EXPECT_GE(v.capacity(), 20);
}

TEST(VectorCapacityTests, ResizeGrowTest) {
    Vector<int> v = { 1, 2 };

    v.resize(5);

    EXPECT_EQ(v.size(), 5);
}

TEST(VectorCapacityTests, ResizeShrinkTest) {
    Vector<int> v = { 1, 2, 3, 4, 5 };

    v.resize(2);

    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
}

TEST(VectorCapacityTests, ShrinkToFitTest) {
    Vector<int> v;

    v.reserve(20);
    v.push_back(1);
    v.push_back(2);

    v.shrink_to_fit();

    EXPECT_EQ(v.capacity(), v.size());
}

TEST(VectorEmplaceTests, EmplaceBackTest) {
    Vector<std::string> v;

    v.emplace_back("hello");
    v.emplace_back("world");

    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], "hello");
    EXPECT_EQ(v[1], "world");
}

TEST(VectorEmplaceTests, EmplaceTest) {
    Vector<std::string> v = { "one", "three" };

    v.emplace(v.begin() + 1, "two");

    EXPECT_EQ(v.size(), 3);

    EXPECT_EQ(v[0], "one");
    EXPECT_EQ(v[1], "two");
    EXPECT_EQ(v[2], "three");
}

TEST(VectorAssignTests, AssignCountValueTest) {
    Vector<int> v;

    v.assign(5, 9);

    EXPECT_EQ(v.size(), 5);

    for (size_t i = 0; i < v.size(); i++) {
        EXPECT_EQ(v[i], 9);
    }
}

TEST(VectorAssignTests, AssignRangeTest) {
    Vector<int> v;
    std::vector<int> src = { 1, 2, 3, 4 };

    v.assign_range(src);

    EXPECT_EQ(v.size(), 4);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
}

TEST(VectorOperatorTests, EqualityOperatorTest) {
    Vector<int> a = { 1, 2, 3 };
    Vector<int> b = { 1, 2, 3 };

    EXPECT_TRUE(a == b);
}

TEST(VectorOperatorTests, InequalityOperatorTest) {
    Vector<int> a = { 1, 2, 3 };
    Vector<int> b = { 1, 2, 4 };

    EXPECT_TRUE(a != b);
}

TEST(VectorOperatorTests, LessOperatorTest) {
    Vector<int> a = { 1, 2, 3 };
    Vector<int> b = { 1, 2, 4 };

    EXPECT_TRUE(a < b);
}

TEST(VectorOperatorTests, GreaterOperatorTest) {
    Vector<int> a = { 1, 2, 5 };
    Vector<int> b = { 1, 2, 4 };

    EXPECT_TRUE(a > b);
}

TEST(VectorRuleOfFiveTests, CopyAssignmentTest) {
    Vector<int> v1 = { 1, 2, 3 };

    Vector<int> v2;

    v2 = v1;

    EXPECT_EQ(v2.size(), 3);

    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
}

TEST(VectorRuleOfFiveTests, MoveAssignmentTest) {
    Vector<int> v1 = { 1, 2, 3 };

    Vector<int> v2;

    v2 = std::move(v1);

    EXPECT_EQ(v2.size(), 3);

    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
}

TEST(VectorRuleOfFiveTests, SwapTest) {
    Vector<int> a = { 1, 2 };
    Vector<int> b = { 9, 8, 7 };

    a.swap(b);

    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(b.size(), 2);

    EXPECT_EQ(a[0], 9);
    EXPECT_EQ(b[0], 1);
}

TEST(VectorNonMemberTests, EraseValueTest) {
    Vector<int> v = { 1, 2, 3, 2, 4 };
    using size_type = size_t;

    size_type removed = erase(v,2); //how many elems erased

    EXPECT_EQ(removed, 2);
    EXPECT_EQ(v.size(), 3);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 4);
}

TEST(VectorNonMemberTests, EraseIfTest) {
    Vector<int> v = { 1, 2, 3, 4, 5, 6 };

    size_t removed = erase_if(v, [](int x) {
        return x % 2 == 0;
        });

    EXPECT_EQ(removed, 3);
    EXPECT_EQ(v.size(), 3);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 5);
}