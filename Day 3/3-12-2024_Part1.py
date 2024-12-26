import re
def calculate_mul_sum(file_path):
    # Regular expression to match valid mul instructions
    mul_pattern = r"mul\((\d+),(\d+)\)"    
    total_sum = 0

    try:    
        with open(file_path, 'r') as f:
            data = f.read()
            
        # Find all valid mul instructions
        matches = re.findall(mul_pattern, data)
            
        # Calculate the sum of all multiplications
        for match in matches:
            num1, num2 = map(int, match)
            total_sum += num1 * num2
            
    except FileNotFoundError:
        print(f"Error: File not found at {file_path}")
    except Exception as e:
        print(f"An error occurred: {e}")
    
    return total_sum

file_path = "/home/dell/CODING/Advent of Code 2024/Day 3/3-12-2024.txt"
result = calculate_mul_sum(file_path)
print(f"The sum of all valid mul instructions is: {result}")