#include <minefield/minefield.h>
#include <minefield/select_mines.h>
#include <minefield/shared.h>
#include <minefield/show_board.h>

#include <iomanip>
#include <iostream>

void printCell(std::ostream& outputStream, int cellValue)
{
    outputStream << std::setw(3) << cellValue << " ";
}

NextState showBoard(GameContext& context)
{
    printMessage(context.io.outputStream, "What a battlefield! Hide your mines carefully --but remember, tiles marked with -1 are disabled!\n");

    for (int i = 0; i < context.board.boardCells.size(); ++i)
    {
        if (i % context.board.width == 0)
        {
            printMessage(context.io.outputStream, "\n");
        }
        printCell(context.io.outputStream, context.board.boardCells[i]);
    }
    printMessage(context.io.outputStream, "\n");
    return {&selectMines};
}
