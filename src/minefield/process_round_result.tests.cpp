#include <gtest/gtest.h>
#include <minefield/minefield.h>
#include <minefield/setup_game.h>

std::string mockGetUserInput(){
    static int identifier = 1;
    identifier++;
    return ("roberto" + std::to_string(identifier));
}