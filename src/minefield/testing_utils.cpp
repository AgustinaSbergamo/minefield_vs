#include <minefield/testing_utils.h>

std::string getInputBuffer(TestContext const &testContext) {
	return testContext.fakeInput.str();
}
void setInputBuffer(TestContext &testContext, std::string input) {
	testContext.fakeInput.rdbuf()->str(input);
}
std::string getOutputBuffer(TestContext const &testContext) {
	return testContext.fakeOutput.str();
}
void setOutputBuffer(TestContext &testContext, std::string input) {
	testContext.fakeOutput.rdbuf()->str(input);
}

template <typename T>
void concatInput(std::string &currentInput, T const newInput) {
	std::ostringstream mockputStream;
	mockputStream << newInput;
	currentInput.append(mockputStream.str() + '\n');
}

//helper function for quickly instantiating games without user input
State setupTestGame(TestContext &testContext, unsigned int humanPlayers, unsigned int computerPlayers, unsigned int width, unsigned int height, int initialMines) {
	std::string inputString;
	if (humanPlayers < 1) throw std::exception("must be at least one human player!");

	concatInput(inputString, humanPlayers);// human players
	concatInput(inputString, computerPlayers);// bot players
	for (int i = 1; i <= humanPlayers; i++) { // name of every human
		concatInput(inputString, "human_" + std::to_string(i));
	}
	concatInput(inputString, width);//width of board
	concatInput(inputString, height);// height of board
	concatInput(inputString, initialMines);// initial mines
	setInputBuffer(testContext, inputString);

	return setupGame(testContext.context);
}