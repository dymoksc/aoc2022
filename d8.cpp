#include <iostream>
#include <cassert>
#include <vector>
#include <limits>

using namespace std;

struct Tree {
    char val;
    bool visible;
};

int main() {
    vector<vector<Tree>> grid;

    vector<char> maxTop{};
    while (!cin.eof() && cin.peek() != -1) {
        grid.emplace_back();

        char maxLeft = numeric_limits<char>::min();
        int i{};
        while (cin.peek() != '\n') {
            if (grid.size() == 1) {
                maxTop.emplace_back(numeric_limits<char>::min());
            }

            char c = cin.get();
            grid.back().push_back({c, c > maxLeft || c > maxTop[i]});

            maxLeft = max(maxLeft, c);
            maxTop[i] = max(maxTop[i], c);
            ++i;
        }
        assert(cin.get() == '\n');
    }

    int visibleCount = 0;
    vector<char> maxBottom(grid.size(), numeric_limits<char>::min());
    for (auto it = grid.rbegin(); it != grid.rend(); ++it) {
        char maxRight = numeric_limits<char>::min();
        int i{};
        for (auto jt = it->rbegin(); jt != it->rend(); ++jt) {
            jt->visible = jt->visible || jt->val > maxRight || jt->val > maxBottom[i];
            visibleCount += jt->visible;

            maxRight = max(maxRight, jt->val);
            maxBottom[i] = max(maxBottom[i], jt->val);
            ++i;
        }
    }

    for (auto& row : grid) {
        for (auto tree : row) {
            if (tree.visible) cout << "/" << tree.val << "\\";
            else cout << " " << tree.val << " ";
        }
        cout << endl;
    }

    cout << visibleCount;

    return 0;
}