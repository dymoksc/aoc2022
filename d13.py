import fileinput
import json 
from pprint import pprint
from typing import List, Union

def compare (lhs: Union[List, int], rhs: Union[List, int]) -> int:
	print("Comparing {} and {}".format(lhs, rhs))

	if isinstance(lhs, int) and isinstance(rhs, int):
		print("Both are ints, returning difference")
		return lhs - rhs

	if isinstance(lhs, list) and isinstance(rhs, int):
		print("Wrapping rhs in list")
		return compare(lhs, [rhs])
	if isinstance(rhs, list) and isinstance(lhs, int):
		print("Wrapping lhs in list")
		return compare([lhs], rhs)

	for i in range(min(len(lhs), len(rhs))):
		print("Comparing", i, "element")
		v = compare(lhs[i], rhs[i])
		if v != 0:
			return v

	print("Returning len difference")
	return len(lhs) - len(rhs)

i = 0
pair = []
s = 0
pairNum = 1
for line in fileinput.input():
	line = line.rstrip()
	result = 0
	if i % 3 == 0:
		pair.append(json.loads(line))
	elif i % 3 == 1:
		pair.append(json.loads(line))
		if compare(pair[0], pair[1]) < 0:
			s = s + pairNum
	else:
		print("==============")
		pair = []
		pairNum = pairNum + 1
	i = i + 1

print("sum: ", s)
