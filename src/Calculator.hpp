#pragma once

#include <string>

enum class ErrorCode
{
    ParsingError,
    OutOfRange,
    Undefined
};

struct CalculateException : public std::exception {

    CalculateException(ErrorCode error): errorCode{error}{}
    const char* what() const throw () {

        switch (errorCode) {
        case ErrorCode::ParsingError:
            return "Parsing Error! Invalid character in the input string";
        case ErrorCode::OutOfRange:
            return "Parsing Error! Output out of range";

        default:
        {
            return "Error! Undefined error while evaluating the input string";
        }
        }
    }

private:
    ErrorCode errorCode = ErrorCode::Undefined;
};


double calculate(std::string input, int precision=3);