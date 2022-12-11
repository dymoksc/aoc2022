#include <iostream>
#include <algorithm>
#include <deque>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

struct Monkey {
	deque<int> items{};
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

	int execOp(int val) const {
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

ostream& operator<<(ostream& os, const Monkey& m) {
	os << "Items: ";
	for (auto x : m.items) {
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

	for (int i = 0; i < monkeys.size(); ++i) {
		cout << "Monkey #" << i << ": ";
		for (auto item : monkeys[i].items) {
			cout << item << ", ";
		}
		cout << endl;
	}

	for (int j = 0; j < 20; ++j) {
		int i = 0;
		for (Monkey& m : monkeys) {
			while (!m.items.empty()) {
				// cout << "Item " << m.items.front() << " ";
				m.items.front() = m.execOp(m.items.front());
				// cout << "-> " << m.items.front();
				m.items.front() /= 3;
				// cout << " -> " << m.items.front() << endl;
				int targetMonkey = m.items.front() % m.divisor == 0 ?
					m.testTrueDir :
					m.testFalseDir;
				// cout << "Monkey " << i << " throws " << m.items.front()
				// 	 << " to " << targetMonkey << endl;
				monkeys[targetMonkey].items.push_back(m.items.front());
				m.items.pop_front();
				++m.inspections;
			}
			++i;
		}

		cout << "-------- Round " << j << " ------------" << endl;
		for (int i = 0; i < monkeys.size(); ++i) {
			cout << "Monkey #" << i << ": ";
			for (auto item : monkeys[i].items) {
				cout << item << ", ";
			}
			cout << endl;
		}
	}

	sort(
			monkeys.begin(),
			monkeys.end(),
			[](const Monkey& lhs, const Monkey& rhs) -> bool {
				return lhs.inspections > rhs.inspections;
			});

	for (auto& m : monkeys) {
		cout << m.inspections << endl;
	}

	cout << monkeys[0].inspections * monkeys[1].inspections << endl;

	return 0;
}
