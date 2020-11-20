CC= gcc
CXXFLAGS= -Wall -Werror -ansi --pedantic -O3

CPP_O_FILE = keygen.o sdes.o fk.o main.o
LIB = -lm


all: $(CPP_O_FILE)
	$(CC) $(CXXFLAGS) -o s_des $(CPP_O_FILE) $(LIB)

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf s_des
