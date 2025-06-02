/* Artem Churilov st130184@student.spbu.ru
    LabWork 3 task "STL-containers" step 2 "Create Template"
*/

#include <vector>
#include <algorithm>
#include <gtest/gtest.h>
#include "../include/list.h"

int main(int argc, char **argv) {
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
TEST(ConstIterator, BasicTest) {
    CircularList<int> list;
    list.push_front(42);
    list.push_front(24);
    list.push_front(43);
    list.push_front(422);
    
    const CircularList<int> constList = list;
    std::vector<int> expected_values = {422, 43, 24, 42};
    std::vector<int> actual_values;

    for (auto it = constList.begin(); it != constList.end(); ++it) {
        actual_values.push_back(*it);
    }
    std::cout << "\n";
    
    EXPECT_EQ(expected_values, actual_values);
    EXPECT_FALSE(actual_values.empty());          
    EXPECT_EQ(4, actual_values.size());       
}

TEST(ConstIterator, AdvancedTest) {
    CircularList<int> list;
    list.push_front(42);
    list.push_front(24);
    list.push_front(43);
    list.push_front(422);
    
    const CircularList<int> constList = list;
    
    std::vector<int> expected = {422, 43, 24, 42};
    std::vector<int> actual;
    for (const auto& val : constList) {
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

// TEST(Operations, Clear)
// {
//     CircularList<int> list;
//     list.insert(1);
//     list.insert(2);
//     list.insert(3);
//     list.clear();
//     std::streambuf* oldCoutBuffer = std::cout.rdbuf();
//     std::ostringstream capturedOutput;
//     std::cout.rdbuf(capturedOutput.rdbuf());

//     list.print();
//     std::cout.rdbuf(oldCoutBuffer);

//     std::string expectedOutput = "\n";
//     EXPECT_EQ(capturedOutput.str(), expectedOutput);
// }

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
