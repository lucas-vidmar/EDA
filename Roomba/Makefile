

all: main piso robot sim allegro pcmdl
	g++ -Wall main.o piso.o robot.o sim.o pcmdl.o allegro.o -o main -lallegro -lallegro_main -lallegro_image -lallegro_font -lallegro_ttf

main: main.cpp
	g++ -c main.cpp -o main.o

piso: piso.cpp piso.h
	g++ -c piso.cpp -o piso.o

robot: robot.cpp robot.h
	g++ -c robot.cpp -o robot.o

sim: sim.cpp sim.h
	g++ -c sim.cpp -o sim.o

pcmdl: pcmdl.cpp pcmdl.h
	g++ -c pcmdl.cpp -o pcmdl.o

allegro: allegro.cpp allegro.h
	g++ -c allegro.cpp -o allegro.o

clean:
	rm -f *.o main