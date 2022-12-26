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


class Cube:
	planes = []  # list[Plane]

	def __init__(self, p: Point):
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

cube = Cube(Point(1, 1, 1))
assert len(cube.planes) == 6

for plane in cube.planes:
	print(plane.p1, plane.p2)

# XY planes
assert Plane(Point(0, 0, 0), Point(1, 1, 0)) in cube.planes
assert Plane(Point(0, 0, 1), Point(1, 1, 1)) in cube.planes

# XZ planes
assert Plane(Point(0, 0, 0), Point(1, 0, 1)) in cube.planes
assert Plane(Point(0, 1, 0), Point(1, 1, 1)) in cube.planes

# YZ planes
assert Plane(Point(0, 0, 0), Point(0, 1, 1)) in cube.planes
assert Plane(Point(1, 0, 0), Point(1, 1, 1)) in cube.planes
