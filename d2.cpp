#include <iostream>
#include <algorithm>
#include <cassert>
#include <map>

using namespace std;

enum class Result : char {
    Lose = 'X',
    Draw = 'Y',
    Win  = 'Z',
};

enum class Shape : int {
    Rock     = 1,
    Paper    = 2,
    Scissors = 3,
};

ostream& operator<<(ostream& out, Shape s) {
    switch (s) {
        case Shape::Rock:
            out << "Rock    ";
            break;

        case Shape::Scissors:
            out << "Scissors";
            break;

        case Shape::Paper:
            out << "Paper   ";
            break;
    }
    return out;
}

std::map<Shape, Shape> keyWinsOverValue;
std::map<Shape, Shape> keyLosesToValue;

// Returns 1 if lhs is worse than rhs
int rhsWon(Shape lhs, Shape rhs) {
    if (lhs == rhs) {
        return 0;
    }

    // cout << rhs << " wins over " << keyWinsOverValue[rhs] << endl;

    if (keyWinsOverValue[rhs] == lhs) {
        return 1;
    }

    return -1;

    // if (rhs == Shape::Rock && lhs == Shape::Scissors ||
    //     rhs == Shape::Scissors && lhs == Shape::Paper ||
    //     rhs == Shape::Paper && lhs == Shape::Rock) {
    //     return 1;
    // }
    //
    // return -1;
}

int main() {
    keyWinsOverValue = {
        {Shape::Rock,     Shape::Scissors},
        {Shape::Scissors, Shape::Paper},
        {Shape::Paper,    Shape::Rock},
    };

    std::transform(
            keyWinsOverValue.begin(),
            keyWinsOverValue.end(),
            inserter(keyLosesToValue, keyLosesToValue.end()),
            [](decltype(keyWinsOverValue)::value_type p) {
                return decltype(keyLosesToValue)::value_type(p.second, p.first);
            });

    assert(rhsWon(Shape::Rock, Shape::Rock) == 0);

    assert(rhsWon(Shape::Scissors, Shape::Rock) == 1);
    assert(rhsWon(Shape::Paper, Shape::Scissors) == 1);
    assert(rhsWon(Shape::Rock, Shape::Paper) == 1);

    assert(rhsWon(Shape::Scissors, Shape::Paper) == -1);
    assert(rhsWon(Shape::Rock, Shape::Scissors) == -1);
    assert(rhsWon(Shape::Paper, Shape::Rock) == -1);

    int i{};
    char c{};
    int score{};
    while (cin.peek() != -1) {
        cout << ++i << "\t: ";

        cin >> c;
        // cout << c << endl;
        assert(c >= 'A' && c <= 'C');
        Shape opponentShape = Shape(c - 'A' + 1);
        cout << "Op: " << opponentShape << " vs ";

        cin >> c;
        // cout << c << endl;
        assert(c >= 'X' && c <= 'Z');

        Shape myShape;
        switch (Result(c)) {
        case Result::Lose:
            myShape = keyWinsOverValue[opponentShape];
            break;

        case Result::Draw:
            myShape = opponentShape;
            break;

        case Result::Win:
            myShape = keyLosesToValue[opponentShape];
            break;
        }

        cout << "Me: " << myShape << " (" << int(myShape) << ") -> ";

        switch (rhsWon(opponentShape, myShape)) {
            case 1:
                cout << 6 << "             ";
                score += 6;
                break;

            case -1:
                cout << 0 << "             ";
                break;

            case 0:
                cout << 3 << "             ";
                score += 3;
                break;
        }

        // cout << "Getting " << int(myShape) << " for the shape" << "\n";
        score += int(myShape);
        cout << "Score: " << score << "\n";

        assert(cin.get() == '\n' || cin.get() == -1);
    }


    return 0;
}
