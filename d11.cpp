#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

struct Monkey {
	vector<int> itemLevels{};
	char op{};
	int operand{};
	int divisor{};
	int testTrueDir{};
	int testFalseDir{};

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

			itemLevels.emplace_back();
			in >> itemLevels.back();
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
};

ostream& operator<<(ostream& os, const Monkey& m) {
	os << "Items: ";
	for (auto x : m.itemLevels) {
		os << x << ", ";
	}
	os << "\nOperation: new = old " << m.op << " " << m.operand << "\n";
	os << "Divisor: " << m.divisor << endl;
	os << "If true then " << m.testTrueDir << endl;
	os << "If false then " << m.testFalseDir << endl;
	return os;
}


int main() {
	vector<Monkey> monkeys;

	while (cin.peek() != -1) {
		monkeys.emplace_back(cin);
		assert(cin.get() == '\n');
		if (cin.peek() == '\n') {
			cin.get();
		}
	}

	cout << monkeys.size() << endl;
	cout << monkeys[2] << endl;
	

	return 0;
}
