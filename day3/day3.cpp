#include <cctype>
#include <fstream>
#include <iostream>
using namespace std;

vector<pair<int, int>> dirs = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
bool isInRange(vector<string> &engine, int y, int x) {
    if (y < 0 || y >= engine.size() || x < 0 || x >= engine[y].size()) {
        return false;
    }

    return true;
}

bool isSurronded(vector<string> &engine, int y, int x) {
    for (const auto &dir : dirs) {
        int newY = y + dir.first;
        int newX = x + dir.second;

        if (isInRange(engine, newY, newX) && engine[newY][newX] != '.' && !isdigit(engine[newY][newX])) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream input_file("./input");
    string line;
    vector<string> lines;
    while (getline(input_file, line)) {
        lines.push_back(line);
    }

    int ans = 0;
    for (int y = 0; y < lines.size(); ++y) {
        for (int x = 0; x < lines[y].length(); ++x) {
            // cout << lines[y][x] << ' ';

            // if (isdigit(lines[y][x]) && isSurronding(lines, y, x)) {
            //     cout << lines[y][x];
            // }
            if (isdigit(lines[y][x])) {
                bool isValid = isSurronded(lines, y, x);
                int num = int(lines[y][x] - '0');
                while (x < lines[0].size() - 1 && isdigit(lines[y][x + 1])) {
                    ++x;
                    if (!isValid) {
                        isValid = isSurronded(lines, y, x);
                    }
                    num = num * 10 + int(lines[y][x] - '0');
                }
                if (isValid) {
                    cout << num << "(" << y << ' ' << x << ")"
                         << " - ";
                    ans += num;
                }
            }
        }
    }
    cout << '\n' << ans;
}
