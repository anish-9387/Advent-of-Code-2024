#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int countInDirection(const vector<string>& grid, const string& word, int startRow, int startCol, int dr, int dc) {
    // Count occurrences of a word starting from a position in a specific direction
    int count = 0;
    int wordLength = word.length();
    int rows = grid.size();
    int cols = grid[0].size();

    int r = startRow, c = startCol;
    for (int i = 0; i < wordLength; ++i) {
        if (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == word[i]) {
            r += dr;
            c += dc;
        } 
        else {
            return 0; // Break out of the loop if any character doesn't match
        }
    }
    return 1; // If all characters match, return 1 occurrence
}

int countXMASOccurrences(const string& filePath) {
    // Read the grid from the file
    ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        cerr << "Error: File not found at " << filePath << endl;
        return 0;
    }

    vector<string> grid;
    string line;
    while (getline(inputFile, line)) {
        grid.push_back(line);
    }
    inputFile.close();

    string word = "XMAS";
    vector<pair<int, int>> directions = { // All 8 possible directions
        {0, -1},   // Down
        {0, 1},    // Up
        {-1, 0},   // Left
        {1, 0},    // Right
        {-1, -1},  // Bottom-left diagonal
        {-1, 1},   // Top-left diagonal
        {1, -1},   // Bottom-right diagonal
        {1, 1}     // Top-right diagonal
    };

    int totalCount = 0;

    // Check all positions in the grid
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            for (const auto& direction : directions) {
                totalCount += countInDirection(grid, word, row, col, direction.first, direction.second);
            }
        }
    }

    return totalCount;
}

int main() {
    string filePath = "/home/dell/CODING/Advent of Code 2024/Day 4/4-12-2024.txt";
    int result = countXMASOccurrences(filePath);
    cout << "The total number of times XMAS appears is: " << result << endl;
    return 0;
}