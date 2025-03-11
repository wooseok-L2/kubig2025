TARGET = myrandom

all : $(TARGET)

myrandom : main.o myRandom.o
	cc -o myrandom main.o myRandom.o

main.o : main.c myrandom.h
	cc -c main.c

myRandom.o : myRandom.c
	cc -c myRandom.c


clean : 
	rm $(TARGET) main.o myRandom.o