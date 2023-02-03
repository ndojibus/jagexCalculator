#pragma once

#include<cmath>
#include<stack>
#include<vector>
#include<string>
#include<climits>

#include "Calculator.hpp"

float operation(float a, float b, std::string op) {
    //Perform operation
    if (op == "+")
        return b + a;
    else if (op == "-")
        return b - a;
    else if (op == "*")
        return b * a;
    else if (op == "/")
        return b / a;
    else if (op == "^")
        return pow(b, a); //find b^a
    else
        return INT_MIN; //return negative infinity
}

void tokenize(std::string const& str, std::vector<std::string>& out)
{
    int currIndex = 0, i = 0;
    int startIndex = 0, endIndex = 0;
    char separator1 = ' ';
    char separator2 = '(';
    char separator3 = ')';

    while (i <= str.length())
    {
        if (str[i] == separator1 
            || str[i] == separator2 
            || str[i] == separator3 
            || i == str.length())
        {
            endIndex = i;
            std::string subStr = "";
            if (str[i] == separator2)
            {
                out.push_back({ separator2 });
            }
            if ((endIndex - startIndex) != 0)
            {
                subStr.append(str, startIndex, endIndex - startIndex);
                out.push_back(subStr);
            }
            if (str[i] == separator3)
            {
                out.push_back({ separator3 });
            }
            currIndex += 1;
            startIndex = endIndex + 1;
        }
        i++;
    }
}

bool isNumber(std::string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && (std::isdigit(*it) || (*it)=='.')) ++it;
    return (!s.empty() && it == s.end()) || (s[0] == '-' && s.length()> 1);
}

bool isOperator(std::string s)
{
    if (s == "+" || s == "-" || s == "*" || s == "/" || s == "^")
        return true;//character is an operator
    return false;//not an operator
}

int priority(std::string operation)
{
    if (operation == "+" || operation == "-")
        return 1;
    if (operation == "*" || operation == "/")
        return 2;
    if (operation == "^")
        return 3;
    return -1;
}

void toPostFix(std::vector<std::string> input, std::vector<std::string>& postfix)
{
    std::stack<std::string> operation;


    for (auto it = input.begin(); it != input.end(); it++)
    {
        if (isNumber(*it))
        {
            postfix.push_back({ *it });
        }
        else if ((*it) == "(") {
            operation.push("(");
        }
        else if ((*it) == ")")
        {
            while (!operation.empty() && operation.top() != "(")
            {
                postfix.push_back({ operation.top() });
                operation.pop();
            }
            operation.pop();
        }
        else if(isOperator(*it))
        {
            if (operation.empty())
            {
                operation.push(*it);
            }  
            else
            {
                if (isOperator(operation.top()))
                {
                    while (!operation.empty() && (priority(*it) <=priority(operation.top())))
                    {
                        postfix.push_back({ operation.top() });
                        operation.pop();
                    }
                }
                operation.push(*it);
            }
        }
    }
    while (!operation.empty())
    {
        postfix.push_back(operation.top());
        operation.pop();
    }
}

float evaluatePostfix(std::vector<std::string> postFix)
{
    float a, b;

    std::stack<float> result;

    for (auto it = postFix.begin(); it != postFix.end(); it++)
    {
        if (isOperator(*it)) {
            a = result.top();
            result.pop();
            b = result.top();
            result.pop();
            result.push(operation(a, b, *it));
        }
        else if (isNumber(*it))
        {
            result.push(stof(*it));
        }
    }

    return result.top();

}

float calculate(std::string input, int precision) {

    std::vector<std::string> tokenizedInput;

    tokenize(input, tokenizedInput);

    std::vector<std::string> postFix;

    toPostFix(tokenizedInput, postFix);

    float result = evaluatePostfix(postFix);

    return floorf(result * (pow(10,precision))) / pow(10, precision);
}