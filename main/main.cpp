#include<iostream>
#include<fstream>
#include<string>

#include "../src/Calculator.hpp"

int main()
{
    std::string line;
    std::ifstream myfile("tests.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::string::size_type pos = line.find(':');
            if (pos != std::string::npos)
            {
                std::cout << " Line: " << line << " result: " << calculate(line.substr(0, pos)) << std::endl;
            }
            else
            {
                std::cout << "Line not well formatted" << std::endl;;

            }
        }
        myfile.close();
    }

    else std::cout << "Unable to open file" << std::endl;;

    return 0;
}