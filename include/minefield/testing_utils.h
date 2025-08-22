#pragma once
#include "minefield.h"
#include <minefield/setup_game.h>
#include <sstream>

struct TestSystem { // it contains a game context and a readable/writeable interface
public:
	GameContext context{.io{fakeOutput, fakeInput}}; // context initialized with mocked input and output

	std::string getInputBuffer();
	void setInputBuffer(std::string input);
	std::string getOutputBuffer();
	void setOutputBuffer(std::string input);

private: // fakeInput and fakeOutput must exist for them to be referenced by gamecontext.io members, so we set them private
	std::istringstream fakeInput;
	std::ostringstream fakeOutput;
	
};

State createTestGame(GameContext &context, unsigned int humanPlayers, unsigned int computerPlayers, unsigned int width, unsigned int height, int initialMines);