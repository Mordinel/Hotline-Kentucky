all:
	x86_64-w64-mingw32-g++ src/* -o bin/main.exe -DSFML_STATIC -static -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lgcc -lm


linux:
	g++ src/* -o bin/main-linux -lsfml-graphics -lsfml-window -lsfml-system -lm
