#include <gtest/gtest.h>
#include <minefield/testing_utils.h>
#include <minefield/select_mines.h>
#include <minefield/setup_game.h>
#include <minefield/show_board.h>

TEST(MINES, selectMines_transitions_to_selectGuesses) {

	GameContext context;
	std::istringstream fakeInput;
	std::ostringstream fakeOutput;
	context.io.inputStream = fakeInput;
	context.io.outputStream = fakeOutput;
	NextState next = createTestGame(context, 1, 4, 30, 30, 8);
	ASSERT_EQ(next.updateFunction, &showBoard);
}

TEST(MINES, selectMines_places_mines_in_specified_spot) {

	GameContext context;
	std::ostringstream fakeOutput;
	context.io.outputStream = fakeOutput;

	int humanPlayers = MAX_PLAYERS;
	int botPlayers = MAX_PLAYERS - humanPlayers;
	NextState next = createTestGame(context, humanPlayers, botPlayers, MAX_BOARD_SIZE, MAX_BOARD_SIZE, MAX_MINES);

	std::string mineInput = ""; // build input for selectMines function
	int i = 1; // position of mine
	for (int player = 0; player < humanPlayers; player++) { // for each player in the game
		for (int mine = 0; mine < context.players[player].mines.size(); mine++) { // for each mine the player can place
			mineInput.append(std::to_string(i) + "\n");
			i++;
		}
	}
	std::istringstream fakeInput(mineInput);
	context.io.inputStream = fakeInput;
	selectMines(context);

	i = 1;
	for (int player = 0; player < humanPlayers; player++) { // for each player in the game
		for (int mine = 0; mine < context.players[player].mines.size(); mine++) { // for each mine the player can place
			EXPECT_EQ(context.players[player].mines[mine], i);
			i++;
		}
	}
}

TEST(MINES, selectMines_handles_out_of_bounds_inputs) {

	GameContext context;
	std::ostringstream fakeOutput;
	context.io.outputStream = fakeOutput;

	int humanPlayers = 1; //there will be only one human player
	int botPlayers = MAX_PLAYERS - humanPlayers;
	NextState next = createTestGame(context, humanPlayers, botPlayers, MAX_BOARD_SIZE, MAX_BOARD_SIZE, MIN_MINES);

	std::string mineInput = ""; 
	int validPosition = 1;
	int invalidPosition = (MAX_BOARD_SIZE * MAX_BOARD_SIZE) + 1; 

	for (int player = 0; player < humanPlayers; player++) { // for each human player in the game
		for (int mine = 0; mine < context.players[player].mines.size(); mine++) { // for each mine the player can place
			mineInput.append(std::to_string(invalidPosition) + "\n"); //we input an invalid position
			mineInput.append(std::to_string(validPosition) + "\n");  //then, when asked for correction, we input a valid position
			validPosition++;
		}
	}

	std::istringstream fakeInput(mineInput);
	context.io.inputStream = fakeInput;
	selectMines(context);

	std::string output = fakeOutput.str();
	std::string expectedErrorMessage = "Please choose a different one";
	size_t positionOfErrorInOutput;
	for (int mine = 0; mine < context.players[0].mines.size(); mine++) {
		// there will be an amount of ocurrences of "Error:" equal to the number of mines of the human player
		// thusly, we assert to find that number of substrings pertaining to manualMineSelection's invalid input response in the output string
		positionOfErrorInOutput = output.find(expectedErrorMessage); 
		ASSERT_NE(positionOfErrorInOutput, output.npos);
		output.erase(0, positionOfErrorInOutput + expectedErrorMessage.size());
	}
	// lastly we expect there to be no more ocurrences
	positionOfErrorInOutput = output.find(expectedErrorMessage);
	ASSERT_EQ(positionOfErrorInOutput, output.npos);
}