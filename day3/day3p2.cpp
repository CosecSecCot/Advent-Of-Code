#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <set>
using namespace std;

bool isInRange(vector<string> &engine, int y, int x) {
    if (y < 0 || y >= engine.size() || x < 0 || x >= engine[y].size()) {
        return false;
    }

    return true;
}

vector<pair<int, int>> isSurronded(vector<string> &engine, int y, int x) {
    vector<pair<int, int>> right_dirs = {{-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
    // vector<pair<int, int>> middle_dirs = {{0, -1}, {0, 1}};
    vector<pair<int, int>> left_dirs = {{-1, -1}, {0, -1}, {1, -1}};
    vector<pair<int, int>> positions;

    if (isInRange(engine, y - 1, x) && isdigit(engine[y - 1][x])) {
        if (isInRange(engine, y - 1, x + 1) && isdigit(engine[y - 1][x + 1])) {
            int i = 1;
            while (isInRange(engine, y - 1, x + 1 + i) && isdigit(engine[y - 1][x + 1 + i])) {
                ++i;
            }
            positions.push_back({y - 1, x + 1 + i});
        } else {
            positions.push_back({y - 1, x});
        }
    } else {
        if (isInRange(engine, y - 1, x + 1) && isdigit(engine[y - 1][x + 1])) {
            int i = 1;
            while (isInRange(engine, y - 1, x + 1 + i) && isdigit(engine[y - 1][x + 1 + i])) {
                ++i;
            }
            positions.push_back({y - 1, x + 1 + i});
        }
        if (isInRange(engine, y - 1, x - 1) && isdigit(engine[y - 1][x - 1])) {
            positions.push_back({y - 1, x - 1});
        }
    }

    if (isInRange(engine, y, x + 1) && isdigit(engine[y][x + 1])) {
        int i = 1;
        while (isInRange(engine, y, x + 1 + i) && isdigit(engine[y][x + 1 + i])) {
            ++i;
        }
        positions.push_back({y, x + 1 + i});
    }
    if (isInRange(engine, y, x - 1) && isdigit(engine[y][x - 1])) {
        positions.push_back({y, x - 1});
    }

    if (isInRange(engine, y + 1, x) && isdigit(engine[y + 1][x])) {
        if (isInRange(engine, y + 1, x + 1) && isdigit(engine[y + 1][x + 1])) {
            int i = 1;
            while (isInRange(engine, y + 1, x + 1 + i) && isdigit(engine[y + 1][x + 1 + i])) {
                ++i;
            }
            positions.push_back({y + 1, x + 1 + i});
        } else {
            positions.push_back({y + 1, x});
        }
    } else {
        if (isInRange(engine, y + 1, x + 1) && isdigit(engine[y + 1][x + 1])) {
            int i = 1;
            while (isInRange(engine, y + 1, x + 1 + i) && isdigit(engine[y + 1][x + 1 + i])) {
                ++i;
            }
            positions.push_back({y + 1, x + 1 + i});
        }
        if (isInRange(engine, y + 1, x - 1) && isdigit(engine[y + 1][x - 1])) {
            positions.push_back({y + 1, x - 1});
        }
    }

    return positions;
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
            if (lines[y][x] == '*') {
                vector<pair<int, int>> positions = isSurronded(lines, y, x);
                // iterate thourh positions, and calculate num

                if (positions.size() != 2) {
                    break;
                }

                int gear_ratio = 1;
                for (const auto &pos : positions) {
                    int y_pos = pos.first;
                    int upperbound = pos.second;
                    cout << y_pos << ' ' << upperbound << '\n';

                    int final_num = -1;
                    for (int i = 0; i <= upperbound; ++i) {
                        if (isdigit(lines[y_pos][i])) {
                            int num = int(lines[y_pos][i] - '0');
                            while (i < upperbound && isdigit(lines[y_pos][i + 1])) {
                                ++i;
                                num = num * 10 + int(lines[y_pos][i] - '0');
                            }
                            final_num = num;
                            // ans += num;
                        }
                    }
                    cout << final_num << "\n\n";
                    gear_ratio *= final_num;
                }
                ans += gear_ratio;
            }
        }
    }
    cout << '\n' << ans;
}
