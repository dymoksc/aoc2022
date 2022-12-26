import fileinput
import re
from enum import Enum

class Resource(Enum):
	Ore = "ore"
	Clay = "clay"
	Obsidian = "obsidian"
	Geode = "geode"


class State:
	resources = ...  # map[Resource, int]
	robots = ...  # map[Resource, int]

	def __init__(self):
		self.resources = {
			Resource.Ore: 0,
			Resource.Clay: 0,
			Resource.Obsidian: 0,
			Resource.Geode: 0,
		}
		self.robots = {
			Resource.Ore: 0,
			Resource.Clay: 0,
			Resource.Obsidian: 0,
			Resource.Geode: 0,
		}


class Blueprint:
	price = ...  # map[Resource, map[Resource, int]]

	def __init__(self):
		self.price = {
			Resource.Ore: {
				Resource.Ore: 0,
				Resource.Clay: 0,
				Resource.Obsidian: 0,
				Resource.Geode: 0,
			},
			Resource.Clay: {
				Resource.Ore: 0,
				Resource.Clay: 0,
				Resource.Obsidian: 0,
				Resource.Geode: 0,
			},
			Resource.Obsidian: {
				Resource.Ore: 0,
				Resource.Clay: 0,
				Resource.Obsidian: 0,
				Resource.Geode: 0,
			},
			Resource.Geode: {
				Resource.Ore: 0,
				Resource.Clay: 0,
				Resource.Obsidian: 0,
				Resource.Geode: 0,
			},
		}

	def __repr__(self):
		s = ""
		for robot, price in self.price.items():
			s += "Each {} robot costs".format(robot.value)
			for res, amount in price.items():
				if amount != 0:
					s += " {} {}".format(amount, res.value)
			s += ". "
		return s


i = 0
blueprints = []

for line in fileinput.input():
	i += 1
	line = line.rstrip()
	title, body = line.split(": ")
	assert title == "Blueprint {}".format(i)
	
	blueprint = Blueprint()
	price_lines = body.split(". ")
	for price_line in price_lines:
		match = re.match(r'Each (\w+) robot costs (.+)', price_line)
		for price in match[2].split(" and "):
			submatch = re.match(r'(\d+) (\w+)', price)
			blueprint.price[Resource(match[1])][Resource(submatch[2])] = int(submatch[1])
	blueprints.append(blueprint)

print(blueprints)

