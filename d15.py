import fileinput
import re

# Parsing
rx = re.compile(r"Sensor at x=([-0-9]+), y=([-0-9]+): closest beacon is at x=([-0-9]+), y=([-0-9]+)")
beacons_by_sensors = {}
minX = 0
minY = 0
maxX = 9999
maxY = 9999
for line in fileinput.input():
	line = line.rstrip()
	m = re.match(rx, line)
	beacons_by_sensors[(int(m[1]), int(m[2]))] = (int(m[3]), int(m[4]))
	minX = min(minX, int(m[1]), int(m[3]))
	maxX = max(minX, int(m[1]), int(m[3]))
	minY = min(minY, int(m[2]), int(m[4]))
	maxY = max(minY, int(m[4]), int(m[4]))

print(beacons_by_sensors)
