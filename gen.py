import random
CASE = ['#', '.', '$', '*',' ',' ',' ',' ',' ',' ',' ',' ']
SIZE = 1000
file = open("data/hugemap.lvl", "w")
file.write(";LEVEL 1\n")
perso = False
STRING=""
x_1, y_1 = random.randint(1,SIZE-1), random.randint(1,SIZE-1)
for x in range(SIZE):
    for y in range(SIZE):
        if x == x_1 and y == y_1:
            STRING += '@'
        else:
            STRING += random.choice(CASE)
    STRING += '\n'

file.write(STRING)
