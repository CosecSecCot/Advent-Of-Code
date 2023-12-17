#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
struct Hand {};
using namespace std;

bool isInRange(const vector<string> &engine, const int y, const int x) {
    if (y < 0 || y >= engine.size() || x < 0 || x >= engine[y].size()) {
        return false;
    }

    return true;
}

string getForward(const vector<string> &lines, const int y, const int x) {
    int i = 0;
    string num = "";
    num += lines[y][x];
    while (isInRange(lines, y, x + 1 + i) && isdigit(lines[y][x + 1 + i])) {
        num = num + lines[y][x + 1 + i];
        ++i;
    }
    return num;
}

string getBackward(const vector<string> &lines, const int y, const int x) {
    int i = 0;
    string num = "";
    num += lines[y][x];
    while (isInRange(lines, y, x - 1 - i) && isdigit(lines[y][x - 1 - i])) {
        num = num + lines[y][x - 1 - i];
        ++i;
    }
    reverse(num.begin(), num.end());
    return num;
}

string getMiddle(const vector<string> &lines, const int y, const int x) {
    string prev = getBackward(lines, y, x);
    string next = getForward(lines, y, x).substr(1);
    return prev + next;
}

vector<int> getSurrounded(const vector<string> &lines, const int y, const int x) {
    vector<int> nums;

    // Top row
    if (isInRange(lines, y - 1, x) && isdigit(lines[y - 1][x])) {
        if (isInRange(lines, y - 1, x + 1) && isdigit(lines[y - 1][x + 1])) {
            int num = stoi(getMiddle(lines, y - 1, x));
            nums.push_back(num);
        } else {
            int num = stoi(getBackward(lines, y - 1, x));
            nums.push_back(num);
        }
    } else {
        if (isInRange(lines, y - 1, x + 1) && isdigit(lines[y - 1][x + 1])) {
            int num = stoi(getForward(lines, y - 1, x + 1));
            nums.push_back(num);
        }
        if (isInRange(lines, y - 1, x - 1) && isdigit(lines[y - 1][x - 1])) {
            int num = stoi(getBackward(lines, y - 1, x - 1));
            nums.push_back(num);
        }
    }

    // Middle Row
    if (isInRange(lines, y, x - 1) && isdigit(lines[y][x - 1])) {
        int num = stoi(getBackward(lines, y, x - 1));
        nums.push_back(num);
    }
    if (isInRange(lines, y, x + 1) && isdigit(lines[y][x + 1])) {
        int num = stoi(getForward(lines, y, x + 1));
        nums.push_back(num);
    }

    // Bottom Row
    if (isInRange(lines, y + 1, x) && isdigit(lines[y + 1][x])) {
        if (isInRange(lines, y + 1, x + 1) && isdigit(lines[y + 1][x + 1])) {
            int num = stoi(getMiddle(lines, y + 1, x));
            nums.push_back(num);
        } else {
            int num = stoi(getBackward(lines, y + 1, x));
            nums.push_back(num);
        }
    } else {
        if (isInRange(lines, y + 1, x + 1) && isdigit(lines[y + 1][x + 1])) {
            int num = stoi(getForward(lines, y + 1, x + 1));
            nums.push_back(num);
        }
        if (isInRange(lines, y + 1, x - 1) && isdigit(lines[y + 1][x - 1])) {
            int num = stoi(getBackward(lines, y + 1, x - 1));
            nums.push_back(num);
        }
    }

    return nums;
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
            if (lines[y][x] == '*') {
                vector<int> nums = getSurrounded(lines, y, x);
                if (nums.size() != 2) {
                    continue;
                }

                int gear_ratio = 1;
                for (const int num : nums) {
                    cout << num << ' ';
                    gear_ratio *= num;
                }
                cout << '\n';

                ans += gear_ratio;
            }
        }
    }
    cout << '\n' << ans;

    return 0;
}
