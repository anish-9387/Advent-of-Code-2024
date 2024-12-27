#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to parse the input file
pair<vector<pair<int, int>>, vector<vector<int>>> parseInput(const string &filePath) {
    ifstream file(filePath);
    vector<pair<int, int>> rules;
    vector<vector<int>> updates;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file!" << endl;
        exit(1);
    }

    string line;
    bool isRulesSection = true;

    while (getline(file, line)) {
        if (line.empty()) {
            isRulesSection = false; // Switch to updates section
            continue;
        }

        if (isRulesSection) {
            stringstream ss(line);
            string first, second;
            getline(ss, first, '|');
            getline(ss, second, '|');
            rules.emplace_back(stoi(first), stoi(second));
        }
        else {
            stringstream ss(line);
            vector<int> update;
            string number;
            while (getline(ss, number, ',')) {
                update.push_back(stoi(number));
            }
            updates.push_back(update);
        }
    }

    file.close();
    return {rules, updates};
}

// Function to check if an update is correctly ordered
bool checkOrder(const vector<int> &update, const vector<pair<int, int>> &rules) {
    for (const auto &[x, y] : rules) {
        auto itX = find(update.begin(), update.end(), x);
        auto itY = find(update.begin(), update.end(), y);

        // Both x and y must be present in the update, and x must appear before y
        if (itX != update.end() && itY != update.end() && itX > itY) {
            return false;
        }
    }
    return true;
}

// Function to calculate the sum of middle page numbers from correctly-ordered updates
int sumMiddlePages(const string &filePath) {
    auto [rules, updates] = parseInput(filePath);
    int middleSum = 0;

    for (const auto &update : updates) {
        if (checkOrder(update, rules)) {
            int middleIndex = update.size() / 2;
            middleSum += update[middleIndex];
        }
    }

    return middleSum;
}

int main() {
    string filePath = "/home/dell/CODING/Advent of Code 2024/Day 5/5-12-2024.txt";
    int result = sumMiddlePages(filePath);
    cout << "The sum of the middle page numbers is: " << result << endl;
    return 0;
}