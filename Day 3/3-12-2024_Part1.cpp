#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using namespace std;

int calculateMulSum(const string& filePath) {
    // Regular expression to match valid mul instructions
    regex mulPattern(R"(mul\((\d+),(\d+)\))");
    smatch matches;

    int totalSum = 0;
    string line;

    try {
        ifstream inputFile(filePath);
        if (!inputFile.is_open()) {
            throw ios_base::failure("File not found");
        }

        // Read the file content
        string data((istreambuf_iterator<char>(inputFile)),
                    istreambuf_iterator<char>());

        // Use regex iterator to find all matches
        auto begin = sregex_iterator(data.begin(), data.end(), mulPattern);
        auto end = sregex_iterator();

        for (auto it = begin; it != end; ++it) {
            matches = *it;
            int num1 = stoi(matches[1].str());
            int num2 = stoi(matches[2].str());
            totalSum += num1 * num2;
        }
    } 
    catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }

    return totalSum;
}

int main() {
    string filePath = "/home/dell/CODING/Advent of Code 2024/Day 3/3-12-2024.txt";
    int result = calculateMulSum(filePath);
    cout << "The sum of all valid mul instructions is: " << result << endl;
    return 0;
}