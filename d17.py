import fileinput
from collections import namedtuple

row = ['.'] * 7
field = []
highest_point = -1
rocks_count = 0
figure_num = 0
Figure = namedtuple("Figure", ["points", "height"])
figures = [
    Figure(lambda x, y: [(x, y), (x + 1, y), (x + 2, y), (x + 3, y)], 1),
    Figure(lambda x, y: [(x + 1, y + 1), (x, y + 1), (x + 2, y + 1), (x + 1, y), (x + 1, y + 2)], 3),
    Figure(lambda x, y: [(x, y), (x + 1, y), (x + 2, y), (x + 2, y + 1), (x + 2, y + 2)], 3),
    Figure(lambda x, y: [(x, y), (x, y + 1), (x, y + 2), (x, y + 3)], 4),
    Figure(lambda x, y: [(x, y), (x, y + 1), (x + 1, y + 1), (x + 1, y)], 4),
]


def print_field():
    print()
    for i in range(len(field) - 1, -1, -1):
        print(i % 10, end=' |')
        for j in range(len(field[i])):
            if (int(j), int(i)) in rock:
                print('@', end='')
            else:
                print(field[i][j], end='')
        print('|')
    print('  +-------+')


def spawn_rock() -> list[tuple[int, int]]:
    global rocks_count, figure_num

    # Getting coordinates for a rock
    y = highest_point + 4
    x = 2

    # print("Getting figure #", figure_num % len(figures))
    figure = figures[figure_num]
    figure_num += 1
    figure_num %= len(figures)

    while len(field) < y + figure.height:
        field.append(row.copy())

    # Spawning a rock
    rocks_count += 1

    return figure.points(x, y)


# Parsing
for line in fileinput.input():
    line = line.rstrip()

# Adding down movement
directions = []
for c in line:
    directions.append(c)
    directions.append('v')

rock = spawn_rock()
# print_field()

# Moving a rock
dir_iter = 0

# loop = len(directions) * len(figures)
# loop = 100

# loop_height = 608
# n = 10000
n = 1000000000000

# example
# start = 25 height, 17 rocks
# loop = 53 height, 35 rocks

# full
# start = 349 height, 219 rocks
# loop = 2644 height, 1730 rocks

height_addition = 0

# start = 17
# loop_rocks = 35
# loop_height = 53

start_rocks = 222
loop_rocks = 1730
loop_height = 2644

# n = start_rocks + loop_rocks * 2 + 15

if n - start_rocks > loop_rocks:
    height_addition = (n - start_rocks) // loop_rocks * loop_height
    n = start_rocks + (n - start_rocks) % loop_rocks

# n = 222 + 1730 * 4
while rocks_count < (n):
    # if highest_point % 52 == 0:
    #     print(rocks_count)

    dir = directions[dir_iter]
    # Getting direction
    dir_iter += 1
    if dir_iter == len(directions):
        dir_iter = 0

    new_rock = rock.copy()
    if dir == 'v':
        new_rock = [(c[0], c[1] - 1) for c in new_rock]
        # print("Going down. New coordinates are", new_rock)
    elif dir == '>':
        new_rock = [(c[0] + 1, c[1]) for c in new_rock]
        # print("Going right. New coordinates are", new_rock)
    elif dir == '<':
        new_rock = [(c[0] - 1, c[1]) for c in new_rock]
        # print("Going left. New coordinates are", new_rock)

    cont = False
    brk = False
    for c in new_rock:
        if c[1] < 0:
            # Violated vertical constraint
            # print(c, "violates vertical constraint")
            brk = True
            break

        if not 0 <= c[0] <= 6:
            # Violated horizontal constraint
            # print(c, "violates horizontal constraints")
            cont = True
            break

        if field[c[1]][c[0]] == '#':
            # print(c, "collides with older rock")
            if dir == 'v':
                brk = True
            else:
                cont = True
            break

    if cont:
        # print("Continuing")
        continue

    if brk:
        # print("Breaking")

        # Add rock to field
        for c in rock:
            # print(c)
            field[c[1]][c[0]] = '#'
            highest_point = max(highest_point, c[1])
        # print(rocks_count, "rock stopped")
        rock = spawn_rock()

    else:
        rock = new_rock

print_field()
print(highest_point + 1 + height_addition)
print(highest_point, "+", 1, "+", height_addition)
print(rocks_count)

