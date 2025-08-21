#pragma once
#include "minefield.h"
#include <minefield/setup_game.h>
#include <sstream>

GameContext createTestGame(unsigned int humanPlayers, unsigned int botPlayers, unsigned int width, unsigned int height, int initialMines);