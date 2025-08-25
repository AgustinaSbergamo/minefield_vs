#include <gtest/gtest.h>
#include <minefield/testing_utils.h>
#include <minefield/select_mines.h>
#include <minefield/setup_game.h>
#include <minefield/show_board.h>

TEST(MINES, selectMines_transitions_to_selectGuesses) {
	TestContext testContext;
	GameContext &context = testContext.context;
	NextState next = setupTestGame(testContext, 1, 4, 30, 30, 8);
	EXPECT_EQ(next.updateFunction, &showBoard);
}

TEST(MINES, selectMines_places_mines_in_specified_spot) {

	TestContext testContext;
	GameContext& context = (testContext.context);

	int humanPlayers = MAX_PLAYERS;
	int computerPlayers = MAX_PLAYERS - humanPlayers;
	NextState next = setupTestGame(testContext, humanPlayers, computerPlayers, MAX_BOARD_SIZE, MAX_BOARD_SIZE, MAX_MINES);

	std::string mineInput = ""; // build input for selectMines function
	int i = 1; // position of mine
	for (int player = 0; player < humanPlayers; player++) { // for each player in the game
		for (int mine = 0; mine < context.players[player].mines.size(); mine++) { // for each mine the player can place
			mineInput.append(std::to_string(i) + "\n");
			i++;
		}
	}
	setInputBuffer(testContext, mineInput);
	selectMines(context);

	i = 1;
	for (int player = 0; player < humanPlayers; player++) { // for each player in the game
		for (int mine = 0; mine < context.players[player].mines.size(); mine++) { // for each mine the player can place
			EXPECT_EQ(context.players[player].mines[mine], i); // each player should have the corresponding amount of mines
			i++;
		}
	}
}

TEST(MINES, selectMines_handles_out_of_bounds_inputs) {

	TestContext testContext;
	GameContext &context = testContext.context;
	int humanPlayers = 1; //there will be only one human player
	int computerPlayers = MAX_PLAYERS - humanPlayers;
	NextState next = setupTestGame(testContext, humanPlayers, computerPlayers, MAX_BOARD_SIZE, MAX_BOARD_SIZE, MIN_MINES);

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

	std::string output = getOutputBuffer(testContext);
	std::string expectedErrorMessage = "Please choose a different one"; // if error message is changed, so too should this variable
	size_t positionOfErrorInOutput;
	for (int player = 0; player < humanPlayers; player++) {
		for (int mine = 0; mine < context.players[player].mines.size(); mine++) {
			positionOfErrorInOutput = output.find(expectedErrorMessage);
			// we expect there to be an amount of errors equal to the amount of mines placed by a human, since we make a mistake for each one
			// for this, we use the find function, which returns npos if the substring is not found within the string
			ASSERT_NE(positionOfErrorInOutput, output.npos);
			output.erase(0, positionOfErrorInOutput + expectedErrorMessage.size()); // we delete the input string until the currect ocurrence of an error
		}
	}
	// lastly we expect there to be no more ocurrences
	positionOfErrorInOutput = output.find(expectedErrorMessage);
	ASSERT_EQ(positionOfErrorInOutput, output.npos);
}