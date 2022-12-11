#include <numeric>
#include <iostream>
#include <algorithm>
#include <deque>
#include <string>
#include <cassert>
#include <vector>
#include <array>

using namespace std;

struct Monkey {
	deque<long> items{};
	char op{};
	int operand{};
	int divisor{};
	int testTrueDir{};
	int testFalseDir{};
	int inspections{};

	Monkey(istream& in) {
		string s;
		char c;

		// Monkey 1:
		in >> s;
		assert(s == "Monkey");
		in >> c;
		assert(c >= '0' && c <= '9');
		assert(in.get() == ':');

		//   Starting items: 52, 43, 92
		in >> s;
		assert(s == "Starting");
		in >> s;
		assert(s == "items:");
		assert(in.get() == ' ');
		while (in.peek() != '\n') {
			if (in.peek() == ',') {
				assert(in.get() == ',');
				assert(in.get() == ' ');
			}

			items.emplace_back();
			in >> items.back();
		}

		// Operation: new = old * old
		assert(in.get() == '\n');
		getline(in, s, '=');
		assert("  Operation: new " == s);
		in >> s;
		assert(s == "old");
		in >> op;
		assert(op == '+' || op == '*');
		in >> s;
		if (s == "old") {
			operand = -1;
		} else {
			operand = stoi(s);
		}

		// Test: divisible by 12
		assert(in.get() == '\n');
		getline(in, s, 'y');
		assert(s == "  Test: divisible b");
		in >> divisor;

		// If true
		assert(in.get() == '\n');
		getline(in, s, 'y');
		assert(s == "    If true: throw to monke");
		in >> testTrueDir;

		// If false
		assert(in.get() == '\n');
		getline(in, s, 'y');
		assert(s == "    If false: throw to monke");
		in >> testFalseDir;
	}

	template <typename T>
	T execOp(T val) const {
		switch (op) {
		case '*':
			return val * (operand == -1 ? val : operand);
		case '+':
			return val + (operand == -1 ? val : operand);
		default:
			assert(false);
		}
	}
};

int main() {
	// Scanning monkey's characteristics
	vector<Monkey> monkeys;
	while (cin.peek() != -1) {
		monkeys.emplace_back(cin);
		assert(cin.get() == '\n');
		if (cin.peek() == '\n') {
			cin.get();
		}
	}

	// Set to 3 for part 1
	int commonDivisable = accumulate(
			monkeys.begin(),
			monkeys.end(),
			1,
			[](int commonDiv, const Monkey& m) -> int {
				return commonDiv * m.divisor;
			});

	array<int, 2> topInspections{0, 0};
	for (int j = 0; j < 10000; ++j) {
		for (Monkey& m : monkeys) {
			while (!m.items.empty()) {
				// Throwing item
				m.items.front() = m.execOp(m.items.front()) % commonDivisable;
				int targetMonkey = m.items.front() % m.divisor == 0 ?
					m.testTrueDir :
					m.testFalseDir;
				monkeys[targetMonkey].items.push_back(m.items.front());
				m.items.pop_front();

				// Keeping top inspections up to date
				++m.inspections;
				if (m.inspections > topInspections[0]) {
					topInspections[1] = topInspections[0];
					topInspections[0] = m.inspections;
				} else if (m.inspections > topInspections[1]) {
					topInspections[1] = m.inspections;
				}
			}
		}
	}

	cout << long(topInspections[0]) * long(topInspections[1]) << endl;

	return 0;
}
