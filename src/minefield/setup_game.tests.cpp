#include <gtest/gtest.h>

#include <minefield/create_test_game.h>
#include <minefield/minefield.h>
#include <minefield/setup_game.h>
#include <minefield/show_board.h>

TEST(INPUT, input_validation_works_correctly) {
	auto getOutputofReading = [](unsigned int min, unsigned int max, unsigned int value) { //
		std::string input = "";
		input.append(std::to_string(value) + "\n");
		if (value < min || value > max) {
			input.append(std::to_string(max) + "\n");
		}
		std::cout << input << std::endl;
		std::istringstream fakeInput(input);
		std::ostringstream fakeOutput;
		GameContext context;
		context.io.inputStream = fakeInput;
		context.io.outputStream = fakeOutput;
		readIntInRange(min, max, context.io);
		return fakeOutput.str();
	};

	std::string expectedErrorMessage = "Too wild! Choose something in the safe zone";
	EXPECT_EQ(getOutputofReading(0, 5, 3).find(expectedErrorMessage), std::string::npos);
	EXPECT_NE(getOutputofReading(0, 5, 9).find(expectedErrorMessage), std::string::npos);
	EXPECT_EQ(getOutputofReading(0, 5, 5).find(expectedErrorMessage), std::string::npos);
	// EXPECT_EQ(getOutputofReading(-1, 5, 3).find(expectedErrorMessage), std::string::npos); // currently these tests hang up the program
	// EXPECT_ANY_THROW(getOutputofReading(5, 0, 9));
}

TEST(SETUP, game_is_set_up_correctly) { // made by agus to guide me, thanks agus!
	std::istringstream fakeInput;
	std::ostringstream fakeOutput;

	GameContext context;

	context.io.inputStream = fakeInput;
	context.io.outputStream = fakeOutput;
	NextState next = createTestGame(context, 1, 2, 24, 24, 3);

	EXPECT_EQ(context.players.size(), 3);
	EXPECT_EQ(context.players[0].name, "human_1");
	EXPECT_EQ(context.board.width, 24);
	EXPECT_EQ(context.board.height, 24);
	EXPECT_EQ(context.board.initialMines, 3);
	EXPECT_EQ(next.updateFunction, &showBoard);
	std::string output = fakeOutput.str();
	EXPECT_NE(output.find("Welcome to Minefield"), std::string::npos);
}

TEST(SETUP, board_does_not_accept_invalid_values) {
	int const MAXWIDTH = 50;
	int const MAXHEIGHT = 50;

	auto buildInputString = [](int width, int height) {					  // build the string of player inputs for the game width and height definitions
		auto buildDimensionString = [](int dimension, int dimensionMax) { // build the string of player inputs for each dimension
			std::string gameDimensionInputString = "";
			gameDimensionInputString.append(std::to_string(dimension) + "\n");
			if (dimension > MAX_BOARD_SIZE || dimension < MIN_BOARD_SIZE)			  // if this is the case, the program will output an error message and will ask for input again
				gameDimensionInputString.append(std::to_string(dimensionMax) + "\n"); // this time we create an input that will be accepted
			return gameDimensionInputString;
		};

		std::string gameDimensionsInputString = "";
		gameDimensionsInputString.append(buildDimensionString(width, MAXWIDTH));
		gameDimensionsInputString.append(buildDimensionString(height, MAXHEIGHT));
		return gameDimensionsInputString;
	};

	auto getOutputWH = [buildInputString](int width, int height) { // build the whole input string
		std::string input = "1\n2\nRoberto\n" + buildInputString(width, height) + "\n3\n ";
		std::istringstream fakeInput(
			input); // fake input and output must be defined within each function and not in a common fixture because they will become inaccesible outside of the scope they were created in
		std::ostringstream fakeOutput;
		GameContext context;
		context.io.inputStream = fakeInput;
		context.io.outputStream = fakeOutput;
		NextState next = setupGame(context);
		std::string output = fakeOutput.str();
		return output;
	};

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