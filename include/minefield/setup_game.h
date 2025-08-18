#pragma once
#include "minefield.h"

NextState setupGame(GameContext& context);
int readIntInRange(unsigned int min, unsigned int max, std::ostream& outputStream, GetInputFn<unsigned int> getInput = getInputFromCin);
void createPlayers(GameContext& context,
    unsigned int humanPlayers,
    unsigned int computerPlayers,
    std::ostream& outputStream,
    GetInputFn<std::string> getInput = getInputFromCin);
