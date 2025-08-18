#pragma once
#include "minefield.h"

NextState setupGame(GameContext& context);
int readIntInRange(unsigned int min,
    unsigned int max,
    std::ostream& outputStream,
    std::istream& inputStream,
    GetInputFn<unsigned int> getInput = getInputFromStream);
void createPlayers(GameContext& context,
    unsigned int humanPlayers,
    unsigned int computerPlayers,
    std::ostream& outputStream,
    std::istream& inputStream,
    GetInputFn<std::string> getInput = getInputFromStream);
