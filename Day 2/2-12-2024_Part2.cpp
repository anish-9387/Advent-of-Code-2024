#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

// Function to check if a report is monotonic and has valid differences
bool is_safe(const vector<int>& report) {
    bool increasing = true, decreasing = true, valid_differences = true;

    for (size_t i = 0; i < report.size() - 1; ++i) {
        if (report[i] > report[i + 1]) {
            increasing = false;
        }
        if (report[i] < report[i + 1]) {
            decreasing = false;
        }
        int difference = abs(report[i] - report[i + 1]);
        if (difference < 1 || difference > 3) {
            valid_differences = false;
        }
    }

    // The report is safe if it satisfies both conditions
    return (increasing || decreasing) && valid_differences;
}

// Function to check if the report becomes safe after removing one element
bool is_safe_after_removal(const vector<int>& report) {
    // Check if the original report is safe
    if (is_safe(report)) {
        return true;
    }

    // Check if removing any single number makes the report safe
    for (size_t i = 0; i < report.size(); ++i) {
        vector<int> modified_report;
        for (size_t j = 0; j < report.size(); ++j) {
            if (j != i) {
                modified_report.push_back(report[j]);
            }
        }
        if (is_safe(modified_report)) {
            return true;
        }
    }

    return false;
}

// Function to count the number of safe reports
int count_safe_reports(const string& file_path) {
    int safe_count = 0;
    ifstream file(file_path);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return -1;
    }

    string line;
    while (getline(file, line)) {
        vector<int> report;
        stringstream ss(line);
        int number;

        // Convert the line to a list of integers
        while (ss >> number) {
            report.push_back(number);
        }

        // Check if the report is safe
        if (is_safe_after_removal(report)) {
            ++safe_count;
        }
    }

    file.close();
    return safe_count;
}

int main() {
    string file_path = "/home/dell/CODING/Advent of Code 2024/Day 2/2-12-2024.txt";

    // Count the safe reports
    int safe_reports_count = count_safe_reports(file_path);

    if (safe_reports_count != -1) {
        cout << "Number of safe reports (after possible removal): " << safe_reports_count << endl;
    }
    return 0;
}