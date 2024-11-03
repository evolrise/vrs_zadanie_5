#ifndef LPS25HB_H
#define LPS25HB_H

#include <stdint.h>

#define LPS25HB_I2C_ADDRESS 0x5C

// Register addresses
#define LPS25HB_WHO_AM_I      0x0F
#define LPS25HB_CTRL_REG1     0x20
#define LPS25HB_PRESS_OUT_XL  0x28
#define LPS25HB_PRESS_OUT_L   0x29
#define LPS25HB_PRESS_OUT_H   0x2A
#define LPS25HB_TEMP_OUT_L    0x2B
#define LPS25HB_TEMP_OUT_H    0x2C

#define EXPECTED_WHO_AM_I_VALUE 0xBD

void LPS25HB_Init(void);
int LPS25HB_ReadPressure(float *pressure);

#endif // LPS25HB_H
