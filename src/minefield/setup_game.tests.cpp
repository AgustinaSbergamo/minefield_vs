#include <gtest/gtest.h>
#include <minefield/setup_game.h>
#include <minefield/minefield.h>
#include <minefield/show_board.h>

TEST(SETUP, game_is_set_up_correctly) { // made by agus to guide me, thanks agus!
	std::istringstream fakeInput("1\n2\nRoberto\n24\n24\n3\n");
	std::ostringstream fakeOutput;

	GameContext context;
	context.io.inputStream = fakeInput;
	context.io.outputStream = fakeOutput;

	NextState next = setupGame(context);

	EXPECT_EQ(context.players.size(), 3);
	EXPECT_EQ(context.players[0].name, "Roberto");
	EXPECT_EQ(context.board.width, 24);
	EXPECT_EQ(context.board.height, 24);
	EXPECT_EQ(context.board.initialMines, 3);
	EXPECT_EQ(next.updateFunction, &showBoard);
	std::string output = fakeOutput.str();
	EXPECT_NE(output.find("Welcome to Minefield"), std::string::npos);
}

TEST(SETUP, board_does_not_accept_invalid_values) {
	const int MAXWIDTH = 50;
	const int MAXHEIGHT = 50;

	auto buildInputString = [](int width, int height) { // build the string of player inputs for the game width and height definitions
		auto buildDimensionString = [](int dimension, int dimensionMax) { // build the string of player inputs for each position
			std::string gameDimensionInputString = "";
			gameDimensionInputString.append(std::to_string(dimension) + "\n");
			if (dimension > dimensionMax) // if this is the case, the program will output an error message and will ask for input again
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
		std::istringstream fakeInput(input); //fake input and output must be defined within each function and not in a common fixture because they will become inaccesible outside of the scope they were created in
		std::ostringstream fakeOutput;
		GameContext context;
		context.io.inputStream = fakeInput;
		context.io.outputStream = fakeOutput;
		NextState next = setupGame(context);
		std::string output = fakeOutput.str();
		return output;
	};

	std::string expectedErrorMessage = "Too wild! Choose something in the safe zone";
	EXPECT_EQ((getOutputWH(MAXWIDTH, MAXHEIGHT)).find(expectedErrorMessage), std::string::npos); // there will be no error message if width and height are valid values
	EXPECT_NE((getOutputWH(MAXWIDTH + 1, MAXHEIGHT)).find(expectedErrorMessage), std::string::npos);
	EXPECT_NE((getOutputWH(MAXWIDTH, MAXHEIGHT + 1)).find(expectedErrorMessage), std::string::npos);
	EXPECT_NE((getOutputWH(MAXWIDTH + 1, MAXHEIGHT + 1)).find(expectedErrorMessage), std::string::npos);
	//will build for minimum values when agus defines dimension constraint values as global constants 
}