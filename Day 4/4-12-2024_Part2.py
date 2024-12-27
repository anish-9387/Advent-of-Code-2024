def is_x_mas(grid, row, col):
    # Check if a valid X-MAS pattern exists with the center at grid[row][col]
    rows, cols = len(grid), len(grid[0])
    # Ensure boundaries are valid
    if not (0 <= row - 1 < rows and 0 <= row + 1 < rows and
            0 <= col - 1 < cols and 0 <= col + 1 < cols):
        return False

    # Check the X-MAS pattern
    return (
        (grid[row - 1][col - 1] == 'M' and
        grid[row + 1][col - 1] == 'M' and
        grid[row - 1][col + 1] == 'S' and
        grid[row + 1][col + 1] == 'S' and
        grid[row][col] == 'A')
        or
        (grid[row - 1][col - 1] == 'S' and
        grid[row + 1][col - 1] == 'S' and
        grid[row - 1][col + 1] == 'M' and
        grid[row + 1][col + 1] == 'M' and
        grid[row][col] == 'A')
        or
        (grid[row - 1][col - 1] == 'M' and
        grid[row + 1][col - 1] == 'S' and
        grid[row - 1][col + 1] == 'M' and
        grid[row + 1][col + 1] == 'S' and
        grid[row][col] == 'A')
        or
        (grid[row - 1][col - 1] == 'S' and
        grid[row + 1][col - 1] == 'M' and
        grid[row - 1][col + 1] == 'S' and
        grid[row + 1][col + 1] == 'M' and
        grid[row][col] == 'A')
    )

def count_x_mas(file_path):
    # Read the grid from the file
    with open(file_path, 'r') as f:
        grid = [line.strip() for line in f.readlines()]

    # Initialize count
    count = 0

    # Traverse the grid
    for row in range(len(grid)):
        for col in range(len(grid[0])):
            if is_x_mas(grid, row, col):
                count += 1

    return count

if __name__ == "__main__":   # Just an indication that main function starts here
    file_path = "/home/dell/CODING/Advent of Code 2024/Day 4/4-12-2024.txt"
    result = count_x_mas(file_path)
    print(f"The total number of X-MAS patterns is: {result}")