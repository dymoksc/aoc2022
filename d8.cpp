#include <iostream>
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

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {

            bool visible = false;

            // Visible from top
            bool hasHigherTop = false;
            for (int k = 0; k < i; ++k) {
                if (grid[k][j] >= grid[i][j]) {
                    hasHigherTop = true;
                    break;
                }
            }

            // Visible from bottom
            bool hasHigherBottom = false;
            for (int k = grid.size() - 1; k > i; --k) {
                if (grid[k][j] >= grid[i][j]) {
                    hasHigherBottom = true;
                    break;
                }
            }

            // Visible from left
            bool hasHigherLeft = false;
            for (int k = 0; k < j; ++k) {
                if (grid[i][k] >= grid[i][j]) {
                    hasHigherLeft = true;
                    break;
                }
            }

            // Visible from right
            bool hasHigherRight = false;
            for (int k = grid[i].size() - 1; k > j; --k) {
                if (grid[i][k] >= grid[i][j]) {
                    hasHigherRight = true;
                    break;
                }
            }

            visible = !hasHigherTop || !hasHigherBottom || !hasHigherRight || !hasHigherLeft;
            visCount += visible;

            if (visible) {
                cout << "/" << grid[i][j] << "\\ ";
            } else {
                cout << " " << grid[i][j] << "  ";
            }

        }
        cout << endl;
    }

    cout << visCount;

    return 0;
}