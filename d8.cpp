#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <limits>

using namespace std;

int main() {
    vector<string> grid;

    while (!cin.eof() && cin.peek() != -1) {
        string s;
        getline(cin, s);
        if (!s.empty()) {
            grid.emplace_back(move(s));
        }
    }

    int visCount = 0;
    int topScenic = 0;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {

            bool visible = false;
            int scenicScoreTop = 0;
            int scenicScoreBottom = 0;
            int scenicScoreLeft = 0;
            int scenicScoreRight = 0;

            // Visible from top
            bool hasHigherTop = false;
            scenicScoreTop = i;
            for (int k = 0; k < i; ++k) {
                if (grid[k][j] >= grid[i][j]) {
                    hasHigherTop |= true;
                    scenicScoreTop = i - k;
                }
            }

            // Visible from bottom
            bool hasHigherBottom = false;
            scenicScoreBottom = grid.size() - 1 - i;
            for (int k = grid.size() - 1; k > i; --k) {
                if (grid[k][j] >= grid[i][j]) {
                    hasHigherBottom |= true;
                    scenicScoreBottom = k - i;
                }
            }

            // Visible from left
            bool hasHigherLeft = false;
            scenicScoreLeft = j;
            for (int k = 0; k < j; ++k) {
                if (grid[i][k] >= grid[i][j]) {
                    hasHigherLeft |= true;
                    scenicScoreLeft = j - k;
                }
            }

            // Visible from right
            bool hasHigherRight = false;
            scenicScoreRight = grid[i].size() - 1 - j;
            for (int k = grid[i].size() - 1; k > j; --k) {
                if (grid[i][k] >= grid[i][j]) {
                    hasHigherRight |= true;
                    scenicScoreRight = k - j;
                }
            }

            visible = !hasHigherTop || !hasHigherBottom || !hasHigherRight || !hasHigherLeft;
            visCount += visible;

            if (visible) {
                cout << "/" << grid[i][j] << "\\ ";

            } else {
                cout << " " << grid[i][j] << "  ";
            }

            cout << "[";
            cout << fixed << setfill('0');
            cout << "T" << setw(2) << scenicScoreTop << ", ";
            cout << "L" << setw(2) << scenicScoreLeft << ", ";
            cout << "B" << setw(2) << scenicScoreBottom << ", ";
            cout << "R" << setw(2) << scenicScoreRight << "]  ";

            topScenic = max(topScenic, scenicScoreTop * scenicScoreLeft * scenicScoreBottom * scenicScoreRight);

        }
        cout << endl;
    }

    cout << visCount << endl;
    cout << topScenic << endl;

    return 0;
}