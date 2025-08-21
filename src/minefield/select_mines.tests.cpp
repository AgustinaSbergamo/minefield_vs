#include <gtest/gtest.h>
#include <minefield/setup_game.h>
#include <minefield/select_mines.h>
#include <minefield/create_test_game.h>

TEST(MINES, selectMines_transitions_to_selectGuesses) {

	GameContext context = createTestGame(1, 4, 30, 30, 8);
	std::istringstream fakeInput;
	std::ostringstream fakeOutput;
	context.io.inputStream = fakeInput;
	context.io.outputStream = fakeOutput;

}