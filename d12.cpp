#include <iostream>
#include <vector>
#include <utility>
#include <limits>

using namespace std;

struct Node {
    char c{};
    vector<Node*> neighbours{};
    bool end = false;
    bool visited = false;

    explicit Node(char c) : c(c) {}
};

int minPath = 1000;

void dfs(Node* node, int depth) {
    node->visited = true;

    if (depth == 16) {
        int aa = 1;
    }

    if (node->end) {
        minPath = min(minPath, depth);
    }
    cout << depth << endl;

    for (auto neighbour : node->neighbours) {
        if (!neighbour->visited) {
            // string prepad(depth, ' ');
            // cout << prepad << "From " << node->c << " going to " << neighbour->c << " (" << depth << ")" << endl;
            dfs(neighbour, depth + 1);
        }
    }

    node->visited = false;
}

int main() {
    pair<int, int> start;
    vector<vector<Node>> field{{}};

    // Read to vector
    cerr << "Reading to vector..." << endl;
    char c;
    while (cin.peek() != -1) {
        c = cin.get();
        if (c == '\n') {
            if (cin.peek() == -1) {
                break;
            }
            field.emplace_back();
        } else {
            if (c == 'S') {
                start = {field.size() - 1, field.back().size()};
                field.back().emplace_back('a');
            } else if (c == 'E') {
                field.back().emplace_back('z');
                field.back().back().end = true;
            } else {
                field.back().emplace_back(c);
            }
        }
    }

    cerr << "Converting to graph..." << endl;
    // Convert vector to graph
    const vector<pair<int, int>> neighbourMod{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[i].size(); ++j) {
            for (const auto& x : neighbourMod) {
                // Checking edges
                pair<int, int> neighbour{i + x.first, j + x.second};
                if (neighbour.first == -1 || neighbour.first == field.size() ||
                    neighbour.second == -1 || neighbour.second == field[i].size()) {
                    continue;
                }

                // Checking height
                if (abs(field[neighbour.first][neighbour.second].c - field[i][j].c) < 2) {
                    field[i][j].neighbours.push_back(&field[neighbour.first][neighbour.second]);
                }
            }
        }
    }

    cerr << "Running shortest path..." << endl;
    // Do DFS
    dfs(&field[start.first][start.second], 0);
    cout << minPath << endl;

    return 0;
}