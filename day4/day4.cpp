#include <cctype>
#include <fstream>
#include <iostream>
using namespace std;

int getNumber(const string &lines, int &x) {
    string num = "";
    num += lines[x];
    while (x + 1 < lines.length() && isdigit(lines[x + 1])) {
        num = num + lines[x + 1];
        ++x;
    }
    return stoi(num);
}

bool isMatching(const vector<int> &winning, const int num) {
    for (const auto &winningNum : winning) {
        if (num == winningNum) {
            return true;
        }
    }
    return false;
}

struct Card {
    vector<int> winningList;
    vector<int> elfList;
    int count = 1;
    int matches = 0;
};

int main() {
    ifstream input_file("../input");
    string line;
    int ans = 0;
    vector<Card> scr_cards;
    while (getline(input_file, line)) {
        string lists = line.substr(line.find(':') + 2);
        string winning = lists.substr(0, lists.find("|") - 1);
        string elf = lists.substr(lists.find("|") + 2);

        Card scr_card;
        // cout << winning << '\n';
        for (int i = 0; i < winning.length(); ++i) {
            if (isdigit(winning[i])) {
                scr_card.winningList.push_back(getNumber(winning, i));
            }
        }
        // cout << elf << '\n';
        for (int i = 0; i < elf.length(); ++i) {
            if (isdigit(elf[i])) {
                // cout << getNumber(elf, i) << ' ';
                scr_card.elfList.push_back(getNumber(elf, i));
            }
        }

        for (const auto &num : scr_card.elfList) {
            if (isMatching(scr_card.winningList, num)) {
                scr_card.matches++;
            }
        }

        scr_cards.push_back(scr_card);
    }

    // cout << scr_cards.size() << '\n';
    // for (const auto &card : scr_cards) {
    //     cout << card.matches << '\n';
    // }

    cout << '\n';
    for (int i = 0; i < scr_cards.size(); ++i) {
        cout << "Card " << i + 1 << ":\n";
        cout << "Matches :" << scr_cards[i].matches << '\n';

        for (int j = 1; j <= scr_cards[i].matches; ++j) {
            cout << i + j << ' ';
            scr_cards[i + j].count += scr_cards[i].count;
        }

        cout << '\n';
        cout << "Count :" << scr_cards[i].count << '\n';
        cout << "\n-------------------\n";
    }

    cout << '\n';
    for (const auto &card : scr_cards) {
        ans += card.count;
    }

    cout << ans;

    return 0;
}
