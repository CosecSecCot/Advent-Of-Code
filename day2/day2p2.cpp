#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream input_file("./input");
    string line;
    vector<string> lines;
    while (getline(input_file, line)) {
        lines.push_back(line);
    }

    int ans = 0;
    for (auto line : lines) {
        cout << line << '\n';

        int red = INT_MIN;
        int green = INT_MIN;
        int blue = INT_MIN;
        for (int i = 0; i < line.size(); ++i) {
            if (isdigit(line[i])) {
                int num = int(line[i] - '0');
                while (i < line.size() - 1 && isdigit(line[i + 1])) {
                    ++i;
                    num = num * 10 + int(line[i] - '0');
                }

                if (line.substr(i + 2, 3) == "red") {
                    red = max(red, num);
                } else if (line.substr(i + 2, 5) == "green") {
                    green = max(green, num);
                } else if (line.substr(i + 2, 4) == "blue") {
                    blue = max(blue, num);
                }
            }
        }

        cout << red << ' ' << green << ' ' << blue << '\n';
        ans += (red * green * blue);
    }
    cout << ans;

    return 0;
}
