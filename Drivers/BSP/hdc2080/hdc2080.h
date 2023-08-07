/*
 * hdc2080.h
 *
 *  Created on: Aug 1, 2023
 *      Author: Natan
 */

#ifndef BSP_HDC2080_HDC2080_H_
#define BSP_HDC2080_HDC2080_H_
//#ifndef _HDC2080_H_
//#define _HDC2080_H_

HAL_StatusTypeDef hdc2080_StartMeassuring(void);
HAL_StatusTypeDef hdc2080_Read_Temperature(uint8_t *data);
HAL_StatusTypeDef hdc2080_Read_TempAndHum(uint8_t *data);
HAL_StatusTypeDef hdc2080_Read_ManufacturerID(uint8_t *data);
HAL_StatusTypeDef hdc2080_Read_DevID(uint8_t *data);
HAL_StatusTypeDef hdc2080_IsDeviceReady(void);
float hdc2080_GetTemperature(void);
float hdc2080_GetHumidity(void);

#endif /* BSP_HDC2080_HDC2080_H_ */
