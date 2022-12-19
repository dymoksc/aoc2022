import fileinput


def print_field():
    print()
    for i in range(len(field) - 1, -1, -1):
        print(i, end=' ')
        for j in range(len(field[i])):
            if (int(j), int(i)) in rock:
                print('@', end='')
            else:
                print(field[i][j], end='')
        print()
    print('  +-------+')


for line in fileinput.input():
    line = line.rstrip()

directions = []
for c in line:
    directions.append(c)
    directions.append('v')

row = ['|'] + ['.'] * 7 + ['|']
field = []
highest_point = 0

# Getting coordinates for a rock
y = highest_point + 3
x = 3
while len(field) < y + 1:
    field.append(row)

# Spawning a rock
rock = [(x, y), (x + 1, y), (x + 2, y), (x + 3, y)]
print_field()

# Moving a rock
dir_iter = 0
i = 0
while i < 20:
    i += 1

    dir = directions[dir_iter]
    # Getting direction
    dir_iter += 1
    if dir_iter == len(directions):
        dir_iter = 0

    new_rock = rock.copy()
    if dir == 'v':
        new_rock = [(c[0], c[1] - 1) for c in new_rock]
        print("Going down. New coordinates are", new_rock)
    elif dir == '>':
        new_rock = [(c[0] + 1, c[1]) for c in new_rock]
        print("Going right. New coordinates are", new_rock)
    elif dir == '<':
        new_rock = [(c[0] - 1, c[1]) for c in new_rock]
        print("Going left. New coordinates are", new_rock)

    cont = False
    brk = False
    for c in new_rock:
        if c[1] < 0:
            # Violated vertical constraint
            print(c, "violates vertical constraint")
            brk = True
            break
        if not 0 <= c[0] <= 6:
            # Violated horizontal constraint
            print(c, "violates horizontal constraints")
            cont = True
            break

    if cont:
        print("Continuing")
        continue

    if brk:
        print("Breaking")
        break

    rock = new_rock
    print_field()
