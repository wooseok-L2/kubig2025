TARGET = mystring

all : $(TARGET)

mystring : main.o mystring.o
	cc -o mystring main.o mystring.o

main.o : main.c mystring.h
	cc -c main.c

mystring.o : mystring.c
	cc -c mystring.c


clean : 
	rm $(TARGET) main.o mystring.o