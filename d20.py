import fileinput
from typing import Tuple


def mix(nums: list[Tuple[int, int]], num: Tuple[int]) -> list[Tuple[int, int]]:
	i = nums.index(num)
	del nums[i]
	i += num[1]
	i %= len(nums)
	if num[1] != 0 and i == 0:
		i = len(nums)
	nums.insert(i, num)

	return nums

assert mix([(0, 1), (1, 2), (2, -3), (3, 3), (4, -2), (5, 0), (6, 4)], (0, 1)) == [(1, 2), (0, 1), (2, -3), (3, 3), (4, -2), (5, 0), (6, 4)], mix([(0, 1), (1, 2), (2, -3), (3, 3), (4, -2), (5, 0), (6, 4)], (0, 1))
assert mix([(1, 2), (0, 1), (2, -3), (3, 3), (4, -2), (5, 0), (6, 4)], (1, 2)) == [(0, 1), (2, -3), (1, 2), (3, 3), (4, -2), (5, 0), (6, 4)], mix([(1, 2), (0, 1), (2, -3), (3, 3), (4, -2), (5, 0), (6, 4)], (1, 2))


def decrypt(nums: list[int], times: int=1) -> list[int]:
	nums = [(k, v) for k, v in enumerate(nums)]
	decrypted = nums.copy()
	for i in range(times):
		for num in nums:
			decrypted = mix(decrypted, num)
		# print([t[1] for t in decrypted])
	return [t[1] for t in decrypted]

assert decrypt([1, 2, -3, 3, -2, 0, 4]) == [1, 2, -3, 4, 0, 3, -2], decrypt([1, 2, -3, 3, -2, 0, 4]) 


def get_nth(nums: list[int], n: int) -> int:
	i = nums.index(0)
	i += n
	return nums[i % len(nums)]

assert get_nth([1, 2, -3, 4, 0, 3, -2], 1) == 3, get_nth([1, 2, -3, 4, 0, 3, -2], 1)
assert get_nth([1, 2, -3, 4, 0, 3, -2], 1000) == 4, get_nth([1, 2, -3, 4, 0, 3, -2], 1000)
assert get_nth([1, 2, -3, 4, 0, 3, -2], 2000) == -3, get_nth([1, 2, -3, 4, 0, 3, -2], 2000)
assert get_nth([1, 2, -3, 4, 0, 3, -2], 3000) == 2, get_nth([1, 2, -3, 4, 0, 3, -2], 3000)


lst = []
for line in fileinput.input():
	lst.append(int(line) * 811589153)

print(len(lst))
decrypted = decrypt(lst, 10)
assert 0 in decrypted
print(get_nth(decrypted, 1000) + get_nth(decrypted, 2000) + get_nth(decrypted, 3000))
