#pragma once
#include "minefield.h"

NextState showBoard(GameContext& context);
void printCell(std::ostream& outputStream, int cellValue);