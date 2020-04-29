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

