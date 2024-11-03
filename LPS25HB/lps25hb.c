#include "lps25hb.h"
#include "i2c.h"
#include <math.h>

void LPS25HB_Init(void) {
    uint8_t who_am_i;
    I2C_Read(LPS25HB_I2C_ADDRESS, LPS25HB_WHO_AM_I, &who_am_i, 1);
    if (who_am_i != EXPECTED_WHO_AM_I_VALUE) {
            // Handle error: sensor not found or incorrect sensor
        }
    else
    {
    	uint8_t config = 0x90;
    	I2C_Write(LPS25HB_I2C_ADDRESS, LPS25HB_CTRL_REG1, &config, 1);
    }
}

int LPS25HB_ReadPressure(float *pressure) {
    uint8_t data[3];
    I2C_Read(LPS25HB_I2C_ADDRESS, LPS25HB_PRESS_OUT_XL, data, 3);
    int32_t raw_pressure = (int32_t)(data[2] << 16 | data[1] << 8 | data[0]);
    *pressure = raw_pressure / 4096.0;
    return 0;
}

float LPS25HB_CalculateAltitude(float pressure) {
    const float seaLevelPressure = 1013.25;
    float altitude;

    altitude = 44330.0 * (1.0 - pow(pressure / seaLevelPressure, 0.1903));

    return altitude;
}