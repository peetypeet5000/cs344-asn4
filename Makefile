CC = gcc --std=gnu99 -g
exe_file = line_processor
$(exe_file): main.o processing.o
	$(CC) main.o processing.o -o $(exe_file)

processing.o: input.c input.h
	$(CC) -c input.c
main.o: main.c main.h
	$(CC) -c main.c

clean:
	rm *.o $(exe_file)

tar:
	tar -cvf $(exe_file).tar *.c *.h Makefile