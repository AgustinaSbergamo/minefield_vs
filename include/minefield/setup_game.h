#pragma once
#include "minefield.h"

NextState setupGame(GameContext &context);
int readIntInRange(unsigned int min, unsigned int max, GetInputFn<unsigned int> getInput);
void createPlayers(GameContext &context, unsigned int humanPlayers, unsigned int computerPlayers, GetInputFn<std::string> getInput);


