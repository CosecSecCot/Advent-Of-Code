#include <cctype>
#include <iostream>
using namespace std;

int main() {
    freopen("input", "r", stdin);
    vector<string> lines;
    string line;
    while (cin >> line) {
        lines.push_back(line);
    }

    int ans = 0;
    for (auto line : lines) {
        int caliberation_value = 0;

        int start = 0;
        for (int i = 0; i < line.size(); ++i) {
            if (isdigit(line[start])) {
                caliberation_value += 10 * int(line[start] - '0');
                break;
            }
            start++;
        }

        int end = line.size() - 1;
        for (int j = line.size() - 1; j >= 0; --j) {
            if (isdigit(line[end])) {
                caliberation_value += int(line[end] - '0');
                cout << line[end] << " - ";
                break;
            }
            end--;
        }

        cout << line << ' ' << caliberation_value << '\n';
        ans += caliberation_value;
    }
    cout << ans;

    return 0;
}
