#pragma once
#include "minefield.h"

#include <set>
#include <string>
#include <unordered_set>
#include <vector>

NextState processMineDetection(GameContext& context);
std::set<unsigned int> getExplodedMines(std::vector<unsigned int> const& minesToCheck, std::vector<unsigned int> const& minesToMatchAgainst);
void disableUsedCells(std::unordered_set<unsigned int> usedCells, Board& board);
void resizePlayerMineCount(std::unordered_map<Player*, int> playerExplodedMineCount);
void printExplodedMinesMessage(std::set<unsigned int> const& explodedMines, std::string const& playerName, std::ostream& outputStream);