#define CYCLE_FREQ 50
#define F_CPU 16000000UL
#define CYCLE_PERIOD 1 / CYCLE_FREQ
#define PRESCALER 1024
#define PI 3.14159
#define accel_degrees 0.061035     // Convert accel readings to (g) * 1000 
#define gyro_degrees 15.267       // Convert gyr to degrees / s * 10

typedef struct 
{
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
} DataFrame;