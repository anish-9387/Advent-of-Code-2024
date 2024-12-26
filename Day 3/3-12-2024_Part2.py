import re
def calculate_mul_sum_with_conditions(file_path):
    # Regular expressions for mul, do, and don't instructions
    mul_pattern = r"mul\((\d+),(\d+)\)"
    do_pattern = r"do\(\)"
    dont_pattern = r"don't\(\)"
    
    total_sum = 0
    mul_enabled = True  # By default, mul instructions are enabled

    try:
        with open(file_path, 'r') as f:
            data = f.read()
        
        # Combine all patterns to process in sequence
        combined_pattern = f"{do_pattern}|{dont_pattern}|{mul_pattern}"
        matches = re.finditer(combined_pattern, data)
        
        for match in matches:
            if match.group(0) == "do()":
                mul_enabled = True  # Enable future mul instructions
            elif match.group(0) == "don't()":
                mul_enabled = False  # Disable future mul instructions
            elif match.group(1) and match.group(2) and mul_enabled:
                # Process valid mul instructions if enabled
                num1, num2 = int(match.group(1)), int(match.group(2))
                total_sum += num1 * num2

    except FileNotFoundError:
        print(f"Error: File not found at {file_path}")
    except Exception as e:
        print(f"An error occurred: {e}")
    
    return total_sum

file_path = "/home/dell/CODING/Advent of Code 2024/Day 3/3-12-2024.txt"
result = calculate_mul_sum_with_conditions(file_path)
print(f"The sum of all enabled mul instructions is: {result}")