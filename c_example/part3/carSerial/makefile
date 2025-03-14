TARGET = serial

all : $(TARGET)

serial : main.o serial.o
	cc -o serial main.o serial.o

main.o : main.c serial.h
	cc -c main.c

serial.o : serial.c
	cc -c serial.c


clean : 
	rm $(TARGET) main.o serial.o