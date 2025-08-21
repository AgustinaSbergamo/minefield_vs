#include <gtest/gtest.h>
#include <minefield/minefield.h>

template <typename T>
T setupGameInputStream() {
	static int invocation = 0;
	int const botCount = 4;
	if (invocation == 0) { // how many human players will be joining the game
		invocation++;
		return 0;
	}
	if (invocation == 1) { // how many fearless computer-controlled players shall we unleash
		return botCount;
	}
	if (invocation >= 2 && invocation < 2 +botCount) {
        return ("roberto " + std::to_string(invocation - 2));
	}
}

TEST(ASD, dsa) {
}
