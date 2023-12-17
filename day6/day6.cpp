#include <cctype>
#include <fstream>
#include <iostream>
using namespace std;

long getNumber(const string &line, long &x) {
    string num = "";
    num += line[x];
    while (x + 1 < line.length() && isdigit(line[x + 1])) {
        cout << "-->" << num;
        num = num + line[x + 1];
        ++x;
    }
    cout << "-->" << num;
    return stoi(num);
}

int main() {
    freopen("output.txt", "w", stdout);
    vector<long> times = {42899189};
    vector<long> distances = {308117012911467};

    long count = 0;
    for (long i = 0; i < 42899189; ++i) {
        long distance = abs(42899189 - i) * i;
        cout << distance << ' ';
        if (distance > 308117012911467) {
            count++;
            cout << count;
        }
        cout << '\n';
    }
    cout << count;

    return 0;
}
