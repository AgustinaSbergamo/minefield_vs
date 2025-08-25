#pragma once
#include "minefield.h"
#include <minefield/setup_game.h>
#include <sstream>

State createTestGame(GameContext &context, unsigned int humanPlayers, unsigned int botPlayers, unsigned int width, unsigned int height, int initialMines);