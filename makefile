all:
	g++ -Isrc/Include -Lsrc/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
	g++ -Isrc/Include -Lsrc/lib -o main2 main2.cpp -lmingw32 -lSDL2main -lSDL2
	g++ -Isrc/Include -Lsrc/lib -o main3 main3.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image