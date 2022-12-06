#include <iostream>
#include <algorithm>
#include <cassert>
#include <array>

using namespace std;

int main() {
    array<string, 3> s{};

    int sum{};
    while (!cin.eof()) {
        // auto next = cin.peek();

        cin >> s[0];
        cin >> s[1];
        cin >> s[2];

        // assert(s.size() % 2 == 0);
        // assert(s.size() != 0);

        char c{};

        for (char c0 : s[0]) {
            for (char c1 : s[1]) {
                if (c0 == c1) {
                    for (char c2 : s[2]) {
                        if (c0 == c2) {
                            c = c0;
                            break;
                        }
                    }
                }
            }
        }

        // auto middleIt = s.begin() + s.size() / 2;
        // for (auto it1 = s.begin(); it1 != middleIt; ++it1) {
        //     for (auto it2 = middleIt; it2 != s.end(); ++it2) {
        //         if (*it1 == *it2) {
        //             assert(c == 0 || c == *it1);
        //             c = *it1;
        //             break;
        //         }
        //     }
        // }

        if (c > 'Z') {
            assert(c >= 'a' && c <= 'z');
            c -= 'a' - 1;
        } else {
            assert(c >= 'A' && c <= 'Z');
            c -= 'A' - 27;
        }

        assert(c <= 52);
        sum += c;

        cout << s[0] << " (" << int(c) << ")" << " - " << sum << endl;
        cout << s[1] << " (" << int(c) << ")" << " - " << sum << endl;
        cout << s[2] << " (" << int(c) << ")" << " - " << sum << endl;

        const int cc = cin.get();
        // cerr << cc << endl;
        if (cin.peek() == -1) {
            break;
        }
        assert(cc == '\n' || cc == -1);

    }

    cout << "Sum: " << sum << endl;

    return 0;
}
