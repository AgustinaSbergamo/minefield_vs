#include <minefield/minefield.h>
#include <minefield/setup_game.h>
#include <minefield/shared.h>
#include <minefield/show_board.h>

#include <iostream>
#include <limits>

int readIntInRange(unsigned int min, unsigned int max, GameContext::IO& io, GetInputFn<unsigned int> getInput)
{
    unsigned int input = 0;
    bool validInput = false;

    while (!validInput)
    {
        input = getInput(io.inputStream, io.outputStream);
        validInput = input >= min && input <= max;
        if (!validInput)
        {
            printMessage(io.outputStream, "Too wild! Choose something in the safe zone: ", min, " to ", max, "\n");
        }
    }
    return input;
}

void createPlayers(GameContext& context, unsigned int humanPlayers, unsigned int computerPlayers, GetInputFn<std::string> getInput)
{
    context.players.clear();
    std::vector<std::string> usedNames;
    unsigned int playerNumber = 1;

    for (unsigned int i = 0; i < humanPlayers; ++i)
    {
        std::string name;
        bool validName = false;

        while (!validName)
        {
            printMessage(context.io.outputStream, "What's the name of human player #", playerNumber, "? ");
            name = getInput(context.io.inputStream, context.io.outputStream);

            validName = std::find(usedNames.begin(), usedNames.end(), name) == usedNames.end();
            if (!validName)
            {
                printMessage(context.io.outputStream, "That name already exists. Please choose a different one!\n");
            }
            else
            {
                usedNames.push_back(name);
            }
        }

        Player player;
        player.name = name;
        player.type = PlayerType::Human;

        context.players.push_back(player);
        ++playerNumber;
    }

    for (unsigned int i = 0; i < computerPlayers; ++i)
    {
        Player player;
        player.name = "Computer_" + std::to_string(i + 1);
        player.type = PlayerType::Computer;
        printMessage(context.io.outputStream, "Our creative team (the compiler) named computer player #", playerNumber, ": ", player.name, "\n");
        context.players.push_back(player);
        ++playerNumber;
    }
}

NextState setupGame(GameContext& context)
{
    printMessage(context.io.outputStream,
        "=================================\nWelcome to Minefield, brave soul!\n=================================\nLet's start defining the basics of the "
        "game\n");

    printMessage(context.io.outputStream, "First things first: how many human players will be joining the game? (up to 5!)\n");
    int humanPlayers = readIntInRange(1, MAX_PLAYERS, context.io);

    printMessage(context.io.outputStream, "And how many fearless computer-controlled players shall we unleash? (again, no more than 5)\n");
    int minComputerPlayers = (humanPlayers > 1) ? 0 : 1;
    int computerPlayers = readIntInRange(minComputerPlayers, MAX_PLAYERS, context.io);

    printMessage(
        context.io.outputStream, "Perfect! That makes us ", (humanPlayers + computerPlayers), ". Now, to keep things organized, let's name our heroes\n");
    createPlayers(context, humanPlayers, computerPlayers);

    printMessage(context.io.outputStream, "Let's craft the board now. How many tiles across? (it should be a number between 24 and 50)\n");
    context.board.width = readIntInRange(MIN_BOARD_SIZE, MAX_BOARD_SIZE, context.io);

    printMessage(context.io.outputStream, "Now, how many tiles from top to bottom? (again, between 24 and 50)\n");
    context.board.height = readIntInRange(MIN_BOARD_SIZE, MAX_BOARD_SIZE, context.io);

    printMessage(context.io.outputStream, "Final step: how many mines should we drop? (let's say, between 3 and 8)\n");
    context.board.initialMines = readIntInRange(MIN_MINES, MAX_MINES, context.io);

    for (Player& player : context.players)
    {
        player.mines = std::vector<unsigned int>(context.board.initialMines);
        player.guesses = std::vector<unsigned int>(context.board.initialMines);
    }

    for (int i = 0; i < context.board.width * context.board.height; i++)
    {
        context.board.boardCells.push_back(i + 1);
        context.board.availableCells.push_back(i + 1);
    }
    return {&showBoard};
}