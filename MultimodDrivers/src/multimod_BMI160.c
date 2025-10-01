// multimod_BMI160.c
// Date Created: 2023-07-25
// Date Updated: 2023-07-27
// Defines for BMI160 functions

/************************************Includes***************************************/

#include "../multimod_BMI160.h"

#include <stdint.h>
#include "../multimod_i2c.h"

/************************************Includes***************************************/

#define ACCEL_EN 0x11
#define GYRO_EN  0x15

/********************************Public Functions***********************************/

// BMI160_Init
// Initializes the BMI160. Currently enables the accelerometer
// in full-power mode.
// Return: void
void BMI160_Init() {
    I2C_Init(I2C_A_BASE);

    // Power on accelerometer
    
    // Accelerometer
    BMI160_WriteRegister(BMI160_CMD_ADDR, ACCEL_EN);
    // Gyroscope
    BMI160_WriteRegister(BMI160_CMD_ADDR, GYRO_EN);

    return;
}

// BMI160_Init
// Writes to a register address in the BMI160.
// Param uint8_t "addr": Register address
// Param uint8_t "data": data to write
// Return: void
void BMI160_WriteRegister(uint8_t addr, uint8_t data) {
    // write a single register
    // write where?
    // with what? (hint youre writing only 1 data item, but you still need to specify where)

    // 1. address, 2. data
    uint8_t addr_data[] = {addr, data};

    // write I2C device
    I2C_WriteMultiple(I2C_A_BASE, BMI160_ADDR, addr_data, 2);
}

// BMI160_ReadRegister
// Reads from a register address in the BMI160.
// Param uint8_t "addr": Register address
// Return: void
uint8_t BMI160_ReadRegister(uint8_t addr) {
    // read from which addr?

    // Send the address of the register to read.
    I2C_WriteSingle(I2C_A_BASE, BMI160_ADDR, addr);

    // return the data
    return I2C_ReadSingle(I2C_A_BASE, BMI160_ADDR);
}

// BMI160_MultiReadRegister
// Uses the BMI160 auto-increment function to read from multiple registers.
// Param uint8_t "addr": beginning register address
// Param uint8_t* "data": pointer to an array to store data in
// Param uint8_t "num_bytes": number of bytes to read
// Return: void
void BMI160_MultiReadRegister(uint8_t addr, uint8_t* data, uint8_t num_bytes) {
    // write to which addr?

    I2C_WriteSingle(I2C_A_BASE, BMI160_ADDR, addr);

    // read the data from that addr

    I2C_ReadMultiple(I2C_A_BASE, BMI160_ADDR, data, num_bytes);

    return;
}

// BMI160_AccelXGetResult
// Gets the 16-bit x-axis acceleration result.
// Return: uint16_t
int16_t BMI160_AccelXGetResult() {
    // if not read, wait till read

    while (!(BMI160_STATUS_DRDY_ACC & BMI160_GetDataStatus()));

    // read data

    uint8_t data[2];

    BMI160_MultiReadRegister(BMI160_DATA_O + ACCELX_O, data, 2);

    // write data 

    return (data[1] << 8 | data[0]);
}

// BMI160_AccelYGetResult
// Gets the 16-bit y-axis acceleration result.
// Return: uint16_t
int16_t BMI160_AccelYGetResult() {
    // if not read, wait till read

    while (!(BMI160_STATUS_DRDY_ACC & BMI160_GetDataStatus()));

    // read data

    uint8_t data[2];

    BMI160_MultiReadRegister(BMI160_DATA_O + ACCELY_O, data, 2);

    // write data

    return (data[1] << 8 | data[0]);
}

// BMI160_AccelZGetResult
// Gets the 16-bit z-axis acceleration result.
// Return: uint16_t
int16_t BMI160_AccelZGetResult() {
    // if not read, wait till read

    while (!(BMI160_STATUS_DRDY_ACC & BMI160_GetDataStatus()));

    // read data

    uint8_t data[2];

    BMI160_MultiReadRegister(BMI160_DATA_O + ACCELZ_O, data, 2);

    // write data

    return (data[1] << 8 | data[0]);
}

// BMI160_GyroXGetResult
// Gets the 16-bit x-axis gyroscope result.
// Return: uint16_t
int16_t BMI160_GyroXGetResult() {
    // if not read, wait till read
    while (!(BMI160_STATUS_DRDY_GYR & BMI160_GetDataStatus()));

    // read data
    uint8_t data[2];

    BMI160_MultiReadRegister(BMI160_DATA_O + GYROX_O, data, 2);

    // write data 
    return (data[1] << 8 | data[0]);
}

// BMI160_GyroYGetResult
// Gets the 16-bit y-axis gyroscope result.
// Return: uint16_t
int16_t BMI160_GyroYGetResult() {
    // if not read, wait till read
    while (!(BMI160_STATUS_DRDY_GYR & BMI160_GetDataStatus()));

    // read data
    uint8_t data[2];

    BMI160_MultiReadRegister(BMI160_DATA_O + GYROY_O, data, 2);

    // write data 
    return (data[1] << 8 | data[0]);
}

// BMI160_GyroZGetResult
// Gets the 16-bit z-axis gyroscope result.
// Return: uint16_t
int16_t BMI160_GyroZGetResult() {
    // if not read, wait till read
    while (!(BMI160_STATUS_DRDY_GYR & BMI160_GetDataStatus()));

    // read data
    uint8_t data[2];

    BMI160_MultiReadRegister(BMI160_DATA_O + GYROZ_O, data, 2);

    // write data 
    return (data[1] << 8 | data[0]);
}

// BMI160_AccelXYZGetResult
// Stores the 16-bit XYZ accelerometer results in an array.
// Param uint16_t* "data": pointer to an array of 16-bit data.
// Return: void
void BMI160_AccelXYZGetResult(uint16_t* data) {
    // if not read, wait till read
    while (!(BMI160_STATUS_DRDY_ACC & BMI160_GetDataStatus()));

    // read data
    // 3 16-bit values
    uint8_t accel_data[6];

    BMI160_MultiReadRegister(BMI160_DATA_O + ACCELX_O, accel_data, 6);

    // write data 
    data[0] = (accel_data[1] << 8 | accel_data[0]);
    data[1] = (accel_data[3] << 8 | accel_data[2]);
    data[2] = (accel_data[5] << 8 | accel_data[4]);

    return;
}

// BMI160_GyroXYZGetResult
// Stores the 16-bit XYZ gyroscope results in an array.
// Param uint16_t* "data": pointer to an array of 16-bit data.
// Return: void
void BMI160_GyroXYZGetResult(uint16_t* data) {
    // if not read, wait till read
    while (!(BMI160_STATUS_DRDY_GYR & BMI160_GetDataStatus()));

    // read data
    // 3 16-bit values
    uint8_t gyro_data[6];

    BMI160_MultiReadRegister(BMI160_DATA_O + GYROX_O, gyro_data, 6);

    // write data 
    data[0] = (gyro_data[1] << 8 | gyro_data[0]);
    data[1] = (gyro_data[3] << 8 | gyro_data[2]);
    data[2] = (gyro_data[5] << 8 | gyro_data[4]);

    return;
}

// BMI160_GetDataStatus
// Gets the status register to determine if data is ready to read.
// Return: uint8_t
uint8_t BMI160_GetDataStatus() {
    // insert your code here
    return BMI160_ReadRegister(BMI160_STATUS_ADDR);
}

/********************************Public Functions***********************************/
