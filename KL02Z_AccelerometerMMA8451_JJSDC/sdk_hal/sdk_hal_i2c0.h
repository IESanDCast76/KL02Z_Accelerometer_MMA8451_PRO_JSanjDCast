/*! @file : sdk_hal_i2c0.h
 * @author  Jorge J. Sanjuan De Castro
 * @version 1.0.0
 * @date    29/01/2021
 * @brief   SDK Hal I2C0.h File
 * @details
 *
 */
#ifndef SDK_HAL_I2C0_H_
#define SDK_HAL_I2C0_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_common.h"


/*!
 * @addtogroup HAL
 * @{
 */
/*!
 * @addtogroup I2C
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/
enum _gpio_port_aCCel_list_available
{
	STATUS_F_STATUS=0x00,
	OUT_X_MSB,
	OUT_X_LSB,
	OUT_Y_MSB,
	OUT_Y_LSB,
	OUT_Z_MSB,
	OUT_Z_LSB
};
/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/
/*--------------------------------------------*/
/*!
 * @brief Inicializa I2C0 al baudrate especificado
 *
 * @param baud_rate   baudrate (bps) que se quiere configurado en I2C0
 * @return            resultado de la ejecución
 * @code
 * 		kStatus_Success
 * 		kStatus_Fail
 * @endcode
 */
status_t i2c0MasterInit(uint32_t baud_rate);

/*!
 * @brief Lee 1 byte usando puerto I2C0
 *
 * @param data   			apuntador a memoria donde almacenar dato obtenido
 * @param device_address	direccion en bus I2C de dispositivo remoto a leer
 * @param memory_address	posicion de memoria en el dispositivo remoto que se quiere leer
 * @return            		resultado de la ejecución
 * @code
 * 		kStatus_Success
 * 		kStatus_Fail
 * @endcode
 */
status_t i2c0MasterReadByte(uint16_t *data, uint8_t device_address, int8_t memory_address, uint8_t *i2c_rx_buffer, uint32_t i2c_rxSize);

status_t i2c0MasterWriteByte(uint16_t *data, uint8_t device_address, int8_t reg_addr, uint8_t value);




/** @} */ // end of I2C0 group
/** @} */ // end of HAL group

#endif /* SDK_HAL_I2C0_H_ */
