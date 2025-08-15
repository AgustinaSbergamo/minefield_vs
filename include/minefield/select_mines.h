#pragma once
#include "minefield.h"

#include <random>
#include <vector>

NextState selectMines(GameContext& context);
NextState selectGuesses(GameContext& context);
void manualMineSelection(int selectionSize,
    std::vector<unsigned int>& minesVector,
    std::vector<unsigned int> const& availableCells,
    std::ostream& outputStream,
    GetInputFn<unsigned int> getInput);
void randomMineSelection(int selectionSize,
    std::vector<unsigned int>& randomSelection,
    std::vector<unsigned int> const& availableCells,
    RandomGenerationFn const& randomGenerator);
void printMineSelection(std::vector<unsigned int> const& mines, std::ostream& outputStream, std::string const& message = "");
unsigned int getRivalsMaxMineCount(Player const& player, std::vector<Player> const& players);