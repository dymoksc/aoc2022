import fileinput


def parse_directions(s: str) -> list:
	dirs = []
	num = 0
	for c in s:
		if c in ('L', 'R'):
			if num != 0:
				dirs.append(num)
				num = 0
			dirs.append(c)
		else:
			if num != 0:
				num *= 10
			num += int(c)
	if num != 0:
		dirs.append(num)
	return dirs


def change_face(face: str, d: str) -> str:
	face_id = '>v<^'.find(face)
	if d == 'R': face_id = (face_id + 1) % 4
	elif d == 'L': face_id = (face_id - 1) % 4
	else: assert False
	return '>v<^'[face_id]


assert change_face('>', 'R') == 'v'
assert change_face('^', 'R') == '>'
assert change_face('>', 'L') == '^'


def move(pos: tuple[int, int], face: str, num: int, field: list[str]) -> tuple[int, int]:
	while num > 0:
		y = pos[0]
		x = pos[1]
		
		if face == '>':
			x += 1
			if x == len(field[y]) or field[y][x] == ' ':
				x = min(field[y].find('.'), field[y].find('#'))
		elif face == '<':
			x -= 1
			if x == -1 or field[y][x] == ' ':
				x = max(field[y].rfind('.'), field[y].rfind('#'))
		elif face == 'v':
			y += 1
			if y == len(field) or x >= len(field[y]) or field[y][x] == ' ':
				for y in range(len(field)):
					if x < len(field[y]) and field[y][x] != ' ':
						break
		elif face == '^':
			y -= 1
			if y == -1 or x >= len(field[y]) or field[y][x] == ' ':
				for y in range(len(field) - 1, -1, -1):
					if x < len(field[y]) and field[y][x] != ' ':
						break

		if field[y][x] == '#':
			break

		assert field[y][x] == '.'
		pos = (y, x)
		num -= 1
	
	return pos


def print_field(field: list[str], pos: tuple[int, int], face: str):
	for i in range(len(field)):
		for j in range(len(field[i])):
			if pos == (i, j):
				print(face, end="")
			else:
				print(field[i][j], end="")
		print()


field = []
phase = 0
dirs = []
for line in fileinput.input():
	line = line.rstrip()
	if phase == 0:
		field.append(line)
	if phase == 1:
		dirs = parse_directions(line)
	if len(line) == 0:
		phase = 1

pos = (0, field[0].find('.'))
face = '>'

# print_field(field, pos, face)

while len(dirs) != 0:
	d = dirs.pop(0)
	if isinstance(d, int):
		pos = move(pos, face, d, field)
	else:
		face = change_face(face, d)

print((pos[0] + 1) * 1000 + (pos[1] + 1) * 4 + '>v<^'.find(face))
