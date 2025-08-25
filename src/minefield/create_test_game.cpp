#include <minefield/create_test_game.h>

//helper function for quickly instantiating games without user input
State createTestGame(GameContext &context, unsigned int humanPlayers, unsigned int botPlayers, unsigned int width, unsigned int height, int initialMines) {
	std::string inputString = "";
	inputString.append(std::to_string(humanPlayers) + "\n"); // human players
	inputString.append(std::to_string(botPlayers) + "\n"); //bot players
	for (int i = 1; i <= humanPlayers; i++) { // name of every human
		inputString.append("human_" + std::to_string(i) + "\n");
	}
	inputString.append(std::to_string(width) + "\n"); //width of board
	inputString.append(std::to_string(height) + "\n"); // height of board
	inputString.append(std::to_string(initialMines) + "\n"); // initial mines

	std::istringstream fakeInput(inputString);
	context.io.inputStream = fakeInput;

	return setupGame(context);
}