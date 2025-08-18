#include <minefield/exit_game.h>
#include <minefield/minefield.h>
#include <minefield/process_mine_detection.h>
#include <minefield/select_mines.h>
#include <minefield/shared.h>

#include <iostream>
#include <random>
#include <string>
#include <vector>

void printMineSelection(std::vector<unsigned int> const& mines, std::ostream& outputStream, std::string const& message)
{
    printMessage(outputStream, message);
    for (int mine : mines)
    {
        printMessage(outputStream, mine, ' ');
    }
    printMessage(outputStream, "\n");
}

void randomMineSelection(int selectionSize,
    std::vector<unsigned int>& randomSelection,
    std::vector<unsigned int> const& availableCells,
    RandomGenerationFn const& randomGenerator)
{
    randomSelection.clear();
    while (randomSelection.size() < selectionSize)
    {
        int randomIndex = randomGenerator(0, availableCells.size() - 1);
        int candidate = availableCells[randomIndex];
        if (std::find(randomSelection.begin(), randomSelection.end(), candidate) == randomSelection.end())
        {
            randomSelection.push_back(candidate);
        }
    }
}

void manualMineSelection(int selectionSize,
    std::vector<unsigned int>& minesVector,
    std::vector<unsigned int> const& availableCells,
    std::ostream& outputStream,
    GetInputFn<unsigned int> getInput)
{
    minesVector.clear();
    for (int i = 0; i < selectionSize; ++i)
    {
        bool validSelectedCell = false;
        unsigned int selectedCell = 0;

        while (!validSelectedCell)
        {
            printMessage(outputStream, "Enter cell #", (i + 1), ": ");
            selectedCell = getInput();

            if (std::find(availableCells.begin(), availableCells.end(), selectedCell) == availableCells.end())
            {
                printMessage(outputStream, "Cell ", selectedCell, " is disabled! Please choose another one\n");
                continue;
            }

            if (std::find(minesVector.begin(), minesVector.end(), selectedCell) != minesVector.end())
            {
                printMessage(outputStream, "You already picked cell ", std::to_string(selectedCell), ". Please choose a different one!\n");
                continue;
            }

            validSelectedCell = true;
        }

        minesVector.push_back(selectedCell);
    }
}

unsigned int getRivalsMaxMineCount(Player const& player, std::vector<Player> const& players)
{
    unsigned int max = 0;
    for (Player const& rivalPlayer : players)
    {
        if (&rivalPlayer != &player && rivalPlayer.mines.size() > max)
        {
            max = rivalPlayer.mines.size();
        }
    }
    return max;
}

NextState selectGuesses(GameContext& context)
{
    printMessage(
        context.outputStream, "Alright, it's time to strike!\nRemember: if you pick the spots where you hid your own mines, you'll blow up your stash!\n");
    for (Player& player : context.players)
    {
        unsigned int minesToGuess = getRivalsMaxMineCount(player, context.players);
        if (player.type == PlayerType::Human)
        {
            printMessage(context.outputStream, player.name, ", just so you don't trip over your own traps: your mines are in spots ");
            printMineSelection(player.mines, context.outputStream);

            printMessage(context.outputStream, "\nYou've got ", minesToGuess,
                " guess(es) --just as many as the mines your most dangerous rival has left. Where will you shoot?\n");
            manualMineSelection(minesToGuess, player.guesses, context.board.availableCells, context.outputStream, getInputFromCin);
        }
        else
        {
            randomMineSelection(minesToGuess, player.guesses, context.board.availableCells, context.randomGenerator);
        }
#ifdef DEBUG
        printMineSelection(player.guesses, player.name + "'s guesses: ");
#endif
    }
    return {&processMineDetection};
}

NextState selectMines(GameContext& context)
{
    for (Player& player : context.players)
    {
        if (player.type == PlayerType::Human)
        {
            printMessage(context.outputStream, player.name, " it's your turn! Pick ", player.mines.size(), " spot(s) to hide your mine(s)\n");
            manualMineSelection(player.mines.size(), player.mines, context.board.availableCells, context.outputStream, getInputFromCin);
        }
        else
        {
            randomMineSelection(player.mines.size(), player.mines, context.board.availableCells, context.randomGenerator);
        }
#ifdef DEBUG
        printMineSelection(player.mines, player.name + "'s mines: ");
#endif
    }
    return {&selectGuesses};
}
