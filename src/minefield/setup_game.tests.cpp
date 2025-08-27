#include <gtest/gtest.h>

#include <minefield/testing_utils.h>
#include <minefield/minefield.h>
#include <minefield/setup_game.h>
#include <minefield/show_board.h>

auto getOutputofReading = [](unsigned int min, unsigned int max, unsigned int value) { // gets the console output when an input string is sent to the readIntInRange function
	std::string input = "";
	input.append(std::to_string(value) + '\n');
	if (value < min || value > max) { // if input is invalid, the game will asks us to input a valid value
		input.append(std::to_string(max) + '\n');
	}
	TestContext testContext;
	setInputBuffer(testContext, input); // the input string consists of of entering a value, then entering another value of the first one is not within the specified range
	readIntInRange(min, max, testContext.context.io);
	return getOutputBuffer(testContext);
};
TEST(INPUT, input_validation_works_correctly) {
	
	std::string expectedErrorMessage = "Too wild! Choose something in the safe zone";
	EXPECT_EQ(getOutputofReading(0, 5, 3).find(expectedErrorMessage), std::string::npos);
	EXPECT_EQ(getOutputofReading(0, 5, 5).find(expectedErrorMessage), std::string::npos);
	EXPECT_EQ(getOutputofReading(0, 5, 0).find(expectedErrorMessage), std::string::npos);
	EXPECT_NE(getOutputofReading(0, 5, 9).find(expectedErrorMessage), std::string::npos);
	/* currently these tests hang up the program
	EXPECT_EQ(getOutputofReading(-1, 5, 3).find(expectedErrorMessage), std::string::npos);
	EXPECT_ANY_THROW(getOutputofReading(5, 0, 9));
	*/
}

TEST(SETUP, game_is_set_up_correctly) { // made by agus to guide me, thanks agus!
	TestContext testContext;

	GameContext &context = testContext.context;
	NextState next = setupTestGame(testContext);

	EXPECT_EQ(context.players.size(), 3);
	EXPECT_EQ(context.players[0].name, "human_1");
	EXPECT_EQ(context.board.width, 24);
	EXPECT_EQ(context.board.height, 24);
	EXPECT_EQ(context.board.initialMines, 3);
	EXPECT_EQ(next.updateFunction, &showBoard);
	std::string output = getOutputBuffer(testContext);
	EXPECT_NE(output.find("Welcome to Minefield"), std::string::npos);
}

auto buildInputString = [](int width, int height) { // build the string of player inputs for the game width and height definitions
	auto buildDimensionString = [](int dimension) { // build the string of player inputs for each dimension
		std::string gameDimensionInputString = "";
		gameDimensionInputString.append(std::to_string(dimension) + '\n');
		if (dimension > MAX_BOARD_SIZE || dimension < MIN_BOARD_SIZE) { // if this is the case, the program will output an error message and will ask for input again
			gameDimensionInputString.append(std::to_string(MAX_BOARD_SIZE) + '\n'); // this time we create an input that will be accepted
		}
		return gameDimensionInputString;
	};
	std::string gameDimensionsInputString = "";
	gameDimensionsInputString.append(buildDimensionString(width));
	gameDimensionsInputString.append(buildDimensionString(height));
	return gameDimensionsInputString;
};

auto getOutputWH = [](int width, int height) { // build the whole input string
	TestContext testContext;
	GameContext &context = testContext.context;

	std::string input = "1\n2\nRoberto\n" + buildInputString(width, height) + "\n3\n ";
	setInputBuffer(testContext, input);
	// fake input and output must be defined within each function and not in a common fixture because they will become inaccesible outside of the scope they were created in
	NextState next = setupGame(context); // needs to use setupGame instead of setupTestGame since we expect there to be additional input needed for correcting non-valid dimension values
	std::string output = getOutputBuffer(testContext);
	return output;
};
TEST(SETUP, board_does_not_accept_invalid_values) {
	std::string expectedErrorMessage = "Too wild! Choose something in the safe zone";
	EXPECT_EQ((getOutputWH(MAX_BOARD_SIZE, MAX_BOARD_SIZE)).find(expectedErrorMessage), std::string::npos); // there will be no error message if width and height are valid values
	EXPECT_NE((getOutputWH(MAX_BOARD_SIZE + 1, MAX_BOARD_SIZE)).find(expectedErrorMessage), std::string::npos);
	EXPECT_NE((getOutputWH(MAX_BOARD_SIZE, MAX_BOARD_SIZE + 1)).find(expectedErrorMessage), std::string::npos);
	EXPECT_NE((getOutputWH(MAX_BOARD_SIZE + 1, MAX_BOARD_SIZE + 1)).find(expectedErrorMessage), std::string::npos);
	EXPECT_EQ((getOutputWH(MIN_BOARD_SIZE, MIN_BOARD_SIZE)).find(expectedErrorMessage), std::string::npos);
	EXPECT_NE((getOutputWH(MIN_BOARD_SIZE - 1, MIN_BOARD_SIZE)).find(expectedErrorMessage), std::string::npos);
	EXPECT_NE((getOutputWH(MIN_BOARD_SIZE, MIN_BOARD_SIZE - 1)).find(expectedErrorMessage), std::string::npos);
	EXPECT_NE((getOutputWH(MIN_BOARD_SIZE - 1, MIN_BOARD_SIZE - 1)).find(expectedErrorMessage), std::string::npos);
}