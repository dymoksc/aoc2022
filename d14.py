import fileinput
from pprint import pprint

paths = []
x = [None, None]
y = [None, None]
for line in fileinput.input():
	path = [coords.split(",") for coords in line.split(" -> ")]
	path = [(int(coords[0]), int(coords[1])) for coords in path]
	for coords in path:
		x[0] = coords[0] if x[0] is None or x[0] > coords[0] else x[0]
		x[1] = coords[0] if x[1] is None or x[1] < coords[0] else x[1]
		y[0] = coords[1] if y[0] is None or y[0] > coords[1] else y[0]
		y[1] = coords[1] if y[1] is None or y[1] < coords[1] else y[1]
	print(coords)
	paths.append(path)

print(paths)
print(x, y)

field = [['.']* (y[1] + 1) for n in range (x[0], x[1] + 1)]

# Building rock
for path in paths:
	prevCoords = None
	for coords in path:
		if prevCoords is not None:
			for i in range(min(prevCoords[1], coords[1]), max(prevCoords[1], coords[1]) + 1):
				for j in range(min(prevCoords[0], coords[0]), max(prevCoords[0], coords[0]) + 1):
					j = j - x[0]
					field[i][j] = '#'
		prevCoords = coords

for r in range(25):
	print()

	# Sand
	i = 0
	j = 500 - x[0]

	abyss = False
	while True:
		if i + 1 == len(field):
			abyss = True
			break

		if [i + 1][j] == '.':
			i = i + 1
		else:
			break

	if abyss:
		print("ABYSS")
		break

	field[i][j] = 'o'

	for i in range(y[1] + 1):
		print(i, "", end='')
		for j in range(x[1] - x[0] + 1):
			print(field[i][j], end='')
		print()
