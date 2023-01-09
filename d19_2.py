from enum import Enum
from copy import copy
import fileinput
import re

class Price:
	def __init__(self):
		self.ore = 0
		self.clay = 0
		self.obsidian = 0
		self.geode = 0

	def __str__(self):
		return ("{} ORE {} CLAY {} OBS {} GEO".format(self.ore, self.clay, self.obsidian, self.geode))


class Blueprint:
	def __init__(self):
		self.ore_robot = Price()
		self.clay_robot = Price()
		self.obsidian_robot = Price()
		self.geode_robot = Price()


class State:
	def __init__(self, blueprint: Blueprint):
		self.ore = 0
		self.clay = 0
		self.obsidian = 0
		self.geode = 0
		self.ore_robots = 0
		self.clay_robots = 0
		self.obsidian_robots = 0
		self.geode_robots = 0
		self.blueprint = blueprint
		self.to_build = ""
		self.predecessor = None

	def print(self):
		print("ORE	{} ->	{}".format(self.ore_robots, self.ore))
		print("CLAY	{} ->	{}".format(self.clay_robots, self.clay))
		print("OBS	{} ->	{}".format(self.obsidian_robots, self.obsidian))
		print("GEO	{} ->	{}".format(self.geode_robots, self.geode))

	def get_possible_actions(self) -> str:
		possible_actions = ""
		if self.has_right_amount(self.blueprint.ore_robot): possible_actions += "r"
		if self.has_right_amount(self.blueprint.clay_robot): possible_actions += "c"
		if self.has_right_amount(self.blueprint.obsidian_robot): possible_actions += "b"
		if self.has_right_amount(self.blueprint.geode_robot): possible_actions += "g"

		# if possible_actions != "":
		#	self.print()
		#	print("Possible actions:", possible_actions)

		return possible_actions

	def has_right_amount(self, price: Price) -> bool:
		# Has enough resources
		if self.ore >= price.ore and \
				self.clay >= price.clay and \
				self.obsidian >= price.obsidian and \
				self.geode >= price.geode:
			# And at least one resource is exactly at the right amount
			if price.ore != 0 and self.ore - price.ore < self.ore_robots or \
					price.clay != 0 and self.clay - price.clay < self.clay_robots or \
					price.obsidian != 0 and self.obsidian - price.obsidian < self.obsidian_robots or \
					price.geode != 0 and self.geode - price.geode < self.geode_robots:
				return True
		return False

	def deduct(self, price: Price):
		self.ore -= price.ore
		self.clay -= price.clay
		self.obsidian -= price.obsidian
		self.geode -= price.geode

	def get_new_state(self, s: str) -> 'State':
		state = copy(self)
		if s == "r":
			state.deduct(self.blueprint.ore_robot)
		elif s == "c":
			state.deduct(self.blueprint.clay_robot)
		elif s == "b":
			state.deduct(self.blueprint.obsidian_robot)
		elif s == "g":
			state.deduct(self.blueprint.geode_robot)
		state.to_build = s
		state.predecessor = self
		return state

	def add_robot(self, s: str):
		if s == "r":
			self.ore_robots += 1
		elif s == "c":
			self.clay_robots += 1
		elif s == "b":
			self.obsidian_robots += 1
		elif s == "g":
			self.geode_robots += 1

	def progress(self):
		self.ore += self.ore_robots
		self.clay += self.clay_robots
		self.obsidian += self.obsidian_robots
		self.geode += self.geode_robots
		if self.to_build != "":
			self.add_robot(self.to_build)
			self.to_build = ""

blueprints = []
for line in fileinput.input():
	_, pr = line.rstrip().split(":")
	blueprint = Blueprint()
	for p in pr.split(". "):
		price = Price()
		print("'", p, "'")
		match1 = re.search(r"\w+(?= robot)", p)
		print(match1[0])
		match2 = re.findall(r"(\d+) (\w+)", p)
		for count, res in match2:
			if res == "ore": price.ore = int(count)
			elif res == "clay": price.clay = int(count)
			elif res == "obsidian": price.obsidian = int(count)
			else: assert False
		if match1[0] == "ore": blueprint.ore_robot = price
		elif match1[0] == "clay": blueprint.clay_robot = price
		elif match1[0] == "obsidian": blueprint.obsidian_robot = price
		elif match1[0] == "geode": blueprint.geode_robot = price
		else: assert False
	blueprints.append(blueprint)

q_sum = 0
i = 1
for blueprint in blueprints:
	print("Blueprint", i)
	s1 = State(blueprint)
	s1.ore_robots = 1

	q = [s1]
	minute = 1
	target_minutes = 24

	while minute <= target_minutes:
		print("== Minute", minute, "==")
		print("State: ", len(q))
		new_q = []  # list[tuple[str, State]]
		while len(q) != 0:
			s = q.pop()
			new_q.append(s)  # No building task
			actions = s.get_possible_actions()
			if minute < target_minutes:  # No need to process actions if this is the last minute
				for a in actions:
					new_q.append(s.get_new_state(a))  # Different builing tasks
		for s in new_q:
			s.progress()
		q = new_q
		minute += 1

	max_geode = 0
	for s in q:
		max_geode = max(max_geode, s.geode)
	print("max geode:", max_geode)
	print("Quality level: ", max_geode * i)
	q_sum += max_geode * i 
	print()
	i += 1

print("Sum:", q_sum)
