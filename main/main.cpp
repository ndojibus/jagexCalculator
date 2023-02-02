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
            std::cout << line << '\n';
        }
        myfile.close();
    }

    else std::cout << "Unable to open file";

    
    std::string post = "53+62/*35*+";
    std::cout << "The result is: " << calculate(post);

    return 0;
}