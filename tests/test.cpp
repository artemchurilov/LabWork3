/* Artem Churilov st130184@student.spbu.ru
    LabWork 3 task "STL-containers" step 2 "Create Template"
*/

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
TEST(Iterators, BasicTest)
{
    SkipList<int> list;
    list.insert(42);
    list.insert(24);
    list.insert(142);
    list.insert(124);
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
//info
TEST(Information, Print)
{
    SkipList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);

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
    SkipList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    EXPECT_TRUE(list.contains(3));    
}
TEST(Information,Size)
{
    SkipList<int> list;
    list.insert(42);
    list.insert(42);
    list.insert(42);
    EXPECT_TRUE(list.get_size()==3);
}

TEST(Information, IsEmpty)
{
    SkipList<int> list;
    EXPECT_TRUE(list.is_empty());
}
TEST(Information, NotEmpty)
{
    SkipList<int> list;
    list.insert(42);
    EXPECT_FALSE(list.is_empty());
}


//operations
TEST(Operations, Insert)
{
    SkipList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    EXPECT_TRUE(list.contains(3)); 
}


TEST(Operations, PopFront)
{
    SkipList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.pop_front();
    EXPECT_FALSE(list.contains(3)); 
}

TEST(Operations, Clear)
{
    SkipList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.clear();
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::ostringstream capturedOutput;
    std::cout.rdbuf(capturedOutput.rdbuf());

    list.print();
    std::cout.rdbuf(oldCoutBuffer);

    std::string expectedOutput = "\n";
    EXPECT_EQ(capturedOutput.str(), expectedOutput);
}

TEST(Operations, Remove)
{
    SkipList<int> list;
    list.insert(3);
    list.insert(2);
    list.remove(2);
    list.remove(3);
    EXPECT_FALSE(list.contains(3));
    EXPECT_FALSE(list.contains(2));
}
