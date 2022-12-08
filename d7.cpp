#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

enum class EntryType {
    File,
    Dir,
};

struct Entry {
    string name;
    EntryType type;
    vector<Entry*> subEntries;
    int size;
    Entry* parent;

    void addEntry(const string& eName, EntryType eType, int eSize) {
        Entry* e{};
        switch (eType) {
            case EntryType::Dir:
                e = new Entry{eName, eType, {}, 0, this};
                break;

            case EntryType::File:
                e = new Entry{eName, eType, {}, eSize, this};
                incrementSize(eSize);
                break;
        }
        assert(e != nullptr);

        subEntries.push_back(e);
    }

    void incrementSize(int inc) {
        cout << "Incrementing " << name << " size by " << inc << endl;
        size += inc;
        if (parent != nullptr) {
            parent->incrementSize(inc);
        }
    }
};

Entry root{"/", EntryType::Dir, {}, 0, nullptr};

Entry* changeDir(Entry* currentDir, string& cdArgument) {
    if (cdArgument == "/") {
        return &root;
    } else if (cdArgument == "..") {
        return currentDir->parent;
    } else {
        for (auto e : currentDir->subEntries) {
            if (e->name == cdArgument) {
                return e;
            }
        }
    }

    assert(false);
}

int minDeletable = 70000000 - 30000000;
int smallestDeletable = 70000000;

int dfs(Entry* e) {
    int size = 0;

    if (e->type == EntryType::Dir) {
        if (e->size <= 100000) {
            size += e->size;
        }

        if (e->size >= minDeletable) {
            smallestDeletable = min(smallestDeletable, e->size);
        }
    }

    for (auto subE : e->subEntries) {
        size += dfs(subE);
    }

    return size;
}

int main() {
    Entry* currentDir = nullptr;

    string s;
    while (!cin.eof()) {
        char peek = cin.peek();
        if (peek == -1) {
            break;
        }
        cout << "Peeked: '" << peek << "'" << endl;
        if (peek == '$') {    // Command
            assert(cin.get() == '$');
            assert(cin.get() == ' ');
            cin >> s;
            if (s == "cd") {
                cin >> s;
                currentDir = changeDir(currentDir, s);
            }
        } else {                    // LS output
            if (cin.peek() == 'd') {    // dir
                cin >> s;
                assert(s == "dir");
                cin >> s;
                currentDir->addEntry(s, EntryType::Dir, 0);
            } else {                    // file
                int size;
                cin >> size;
                cin >> s;
                currentDir->addEntry(s, EntryType::File, size);
            }
        }

        const int got = cin.get();
        if (got == -1) {
            break;
        }
        assert(got == '\n');
    }

    minDeletable = root.size - minDeletable;
    cout << dfs(&root) << endl;
    cout << smallestDeletable << endl;

    return 0;
}
