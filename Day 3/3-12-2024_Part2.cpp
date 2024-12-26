#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using namespace std;

int calculateMulSumWithConditions(const string& filePath) {
    // Regular expressions for mul, do, and don't instructions
    regex mulPattern(R"(mul\((\d+),(\d+)\))");
    regex doPattern(R"(do\(\))");
    regex dontPattern(R"(don't\(\))");
    
    int totalSum = 0;
    bool mulEnabled = true; // By default, mul instructions are enabled

    try {
        ifstream inputFile(filePath);
        if (!inputFile.is_open()) {
            throw ios_base::failure("File not found");
        }

        // Read the file content
        string data((istreambuf_iterator<char>(inputFile)),
                    istreambuf_iterator<char>());

        // Combine all patterns to process in sequence
        regex combinedPattern(R"((do\(\))|(don't\(\))|(mul\((\d+),(\d+)\)))");
        auto matchesBegin = sregex_iterator(data.begin(), data.end(), combinedPattern);
        auto matchesEnd = sregex_iterator();

        for (auto it = matchesBegin; it != matchesEnd; ++it) {
            smatch match = *it;

            if (match.str(1) == "do()") {
                mulEnabled = true; // Enable future mul instructions
            } else if (match.str(2) == "don't()") {
                mulEnabled = false; // Disable future mul instructions
            } else if (match.str(3).find("mul") != string::npos && mulEnabled) {
                // Process valid mul instructions if enabled
                int num1 = stoi(match.str(4));
                int num2 = stoi(match.str(5));
                totalSum += num1 * num2;
            }
        }

    } 
    catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }

    return totalSum;
}

int main() {
    string filePath = "/home/dell/CODING/Advent of Code 2024/Day 3/3-12-2024.txt";
    int result = calculateMulSumWithConditions(filePath);
    cout << "The sum of all enabled mul instructions is: " << result << endl;
    return 0;
}