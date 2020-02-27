all: zprdemo 

zpr.o: zpr.c
	g++ -O2 -DMACOS -c zpr.c -I/usr/X11/include 

zprdemo.o: zprdemo.cpp
	g++ -O2 -DMACOS -c zprdemo.cpp -I/usr/X11/include -I./cal3d-0.11.0/src

zprdemo: zprdemo.o zpr.o 
	g++ zprdemo.o zpr.o  -o zprdemo -framework OpenGL -framework GLUT 

clean:
	rm *.o zprdemo
