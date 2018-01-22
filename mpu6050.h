#define MPU6050 0x68
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define FS_SEL 0x08
#define AFS_SEL 0x00
#define PWR_MGMT_1 0x6B
#define WAKE 0x00
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43
#define GYRO_X_ZERO -220.5762712

void mpu6050_init(void);
void mpu6050_read(DataFrame* data);
void update_pitch_roll(DataFrame* data, float* pitch, float* roll);


