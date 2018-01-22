#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>
#include <util/twi.h>
#include "main.h"
#include "mpu6050.h"
#include "i2cmaster.h"
#include "uart.h"

static float gyro_pitch = 0;
static float gyro_roll = 0;
static float gyro_yaw = 0;
static float accel_roll = 0;
static float accel_pitch = 0;
static uint16_t gyro_x_offset;
static uint16_t gyro_y_offset;
static uint16_t gyro_z_offset;

void mpu6050_init(void)
{
    i2c_init();
    i2c_start_wait(MPU6050 << 1 | I2C_WRITE);   // set device address and write mode
    i2c_write(PWR_MGMT_1);                      // Write to power management register
    i2c_write(WAKE);                            // Wake device
    i2c_rep_start(MPU6050 << 1 | I2C_WRITE);    // Repeated start condition
    i2c_write(GYRO_CONFIG);
    i2c_write(FS_SEL);                          // Set gyro full scale range to +- 500 deg/s
    i2c_rep_start(MPU6050 << 1 | I2C_WRITE);
    i2c_write(ACCEL_CONFIG);                     
    i2c_write(_BV(AFS_SEL));                    // Set accelerometer full scale range to +- 2g
    i2c_stop();                                 // set stop conditon = release bus
}

void mpu6050_calibrate(void)
{
    DataFrame data;
    for (int i = 0; i < 1000; i++) {
        mpu6050_read(&data);
    }
    

}

void mpu6050_read(DataFrame* data)
{
    i2c_start_wait(MPU6050 << 1 | I2C_WRITE);       // set device address and write mode
    i2c_write(ACCEL_XOUT_H);                        // write address = 5
    i2c_rep_start(MPU6050 << 1 | I2C_READ);
    data->accel_x = i2c_readAck() << 8;
    data->accel_x |= i2c_readAck();
    data->accel_x *= accel_degrees;
    data->accel_y = i2c_readAck() << 8;             // Register pointer auto increments
    data->accel_y |= i2c_readAck();
    data->accel_y *= accel_degrees;
    data->accel_z = i2c_readAck() << 8;
    data->accel_z |= i2c_readNak();
    data->accel_z *= accel_degrees; 
    i2c_rep_start(MPU6050 << 1 | I2C_WRITE);       // set device address and write mode
    i2c_write(GYRO_XOUT_H);                        // write address = 5
    i2c_rep_start(MPU6050 << 1 | I2C_READ); 
    data->gyro_x = i2c_readAck() << 8;
    data->gyro_x |= i2c_readAck();
    data->gyro_y = i2c_readAck() << 8;
    data->gyro_y |= i2c_readAck();
    data->gyro_y *= gyro_degrees;
    data->gyro_z = i2c_readAck() << 8;
    data->gyro_z |= i2c_readNak();
    data->gyro_z *= gyro_degrees;
    i2c_stop(); 
}
void update_pitch_roll(DataFrame* data, float* pitch, float* roll)
{

}

// float get_pitch(DataFrame* data)
// {
//     accel_pitch = atan2(-data->accel_x, sqrt(pow(data->accel_y, 2) + pow(data->accel_z, 2))) * 180 / PI;
//     gyro_pitch += (data->gyro_x / 65.5) * CYCLE_PERIOD
// }

// float get_accel_roll(DataFrame* data)
// {
//     return atan2(data->accel_y, data->accel_z) * 180 / PI;
// }
