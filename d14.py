import fileinput

field = [['.'] * 504 for n in range(10)]

# Reading paths
paths = []
for line in fileinput.input():
	path = [coords.split(",") for coords in line.split(" -> ")]
	path = [(int(coords[0]), int(coords[1])) for coords in path]
	paths.append(path)

# Building rock
for path in paths:
	prevCoords = None
	for coords in path:
		if prevCoords is not None:
			for i in range(min(prevCoords[1], coords[1]), max(prevCoords[1], coords[1]) + 1):
				for j in range(min(prevCoords[0], coords[0]), max(prevCoords[0], coords[0]) + 1):
					field[i][j] = '#'
		prevCoords = coords

# Output
for i in range(10):
	print(i, "", end='')
	for j in range(494, 504):
		print(field[i][j], end='')
	print()
