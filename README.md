# Instructions to make this run:

## Windows

- Install [Msys2](https://www.msys2.org/)
- run `MSYS2 MinGW 64-bit` via the start menu
- run the command:
`pacman -S git make mingw64/mingw-w64-x86_64-sfml mingw64/mingw-w64-x86_64-gcc msys/mingw-w64-cross-gcc`

- cd into the same directory as the `Makefile`
- run `make`

main.exe should appear in bin/

## Unix

- Install `g++` using your package manager
- Install `make` using your package manager
- Install `libsfml` using your package manager
- cd into the same directory as the `Makefile`
- run `make linux`

main-linux should appear in bin/

# Progress
| Feature | State |
|:-- |:--:|
| Displayed	at	the	correct	screen	size	of	1920x1080 | :heavy_check_mark: |
| Dungeon	represented	as	a	tile	map	| :heavy_check_mark: |
| Edge	of	the	world	has	a	dead	zone	which	is	½	the	dimension	of	the	viewable	area | :heavy_check_mark: |
| Dungeon	procedurally	generated	at	each	new	level,	e.g.,	multiple	non-overlapping	rooms,	walls,	corridors	and	portal	tiles	correctly	placed | :heavy_check_mark: |
| Fog	of	war	reveals	the	dungeon	as	the	player	character	progressively	navigates	through	the	dungeon	| :heavy_check_mark: |
| One	or	more	player	characters	are	controlled	by	user	keyword	| :heavy_check_mark: |
| Two	distinct	animated	enemies | :x: |
| Careful	sprite	and	terrain	collision	detection,	e.g.,	sprite	to	enemy,	sprite	to	wall	collision	detection | :x: |
| Careful	collision	detection that	affects	the	score	and	condition,	e.g.,	sprite	to	coin,	sprite	to	health	potion | :x: |
| Working	battle	system,	e.g.,	turn-based	or/and to-the death | :x: |
| Immediate	gameplay	feedback	including	battle	system	feedback,	score,	win	and	loss | :x: |
| One	enemy	that	exhibits	artificial	intelligence	behaviour.	This	may	be	implemented	using	trigonometry | :x: |

