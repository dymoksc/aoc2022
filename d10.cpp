#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int cycle = 1;
int reg = 1;
int sum{};

void dump() {
	if (cycle <= 220 && (cycle + 20) % 40 == 0) {
		cout << cycle << ":\tX = " << reg << "\t" << cycle * reg << endl;
		sum += cycle * reg;
	}
}

int main() {
	string command;
	int operand;

	dump();
	while (cin.peek() != -1) {
		cin >> command;
		// cout << command << endl;
		if (command == "noop") {
			cycle += 1;
			dump();
		} else if (command == "addx") {
			cin >> operand;

			cycle += 1;
			dump();

			cycle += 1;
			reg += operand;
			dump();
		} else {
			assert(false);
		}

		assert(cin.get() == '\n');
	}

	cout << "Sum: " << sum << endl;

	return 0;
}
