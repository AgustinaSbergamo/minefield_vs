#include <minefield/testing_utils.h>

std::string TestSetup::getInputBuffer() {
	return fakeInput.str();
}
void TestSetup::setInputBuffer(std::string input) {
	fakeInput.rdbuf()->str(input);
}
std::string TestSetup::getOutputBuffer() {
	return fakeOutput.str();
}
void TestSetup::setOutputBuffer(std::string input) {
	fakeOutput.rdbuf()->str(input);
}

template <typename T>
void addInput(std::string &currentInput, T const& newInput) {
	currentInput.append(std::to_string(newInput) + "\n");
}

//helper function for quickly instantiating games without user input
State createTestGame(GameContext &context, unsigned int humanPlayers, unsigned int computerPlayers, unsigned int width, unsigned int height, int initialMines) {
	std::string inputString = "";
	addInput(inputString, humanPlayers);// human players
	addInput(inputString, computerPlayers);// bot players
	for (int i = 1; i <= humanPlayers; i++) { // name of every human
		addInput(inputString, "human_" + std::to_string(i));
	}
	addInput(inputString, width);//width of board
	addInput(inputString, height);// height of board
	addInput(inputString, initialMines);// initial mines
	std::istringstream fakeInput(inputString);
	context.io.inputStream = fakeInput;

	return setupGame(context);
}