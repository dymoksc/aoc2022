#include <iostream>
#include <algorithm>
#include <cassert>
#include <array>

using namespace std;

int main() {
    string s;

    array<int, 2> range1{};
    array<int, 2> range2{};

    int sum{};

    while (!cin.eof()) {
        cin >> range1[0];
        assert(cin.get() == '-');
        cin >> range1[1];
        assert(cin.get() == ',');
        cin >> range2[0];
        assert(cin.get() == '-');
        cin >> range2[1];

        sum += range1[0] <= range2[1] && range1[1] >= range2[0];

        cin.get();
        if (cin.peek() == -1) {
            break;
        }

    }

    cout << sum << endl;

    return 0;
}
