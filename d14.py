import fileinput

field = [['.'] * 1000 for n in range(183)]

# Reading paths
paths = []
for line in fileinput.input():
	path = [coords.split(",") for coords in line.split(" -> ")]
	path = [(int(coords[0]), int(coords[1])) for coords in path]
	paths.append(path)

# Building rock
min_y = 99999
max_y = 0

min_x = 99999
max_x = 0
for path in paths:
	prevCoords = None
	for coords in path:
		max_y = max(max_y, coords[1])
		min_y = min(min_y, coords[1])
		max_x = max(max_x, coords[0])
		min_x = min(min_x, coords[0])

		if prevCoords is not None:
			for i in range(min(prevCoords[1], coords[1]), max(prevCoords[1], coords[1]) + 1):
				for j in range(min(prevCoords[0], coords[0]), max(prevCoords[0], coords[0]) + 1):
					pass
					field[i][j] = '#'
		prevCoords = coords

max_y = max_y + 2
for i in range(min_x, max_x + 1):
	field[max_y][i] = '#'

abyss = False

sand_units = 0
source_blocked = False
while True:
	# Handling sand
	i = 0
	j = 500
	while i < max_y - 1:
		if field[i + 1][j] == '.':
			i = i + 1
		elif field[i + 1][j - 1] == '.':
			i = i + 1
			j = j - 1
		elif field[i + 1][j + 1] == '.':
			i = i + 1
			j = j + 1
		else:
			if i == 0:
				source_blocked = True
			break
		# if i == len(field) - 1 or j < 0 or j == len(field[0]):
		# 	abyss = True
		# 	break

	# if abyss:
	# 	print("abyss")
	# 	print("sand units:", sand_units)
	# 	break

	field[i][j] = 'o'
	sand_units = sand_units + 1

	if source_blocked:
		print("source blocked")
		print("sand units:", sand_units)
		break

	# Output
	# print()
	# for i in range(max_y + 1):
	# 	print(f'{i:02} ', end='')
	# 	for j in range(min_x, max_x + 1):
	# 		print(field[i][j], end='')
	# 	print()