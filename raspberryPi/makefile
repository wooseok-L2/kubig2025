TARGET = helloRaspberry switch_led device_gpio interrupt

all : $(TARGET)
CFLAGS = -lwiringPi

% : %.c
	cc -o $@ $< ${CFLAGS}

clean : 
	rm $(TARGET)
