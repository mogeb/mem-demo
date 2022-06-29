FLAGS=-fpermissive

all:
	g++ ${FLAGS} -o main main.cpp

run:
	(LD_PRELOAD="/usr/lib64/libdl.so ./libmymalloc.so" ./main)

clean:
	rm -f main
	rm -f mymalloc.o
	rm -f libmymalloc.so
	rm -f libbox.so
