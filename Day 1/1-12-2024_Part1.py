# Initialising empty lists for the two columns
left=[]
right=[]

with open('/home/dell/CODING/Advent of Code 2024/Day 1/1-12-2024.txt', 'r') as f:
    for line in f:
        # Appending the left side numbers in the left list
        left_number=line.split()[0]
        left.append(int(left_number))

        # Appending the right side numbers in the right list
        right_number=line.split()[1]
        right.append(int(right_number))

sum=0
while left!=[]:
    diff=min(left)-min(right)
    if diff>0:
        sum+=diff
    else:
        diff=-diff
        sum+=diff
    
    # Removing the numbers after using them into the sum
    left.remove(min(left))
    right.remove(min(right))
print("Sum:",sum)