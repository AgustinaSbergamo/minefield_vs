#pragma once
#include "minefield.h"

static constexpr int MIN_BOARD_SIZE = 24; 
static constexpr int MAX_BOARD_SIZE = 50;
static constexpr int MIN_MINES = 3;
static constexpr int MAX_MINES = 8;
static constexpr int MAX_PLAYERS = 5;    

NextState setupGame(GameContext& context);
int readIntInRange(unsigned int min,
    unsigned int max,
    GameContext::IO& io,
    GetInputFn<unsigned int> getInput = getInputFromStream);
void createPlayers(GameContext& context, unsigned int humanPlayers, unsigned int computerPlayers, GetInputFn<std::string> getInput = getInputFromStream);
