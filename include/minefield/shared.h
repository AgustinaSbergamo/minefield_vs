#pragma once
#include <random>
#include <iostream>

template<typename T>
using GetInputFn = T(*)();

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
        std::cout << "Invalid input! Try again: ";
    }
}

void clearStandardInput();
std::mt19937 initializeRandomGenerator();
