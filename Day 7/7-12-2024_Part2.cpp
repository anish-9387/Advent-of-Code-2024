#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Function to evaluate the expression formed by numbers and operators in left-to-right order
long int evaluateExpression(const vector<long int>& numbers, const vector<string>& operators) {
    long int result = numbers[0];
    for (size_t i = 0; i < operators.size(); ++i) {
        if (operators[i] == "+") {
            result += numbers[i + 1];
        } else if (operators[i] == "*") {
            result *= numbers[i + 1];
        } else if (operators[i] == "||") {
            result = stol(to_string(result) + to_string(numbers[i + 1]));
        }
    }
    return result;
}

// Recursive function to generate all combinations of '+', '*', and '||' operators
bool canCalibrate(long int target, const vector<long int>& numbers, vector<string>& operators, size_t index) {
    if (index == numbers.size() - 1) {
        return evaluateExpression(numbers, operators) == target;
    }

    // Try '+' operator
    operators[index] = "+";
    if (canCalibrate(target, numbers, operators, index + 1)) {
        return true;
    }

    // Try '*' operator
    operators[index] = "*";
    if (canCalibrate(target, numbers, operators, index + 1)) {
        return true;
    }

    // Try '||' operator
    operators[index] = "||";
    if (canCalibrate(target, numbers, operators, index + 1)) {
        return true;
    }

    return false;
}

// Function to calculate the total calibration result from the input file
long int calculateTotalCalibrationResult(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return -1;
    }

    string line;
    long int total = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string targetStr, numbersStr;
        getline(ss, targetStr, ':');
        getline(ss, numbersStr);

        long int target = stol(targetStr);
        stringstream numStream(numbersStr);
        vector<long int> numbers;
        long int num;

        while (numStream >> num) {
            numbers.push_back(num);
        }

        vector<string> operators(numbers.size() - 1);
        if (canCalibrate(target, numbers, operators, 0)) {
            total += target;
        }
    }

    file.close();
    return total;
}

int main() {
    string inputFile = "/home/dell/CODING/Advent of Code 2024/Day 7/7-12-2024.txt";
    long int result = calculateTotalCalibrationResult(inputFile);

    if (result != -1) {
        cout << "Total Calibration Result: " << result << endl;
    }
    return 0;
}