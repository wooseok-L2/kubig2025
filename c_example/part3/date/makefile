TARGET = date

all : $(TARGET)

date : main.o date.o
	cc -o date main.o date.o

main.o : main.c date.h
	cc -c main.c

date.o : date.c
	cc -c date.c


clean : 
	rm $(TARGET) main.o date.o