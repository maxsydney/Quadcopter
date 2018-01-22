#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "main.h"
#include "mpu6050.h"
#include "pio.h"
#include "uart.h"
#include "pacer.h"

int main (void)
{
    uart_init(9600);
    mpu6050_init();

    DataFrame data;
    float roll_gyro = 0;
    uint16_t count = 0;
    pacer_init(CYCLE_FREQ);
    // uint32_t total_time = 0;
    // float n_cycles = 10.0;

    float pitch, roll;

    while(1) {
        mpu6050_read(&data);
        roll_gyro += (data.gyro_x - GYRO_X_ZERO) / 65.5 * CYCLE_PERIOD;
        
        update_pitch_roll(&data, &pitch, &roll);

        println("%.3lf, %.3lf", 1.0, 2.0);
        pacer_wait();
    }

    // char serialbuf[50];
    // sprintf(serialbuf, "Loop period: %.6lf (s) \n\r",  1024.0 / 16000000 * total_time / n_cycles);
    // serial_write(serialbuf);
}   