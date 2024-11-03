#include "hts221.h"
#include "i2c.h"

// Initialize the HTS221 sensor
int HTS221_Init(void) {
    uint8_t who_am_i;
    if (I2C_Read(HTS221_I2C_ADDRESS, HTS221_WHO_AM_I_REG, &who_am_i, 1) != 0) {
        return -1; // I2C read failed
    }

    if (who_am_i != HTS221_WHO_AM_I_VALUE) {
        return -2; // Incorrect sensor ID
    }

    // Configure CTRL_REG1 for power-up and 1 Hz data rate
    uint8_t ctrl_reg1 = 0x81;
    if (I2C_Write(HTS221_I2C_ADDRESS, HTS221_CTRL_REG1, &ctrl_reg1, 1) != 0) {
        return -1; // I2C write failed
    }

    // Read calibration data (specific registers depend on the datasheet)
    // Example (these addresses and calculations should be verified in the HTS221 datasheet):
    // uint8_t calib_data[2];
    // I2C_Read(HTS221_I2C_ADDRESS, CALIB_REG_ADDR, calib_data, 2);
    // Store calibration values as needed for humidity and temperature processing.

    return 0; // Initialization successful
}


float HTS221_ReadHumidity(void) {
    uint8_t hum_l, hum_h;
    uint16_t hum;

    I2C_Read(HTS221_I2C_ADDRESS, HTS221_HUMIDITY_OUT_L, &hum_l, 1);
    I2C_Read(HTS221_I2C_ADDRESS, HTS221_HUMIDITY_OUT_H, &hum_h, 1);

    hum = (hum_h << 8) | hum_l;

    // Convert to percentage based on datasheet formula (example placeholder conversion)
    return (float)hum / 65536.0 * 100.0;
}

// Read temperature from the HTS221 sensor
float HTS221_ReadTemperature(void) {
    uint8_t temp_l, temp_h;
    uint16_t temp;

    I2C_Read(HTS221_I2C_ADDRESS, HTS221_TEMP_OUT_L, &temp_l, 1);
    I2C_Read(HTS221_I2C_ADDRESS, HTS221_TEMP_OUT_H, &temp_h, 1);

    temp = (temp_h << 8) | temp_l;

    // Convert to degrees Celsius based on datasheet formula (example placeholder conversion)
    return (float)temp / 65536.0 * 120.0 - 40.0;
}

