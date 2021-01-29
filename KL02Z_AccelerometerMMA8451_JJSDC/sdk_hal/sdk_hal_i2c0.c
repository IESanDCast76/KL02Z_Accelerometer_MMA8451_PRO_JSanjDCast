/*! @file : sdk_hal_i2c0.c
 * @author  Jorge J. Sanjuan De Castro
 * @version 1.0.0
 * @date    29/01/2021
 * @brief   SDK Hal I2C0.c File
 * @details
 *
*/
/*******************************************************************************
 * Includes
 **************************/
#include "sdk_hal_i2c0.h"
#include "fsl_i2c.h"
/***************************
 * Definitions
 **************************/


/***************************
 * Private Prototypes
 **************************/


/***************************
 * External vars
 **************************/


/***************************
 * Local vars
 **************************/


/***************************
 * Private Source Code
 **************************/


/***************************
 * Public Source Code
 **************************/
status_t i2c0MasterInit(uint32_t baud_rate) {
	i2c_master_config_t masterConfig;
//	status_t status;

	I2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Bps = baud_rate;

    I2C_MasterInit(I2C0, &masterConfig, CLOCK_GetFreq(I2C0_CLK_SRC));
	return(kStatus_Success);
}
//I2C_ReadAccelRegs(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, ACCEL_STATUS, &status0_value, 1);
status_t i2c0MasterReadByte(uint16_t *data, uint8_t device_address, int8_t memory_address, uint8_t *i2c_rx_buffer, uint32_t i2c_rxSize) {
	i2c_master_transfer_t masterXfer;
	//uint8_t i2c_rx_buffer[1];

    masterXfer.slaveAddress = device_address;
    masterXfer.direction = kI2C_Read;
    masterXfer.subaddress = (uint32_t)memory_address;
    masterXfer.subaddressSize = 1;
    masterXfer.data = i2c_rx_buffer;
    masterXfer.dataSize = i2c_rxSize;
    masterXfer.flags = kI2C_TransferDefaultFlag;

    I2C_MasterTransferBlocking(I2C0, &masterXfer);

    *data=i2c_rx_buffer[0];

    return(kStatus_Success);
}
//I2C_WriteAccelReg(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, write_reg, databyte);
status_t i2c0MasterWriteByte(uint16_t *data, uint8_t device_address, int8_t reg_addr, uint8_t value){
//	/* subAddress = 0x01, data = g_master_txBuff - write to slave.
//	 start + slaveaddress(w) + subAddress + length of data buffer + data buffer + stop*/

	i2c_master_transfer_t masterXfer;
    //uint8_t i2c_rx_buffer[1];

	 masterXfer.slaveAddress = device_address;
	    masterXfer.direction = kI2C_Write;
	    //masterXfer.subaddress = (uint32_t)memory_address;
	    masterXfer.subaddress = reg_addr;
	    masterXfer.subaddressSize = 1;
	    masterXfer.data = &value;
	    masterXfer.dataSize = 1;
	    masterXfer.flags = kI2C_TransferDefaultFlag;


	I2C_MasterTransferBlocking(I2C0, &masterXfer);
	return(kStatus_Success);
}
