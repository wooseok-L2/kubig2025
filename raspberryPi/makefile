TARGET = i2c_rgb_led helloRaspberry switch_led device_gpio interrupt led_pwm tone_buzzer hard_buzzer

all : $(TARGET)
CFLAGS = -lwiringPi

% : %.c
	cc -o $@ $< ${CFLAGS}

clean : 
	rm $(TARGET)
