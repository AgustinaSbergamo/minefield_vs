#pragma once
#include <minefield/shared.h>

#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>

struct State;
struct GameContext;
using NextState = State;
using StateUpdateFn = NextState (*)(GameContext&);

struct State
{
    StateUpdateFn updateFunction = nullptr;
};

struct Board
{
    unsigned int width = 0;
    unsigned int height = 0;
    std::vector<int> boardCells;
    std::vector<unsigned int> availableCells;
    unsigned int initialMines = 0;
};

enum class PlayerType
{
    Human,
    Computer
};

struct Player
{
    std::string name;
    PlayerType type = PlayerType::Computer;
    std::vector<unsigned int> mines;
    std::vector<unsigned int> guesses;
};

struct RandomGenerator
{
    std::mt19937 randomGenerator = initializeRandomGenerator();

    int operator()(int min, int max)
    {
        std::uniform_int_distribution<> distrib{min, max};
        return distrib(randomGenerator);
    }
};

using RandomGenerationFn = std::function<int(int, int)>;

struct GameContext
{
    State currentState;
    Board board;
    std::vector<Player> players;
    RandomGenerationFn randomGenerator = RandomGenerator{};
    std::ostream& outputStream = std::cout;
    std::istream& inputStream = std::cin;
};
