# Instructions to make this run:

## Windows
- Checkout to the `visual-studio` branch
- Open the visual studio solution in the `HotlineKentuckyVisualStudio` folder
- Open a `.cpp` file
- In properties make sure it's set to release
- Under C/C++ -> General -> Additional Include Directories add the following path `(repo-path)/SFML-2.5.1/include`
- Under Linker -> General -> Additional Library Directories add the following path `(repo-path)/SFML-2.5.1/lib`
- Under Linker -> Input -> Additional Dependencies add `sfml-system.lib;sfml-window.lib;sfml-graphics.lib;` to the start of it


## Unix

- Install `g++` using your package manager
- Install `make` using your package manager
- Install `libsfml` or `libsfml-dev` using your package manager
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
| Two	distinct	animated	enemies | :heavy_check_mark: |
| Careful	sprite	and	terrain	collision	detection,	e.g.,	sprite	to	enemy,	sprite	to	wall	collision	detection | :heavy_check_mark: |
| Careful	collision	detection that	affects	the	score	and	condition,	e.g.,	sprite	to	coin,	sprite	to	health	potion | :heavy_check_mark: |
| Working	battle	system,	e.g.,	turn-based	or/and to-the death | :heavy_check_mark: |
| Immediate	gameplay	feedback	including	battle	system	feedback,	score,	win	and	loss | :heavy_check_mark: |
| One	enemy	that	exhibits	artificial	intelligence	behaviour.	This	may	be	implemented	using	trigonometry | :heavy_check_mark: |

