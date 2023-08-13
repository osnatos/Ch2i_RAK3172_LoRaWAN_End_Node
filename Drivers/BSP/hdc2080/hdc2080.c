/*
 * hdc2080.c
 *
 *  Created on: Aug 1, 2023
 *      Author: Natan
 */
/* Includes ------------------------------------------------------------------*/
//#include "stdint.h"
#include "main.h"
extern I2C_HandleTypeDef hi2c2;
#define hi2c hi2c2
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

//  uint32_t Timeout = 555;
  uint32_t Timeout = 25;
  uint32_t Trials = 3;
  HAL_StatusTypeDef ret;
  //-----------------------------------------------------------------------------
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
	ret = HAL_I2C_Mem_Write(&hi2c, DevAddress, MeasConfig_Address, I2C_MEMADD_SIZE_8BIT,
			                                            meas_trig, 1, Timeout);
	return ret;
  }
//-----------------------------------------------------------------------------
  HAL_StatusTypeDef hdc2080_Read_Temperature(uint8_t *data) {
	  ret = HAL_I2C_Mem_Read(&hi2c, DevAddress, Temperature_LowAddress, I2C_MEMADD_SIZE_8BIT,
			                                             data, 2, Timeout);
	  return ret;
  }
//-----------------------------------------------------------------------------
  HAL_StatusTypeDef hdc2080_Read_TempAndHumCode(uint8_t *data) {
	  ret = HAL_I2C_Mem_Read(&hi2c, DevAddress, Temperature_LowAddress,
			                           I2C_MEMADD_SIZE_8BIT, data, 4, Timeout);
	  return ret;
  }
//-----------------------------------------------------------------------------
#define VDD 3.3       // [V]
#define TEMPpsrr 0.08 // Supply Sensitivity on accuracy [^C/V]
// (40.5+TEMPpsrr*(VDD-1.8)  = 40.5 + (0.08*(3.3-1.8)) = 40.5 +(0.08*1.5)
//  = 40.5 + 0.12 = 40.62

  void hdc2080_GetTempAndHum(float *temp,float *hum) {

	  uint8_t data[4] = {0};

 	  ret = HAL_I2C_Mem_Read(&hi2c, DevAddress, Temperature_LowAddress,
 			                           I2C_MEMADD_SIZE_8BIT, data, 4, Timeout);
 	  if(ret == HAL_OK) {

 	 	uint16_t res = data[0] | (data[1] << 8);
 	  	//*temp = (float)res;
 	  	*temp = ((float)res/65536)*165 - 40.62;

 	 	res = data[2] | (data[3] << 8);
 	  	//*hum = (float)res;
 	  	*hum = ((float)res/65536)*100;
 	  }
 	  else {
 	  		*temp = (float)(-1);
 	  		*hum = (float)(-1);
 	  }
  }
//-----------------------------------------------------------------------------
  HAL_StatusTypeDef hdc2080_Read_ManufacturerID(uint8_t *data) {
	  ret = HAL_I2C_Mem_Read(&hi2c, DevAddress, ManufacturerId_LowAddress,
			                           I2C_MEMADD_SIZE_8BIT, data, 2, Timeout);
	  return ret;
  }
//-----------------------------------------------------------------------------
  HAL_StatusTypeDef hdc2080_Read_DevID(uint8_t *data) {
	  return HAL_I2C_Mem_Read(&hi2c, DevAddress, DevId_LowAddress,
			                           I2C_MEMADD_SIZE_8BIT, data, 2, Timeout);
  }
//-----------------------------------------------------------------------------
  HAL_StatusTypeDef hdc2080_IsDeviceReady(void) {
	  return HAL_I2C_IsDeviceReady(&hi2c, DevAddress, Trials, Timeout);
  }
//-----------------------------------------------------------------------------
  HAL_StatusTypeDef hdc2080_Read_Humidity(uint8_t *data) {
	  return  HAL_I2C_Mem_Read(&hi2c, DevAddress, Humidity_LowAddress,
  			                           I2C_MEMADD_SIZE_8BIT, data, 2, Timeout);
  }
//-----------------------------------------------------------------------------
 uint16_t hdc2080_GetTempCode(uint8_t *data) {
  	uint16_t res = data[0] | (data[1] << 8);
   	return res;
  }
//-----------------------------------------------------------------------------
 uint16_t hdc2080_GetHumCode(uint8_t *data) {
  	uint16_t res = data[0] | (data[1] << 8);
   	return res;
  }
//-----------------------------------------------------------------------------
  float hdc2080_GetTemperature(void) {
	uint8_t data[2] = {0};
  	uint16_t res;
  	float f_temp;

  	if(hdc2080_Read_Temperature(data) == HAL_OK) {
  	res = data[0] | (data[1] << 8);
  	f_temp = (float)res;
  	f_temp = (f_temp/65536)*165 - 40.5;
  	}
  	else {
  		f_temp = -1;
  	}
  	return f_temp;
  }
//-----------------------------------------------------------------------------
  float hdc2080_GetHumidity(void) {
	uint8_t data[2] = {0};
	uint16_t res;
    float f_hum;

  	if(hdc2080_Read_Humidity(data) == HAL_OK) {
  	res = data[0] | (data[1] << 8);
  	f_hum = (float)res;
  	f_hum = (f_hum/65536)*100;
  	}
  	else {
  		f_hum = -1;
  	}
    	return f_hum;
 }
//-----------------------------------------------------------------------------



