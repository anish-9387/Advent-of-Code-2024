#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    // Initialising empty vectors for the two columns
    vector<int> left;
    vector<int> right;

    ifstream file("/home/dell/CODING/Advent of Code 2024/Day 1/1-12-2024.txt");

    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        size_t spacePos = line.find(' ');
        if (spacePos != string::npos) {
            int left_number = stoi(line.substr(0, spacePos));
            int right_number = stoi(line.substr(spacePos + 1));
            // Appending the left side numbers in the left vector
            left.push_back(left_number);

            // Appending the right side numbers in the right vector
            right.push_back(right_number);
        }
    }
    file.close();

    int sum = 0;
    unordered_map<int, int> right_count;
    for (int num : right) {
        right_count[num]++;
    }

    for (int i : left) {
        sum += i * right_count[i];
    }

    cout << "Sum: " << sum << endl;

    return 0;
}