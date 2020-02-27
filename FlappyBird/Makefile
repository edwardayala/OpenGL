all: flappy 

flappy-bird.o: flappy-bird.cpp
	g++ -O2 -DMACOS -c flappy-bird.cpp -I/usr/X11/include -I./cal3d-0.11.0/src

flappy: flappy-bird.o
	g++ flappy-bird.o  -o flappy -framework OpenGL -framework GLUT 

run:
	./flappy

clean:
	rm *.o flappy
