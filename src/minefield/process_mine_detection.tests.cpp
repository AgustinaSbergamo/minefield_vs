#include <gtest/gtest.h>
#include <minefield/process_mine_detection.h>
#include <minefield/testing_utils.h>
#include <minefield/select_mines.h>


TEST(CELL, disableCell_disables_cell) {
	const int numberOfTests = 3;
	for (int currentTest = 0; currentTest < numberOfTests; currentTest++) {
		TestContext testContext;
		GameContext &context = testContext.context;
		setupTestGame(testContext);
		int numberOfCells = context.board.boardCells.size();
		// we divide the number of cells by the amount of test we'll run, then we test the value at the beginning of each of these splices
		// since the cell numbers start at 1 and not at 0, we have to make sure that the first cell we test has a valid number (equal or greater than 1)
		unsigned int cellToDisable = std::max(numberOfCells / (numberOfTests - 1) * currentTest, 1); 

		std::unordered_set<unsigned int> boardUsedCells;
		boardUsedCells.insert(cellToDisable);
		disableUsedCells(boardUsedCells, context.board);

		ASSERT_EQ(std::find(context.board.availableCells.begin(), context.board.availableCells.end(), cellToDisable), context.board.availableCells.end());
	}
}

TEST(PLAYER, resizePlayerMineCount_shrinks_size) {
}

std::string setTestSelection(int i, unsigned int playersMineSize) {
	int offset = i * playersMineSize;
	std::string testInput;
	for (int cell = 0; cell < playersMineSize; cell++) {
		concatInput(testInput, cell + 1 + offset);
	}
	return testInput;
}

TEST(MINES, getExplodedMines_detects_self_hits) {
	TestContext testContext;
	GameContext &context = testContext.context;
	setupTestGame(testContext, 3, 0);

	std::string testInput;
	unsigned int playerCount = context.players.size();
	unsigned int playersMineSize = context.board.initialMines;

	for (int i = 0; i < playerCount; i++) {
		testInput.append(setTestSelection(i, playersMineSize));
	}
	setInputBuffer(testContext, testInput);
	selectMines(context);

	for (int i = 0; i < playerCount; i++) {
		testInput.append(setTestSelection(i, playersMineSize));
	}
	setInputBuffer(testContext, testInput);
	selectGuesses(context);

	std::set<unsigned int> selfMineHits;
	for (Player &player: context.players) {
		std::set<unsigned int> playerSelfMineHits = getExplodedMines(player.mines, player.guesses);
		selfMineHits.insert(playerSelfMineHits.begin(), playerSelfMineHits.end());
	}

	EXPECT_EQ(selfMineHits.size(), playersMineSize * playerCount);
	
}


TEST(MINE_DETECTION, disableCell_disables_cell) {
}



