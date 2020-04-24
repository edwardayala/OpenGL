all: raytracing

raytrace.o: raytracer-orig.cpp
	g++ -c raytracer-orig.cpp

raytracing: raytrace.o
	g++ raytracer-orig.o -o raytracing

run:
	./raytracing

clean:
	rm *.o raytracing

clear:
	rm *.o