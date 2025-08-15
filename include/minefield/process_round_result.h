#pragma once
#include "minefield.h"

NextState processRoundResult(GameContext& context);
unsigned int getMaxMineCount(std::vector<Player> const& players);