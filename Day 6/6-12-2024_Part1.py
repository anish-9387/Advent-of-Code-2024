def read_map(file_path):
    with open(file_path, 'r') as f:
        return [list(line.strip()) for line in f.readlines()]

def find_guard_position(grid):
    for y, row in enumerate(grid):
        for x, cell in enumerate(row):
            if cell in "^v<>":
                return x, y, cell  # Return x, y, and the direction

def turn_right(direction):
    directions = {"^": ">", ">": "v", "v": "<", "<": "^"}
    return directions[direction]

def move(x, y, direction):
    moves = {"^": (0, -1), "v": (0, 1), "<": (-1, 0), ">": (1, 0)}
    dx, dy = moves[direction]
    return x + dx, y + dy

def simulate(file_path):
    grid = read_map(file_path)
    x, y, direction = find_guard_position(grid)
    visited = set()
    rows, cols = len(grid), len(grid[0])

    while 0 <= x < cols and 0 <= y < rows:
        visited.add((x, y))
        next_x, next_y = move(x, y, direction)

        # Check if the next position is within bounds and not an obstacle
        if 0 <= next_x < cols and 0 <= next_y < rows and grid[next_y][next_x] != "#":
            x, y = next_x, next_y
        else:
            direction = turn_right(direction)

    return len(visited)

file_path = "/home/dell/CODING/Advent of Code 2024/Day 6/6-12-2024.txt"
print("Distinct positions visited:", simulate(file_path))