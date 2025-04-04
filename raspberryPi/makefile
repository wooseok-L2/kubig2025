TARGET = touch_ATQT1070 pir_cnt rgb_switch_fnd fnd_cnt i2c_servo i2c_switch_led i2c_rgb_led helloRaspberry switch_led device_gpio interrupt led_pwm tone_buzzer hard_buzzer

all : $(TARGET)
CFLAGS = -lwiringPi

% : %.c
	cc -o $@ $< ${CFLAGS}

clean : 
	rm $(TARGET)
