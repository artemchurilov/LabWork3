/* Artem Churilov st130184@student.spbu.ru
    LabWork 3 task "STL-containers" step 2 "Create Template"
*/

#include <gtest/gtest.h>
#include "../include/list.h"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(CI_test, first_test)
{
    EXPECT_TRUE(true);
}

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