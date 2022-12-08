#include <iostream>
#include <cassert>
#include <vector>
#include <limits>

using namespace std;

struct tree {
    char val;
    char maxLeft;
    char maxRight;
    char maxTop;
    char maxBottom;

    bool isVisible() const {


        return val > maxLeft || val > maxRight || val > maxTop || val > maxBottom;
    }
};

int main() {
    vector<vector<tree>> grid;

    char c;
    vector<char> maxTop;
    do {
        grid.emplace_back();
        char maxLeft = numeric_limits<char>::min();
        int i{};
        do {
            // Making sure there's max top for this column
            if (maxTop.size() == i) {
                maxTop.emplace_back(numeric_limits<char>::min());
            }

            c = char(cin.get());
            grid.back().push_back({c, maxLeft, 0, maxTop[i] , 0});

            // Updating max
            maxLeft = max(maxLeft, c);
            maxTop[i] = max(maxTop[i], c);

            ++i;
        } while (cin.peek() != '\n');
        assert(cin.get() == '\n');
    } while (cin.peek() != -1);

    vector<char> maxBottom;
    int visibleCount = 0;
    for (int i = grid.size() - 1; i >= 0; --i) {
        char maxRight = numeric_limits<char>::min();
        for (int j = grid[i].size() - 1; j >= 0; --j) {
            if (i == grid.size() - 1) {
                maxBottom.emplace_back(numeric_limits<char>::min());
            }

            grid[i][j].maxRight = maxRight;
            grid[i][j].maxBottom = maxBottom[i];

            visibleCount += grid[i][j].isVisible();

            maxRight = max(maxRight, grid[i][j].val);
            maxBottom[i] = max(maxBottom[i], grid[i][j].val);
        }
    }

    for (auto row : grid) {
        for (tree t : row) {
            if (t.isVisible()) {
                char dir;
                if (t.maxBottom < t.val) {
                    dir = 'B';
                } else if (t.maxTop < t.val) {
                    dir = 'T';
                } else if (t.maxRight < t.val) {
                    dir = 'R';
                } else if (t.maxLeft < t.val) {
                    dir = 'L';
                }

                cout << "/" << t.val << dir << " ";
            } else {
                cout << "-" << t.val << "- ";
            }
        }
        cout << endl;
    }

    cout << visibleCount << endl;

    return 0;
}