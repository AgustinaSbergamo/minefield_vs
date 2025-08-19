#pragma once
#include "minefield.h"

NextState setupGame(GameContext& context);
int readIntInRange(unsigned int min,
    unsigned int max,
    GameContext::IO& io,
    GetInputFn<unsigned int> getInput = getInputFromStream);
void createPlayers(GameContext& context, unsigned int humanPlayers, unsigned int computerPlayers, GetInputFn<std::string> getInput = getInputFromStream);
