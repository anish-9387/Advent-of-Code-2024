#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>

using namespace std;

// Function to parse the input file into ordering rules and updates
pair<vector<pair<int, int>>, vector<vector<int>>> parseInput(const string& filePath) {
    ifstream file(filePath);
    vector<pair<int, int>> rules;
    vector<vector<int>> updates;
    string line;
    bool isUpdateSection = false;

    while (getline(file, line)) {
        if (line.empty()) {
            isUpdateSection = true;
            continue;
        }

        if (!isUpdateSection) {
            stringstream ss(line);
            string x, y;
            getline(ss, x, '|');
            getline(ss, y, '|');
            rules.emplace_back(stoi(x), stoi(y));
        }
        else {
            stringstream ss(line);
            vector<int> update;
            string num;
            while (getline(ss, num, ',')) {
                update.push_back(stoi(num));
            }
            updates.push_back(update);
        }
    }

    return {rules, updates};
}

// Function to check if an update is correctly ordered based on the rules
bool checkOrder(const vector<int>& update, const vector<pair<int, int>>& rules) {
    unordered_map<int, int> indexMap;
    for (int i = 0; i < update.size(); ++i) {
        indexMap[update[i]] = i;
    }

    for (const auto& rule : rules) {
        int x = rule.first, y = rule.second;
        if (indexMap.count(x) && indexMap.count(y) && indexMap[x] > indexMap[y]) {
            return false;
        }
    }
    return true;
}

// Function to reorder an update according to the rules
vector<int> orderUpdate(const vector<int>& update, const vector<pair<int, int>>& rules) {
    unordered_map<int, unordered_set<int>> dependencyMap;
    for (int page : update) {
        dependencyMap[page] = {};
    }

    for (const auto& rule : rules) {
        int x = rule.first, y = rule.second;
        if (dependencyMap.count(x) && dependencyMap.count(y)) {
            dependencyMap[y].insert(x);
        }
    }

    vector<int> orderedUpdate;
    unordered_set<int> visited;

    function<void(int)> visit = [&](int page) {
        if (visited.count(page)) return;
        visited.insert(page);
        for (int dep : dependencyMap[page]) {
            visit(dep);
        }
        orderedUpdate.push_back(page);
    };

    for (int page : update) {
        visit(page);
    }

    reverse(orderedUpdate.begin(), orderedUpdate.end());
    return orderedUpdate;
}

// Function to calculate the sum of the middle page numbers of fixed updates
int sumMiddlePagesOfFixedUpdates(const string& filePath) {
    auto [rules, updates] = parseInput(filePath);
    int middleSum = 0;

    for (const auto& update : updates) {
        if (!checkOrder(update, rules)) {
            vector<int> fixedUpdate = orderUpdate(update, rules);
            int middleIndex = fixedUpdate.size() / 2;
            middleSum += fixedUpdate[middleIndex];
        }
    }

    return middleSum;
}

int main() {
    string filePath = "/home/dell/CODING/Advent of Code 2024/Day 5/5-12-2024.txt";
    int result = sumMiddlePagesOfFixedUpdates(filePath);
    cout << "The sum of the middle page numbers of the fixed updates is: " << result << endl;
    return 0;
}