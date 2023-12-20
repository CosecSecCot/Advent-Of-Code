#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>
using namespace std;

struct Node {
    string left;
    string right;
};

template <typename T>
T LcmOfVector(vector<T> arr, T idx) {
    // lcm(a,b) = (a*b/gcd(a,b))
    if (idx == arr.size() - 1) {
        return arr[idx];
    }
    T a = arr[idx];
    T b = LcmOfVector(arr, idx + 1);
    return (a * b / gcd(a, b));
}

int main() {
    ifstream input_file("../input");
    string line;
    vector<string> lines;
    while (getline(input_file, line)) {
        lines.push_back(line);
    }
    // #ifndef ONLINE_JUDGE
    //     freopen("output.txt", "w", stdout);
    // #endif

    string path = lines[0];
    map<string, Node> nodes;

    for (int i = 2; i < lines.size(); ++i) {
        string curr = lines[i].substr(0, 3);
        string left = lines[i].substr(lines[i].find('(') + 1, 3);
        string right = lines[i].substr(lines[i].find(',') + 2, 3);
        Node currNode;
        currNode.left = left;
        currNode.right = right;
        nodes[curr] = currNode;
    }

    // This was part 1
    // string start = "AAA";
    // string end = "ZZZ";

    vector<string> startingPositions;
    regex endWithA("..A");
    regex endWithZ("..Z");
    for (const auto &[curr, node] : nodes) {
        if (regex_match(curr, endWithA) == 1) {
            startingPositions.push_back(curr);
        }
    }

    for (auto pos : startingPositions) {
        cout << pos << ' ';
    }
    cout << '\n';
    cout << path << '\n';

    /*
     *
     * these stating positions reach ..Z after the following steps
     * and repeat that pattern
     *
     * AAA: ** (2 steps)
     * DNA: *** (3 steps)
     * VGA: **** (4 steps)
     *
     *
     */

    /*
     *  notation :
     *  * - for non ..Z position
     *  & - for ..Z position
     *
     * Steps |   0  1 2 3 4 5 6 7 8 9 10 11 12 <-- (ans)
     *       | AAA: * & * & * & * & * &  *  &
     *       | DNA: * * & * * & * * & *  *  &
     *       | VGA: * * * & * * * & * *  *  &
     *
     *
     * */

    vector<long> counts;
    for (auto &start_pos : startingPositions) {
        // string start_pos = startingPositions[0];
        long count = 0;
        bool isdone = false;
        while (!isdone) {
            for (auto dir : path) {
                if (dir == 'L') {
                    start_pos = nodes[start_pos].left;
                } else {
                    start_pos = nodes[start_pos].right;
                }
                if (isdone) {
                    break;
                }
                count++;
                isdone = regex_match(start_pos, endWithZ) == 1;
                cout << start_pos << ' ' << dir << ' ' << count << ' ' << isdone << '\n';
            }
        }
        counts.push_back(count);
        cout << "\n\n";
    }

    for (auto count : counts) {
        cout << count << '\n';
    }

    // 14429
    // 20569
    // 18727
    // 22411
    // 13201
    // 18113

    // ans : 10921547990923

    long ans = LcmOfVector<long>(counts, 0);
    cout << ans;

    return 0;
}
