#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Function to check if a valid X-MAS pattern exists with the center at grid[row][col]
bool isXMas(const vector<string>& grid, int row, int col) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Ensure boundaries are valid
    if (!(0 <= row - 1 && row + 1 < rows && 0 <= col - 1 && col + 1 < cols)) {
        return false;
    }

    // Check the X-MAS pattern
    return (
        (grid[row - 1][col - 1] == 'M' &&
         grid[row + 1][col - 1] == 'M' &&
         grid[row - 1][col + 1] == 'S' &&
         grid[row + 1][col + 1] == 'S' &&
         grid[row][col] == 'A') ||

        (grid[row - 1][col - 1] == 'S' &&
         grid[row + 1][col - 1] == 'S' &&
         grid[row - 1][col + 1] == 'M' &&
         grid[row + 1][col + 1] == 'M' &&
         grid[row][col] == 'A') ||

        (grid[row - 1][col - 1] == 'M' &&
         grid[row + 1][col - 1] == 'S' &&
         grid[row - 1][col + 1] == 'M' &&
         grid[row + 1][col + 1] == 'S' &&
         grid[row][col] == 'A') ||

        (grid[row - 1][col - 1] == 'S' &&
         grid[row + 1][col - 1] == 'M' &&
         grid[row - 1][col + 1] == 'S' &&
         grid[row + 1][col + 1] == 'M' &&
         grid[row][col] == 'A')
    );
}

// Function to count X-MAS patterns in the grid read from the file
int countXMas(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return -1;
    }

    // Read the grid from the file
    vector<string> grid;
    string line;
    while (getline(file, line)) {
        grid.push_back(line);
    }
    file.close();

    // Initialize count
    int count = 0;

    // Traverse the grid
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            if (isXMas(grid, row, col)) {
                ++count;
            }
        }
    }

    return count;
}

int main() {
    string filePath = "/home/dell/CODING/Advent of Code 2024/Day 4/4-12-2024.txt";
    int result = countXMas(filePath);

    if (result != -1) {
        cout << "The total number of X-MAS patterns is: " << result << endl;
    }
    return 0;
}