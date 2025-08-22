#include <gtest/gtest.h>
#include <minefield/create_test_game.h>
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