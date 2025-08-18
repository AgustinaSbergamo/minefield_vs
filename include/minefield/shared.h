#pragma once
#include <iostream>
#include <random>

template <typename T>
using GetInputFn = T (*)();

template <typename T>
T getInputFromCin()
{
    T value;
    while (true)
    {
        std::cin >> value;
        if (!std::cin.fail())
        {
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        //TODO
        //printMessage("Invalid input! Try again: ");
    }
}

template <typename... Args>
void printMessage(std::ostream& outputStream, Args&&... args)
{
    (outputStream << ... << args);
}

void clearStandardInput();
std::mt19937 initializeRandomGenerator();
