def count_xmas_occurrences(file_path):
    def count_in_direction(grid, word, start_row, start_col, dr, dc):
        # Count occurrences of a word starting from a position in a specific direction
        count = 0
        word_length = len(word)
        rows, cols = len(grid), len(grid[0])

        r, c = start_row, start_col
        for i in range(word_length):
            if 0 <= r < rows and 0 <= c < cols and grid[r][c] == word[i]:
                r += dr
                c += dc
            else:
                break
        else:
            count += 1
        return count

    # Read the grid from the file
    with open(file_path, 'r') as f:
        grid = [line.strip() for line in f.readlines()]

    word = "XMAS"
    directions = [  # All 8 possible directions
        (1, 0),   # Right
        (-1, 0),  # Left
        (0, -1),   # Down
        (0, 1),  # Up
        (1, -1),   # Diagonal Down-Right
        (-1, 1), # Diagonal Up-Left
        (-1, -1),  # Diagonal Down-Left
        (1, 1)   # Diagonal Up-Right
    ]

    total_count = 0

    # Check all positions in the grid
    for row in range(len(grid)):
        for col in range(len(grid[0])):
            for dr, dc in directions:
                total_count += count_in_direction(grid, word, row, col, dr, dc)

    return total_count

# Example usage
file_path = "/home/dell/CODING/Advent of Code 2024/Day 4/4-12-2024.txt"
result = count_xmas_occurrences(file_path)
print(f"The total number of times XMAS appears is: {result}")