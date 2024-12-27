def parse_input(file_path):
    # Parses the input file into ordering rules and updates
    with open(file_path, 'r') as f:
        lines = f.read().strip().split("\n")
    
    # Split rules and updates
    split_index = lines.index("")
    rules = [line.split("|") for line in lines[:split_index]]
    updates = [list(map(int, update.split(","))) for update in lines[split_index + 1:]]
    
    return rules, updates

def check_order(update, rules):
    # Checks if an update is correctly ordered based on the rules
    for x, y in rules:
        if int(x) in update and int(y) in update:
            if update.index(int(x)) > update.index(int(y)):
                return False
    return True

def sum_middle_pages(file_path):
    # Calculates the sum of middle page numbers from correctly-ordered updates
    rules, updates = parse_input(file_path)
    correctly_ordered_updates = []
    
    for update in updates:
        if check_order(update, rules):
            correctly_ordered_updates.append(update)
    
    # Find and sum of the middle page numbers
    middle_sum = 0
    for update in correctly_ordered_updates:
        middle_index = len(update) // 2
        middle_sum += update[middle_index]
    
    return middle_sum

file_path = "/home/dell/CODING/Advent of Code 2024/Day 5/5-12-2024.txt"
result = sum_middle_pages(file_path)
print(f"The sum of the middle page numbers is: {result}")