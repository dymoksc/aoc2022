#include <iostream>
#include <cassert>
#include <utility>
#include <set>
#include <vector>
#include <deque>

using namespace std;

deque<char> lastHeadMoves{};
const int tailSize = 1;

void printField(const pair<int, int>& head, const vector<pair<int, int>>& tails) {
    for (auto x : lastHeadMoves) {
        cout << x;
    }
    cout << endl;

    for (int i = -10; i <= 10; ++i) {
        for (int j = -10; j <= 10; ++j) {
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


    if (abs(newHead.first - tail.first) > 1 || abs(newHead.second - tail.second) > 1) {
        newTail.first = head.first;
        newTail.second = head.second;
    }
    head.first = newHead.first;
    head.second = newHead.second;

    return newTail;
}

int main() {
    vector<pair<int, int>> tails(tailSize, {0, 0});
    pair<int, int> head{};
    set<pair<int, int>> uniquePos{head};

    printField(head, tails);

    char c;
    int n;
    while (cin.peek() != -1) {

        cin >> c;
        assert(c == 'R' || c == 'L' || c == 'U' || c == 'D');
        assert(cin.get() == ' ');
        cin >> n;

        cout << "== " << c << " " << n << "==" << endl;

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
            for (int i = 0; i < tails.size(); ++i) {
                newPartPos = moveRope(*partToUpdate, tails[i], newPartPos);
                uniquePos.insert(tails[i]);
                partToUpdate = &tails[i];
            }
            partToUpdate->first = newPartPos.first;
            partToUpdate->second = newPartPos.second;

            printField(head, tails);

            lastHeadMoves.push_front(c);
            if (lastHeadMoves.size() == 3) {
                lastHeadMoves.pop_back();
            }
        }

        c = cin.peek();
        assert(cin.get() == '\n');
    }

    cout << uniquePos.size() << endl;

    return 0;
}