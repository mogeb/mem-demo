FLAGS=-fpermissive

all:
	g++ ${FLAGS} -c -fPIC -o mymalloc.o mymalloc.cpp
	g++ ${FLAGS} -o libmymalloc.so -shared mymalloc.o
	g++ ${FLAGS} -Wl,-rpath,/home/mogeb/src/malloc -L/home/mogeb/src/malloc -o main main.cpp

box:
	g++ ${FLAGS} -c -fPIC -o box.o box.c

run:
	(LD_PRELOAD="/usr/lib64/libdl.so ./libmymalloc.so" ./main)

clean:
	rm -f main
	rm -f mymalloc.o
	rm -f libmymalloc.so
	rm -f libbox.so
