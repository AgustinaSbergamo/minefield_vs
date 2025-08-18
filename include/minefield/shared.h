#pragma once
#include <iostream>
#include <random>

template <typename T>
using GetInputFn = T (*)(std::istream&, std::ostream&);

template <typename T>
T getInputFromStream(std::istream& inputStream, std::ostream& outputStream)
{
    T value;
    bool validInput = false;

    while (!validInput)
    {
        inputStream >> value;
        if (!inputStream.fail())
        {
            validInput = true;
        }
        else
        {
            inputStream.clear();
            inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            outputStream << "Invalid input! Try again: ";
        }
    }
    return value;
}

template <typename... Args>
void printMessage(std::ostream& outputStream, Args&&... args)
{
    (outputStream << ... << args);
}

void clearStandardInput();
std::mt19937 initializeRandomGenerator();
