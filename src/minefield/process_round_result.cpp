#include <minefield/exit_game.h>
#include <minefield/minefield.h>
#include <minefield/shared.h>
#include <minefield/show_board.h>

#include <iostream>

unsigned int getMaxMineCount(std::vector<Player> const& players)
{
    unsigned int max = 0;
    for (Player const& player : players)
    {
        if (player.mines.size() > max)
        {
            max = player.mines.size();
        }
    }
    return max;
}

NextState processRoundResult(GameContext& context)
{
    unsigned int maxMineCount = getMaxMineCount(context.players);
    if (maxMineCount > context.board.availableCells.size())
    {
        printMessage(context.outputStream,
            "It looks like the available cells on the board are not enough to keep playing. We'll have to call it a tie between the remaining players and "
            "start over!\n");
        return {&exitGame};
    }

    for (auto iterator = context.players.begin(); iterator != context.players.end();)
    {
        if (iterator->mines.empty())
        {
            printMessage(context.outputStream, iterator->name, " got completely mined out!\n");
            iterator = context.players.erase(iterator);
        }
        else
        {
            ++iterator;
        }
    }

    if (context.players.empty())
    {
        printMessage(context.outputStream, "A perfect tie, in total destruction. No mines, no survivors!\n");
        return {&exitGame};
    }
    else if (context.players.size() == 1)
    {
        printMessage(context.outputStream, context.players[0].name, " takes the crown! The sole survivor of the minefield!\n");
        return {&exitGame};
    }
    else
    {
        printMessage(context.outputStream, context.players.size(), " players still in the game. Next round begins!\n");
        return {&showBoard};
    }
}