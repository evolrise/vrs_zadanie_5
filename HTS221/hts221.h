#ifndef HTS221_H
#define HTS221_H

#define HTS221_I2C_ADDRESS 0x5F

// Registers
#define HTS221_WHO_AM_I_REG      0x0F
#define HTS221_CTRL_REG1         0x20
#define HTS221_HUMIDITY_OUT_L    0x28
#define HTS221_HUMIDITY_OUT_H    0x29
#define HTS221_TEMP_OUT_L        0x2A
#define HTS221_TEMP_OUT_H        0x2B

// Calibration registers
#define HTS221_H0_RH_X2          0x30
#define HTS221_H1_RH_X2          0x31
#define HTS221_T0_DEGC_X8        0x32
#define HTS221_T1_DEGC_X8        0x33
#define HTS221_H0_T0_OUT_L       0x36
#define HTS221_H0_T0_OUT_H       0x37
#define HTS221_H1_T0_OUT_L       0x3A
#define HTS221_H1_T0_OUT_H       0x3B
#define HTS221_T0_OUT_L          0x3C
#define HTS221_T0_OUT_H          0x3D
#define HTS221_T1_OUT_L          0x3E
#define HTS221_T1_OUT_H          0x3F

#define HTS221_WHO_AM_I_VALUE    0xBC

int HTS221_Init(void);
float HTS221_ReadHumidity(void);
float HTS221_ReadTemperature(void);

#endif // HTS221_H
