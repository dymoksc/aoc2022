import fileinput
import re
from typing import List, Tuple


def is_overlap(minS, maxE, i: Tuple[int, int]):

	if minS > i[1] or maxE < i[0]:
		return False

	return True


def merge_intervals(intervals: List[Tuple[int, int]]) -> List[Tuple[int, int]]:
	n = len(intervals)
	res = []

	vis = [False for i in range(n)]

	for i in range(n):
		if vis[i] is True:
			continue

		vis[i] = True
		minS = intervals[i][0]
		maxE = intervals[i][1]

		while 1:
			cnt = 0

			for j in range(n):

				if vis[j] is False and is_overlap(minS, maxE, intervals[j]):

					vis[j] = True
					minS = min(minS, intervals[j][0])
					maxE = max(maxE, intervals[j][1])
					cnt += 1
			if cnt == 0:
				break

		res.append((minS, maxE))

	return res


assert(merge_intervals([(0, 1), (9, 12)]) == [(0, 1), (9, 12)])
assert(merge_intervals([(0, 2), (-1, 2), (9, 12)]) == [(-1, 2), (9, 12)])

required_y = 10
# max_coord = 20  # TODO: change to 4000000
max_coord = 4000000  # TODO: change to 4000000

sharp_intervals = [[] for i in range(max_coord + 1)]
sensors_and_beacons_on_line = set()

# Parsing
print("Parsing...")
rx = re.compile(r"Sensor at x=([-0-9]+), y=([-0-9]+): closest beacon is at x=([-0-9]+), y=([-0-9]+)")
beacons_by_sensors = {}
# maxX = 0
# maxY = 0
# minX = 9999
# minY = 9999
for line in fileinput.input():
	line = line.rstrip()
	m = re.match(rx, line)
	beacons_by_sensors[(int(m[1]), int(m[2]))] = (int(m[3]), int(m[4]))
	distance = abs(int(m[1]) - int(m[3])) + abs(int(m[2]) - int(m[4]))
	# maxX = max(maxX, int(m[1]) + distance)
	# minX = min(minX, int(m[1]) - distance)
	# maxY = max(maxY, int(m[2]) + distance)
	# minY = min(minY, int(m[2]) - distance)

	for test_y in range(max_coord + 1):
		if test_y % 100000 == 0:
			print(test_y / max_coord * 100)
		diff = abs(test_y - int(m[2]))
		if diff <= distance:
			sharp_intervals[test_y].append((max(0, int(m[1]) - (distance - diff)),
											min(max_coord, int(m[1]) + (distance - diff)) + 1))
		# if int(m[2]) == required_y:
		# 	sensors_and_beacons_on_line.add(int(m[2]))
		# if int(m[4]) == required_y:
		# 	sensors_and_beacons_on_line.add(int(m[4]))

# Building field
# field = [['.'] * (maxX - minX + 1) for i in range(maxY - minY + 1)]
# for s, b in beacons_by_sensors.items():
# 	field[s[1]][s[0]] = 'S'
# 	field[b[1]][b[0]] = 'B'
# 	distance = abs(s[0] - b[0]) + abs(s[1] - b[1])
#
# 	for i in range(-distance, distance + 1):
# 		y = s[1] + i
# 		for j in range(-distance + abs(i), distance - abs(i) + 1):
# 			x = s[0] + j
# 			if field[y][x] == '.':
# 				field[y][x] = '#'
#
# for i in range(0, max_coord + 1):
# 	for j in range(0, max_coord + 1):
# 		field[i][j] = '_' if field[i][j] != '.' else '@'
#
# print(field[11][14])
# field[11][14] = '='

# Plotting field
# print('    ', end='')
# for j in range(minX, maxX + 1):
# 	print(0 if j % 10 == 0 else 5 if j % 5 == 0 else ' ', end='')
# print()
# for i in range(minY, maxY + 1):
# 	print(f'{i:03} ', end='')
# 	for j in range(minX, maxX + 1):
# 		print(field[i][j], end='')
# 	print()

# Getting answer
# print(len([x for x in field[required_y] if x == '#']))

# print(sum(x[1] - x[0] for x in sharp_intervals))

print("Searching...")
for y, sharp_interval in enumerate(sharp_intervals):
	merged_interval = merge_intervals(sharp_interval)
	if len(merged_interval) == 1 and merged_interval[0][0] > 0:
		print((0, y))
	elif len(merged_interval) == 1 and merged_interval[0][1] < max_coord + 1:
		print((max_coord, y))
	elif len(merged_interval) == 2:
		print((merged_interval[0][1], y))


# 12|3||4567891|234|56789

# merged_intervals = [merge_intervals(sharp_interval) for sharp_interval in sharp_intervals]
# print(sharp_intervals[required_y])
# print(merged_intervals[required_y])
# print(sum(x[1] - x[0] + 1 for x in merged_intervals[required_y]))

