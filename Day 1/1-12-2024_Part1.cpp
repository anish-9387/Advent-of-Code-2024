#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Initialising empty vectors for the two columns
    vector<int> left;
    vector<int> right;
    ifstream file("/home/dell/CODING/Advent of Code 2024/Day 1/1-12-2024.txt");

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
    while (!left.empty()) {
        auto min_left_it = min_element(left.begin(), left.end());
        auto min_right_it = min_element(right.begin(), right.end());

        int diff = *min_left_it - *min_right_it;
        sum += abs(diff);

        // Removing the numbers after using them into the sum
        left.erase(min_left_it);
        right.erase(min_right_it);
    }

    cout << "Sum: " << sum << endl;
    return 0;
}