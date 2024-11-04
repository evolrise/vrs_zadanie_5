#ifndef LPS25HB_H
#define LPS25HB_H

#include <stdint.h>

#define LPS25HB_I2C_ADDRESS 0x5C // To som nasiel na GitHub-e

// Register addresses
#define LPS25HB_WHO_AM_I      0x0F
#define LPS25HB_CTRL_REG1     0x20
#define LPS25HB_PRESS_OUT_XL  0x28
#define LPS25HB_PRESS_OUT_L   0x29
#define LPS25HB_PRESS_OUT_H   0x2A

#define EXPECTED_WHO_AM_I_VALUE 0xBD

// Sea-level pressure
#define SEA_LEVEL_PRESSURE_HPA 1013.25

void LPS25HB_Init(void);
int LPS25HB_ReadPressure(float *pressure);
float LPS25HB_CalculateAltitude(float pressure);

#endif // LPS25HB_H
