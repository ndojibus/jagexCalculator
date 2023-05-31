#include "gtest/gtest.h"
#include "../src/Calculator.hpp"

#include<iostream>
#include<fstream>
#include<string>

typedef std::pair<std::string, double> TestParam;

class CalculatorTest : public testing::TestWithParam<TestParam> {};

std::vector<TestParam> ReadTestCasesFromDisk() {

    std::string line;
    std::ifstream myfile("tests.txt");
    std::vector<TestParam> testParams;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::string::size_type pos = line.find(':');
            if (pos != std::string::npos)
            {
                TestParam element{ line.substr(0, pos), stod(line.substr(pos + 1)) };
                testParams.push_back(element);
            }
            else
            {
                std::cout << "Line not well formatted" << std::endl;;
                
            }
        }
        myfile.close();
    }

    else std::cout << "Unable to open file" << std::endl;;

    return testParams;
}

INSTANTIATE_TEST_SUITE_P(
    TestsSuiteFromFile,  // Instantiation name can be chosen arbitrarily.
    CalculatorTest,
    testing::ValuesIn(ReadTestCasesFromDisk()));

TEST_P(CalculatorTest, CalculateFromFile) {
 
    EXPECT_DOUBLE_EQ(GetParam().second, calculate(GetParam().first));
}

TEST(CalculatorTest, TestingPrecision) {

    double expected3 = 3.333;
    double expected4 = 3.3333;
    EXPECT_EQ(expected3, calculate("10 / 3"));
    EXPECT_EQ(expected3, calculate("10 / 3", 3));
    EXPECT_EQ(expected4, calculate("10 / 3", 4));
    EXPECT_EQ(-18, calculate("(-20 * 1.8) / 2 "));

}

TEST(CalculatorTest, ErrorParsing)
{
    EXPECT_THROW(calculate("10 + s"), CalculateException);
}
