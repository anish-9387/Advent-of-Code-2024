def is_safe(report):

    increasing = all(report[i] <= report[i + 1] for i in range(len(report) - 1))
    decreasing = all(report[i] >= report[i + 1] for i in range(len(report) - 1))
    
    # Check if adjacent numbers differ by at least 1 and at most 3
    valid_differences = all(1 <= abs(report[i] - report[i + 1]) <= 3 for i in range(len(report) - 1))
    
    # The report is safe if it satisfies both conditions
    return (increasing or decreasing) and valid_differences

def count_safe_reports(file_path):
    # Read the input file and count the number of safe reports.
    safe_count = 0
    with open(file_path, 'r') as file:
        for line in file:
            # Convert the line to a list of integers
            report = [int(x) for x in line.strip().split()]
            if is_safe(report):
                safe_count += 1
    return safe_count

file_path = '/home/dell/CODING/Advent of Code 2024/Day 2/2-12-2024.txt'

# Count the safe reports
safe_reports_count = count_safe_reports(file_path)
print(f"Number of safe reports: {safe_reports_count}")