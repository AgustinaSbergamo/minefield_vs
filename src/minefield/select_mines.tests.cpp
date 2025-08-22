#include <gtest/gtest.h>
#include <minefield/show_board.h>
#include <minefield/setup_game.h>
#include <minefield/select_mines.h>
#include <minefield/create_test_game.h>

TEST(MINES, selectMines_transitions_to_selectGuesses) {

	GameContext context;
	std::istringstream fakeInput;
	std::ostringstream fakeOutput;
	context.io.inputStream = fakeInput;
	context.io.outputStream = fakeOutput;
	NextState next = createTestGame(context, 1, 4, 30, 30, 8);
	ASSERT_EQ(next.updateFunction, &showBoard);
}