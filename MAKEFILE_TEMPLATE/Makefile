all: [final-executable-name]

[temp-executable-name].o: [c++ file name].cpp
	g++ -c [c++ file name].cpp

[final-executable-name]: [temp-executable-name].o
	g++ [c++ file name].o -o final-executable-name

run:
	./[final-executable-name]

clean:
	rm *.o [final-executable-name]

clear:
	rm *.o