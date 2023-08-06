/*
 * hdc2080.c
 *
 *  Created on: Aug 1, 2023
 *      Author: Natan
 */
/* Includes ------------------------------------------------------------------*/
//#include "stm32l0xx_hal_def.h"
//#include "stm32l0xx_hal_i2c.h"

#include "stdint.h"
#include "main.h"
//extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

//#include "i2c.h"
//#include "stm32wlxx_hal_i2c.h"
//#include "stm32wlxx_hal_def.h"
//#include "gpio.h"


//#include "app_lorawan.h"
//#include "gpio.h"

//#include "main.h"
//#include "stm32wlxx_nucleo.h"


//-----------------------------------------------------------------------------
  uint16_t DevAddress= 0x80;
  uint16_t DevId_LowAddress= 0xFE;
  uint16_t Temperature_LowAddress= 0x00;
  uint16_t Humidity_LowAddress= 0x02;
  uint16_t ManufacturerId_LowAddress= 0xFC;
  uint16_t MeasConfig_Address= 0x0F;

  uint8_t temperature[2];
  uint8_t humidity[2];
  uint8_t buffer[2];
  uint8_t manufacturerId[2];
  uint8_t meas_trig[2] = {0x01};

  uint32_t Timeout = 555;
  HAL_StatusTypeDef ret;

  //HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,
  //                                    uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
/*  ret = HAL_I2C_Mem_Write(&hi2c1, DevAddress, MeasConfig_Address, 1, &meas_trig, 1, Timeout);  */
// HAL_I2C_Mem_Write(&hi2c1, 0x80, 0x0f, 1, meas_trig, 1, HAL_MAX_DELAY);
// HAL_I2C_Mem_Write(&hi2c1, (0x40 << 1), 0x03, I2C_MEMADD_SIZE_8BIT, dataBuffer, 1, HAL_MAX_DELAY);

	//  HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData,
	//                                            uint16_t Size, uint32_t Timeout);
//	  HAL_I2C_Master_Transmit(&hi2c1,DevAddress,&test_data,1,55555);;

	//  HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData,
	//                                           uint16_t Size, uint32_t Timeout);

	//  HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,
	//                                     uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)

//      HAL_I2C_Mem_Read(hi2c1,DevAddress,ManufacturerId_LowAddress,  1, manufacturerId, 2, Timeout);
 //           HAL_I2C_Mem_Read(hi2c1, DevAddress, DevId_LowAddress, 1, buffer, 2, Timeout);
/*	  ret = HAL_I2C_Mem_Read(&hi2c1, DevAddress, DevId_LowAddress, 1, buffer, 2, Timeout);
	  ret = HAL_I2C_Mem_Read(&hi2c1, DevAddress, Temperature_LowAddress, 1, temperature, 2, Timeout);
	  ret = HAL_I2C_Mem_Read(&hi2c1, DevAddress, Humidity_LowAddress, 1, humidity, 2, Timeout);
*/
//-----------------------------------------------------------------------------
  HAL_StatusTypeDef hdc2080_StartMeassuring(void) {
	ret = HAL_I2C_Mem_Write(&hi2c2, DevAddress, MeasConfig_Address, I2C_MEMADD_SIZE_8BIT,
			                                            meas_trig, 1, Timeout);
	return ret;
  }
//-----------------------------------------------------------------------------
  HAL_StatusTypeDef hdc2080_Read_Temperature(uint8_t *data) {
	  ret = HAL_I2C_Mem_Read(&hi2c2, DevAddress, Temperature_LowAddress, I2C_MEMADD_SIZE_8BIT,
			                                             data, 2, Timeout);
	  return ret;
  }
//-----------------------------------------------------------------------------
  HAL_StatusTypeDef hdc2080_Read_TempAndHum(uint8_t *data) {
	  ret = HAL_I2C_Mem_Read(&hi2c2, DevAddress, Temperature_LowAddress, I2C_MEMADD_SIZE_8BIT,
			                                             data, 4, Timeout);
	  return ret;
  }
//-----------------------------------------------------------------------------
  HAL_StatusTypeDef hdc2080_Read_ManufacturerID(uint8_t *data) {
	  ret = HAL_I2C_Mem_Read(&hi2c2, DevAddress, ManufacturerId_LowAddress, I2C_MEMADD_SIZE_8BIT,
			                                             data, 2, Timeout);
	  return ret;
  }

  //      HAL_I2C_Mem_Read(hi2c1,DevAddress,ManufacturerId_LowAddress,  1, manufacturerId, 2, Timeout);


//-----------------------------------------------------------------------------
  HAL_StatusTypeDef hdc2080_Read_DevID(uint8_t *data) {
	//  ret = HAL_I2C_Mem_Read(&hi2c1, DevAddress, DevId_LowAddress, I2C_MEMADD_SIZE_8BIT,
	//		                                             data, 2, Timeout);
	 // return status;
	  return HAL_I2C_Mem_Read(&hi2c2, DevAddress, DevId_LowAddress, I2C_MEMADD_SIZE_8BIT,
	  			                                             data, 2, Timeout);
  }
//-----------------------------------------------------------------------------
 // HAL_StatusTypeDef HAL_I2C_IsDeviceReady(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Trials,
 //                                         uint32_t Timeout)
  HAL_StatusTypeDef hdc2080_IsDeviceReady(void) {
	  ret = HAL_I2C_IsDeviceReady(&hi2c2, DevAddress,3,Timeout);

	  return ret;
  }
//-----------------------------------------------------------------------------


