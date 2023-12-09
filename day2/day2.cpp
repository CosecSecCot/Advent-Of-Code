#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
    // freopen("input", "r", stdin);
    ifstream input_file("./input");
    string line;
    vector<string> lines;
    while (getline(input_file, line)) {
        lines.push_back(line);
    }

    int ans = 0;
    int game = 1;
    for (auto line : lines) {
        cout << line << '\n';

        bool valid = true;
        for (int i = 0; i < line.size(); ++i) {
            if (isdigit(line[i])) {
                int num = int(line[i] - '0');
                while (i < line.size() - 1 && isdigit(line[i + 1])) {
                    ++i;
                    num = num * 10 + int(line[i] - '0');
                }

                if (line.substr(i + 2, 3) == "red") {
                    if (num > 12) {
                        cout << num << ' ';
                        valid = false;
                        break;
                    }
                } else if (line.substr(i + 2, 5) == "green") {
                    if (num > 13) {
                        cout << num << ' ';
                        valid = false;
                        break;
                    }
                } else if (line.substr(i + 2, 4) == "blue") {
                    if (num > 14) {
                        cout << num << ' ';
                        valid = false;
                        break;
                    }
                }
            }
        }

        if (valid) {
            ans += game;
        }

        cout << '\n';
        game++;
    }
    cout << "ans : " << ans;

    return 0;
}
