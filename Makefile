PROGRAM = test
OBJS = test.o npld/MT.o npld/ndict.o npld/ndouble.o npld/nlist.o npld/npoly.o npld/nrandom.o npld/nutil.o 
CC = gcc
CFLAGS = -O2 -mtune=native -march=native

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS) $(CFLAGS) -lm

$(OBJS): npld.h

clean:
	rm -f *.o npld/*.o

