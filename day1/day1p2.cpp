#include <cctype>
#include <iostream>
#include <map>
using namespace std;

int main() {
    freopen("input", "r", stdin);
    vector<string> lines;
    string line;
    while (cin >> line) {
        lines.push_back(line);
    }

    map<string, int> digits;
    digits["zero"] = 0;
    digits["one"] = 1;
    digits["two"] = 2;
    digits["three"] = 3;
    digits["four"] = 4;
    digits["five"] = 5;
    digits["six"] = 6;
    digits["seven"] = 7;
    digits["eight"] = 8;
    digits["nine"] = 9;

    int ans = 0;
    for (auto line : lines) {
        vector<int> decoded;
        // cout << line << " : ";
        for (int i = 0; i < line.size(); ++i) {
            string three_letter = line.substr(i, 3);
            string four_letter = line.substr(i, 4);
            string five_letter = line.substr(i, 5);
            // cout << '\n' << i << '\n';
            // cout << three_letter << ' ' << four_letter << ' ' << five_letter;
            if (isdigit(line[i])) {
                decoded.push_back(int(line[i] - '0'));
            } else if (three_letter == "one" || three_letter == "two" || three_letter == "six") {
                decoded.push_back(digits[three_letter]);
            } else if (four_letter == "zero" || four_letter == "four" || four_letter == "five" ||
                       four_letter == "nine") {
                decoded.push_back(digits[four_letter]);
            } else if (five_letter == "three" || five_letter == "seven" || five_letter == "eight") {
                decoded.push_back(digits[five_letter]);
            }
        }

        int caliberation_value = decoded[0] * 10 + decoded[decoded.size() - 1];
        ans += caliberation_value;
    }
    cout << ans;

    return 0;
}
