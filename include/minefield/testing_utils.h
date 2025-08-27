#pragma once
#include "minefield.h"
#include <minefield/setup_game.h>
#include <sstream>



struct TestContext { // it contains a game context and a readable/writeable interface
public:
	GameContext context{.io{fakeOutput, fakeInput}}; // context initialized with mocked input and output
	std::istringstream fakeInput; // must keep fakeInput and Output alive during test execution
	std::ostringstream fakeOutput; // thus we need to keep them as variables, public ones so the free functions declared below can acces them
};

template <typename T>
void concatInput(std::string &currentInput, T const newInput);

std::string getInputBuffer(TestContext const &testContext);
void setInputBuffer(TestContext &testContext, std::string input);
std::string getOutputBuffer(TestContext const &testContext);
void setOutputBuffer(TestContext &testContext, std::string input);

State setupTestGame(TestContext &testContext, unsigned int humanPlayers = 1, unsigned int computerPlayers = 2, unsigned int width = 24, unsigned int height = 24, int initialMines = 3);