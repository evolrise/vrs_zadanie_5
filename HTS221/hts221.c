#include "hts221.h"
#include "i2c.h"

// Calibration data variables
static int16_t H0_T0_OUT, H1_T0_OUT;
static int16_t T0_OUT, T1_OUT;
static uint8_t H0_rH_x2, H1_rH_x2;
static int16_t T0_degC_x8, T1_degC_x8;

// Initialize the HTS221 sensor
int HTS221_Init(void)
{
    uint8_t who_am_i;
    if (I2C_Read(HTS221_I2C_ADDRESS, HTS221_WHO_AM_I_REG, &who_am_i, 1) != 0)
    {
        return -1; // I2C read failed
    }

    if (who_am_i != HTS221_WHO_AM_I_VALUE)
    {
        return -2; // Incorrect sensor ID
    }

    uint8_t ctrl_reg1 = 0x81;
    if (I2C_Write(HTS221_I2C_ADDRESS, HTS221_CTRL_REG1, &ctrl_reg1, 1) != 0)
    {
        return -3; // I2C write failed
    }

    // Read calibration data for humidity
    if (I2C_Read(HTS221_I2C_ADDRESS, 0x30, &H0_rH_x2, 1) != 0 ||
        I2C_Read(HTS221_I2C_ADDRESS, 0x31, &H1_rH_x2, 1) != 0)
    {
        return -4; // Calibration data read failed
    }

    uint8_t buffer[2];
    if (I2C_Read(HTS221_I2C_ADDRESS, 0x36, buffer, 2) != 0)
    {
        return -5; // Calibration data read failed
    }
    H0_T0_OUT = (int16_t)(buffer[1] << 8 | buffer[0]);

    if (I2C_Read(HTS221_I2C_ADDRESS, 0x3A, buffer, 2) != 0)
    {
        return -6; // Calibration data read failed
    }
    H1_T0_OUT = (int16_t)(buffer[1] << 8 | buffer[0]);

    // Read calibration data for temperature
    if (I2C_Read(HTS221_I2C_ADDRESS, 0x32, buffer, 2) != 0)
    {
        return -7; // Calibration data read failed
    }
    T0_degC_x8 = buffer[0] | ((buffer[1] & 0x03) << 8);
    T1_degC_x8 = buffer[1] | ((buffer[1] & 0x0C) << 6);

    if (I2C_Read(HTS221_I2C_ADDRESS, 0x3C, buffer, 2) != 0 ||
        I2C_Read(HTS221_I2C_ADDRESS, 0x3E, buffer, 2) != 0)
    {
        return -8; // Calibration data read failed
    }
    T0_OUT = (int16_t)(buffer[1] << 8 | buffer[0]);
    T1_OUT = (int16_t)(buffer[1] << 8 | buffer[0]);

    return 0; // Initialization successful
}

float HTS221_ReadHumidity(void)
{
    uint8_t hum_l, hum_h;
    int16_t hum_raw;

    if (I2C_Read(HTS221_I2C_ADDRESS, HTS221_HUMIDITY_OUT_L, &hum_l, 1) != 0 ||
        I2C_Read(HTS221_I2C_ADDRESS, HTS221_HUMIDITY_OUT_H, &hum_h, 1) != 0)
    {
        return -1; // Read failed
    }

    hum_raw = (hum_h << 8) | hum_l;

    // Calculate humidity in %RH based on calibration data
    float humidity = ((float)(hum_raw - H0_T0_OUT) * (H1_rH_x2 / 2.0 - H0_rH_x2 / 2.0)) / (H1_T0_OUT - H0_T0_OUT) + H0_rH_x2 / 2.0;

    return humidity;
}

float HTS221_ReadTemperature(void)
{
    uint8_t temp_l, temp_h;
    int16_t temp_raw;

    if (I2C_Read(HTS221_I2C_ADDRESS, HTS221_TEMP_OUT_L, &temp_l, 1) != 0 ||
        I2C_Read(HTS221_I2C_ADDRESS, HTS221_TEMP_OUT_H, &temp_h, 1) != 0)
    {
        return -1; // Read failed
    }

    temp_raw = (temp_h << 8) | temp_l;

    // Calculate temperature in °C based on calibration data
    float temperature = ((float)(temp_raw - T0_OUT) * (T1_degC_x8 / 8.0 - T0_degC_x8 / 8.0)) / (T1_OUT - T0_OUT) + T0_degC_x8 / 8.0;

    return temperature;
}
