import fileinput
from collections import namedtuple
from pprint import pprint

Point = namedtuple("Point", ['x', 'y', 'z'])


def manhattan_dist(p1: Point, p2: Point):
	return abs(p1.x - p2.x) + abs(p1.y - p2.y) + abs(p1.z - p2.z)

assert manhattan_dist(Point(0, 0, 0), Point(0, 0, 0)) == 0
assert manhattan_dist(Point(0, 0, 0), Point(0, 0, 1)) == 1
assert manhattan_dist(Point(0, 0, 0), Point(0, 1, 1)) == 2
assert manhattan_dist(Point(0, 0, 0), Point(0, -1, -1)) == 2


class Plane:
	p1 = ...  # Point
	p2 = ...  # Point

	def __init__(self, p1: Point, p2: Point):
		assert manhattan_dist(p1, p2) == 2
		assert p1.x == p2.x or p1.y == p2.y or p1.z == p2.z
		self.p1 = p1
		self.p2 = p2

	def __eq__(self, other: 'Plane') -> bool:
		return self.p1 == other.p1 and self.p2 == other.p2

	def __hash__(self):
		return hash(str(self.p1) + str(self.p2))


class Cube:
	planes = []  # list[Plane]

	def __init__(self, p: Point):
		self.planes = []
		assert len(self.planes) == 0
		for mod in range(-1, 1):
			self.planes.append(Plane(
				Point(p.x + mod, p.y - 1, p.z - 1),
				Point(p.x + mod, p.y, p.z),
			))
			self.planes.append(Plane(
				Point(p.x - 1, p.y + mod, p.z - 1),
				Point(p.x, p.y + mod, p.z),
			))
			self.planes.append(Plane(
				Point(p.x - 1, p.y - 1, p.z + mod),
				Point(p.x, p.y, p.z + mod),
			))
		assert len(self.planes) == 6

cube = Cube(Point(1, 1, 1))

# XY planes
assert Plane(Point(0, 0, 0), Point(1, 1, 0)) in cube.planes
assert Plane(Point(0, 0, 1), Point(1, 1, 1)) in cube.planes

# XZ planes
assert Plane(Point(0, 0, 0), Point(1, 0, 1)) in cube.planes
assert Plane(Point(0, 1, 0), Point(1, 1, 1)) in cube.planes

# YZ planes
assert Plane(Point(0, 0, 0), Point(0, 1, 1)) in cube.planes
assert Plane(Point(1, 0, 0), Point(1, 1, 1)) in cube.planes

planes_map = {}  # map[Plane, int]

# Max values + 1
mx = 20
my = 20
mz = 20
# mx = 4
# my = 4
# mz = 7
area = [[[[0, 0] for z in range(mz + 1)] for y in range(my + 1)] for z in range(mz + 1)]  # list[list[list[bool]]]
for line in fileinput.input():
	point = Point(*[int(i) for i in line.rstrip().split(',')])
	area[point.x][point.y][point.z][0] = 1

	cube = Cube(point)
	for p in cube.planes:
		if p in planes_map:
			planes_map[p] += 1
		else:
			planes_map[p] = 1

def dfs(p: Point):
	area[p.x][p.y][p.z][1] = 1
	for x in range(max(0, p.x - 1), min(mx + 1, p.x + 2)):
		if area[x][p.y][p.z] == [0, 0]:
			dfs(Point(x, p.y, p.z))
	for y in range(max(0, p.y - 1), min(my + 1, p.y + 2)):
		if area[p.x][y][p.z] == [0, 0]:
			dfs(Point(p.x, y, p.z))
	for z in range(max(0, p.z - 1), min(mz + 1, p.z + 2)):
		if area[p.x][p.y][z] == [0, 0]:
			dfs(Point(p.x, p.y, z))

def bfs(p: Point):
	q = []
	area[p.x][p.y][p.z][1] = 1
	q.append(p)
	while len(q) != 0:
		v = q.pop()
		adjacent = []
		if v.x > 0: adjacent.append(Point(v.x - 1, v.y, v.z))
		if v.x < mx: adjacent.append(Point(v.x + 1, v.y, v.z))
		if v.y > 0: adjacent.append(Point(v.x, v.y - 1, v.z))
		if v.y < my: adjacent.append(Point(v.x, v.y + 1, v.z))
		if v.z > 0: adjacent.append(Point(v.x, v.y, v.z - 1))
		if v.z < mz: adjacent.append(Point(v.x, v.y, v.z + 1))
		
		for w in adjacent:
			if area[w.x][w.y][w.z] == [0, 0]:
				area[w.x][w.y][w.z][1] = 1
				q.append(w)

bfs(Point(0, 0, 0))

for x in range(mx + 1):
	for y in range(my + 1):
		for z in range(mz + 1):
			if area[x][y][z][0] == 1:
				print('*', end=' ')
			elif area[x][y][z][0] == 0:
				print('_' if area[x][y][z][1] == 1 else 'O', end=' ')
		print()
	for z in range(mz + 1):
		print('=', end='=')
	print()

for x in range(mx):
	for y in range(my):
		for z in range(mz):
			if area[x][y][z] == [0, 0]:
				empty_cube = Cube(Point(x, y, z))
				for plane in empty_cube.planes:
					if plane in planes_map:
						planes_map[plane] -= 1

print(len([v for v in planes_map.values() if v == 1]))
