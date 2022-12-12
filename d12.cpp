#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <cassert>
#include <numeric>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
    size_t id;
    char c{};
    vector<Node*> neighbours{};
    bool end = false;
    bool visited = false;

    explicit Node(char c) : c(c) {
        static size_t idCounter = 0;
        id = idCounter++;
    }
};

size_t minPath = 0;

// void dfs(Node* node, int depth) {
//     if (node->end) {
//         minPath = min(minPath, depth);
//         cout << depth << endl;
//         return;
//     }
//
//     node->visited = true;
//
//     for (const auto& neighbour : node->neighbours) {
//         if (!neighbour->visited) {
//             dfs(neighbour, depth + 1);
//         }
//     }
//
//     node->visited = false;
// }

typedef vector<vector<Node>> Field;
typedef pair<int, Node*> iPair;

void shortestPath(Field& field, Node* src) {
    Node* end = nullptr;

    priority_queue<iPair, vector<iPair>, greater<>> pq;
    map<Node*, size_t> dist;
    for (auto& row : field) {
        for (Node& n : row) {
            if (n.end) {
                end = &n;
            }
            dist[&n] = numeric_limits<size_t>::max();
        }
    }
    assert(end != nullptr);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
        Node* u = pq.top().second;
        pq.pop();

        for (Node* v : u->neighbours) {
            if (v == end) {
                int d =42;
            }

            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    for (auto& row : field) {
        for (Node& n : row) {
            if (dist[&n] == numeric_limits<size_t>::max()) {
                cout << n.c;
            } else {
                cout << ' ';
            }
        }
        cout << "\n";
    }

    minPath = dist[end];
}

int main() {
    pair<int, int> start;
    Field field{{}};

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
                if (field[neighbour.first][neighbour.second].c - field[i][j].c < 2) {
                    field[i][j].neighbours.push_back(&field[neighbour.first][neighbour.second]);
                }
            }
        }
    }

    cerr << "Running shortest path..." << endl;
    // Do DFS
    // dfs(&field[start.first][start.second], 0);
    shortestPath(field, &field[start.first][start.second]);
    cout << minPath << endl;
    assert(minPath <= field.size() * field.front().size());

    return 0;
}