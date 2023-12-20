#include <fstream>
#include <iostream>
#include <map>
using namespace std;

struct Node {
    string left;
    string right;
};

int main() {
    ifstream input_file("../input");
    string line;
    vector<string> lines;
    while (getline(input_file, line)) {
        lines.push_back(line);
    }

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

    string start = "AAA";
    string end = "ZZZ";
    int count = 0;
    while (start != end) {
        for (auto dir : path) {
            if (dir == 'L') {
                start = nodes[start].left;
            } else {
                start = nodes[start].right;
            }
            count++;
        }
    }
    cout << count;

    return 0;
}
