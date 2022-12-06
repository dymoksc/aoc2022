#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

const int markerLength = 14;

int main() {
    char c;
    deque<char> buf{};
    int i{};
    while (!cin.eof()) {
        c = cin.get();
        ++i;
        if (c >= 'a' && c <= 'z') {
            buf.push_back(c);
            if (buf.size() == markerLength + 1) {
                buf.pop_front();
            }

            if (buf.size() == markerLength) {

                bool encounteredRepeated = false;
                for (int j = 0; j < markerLength - 1 && !encounteredRepeated; ++j) {
                    for (int k = j + 1; k < markerLength && !encounteredRepeated; ++k) {
                        encounteredRepeated = buf[j] == buf[k];
                    }
                }
                if (!encounteredRepeated) {
                    cout << i << endl;
                    for (char x : buf) {
                        cout << x;
                    }
                    cout << endl;
                    while (c != '\n') {
                        c = cin.get();
                    }
                }
            }
        }

        if (c == '\n') {
            i = 0;
            buf.erase(buf.begin(), buf.end());
        }
    }

    return 0;
}
