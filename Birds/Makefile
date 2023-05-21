
all: main bird background ParseCmdLine Point allegro
	g++ main.o Bird.o background.o ParseCmdLine.o Point.o allegro.o -o birds -lallegro -lallegro_image -lallegro_font -lallegro_ttf -lallegro_primitives -lallegro_main 

bird: Bird.cpp Bird.h
	g++ -c Bird.cpp -o Bird.o

background: background.cpp background.h
	g++ -c background.cpp -o background.o

ParseCmdLine: ParseCmdLine.cpp ParseCmdLine.h
	g++ -c ParseCmdLine.cpp -o ParseCmdLine.o

Point: Point.cpp Point.h
	g++ -c Point.cpp -o Point.o

allegro: allegro.cpp allegro.h
	g++ -c allegro.cpp -o allegro.o

main: main.cpp
	g++ -c main.cpp -o main.o

clean:
	rm -f *.o birds