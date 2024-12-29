import re

def read_input(file_path):
    with open(file_path, 'r') as file:
        return [line.strip() for line in file]

def find_antenna_positions(grid):
    antennas = {}
    r = 0
    while r < len(grid):
        row = grid[r]
        c = 0
        while c < len(row):
            cell = row[c]
            if cell != '.':
                if cell not in antennas:
                    antennas[cell] = []
                antennas[cell].append((r, c))
            c += 1
        r += 1
    return antennas

def find_antinodes(antenna_positions, grid_height, grid_width):
    antinodes = set()
    
    # For each unique antenna frequency
    for freq, positions in antenna_positions.items():
        for i in range(len(positions)):
            r1, c1 = positions[i]
            for j in range(i + 1, len(positions)):
                r2, c2 = positions[j]
                # Check if one antenna is twice the distance of the other
                dr = r2 - r1
                dc = c2 - c1
                dist_sq = dr * dr + dc * dc
                if dist_sq % 2 == 0:  # Only consider the pair if the distance is even
                    half_dist = dist_sq // 2
                    # Compute the antinode positions
                    antinode_r1 = r1 + (dr // 2)
                    antinode_c1 = c1 + (dc // 2)
                    if 0 <= antinode_r1 < grid_height and 0 <= antinode_c1 < grid_width:
                        antinodes.add((antinode_r1, antinode_c1))
                    antinode_r2 = r2 - (dr // 2)
                    antinode_c2 = c2 - (dc // 2)
                    if 0 <= antinode_r2 < grid_height and 0 <= antinode_c2 < grid_width:
                        antinodes.add((antinode_r2, antinode_c2))

    return antinodes

def count_unique_antinodes(file_path):
    grid = read_input(file_path)
    grid_height = len(grid)
    grid_width = len(grid[0])
    antenna_positions = find_antenna_positions(grid)
    antinodes = find_antinodes(antenna_positions, grid_height, grid_width)
    return len(antinodes)

# Example Usage:
file_path = "/home/dell/CODING/Advent of Code 2024/Day 8/8-12-2024.txt"
result = count_unique_antinodes(file_path)
print(f'Number of unique locations containing an antinode: {result}')