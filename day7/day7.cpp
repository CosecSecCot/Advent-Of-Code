#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
using namespace std;

struct Hand {
    string cards;
    int bid;
    int strength;
};

int calculate(string hand) {
    vector<char> set_of_cards;
    for (auto card : hand) {
        if (find(set_of_cards.begin(), set_of_cards.end(), card) == set_of_cards.end()) {
            set_of_cards.push_back(card);
        }
    }

    int size = set_of_cards.size();
    if (size == 1) {
        return 7;
    } else if (size == 2) {
        int count_a = 0;
        int count_b = 0;
        for (auto card : hand) {
            if (card == set_of_cards[0]) {
                count_a += 1;
            } else if (card == set_of_cards[1]) {
                count_b += 1;
            }
        }

        if (count_a == 4 or count_b == 4) {
            return 6;
        } else {
            return 5;
        }
    } else if (size == 3) {
        int count_a = 0;
        int count_b = 0;
        int count_c = 0;
        for (auto card : hand) {
            if (card == set_of_cards[0]) {
                count_a += 1;
            } else if (card == set_of_cards[1]) {
                count_b += 1;
            } else if (card == set_of_cards[2]) {
                count_c += 1;
            }
        }

        if (count_a == 3 or count_b == 3 or count_c == 3) {
            return 4;
        } else {
            return 3;
        }
    } else if (size == 4) {
        return 2;
    } else {
        return 1;
    }
}

map<char, int> cardValue = {
    {'2', 2}, {'3', 3},  {'4', 4},  {'5', 5},  {'6', 6},  {'7', 7},  {'8', 8},
    {'9', 9}, {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14},
};

bool comparison(Hand h1, Hand h2) { return h1.strength < h2.strength; }

bool comparison2(Hand h1, Hand h2) {
    if (h1.strength == h2.strength) {
        // return h1.cards < h2.cards;
        return h1.cards.compare(h2.cards) < 0;
    }
    return h1.strength < h2.strength;
}

int main() {
    ifstream input_file("../input");
    string line;
    vector<Hand> game;
    while (getline(input_file, line)) {
        Hand curr;
        string cards = line.substr(0, 5);
        int bid = stoi(line.substr(line.find(' ') + 1));
        int strength = calculate(cards);
        curr.cards = cards;
        curr.bid = bid;
        curr.strength = strength;

        // cout << curr.cards << ' ' << curr.bid << ' ' << curr.strength << '\n';
        game.push_back(curr);
    }

    sort(game.begin(), game.end(), comparison);
    sort(game.begin(), game.end(), comparison2);
    int ans = 0;
    for (int rank = 0; rank < game.size(); ++rank) {
        ans += game[rank].bid * (rank + 1);
        cout << rank + 1 << ' ' << game[rank].cards << ' ' << game[rank].bid << ' ' << game[rank].strength << '\n';
    }
    cout << ans;

    return 0;
}
