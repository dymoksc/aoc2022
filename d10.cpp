#include <iostream>
#include <string>
#include <cassert>
#include <array>

using namespace std;

typedef array<array<char, 40>, 6> Screen;

constexpr const int screenWidth = 40;
constexpr const int screenHeight = 6;
constexpr const int spriteSideLen = 2;

void updateScreen(int cycle, int reg, Screen& screen) {
	int i = cycle / screenWidth;
	int j = cycle % screenWidth;

	if (i > screenHeight - 1) {	// Reached the end of the screen
		return;
	}

   screen[i][j] = abs(reg - j) < spriteSideLen ? '#' : '.';
}

int main() {
	string command;
	int operand;
	int cycle = 0;
	int reg = 1;
	Screen screen{};

	updateScreen(cycle, reg, screen);
	while (cin.peek() != -1) {
		cin >> command;
		if (command == "noop") {
			cycle += 1;
			updateScreen(cycle, reg, screen);
		} else if (command == "addx") {
			cin >> operand;

			cycle += 1;
			updateScreen(cycle, reg, screen);

			cycle += 1;
			reg += operand;
			updateScreen(cycle, reg, screen);
		} else {
			assert(false);
		}

		assert(cin.get() == '\n');
	}

	for (auto& row : screen) {
		for (auto c : row) {
			cout << c;
		}
		cout << endl;
	}

	return 0;
}
