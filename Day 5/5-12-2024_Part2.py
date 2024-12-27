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

def order_update(update, rules):
    # Orders an update according to the rules
    dependency_map = {page: set() for page in update}

    # Build the dependency map
    for x, y in rules:
        x, y = int(x), int(y)
        if x in update and y in update:
            dependency_map[y].add(x)

    # Perform topological sort
    ordered_update = []
    visited = set()

    def visit(page):
        if page not in visited:
            visited.add(page)
            for dep in dependency_map[page]:
                visit(dep)
            ordered_update.append(page)

    for page in update:
        visit(page)

    return ordered_update

def sum_middle_pages_of_fixed_updates(file_path):
    # Parses the input file and calculates the sum of middle page numbers
    rules, updates = parse_input(file_path)
    middle_sum = 0

    for update in updates:
        if not check_order(update, rules):
            # Fix the order of the update
            fixed_update = order_update(update, rules)
            # Calculate the middle page number
            middle_index = len(fixed_update) // 2
            middle_sum += fixed_update[middle_index]

    return middle_sum

file_path = "/home/dell/CODING/Advent of Code 2024/Day 5/5-12-2024.txt"
result = sum_middle_pages_of_fixed_updates(file_path)
print(f"The sum of the middle page numbers of the fixed updates is: {result}")