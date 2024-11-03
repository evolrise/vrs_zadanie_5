#ifndef HTS221_H
#define HTS221_H

#define HTS221_I2C_ADDRESS 0x5F

// Register addresses
#define HTS221_WHO_AM_I_REG      0x0F
#define HTS221_CTRL_REG1         0x20
#define HTS221_HUMIDITY_OUT_L    0x28
#define HTS221_HUMIDITY_OUT_H    0x29
#define HTS221_TEMP_OUT_L        0x2A
#define HTS221_TEMP_OUT_H        0x2B

#define HTS221_WHO_AM_I_VALUE    0xBC

int HTS221_Init(void);
float HTS221_ReadHumidity(void);
float HTS221_ReadTemperature(void);

#endif // HTS221_H
