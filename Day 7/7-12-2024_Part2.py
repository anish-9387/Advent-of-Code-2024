from itertools import product

def evaluate_expression(numbers, operators):
    # Evaluates the expression formed by numbers and operators in left-to-right order
    result = numbers[0]
    for i in range(len(operators)):
        op = operators[i]
        if op == '+':
            result += numbers[i + 1]
        elif op == '*':
            result *= numbers[i + 1]
        elif op == '||':
            result = int(str(result) + str(numbers[i + 1]))
    return result

def can_calibrate(target, numbers):
    # Checks if the target can be achieved by placing operators between numbers
    # Generate all combinations of '+', '*', and '||' operators
    operator_combinations = product(['+', '*', '||'], repeat=len(numbers) - 1)
    for operators in operator_combinations:
        if evaluate_expression(numbers, operators) == target:
            return True
    return False

def calculate_total_calibration_result(filename):
    # Calculates the total calibration result from the input file
    total = 0
    with open(filename, 'r') as f:
        for line in f:
            if not line.strip():
                continue
            target, numbers = line.split(':')
            target = int(target.strip())
            numbers = [int(num) for num in numbers.split()]
            if can_calibrate(target, numbers):
                total += target
    return total

# Input file path
input_file = "/home/dell/CODING/Advent of Code 2024/Day 7/7-12-2024.txt"
result = calculate_total_calibration_result(input_file)
print("Total Calibration Result:", result)