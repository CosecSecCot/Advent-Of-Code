#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

struct Data {
    long long dest;
    long long src;
    long long range;
};

long long getNumber(const string &line, long long &x) {
    string num = "";
    num += line[x];
    while (x + 1 < line.length() && isdigit(line[x + 1])) {
        num = num + line[x + 1];
        ++x;
    }
    return stol(num);
}

pair<long long, bool> calculate(long long &seed, const Data data) {
    // cout << seed << ' ';
    if (data.src <= seed && seed < data.src + data.range) {
        // cout << '(' << data.dest << ' ' << data.src << ' ' << data.range << ')';
        // cout << ' ' << seed - data.src + data.dest << '\n';
        return {seed - data.src + data.dest, true};
    }
    // cout << "(nope)\n";
    return {seed, false};
}

int main() {
    ifstream input_file("../input");
    string line;
    vector<string> lines;
    while (getline(input_file, line)) {
        lines.push_back(line);
    }

    vector<string> reference = {
        "seed-to-soil map:",         "soil-to-fertilizer map:",      "fertilizer-to-water map:", "water-to-light map:",
        "light-to-temperature map:", "temperature-to-humidity map:", "humidity-to-location map:"};

    vector<long long> seeds;

    for (long long i = 0; i < lines[0].size(); ++i) {
        if (isdigit(lines[0][i])) {
            long long num = getNumber(lines[0], i);
            seeds.push_back(num);
        }
    }

    vector<vector<Data>> data_sheet(7);

    for (int i = 2; i < lines.size(); ++i) {
        for (int j = 0; j < reference.size(); ++j) {
            if (lines[i] == reference[j]) {
                vector<Data> mappings = {};
                while (lines[i + 1] != "") {
                    vector<long long> nums = {};
                    ++i;
                    for (long long k = 0; k < lines[i].size(); ++k) {
                        if (isdigit(lines[i][k])) {
                            long long num = getNumber(lines[i], k);
                            nums.push_back(num);
                        }
                    }
                    Data mapping;
                    mapping.dest = nums[0];
                    mapping.src = nums[1];
                    mapping.range = nums[2];
                    mappings.push_back(mapping);
                }
                data_sheet.push_back(mappings);
                // cout << "------";
            }
        }
    }

    vector<long long> newSeeds;
    for (long long i = 0; i < seeds.size() - 1; i += 2) {
        for (long long j = 0; j < seeds[i + 1]; j++) {
            newSeeds.push_back(seeds[i] + j);
        }
    }

    for (long long i = 0; i < newSeeds.size(); ++i) {
        for (auto mappings : data_sheet) {
            for (auto mapping : mappings) {
                auto calc = calculate(newSeeds[i], mapping);
                newSeeds[i] = calc.first;
                if (calc.second) {
                    break;
                }
                // cout << newSeeds[i] << '\n';
            }
        }
        // cout << "---------------------\n";
    }

    long long min_value = *min_element(newSeeds.begin(), newSeeds.end());
    cout << min_value;
    // 20358599

    return 0;
}
