#include <iostream>
#include <array>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n{};
    int sum{};

    array<int, 3> top3{};
    // vector<int> sums{};

    while (!cin.eof()) {
        if (cin.peek() == '\n') {
            if (sum > top3[0]) {
               // copy(&top3[0], &top3[1], &top3[1]);
                top3 = {sum, top3[0], top3[1]};
//                top3[0] = sum;
            } else if (sum > top3[1]) {
                // copy(&top3[1], &top3[1], &top3[2]);
                // top3[1] = sum;
                top3 = {top3[0], sum, top3[1]};
            } else if (sum > top3[2]) {
                top3 = {top3[0], top3[1], sum};
            }

            // sums.push_back(sum);

            sum = 0;
        }
        cin >> n;
        sum += n;
//        cout << n << endl;
        cin.get();
    }

    // sort(sums.begin(), sums.end(), [](int lhs, int rhs) { return lhs > rhs; });
    for (int i = 0; i != 3; ++i) {
        // cout << i << ": " << top3[i] << "(" << sums[i] << ")" << endl;
        cout << i << ": " << top3[i] << "(" << ")" << endl;
    }
    cout << "----" << endl;
    cout << "Sum: " << accumulate(top3.begin(), top3.end(), 0) << endl;
    cout << "----" << endl;

    return 0;
}
