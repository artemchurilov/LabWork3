/* Artem Churilov st130184@student.spbu.ru
    LabWork 3 task "STL-containers" step 2 "Create Template"
*/

#include <vector>
#include <algorithm>
#include <gtest/gtest.h>
#include "../include/list.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(CITest, FirstTest)
{
    EXPECT_TRUE(true);
}

//iterators
TEST(Iterator, BasicTest)
{
    CircularList<int> list;
    list.push_front(42);
    list.push_front(24);
    list.push_front(142);
    list.push_front(124);
    auto it = list.begin();

    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::ostringstream capturedOutput;
    std::cout.rdbuf(capturedOutput.rdbuf());
    while (it!=list.end())
    {
        if (*it==42)
        {
            std::cout << 42;
        }
        std::cout << *it << "\n";
        ++it;
    }
    std::cout.rdbuf(oldCoutBuffer);

    std::string expectedOutput = "124\n142\n24\n4242\n";
    EXPECT_EQ(capturedOutput.str(), expectedOutput);
}
TEST(Iterator, AdvancedTest)
{
    CircularList<int> list;
    list.push_front(42);
    list.push_front(24);
    list.push_front(142);
    list.push_front(124);
    auto it = list.begin();

    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::ostringstream capturedOutput;
    std::cout.rdbuf(capturedOutput.rdbuf());
    while (it!=list.end())
    {
        auto prev = it++;
        if (*it==42)
        {
            std::cout << 42;
        }
        std::cout<<*prev <<"  " << *it << "\n"<<"  ";
        it++;
    }
    std::cout.rdbuf(oldCoutBuffer);

    std::string expectedOutput = "124  142\n  4224  42\n  ";
    CircularList<std::string> string_list;
    string_list.push_front("Artem");
    auto it2 = string_list.begin();
    EXPECT_TRUE(it2->size()==5);
    EXPECT_EQ(capturedOutput.str(), expectedOutput);
}
TEST(ConstIterator, BasicTest)
{
    CircularList<int> list;
    list.push_front(42);
    list.push_front(24);
    list.push_front(43);
    list.push_front(422);

    const CircularList<int> constList = list;
    std::vector<int> expected_values = {422, 43, 24, 42};
    std::vector<int> actual_values;

    for (auto it = constList.begin(); it != constList.end(); ++it)
    {
        actual_values.push_back(*it);
    }
    std::cout << "\n";

    EXPECT_EQ(expected_values, actual_values);
    EXPECT_FALSE(actual_values.empty());
    EXPECT_EQ(4, actual_values.size());
}

TEST(ConstIterator, AdvancedTest)
{
    CircularList<int> list;
    list.push_front(42);
    list.push_front(24);
    list.push_front(43);
    list.push_front(422);

    const CircularList<int> constList = list;

    std::vector<int> expected = {422, 43, 24, 42};
    std::vector<int> actual;
    for (const auto& val : constList)
    {
        actual.push_back(val);
    }
    EXPECT_EQ(expected, actual);

    EXPECT_NE(constList.begin(), constList.end());

    EXPECT_EQ(constList.begin(), constList.cbegin());
    EXPECT_EQ(constList.end(), constList.cend());
}
//info
TEST(Information, Print)
{
    CircularList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::ostringstream capturedOutput;
    std::cout.rdbuf(capturedOutput.rdbuf());

    list.print();
    std::cout.rdbuf(oldCoutBuffer);

    std::string expectedOutput = "3 2 1 \n";
    EXPECT_EQ(capturedOutput.str(), expectedOutput);
}

TEST(Information, Contains)
{
    CircularList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    EXPECT_TRUE(list.contains(3));
}
TEST(Information,Size)
{
    CircularList<int> list;
    list.push_front(42);
    list.push_front(42);
    list.push_front(42);
    EXPECT_TRUE(list.size()==3);
}

TEST(Information, IsEmpty)
{
    CircularList<int> list;
    EXPECT_TRUE(list.empty());
}
TEST(Information, NotEmpty)
{
    CircularList<int> list;
    list.push_front(42);
    EXPECT_FALSE(list.empty());
}


//operations
TEST(Operations, Insert)
{
    CircularList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    EXPECT_TRUE(list.contains(3));
}


TEST(Operations, PopFront)
{
    CircularList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.pop_front();
    EXPECT_FALSE(list.contains(3));
}


TEST(Operations, Remove)
{
    CircularList<int> list;
    list.push_front(3);
    list.push_front(3);
    list.remove(2);
    list.remove(3);
    EXPECT_FALSE(list.contains(3));
    EXPECT_FALSE(list.contains(2));
}


TEST(Constructors, DefaultConstructor)
{
    CircularList<int> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(Constructors, InitializerList)
{
    CircularList<int> list = {1, 2, 3, 4};
    EXPECT_EQ(list.size(), 4);

    std::vector<int> elements;
    for (const auto& item : list)
    {
        elements.push_back(item);
    }
    EXPECT_EQ(elements, (std::vector<int> {1, 2, 3, 4}));
}

TEST(Constructors, CopyConstructor)
{
    CircularList<int> original = {1, 2, 3};
    CircularList<int> copy(original);

    EXPECT_EQ(original.size(), copy.size());

    auto it1 = original.begin();
    auto it2 = copy.begin();
    while (it1 != original.end() && it2 != copy.end())
    {
        EXPECT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }
}

TEST(Assignment, CopyAssignment)
{
    CircularList<int> original = {5, 6, 7};
    CircularList<int> copy;
    copy = original;

    EXPECT_EQ(original.size(), copy.size());

    original.pop_front();
    EXPECT_NE(original.size(), copy.size());

    auto it = copy.begin();
    EXPECT_EQ(*it, 5);
}

TEST(ErrorHandling, PopFrontEmpty)
{
    CircularList<int> list;
    EXPECT_THROW(list.pop_front(), std::out_of_range);
}

TEST(ErrorHandling, DereferenceEnd)
{
    CircularList<int> list;
    auto it = list.end();
    EXPECT_THROW(*it, std::runtime_error);
    EXPECT_THROW(it.operator->(), std::runtime_error);
}

TEST(Methods, SequentialRemoval)
{
    CircularList<int> list = {1, 2, 3, 4, 5};

    EXPECT_TRUE(list.remove(3));
    EXPECT_EQ(list.size(), 4);

    EXPECT_TRUE(list.remove(1));
    EXPECT_EQ(list.size(), 3);

    EXPECT_TRUE(list.remove(5));
    EXPECT_EQ(list.size(), 2);

    std::vector<int> remaining;
    for (const auto& item : list)
    {
        remaining.push_back(item);
    }
    EXPECT_EQ(remaining, (std::vector<int> {2, 4}));
}

TEST(Methods, PushFrontAndBack)
{
    CircularList<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    list.push_back(4);
    list.push_back(5);

    std::vector<int> expected = {1, 2, 3, 4, 5};
    std::vector<int> actual;
    for (const auto& item : list)
    {
        actual.push_back(item);
    }
    EXPECT_EQ(expected, actual);
}

TEST(Circularity, IteratorLoop)
{
    CircularList<int> list = {1, 2};
    auto it = list.begin();

    std::vector<int> values;
    for (int i = 0; i < 5; ++i)
    {
        values.push_back(*it);
        ++it;
        if (it == list.end())
        {
            it = list.begin();
        }
    }
    EXPECT_EQ(values, (std::vector<int> {1, 2, 1, 2, 1}));
}

TEST(Operations, RemoveFromEmptyList)
{
    CircularList<int> list;
    EXPECT_FALSE(list.remove(42));
    EXPECT_TRUE(list.empty());
}

TEST(Operations, RemoveNonExistent)
{
    CircularList<int> list = {1, 2, 3};
    EXPECT_FALSE(list.remove(99));
    EXPECT_EQ(list.size(), 3);
}

TEST(Iterator, ReverseTraversal)
{
    CircularList<int> list = {1, 2, 3, 4};
    auto it = list.end();
    --it;

    std::vector<int> values;
    while (it != list.begin())
    {
        values.push_back(*it);
        --it;
    }
    values.push_back(*list.begin());

    EXPECT_EQ(values, (std::vector<int> {4, 3, 2, 1}));
}

TEST(ErrorHandling, DereferenceInvalidIterator)
{
    CircularList<int> list;
    auto it = list.begin();
    EXPECT_THROW(*it, std::runtime_error);
    EXPECT_THROW(it.operator->(), std::runtime_error);
}



TEST(Assignment, SelfAssignment)
{
    CircularList<int> list = {5, 10, 15};
    list = list;
    EXPECT_EQ(list.size(), 3);
    EXPECT_TRUE(list.contains(5) && list.contains(10) && list.contains(15));
}

TEST(Methods, ClearList)
{
    CircularList<int> list = {1, 2, 3, 4, 5};
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.begin(), list.end());
}

#include <ranges>
TEST(IteratorConcepts, Bidirectional)
{
    static_assert(std::bidirectional_iterator<CircularList<int>::Iterator>);
    static_assert(std::bidirectional_iterator<CircularList<int>::ConstIterator>);
    static_assert(std::ranges::bidirectional_range<CircularList<int>>);

    static_assert(std::is_default_constructible_v<CircularList<int>::Iterator>);
    static_assert(std::is_copy_constructible_v<CircularList<int>::Iterator>);
    static_assert(std::is_destructible_v<CircularList<int>::Iterator>);
}