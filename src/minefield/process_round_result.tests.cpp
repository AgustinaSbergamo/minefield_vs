#include <gtest/gtest.h>

#include <minefield/testing_utils.h>
#include <minefield/process_round_result.h>
#include <minefield/show_board.h>
#include <minefield/exit_game.h>

TEST(PROCESSING, processRoundResult_leads_to_game_continuation) {
	TestContext testContext;
	GameContext &context = testContext.context;
	setupTestGame(testContext);
	EXPECT_EQ(processRoundResult(context).updateFunction, showBoard);
}

TEST(PROCESSING, processRoundResult_leads_to_game_end_with_winner) {
	TestContext testContext;
	GameContext &context = testContext.context;
	for (int winner = 0; winner < MAX_PLAYERS; winner++) { // for every possible winning player
		for (int i = 1; i <= MAX_PLAYERS; i++) { 
			setupTestGame(testContext, i, MAX_PLAYERS - i, 24, 24, 3);
			std::string nameOfWinner = context.players[winner].name;
			for (int j = 0; j < context.players.size(); j++) {
				if (j != winner) {
					context.players[j].mines.clear();
				}
			}
			NextState state = processRoundResult(context);
			std::string expectedMessage = context.players[0].name + " takes the crown! The sole survivor of the minefield!";
			EXPECT_EQ(nameOfWinner, context.players[0].name);
			EXPECT_NE(getOutputBuffer(testContext).find(expectedMessage), std::string::npos);
			EXPECT_EQ(state.updateFunction, exitGame);
		}
	}
}

TEST(PROCESSING, processRoundResult_leads_to_game_end_in_draw_no_mines) {
	TestContext testContext;
	GameContext &context = testContext.context;
	setupTestGame(testContext);
	for (int i = 0; i < context.players.size(); i++){
		context.players[i].mines.clear();
	}
	NextState state = processRoundResult(context);
	std::string expectedMessage = "A perfect tie, in total destruction. No mines, no survivors!";
	EXPECT_NE(getOutputBuffer(testContext).find(expectedMessage), std::string::npos);
	EXPECT_EQ(state.updateFunction, exitGame);
		
	
}

TEST(PROCESSING, processRoundResult_leads_to_game_end_in_draw_not_enough_available_cells) {
	TestContext testContext;
	GameContext &context = testContext.context;
	setupTestGame(testContext);
	context.board.availableCells.resize(context.board.initialMines - 1);
	NextState state = processRoundResult(context);
	std::string expectedMessage = "It looks like the available cells on the board are not enough to keep playing. We'll have to call it a tie between the remaining players";
	EXPECT_NE(getOutputBuffer(testContext).find(expectedMessage), std::string::npos);
	EXPECT_EQ(state.updateFunction, exitGame);
}