#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <tuple>

using namespace std;

// Function to read the map from a file
vector<string> read_map(const string& file_path) {
    ifstream file(file_path);
    vector<string> grid;
    string line;

    while (getline(file, line)) {
        grid.push_back(line);
    }

    return grid;
}

// Find the guard's position and direction
tuple<int, int, char> find_guard_position(const vector<string>& grid) {
    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            char cell = grid[y][x];
            if (cell == '^' || cell == 'v' || cell == '<' || cell == '>') {
                return {x, y, cell};
            }
        }
    }
    return {-1, -1, ' '}; // Default return in case the guard is not found
}

// Turn right based on the current direction
char turn_right(char direction) {
    switch (direction) {
        case '^': return '>';
        case '>': return 'v';
        case 'v': return '<';
        case '<': return '^';
        default: return ' ';
    }
}

// Calculate the next position based on the direction
tuple<int, int> move(int x, int y, char direction) {
    switch (direction) {
        case '^': return {x, y - 1};
        case 'v': return {x, y + 1};
        case '<': return {x - 1, y};
        case '>': return {x + 1, y};
        default: return {x, y};
    }
}

// Simulate the guard's movements and count visited positions
int simulate(const string& file_path) {
    vector<string> grid = read_map(file_path);
    auto [x, y, direction] = find_guard_position(grid);
    set<pair<int, int>> visited;
    int rows = grid.size();
    int cols = grid[0].size();

    while (x >= 0 && x < cols && y >= 0 && y < rows) {
        visited.insert({x, y});
        auto [next_x, next_y] = move(x, y, direction);

        if (next_x >= 0 && next_x < cols && next_y >= 0 && next_y < rows && grid[next_y][next_x] != '#') {
            x = next_x;
            y = next_y;
        } else {
            direction = turn_right(direction);
        }
    }

    return visited.size();
}

int main() {
    string file_path = "/home/dell/CODING/Advent of Code 2024/Day 6/6-12-2024.txt";
    cout << "Distinct positions visited: " << simulate(file_path) << endl;
    return 0;
}