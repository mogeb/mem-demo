FLAGS=-fpermissive

all:
	g++ ${FLAGS} -c -fPIC -o cyg.o cyg.cpp
	g++ ${FLAGS} -o libcyg.so -shared cyg.o
	g++ ${FLAGS} -pg -o main main.cpp

run:
	(LD_PRELOAD="/usr/lib64/libdl.so ./libcyg.so" ./main)

clean:
	rm -f main
	rm -f cyg.o
	rm -f libcyg.so
