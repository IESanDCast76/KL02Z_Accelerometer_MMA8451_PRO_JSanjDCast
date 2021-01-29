/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 * @file    KL02Z_AccelerometerMMA8451_JJSDC.c
 * @author  Jorge J. Sanjuan De Castro
 * @version 1.0.0
 * @date    28/01/2021
 * @brief   Main File
 * @details Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL02Z4.h"
#include "fsl_debug_console.h"


#include "sdk_hal_gpio.h"
#include "sdk_hal_uart0.h"
#include "sdk_hal_i2c0.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MMA851_I2C_DEVICE_ADDRESS	0x1D

#define MMA8451_WHO_AM_I_MEMORY_ADDRESS		0x0D
#define MMA851_I2C_DEVICE_ADDRESS_ST  0x00
#define CTRL_REG_ONE_ADRESS 0x2A
#define CTRL_REG_ONE_ACTIVE 0x0d

/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/


/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/


/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
int main(void) {
	status_t status;
		uint8_t new_byte_uart;
		//uint8_t	new_dato_i2c;

		uint8_t new_data_i2c;
		uint8_t new_data_i2c_status_read;
		uint8_t new_data_i2c_status_write;
		uint8_t status0_value_buff = 0;

		uint8_t new_data_i2c_axis_X_MSB;
		uint8_t new_data_i2c_axis_x_LSB;

		uint8_t new_data_i2c_axis_Y_MSB;
		uint8_t new_data_i2c_axis_y_LSB;

		uint8_t new_data_i2c_axis_Z_MSB;
		uint8_t new_data_i2c_axis_z_LSB;


  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    (void)uart0Inicializar(115200);	//115200bps
    (void)i2c0MasterInit(100000);	//100kbps

    PRINTF("Use keyboard to control the LEDs\r\n");
    PRINTF("r-R Red Led = ROJO\r\n");
    PRINTF("v-V Green Led = VERDE\r\n");
    PRINTF("a-A Blue Led = AZUL\r\n");
    PRINTF("M Search Accelerometer\r\n");


    while(1) {
    	if(uart0CuantosDatosHayEnBuffer()>0){
    		status=uart0LeerByteDesdeBuffer(&new_byte_uart);
    		if(status==kStatus_Success){
    			printf("data:%c\r\n",new_byte_uart);
    			switch (new_byte_uart) {
				case 'a':
				case 'A':
					gpioPutToggle(KPTB10);
					break;

				case 'v':
					gpioPutHigh(KPTB7);
					break;
				case 'V':
					gpioPutLow(KPTB7);
					break;

				case 'r':
					gpioPutValue(KPTB6,1);
					break;
				case 'R':
					gpioPutValue(KPTB6,0);
					break;

				case 'M':
					i2c0MasterReadByte(&new_data_i2c, MMA851_I2C_DEVICE_ADDRESS, MMA8451_WHO_AM_I_MEMORY_ADDRESS, &status0_value_buff, 1);


					if(new_data_i2c==0x1A)
						printf("MMA8451 Successful!!\r\n");
					else
						printf("MMA8451 Fail¡¡\r\n");

					break;
				case 'x':
				case 'X':
//i2c0MasterWriteByte(&nuevo_dato_i2c_status_write, MMA851_I2C_DEVICE_ADDRESS ,write_reg_i2c, databyte_i2c);
				i2c0MasterWriteByte(&new_data_i2c_status_write, MMA851_I2C_DEVICE_ADDRESS,CTRL_REG_ONE_ADRESS, CTRL_REG_ONE_ACTIVE);


				i2c0MasterReadByte(&new_data_i2c_status_read, MMA851_I2C_DEVICE_ADDRESS_ST,STATUS_F_STATUS, &status0_value_buff, 1);
				i2c0MasterReadByte(&new_data_i2c_axis_X_MSB, MMA851_I2C_DEVICE_ADDRESS, OUT_X_MSB, &status0_value_buff, 1);
				i2c0MasterReadByte(&new_data_i2c_axis_x_LSB, MMA851_I2C_DEVICE_ADDRESS, OUT_X_LSB,  &status0_value_buff, 1);
				printf("Status Value: %d\r\n", new_data_i2c_status_read);
				printf("Axis Value X MSB: %d\r\n", new_data_i2c_axis_X_MSB);
				printf("Axis Value x LSB: %d\r\n", new_data_i2c_axis_x_LSB);

				break;

				case 'y':
				case 'Y':

				i2c0MasterWriteByte(&new_data_i2c_status_write, MMA851_I2C_DEVICE_ADDRESS,CTRL_REG_ONE_ADRESS, CTRL_REG_ONE_ACTIVE);


				i2c0MasterReadByte(&new_data_i2c_status_read, MMA851_I2C_DEVICE_ADDRESS_ST,STATUS_F_STATUS, &status0_value_buff, 1);
				i2c0MasterReadByte(&new_data_i2c_axis_Y_MSB, MMA851_I2C_DEVICE_ADDRESS, OUT_Y_MSB, &status0_value_buff, 1);
				i2c0MasterReadByte(&new_data_i2c_axis_y_LSB, MMA851_I2C_DEVICE_ADDRESS, OUT_Y_LSB,  &status0_value_buff, 1);
				printf("Status Value: %d\r\n", new_data_i2c_status_read);
				printf("Axis Value Y MSB: %d\r\n", new_data_i2c_axis_Y_MSB);
				printf("Axis Value y LSB: %d\r\n", new_data_i2c_axis_y_LSB);

				break;

				case 'z':
				case 'Z':

				i2c0MasterWriteByte(&new_data_i2c_status_write, MMA851_I2C_DEVICE_ADDRESS,CTRL_REG_ONE_ADRESS, CTRL_REG_ONE_ACTIVE);


				i2c0MasterReadByte(&new_data_i2c_status_read, MMA851_I2C_DEVICE_ADDRESS_ST,STATUS_F_STATUS, &status0_value_buff, 1);
				i2c0MasterReadByte(&new_data_i2c_axis_Z_MSB, MMA851_I2C_DEVICE_ADDRESS, OUT_Z_MSB, &status0_value_buff, 1);
				i2c0MasterReadByte(&new_data_i2c_axis_z_LSB, MMA851_I2C_DEVICE_ADDRESS, OUT_Z_LSB,  &status0_value_buff, 1);
				printf("Status Value: %d\r\n", new_data_i2c_status_read);
				printf("Axis Value Z MSB: %d\r\n", new_data_i2c_axis_Z_MSB);
				printf("Axis Value z LSB: %d\r\n", new_data_i2c_axis_z_LSB);

				break;

								}
				    		}else{
				    			printf("error\r\n");
				    		}
				    	}
				    }

				    return 0 ;
				}
