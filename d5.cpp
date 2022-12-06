#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <tuple>

using namespace std;

void printStacks(const vector<vector<char>>& stacks) {
    for (int i = 0; i < stacks.size(); ++i) {
        cout << i << ":\t";
        for (auto ch : stacks[i]) {
            cout << "[" << ch << "] ";
        }
        cout << "\n";
    }
    cout << "----------------" << "\n";
}

int main() {
    // Stack building
    vector<vector<char>> stacks{9, vector<char>{}};
    char c;
    bool stackBuilding{true};
    do {
        int i{};
        do {
            c = char(cin.get());

            if (stackBuilding && i % 4 == 1 && c != ' ') {
                if (c == '1') {
                    stackBuilding = false;
                } else {
                    if (!(c >= 'A' && c <= 'Z')) {
                        int as = 2;
                    }
                    assert(c >= 'A' && c <= 'Z');
                    stacks[i / 4].insert(stacks[i / 4].begin(), c);
                    // cout << i / 4 << ": " << c << "\n";
                }
            }

            ++i;
        } while (c != '\n');
    } while (stackBuilding);

    c = cin.get();
    assert(c == '\n');

    // Operation stack
    vector<tuple<int, int, int>> operations{};
    while (true) {
        string s;
        cin >> s;
        if (s != "move") {
            break;
        }

        int n, from, to;
        cin >> n;
        cin >> s;
        assert(s == "from");

        cin >> from;
        cin >> s;
        assert(s == "to");

        cin >> to;
        assert(cin.get() == '\n');

        operations.emplace_back(from - 1, to - 1, n);
    }

    // Executing operations
    printStacks(stacks);
    for (auto op : operations) {
        // const char &x = stacks[get<0>(op)].back();
        stacks[get<1>(op)].insert(
                stacks[get<1>(op)].end(),
                stacks[get<0>(op)].end() - get<2>(op),
                stacks[get<0>(op)].end());
        // stacks[get<0>(op)].pop_back();
        stacks[get<0>(op)].erase(stacks[get<0>(op)].end() - get<2>(op),
                                 stacks[get<0>(op)].end());
        printStacks(stacks);
    }

    // Result
    for (const vector<char>& stack : stacks) {
        if (!stack.empty()) {
            cout << stack.back();
        }
    }

    cout << "\n";

    return 0;
}
