all: 3dworld

3dworld.o: 3dworld.cpp
	g++ -c 3dworld.cpp -I/usr/X11/include 

Basic.o: Basic.cpp
	g++ -c Basic.cpp -I/usr/X11/include

ObjLoader.o: ObjLoader.cpp
	g++ -c ObjLoader.cpp -I/usr/X11/include

Polyhedron.o: Polyhedron.cpp
	g++ -c Polyhedron.cpp -I/usr/X11/include

3dworld: 3dworld.o Basic.o ObjLoader.o Polyhedron.o
	g++ 3dworld.o Basic.o ObjLoader.o Polyhedron.o -o 3dworld -framework OpenGL -framework GLUT 

clean:
	rm *.o 3dworld
