CC=g++
OPT=-O3
CFLAGS=-Wall -Wextra -Wshadow $(OPT)
CPPFILES=main.c++ HuffmanEncoding.c++ FileOrDirectory.c++ FileHandling.c++
OBJECTS=main.o HuffmanEncoding.o FileOrDirectory.o FileHandling.o

output: $(OBJECTS)
	$(CC) $(CFAGS) $(CPPFILES) -o output.out

main.o: main.c++
	$(CC) $(CFLAGS) -c main.c++

%.o: %.c++ %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o output.* *.exe

# target: dependencies
# 	action
