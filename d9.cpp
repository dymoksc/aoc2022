#include <iostream>
#include <cassert>
#include <utility>
#include <set>
#include <vector>
#include <deque>

using namespace std;

const int tailSize = 9;

void printField(const pair<int, int>& head, const vector<pair<int, int>>& tails) {
    for (int i = -15; i <= 5; ++i) {
        for (int j = -11; j <= 12; ++j) {
            if (head.first == i && head.second == j) {
                cout << "H";
                continue;
            }

            bool printedTail = false;
            for (int k = 0; k < tails.size(); ++k) {
                if (tails[k].first == i && tails[k].second == j) {
                    cout << (k + 1);
                    printedTail = true;
                    break;
                }
            }
            if (printedTail) continue;

            if (i == 0 && j == 0) {
                cout << "s";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }
    cout << endl;
}

pair<int, int> moveRope(pair<int, int>& head, const pair<int, int>& tail, const pair<int, int>& newHead) {
    pair<int, int> newTail = tail;

    const int firstDiff = newHead.first - tail.first;
    const int secondDiff = newHead.second - tail.second;
    if (abs(firstDiff) == 2 || abs(secondDiff) == 2) {
        if (firstDiff != 0) {
            newTail.first += firstDiff > 0 ? 1 : -1;
        }
        if (secondDiff != 0) {
            newTail.second += secondDiff > 0 ? 1 : -1;
        }
    }

    head.first = newHead.first;
    head.second = newHead.second;

    return newTail;
}

int main() {
    vector<pair<int, int>> tails(tailSize, {0, 0});
    pair<int, int> head{};
    set<pair<int, int>> uniquePos{head};

    // printField(head, tails);

    char c;
    int n;
    while (cin.peek() != -1) {

        cin >> c;
        assert(c == 'R' || c == 'L' || c == 'U' || c == 'D');
        assert(cin.get() == ' ');
        cin >> n;

        // cout << "== " << c << " " << n << "==" << endl;

        for (int i = 0; i < n; ++i) {
            pair<int, int> newPartPos = head;
            switch (c) {
                case 'R':
                    ++newPartPos.second;
                    break;

                case 'L':
                    --newPartPos.second;
                    break;

                case 'U':
                    --newPartPos.first;
                    break;

                case 'D':
                    ++newPartPos.first;
                    break;

                default:
                    assert(false);
            }

            pair<int, int>* partToUpdate = &head;
            for (auto & tail : tails) {
                newPartPos = moveRope(*partToUpdate, tail, newPartPos);
                partToUpdate = &tail;
            }
            uniquePos.insert(newPartPos);
            partToUpdate->first = newPartPos.first;
            partToUpdate->second = newPartPos.second;

            // printField(head, tails);
        }

        c = cin.peek();
        assert(cin.get() == '\n');
    }

    cout << uniquePos.size() << endl;

    return 0;
}