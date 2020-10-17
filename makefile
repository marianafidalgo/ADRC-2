#make file - this is a comment section

CC=gcc  #compiler
TARGET=proj #target file name

all:    projeto1.o algorithms.o
	$(CC) -g projeto1.c algorithms.c -o $(TARGET)

clean:
	rm *.o $(TARGET)
