#ifndef MAX31855_H
#define MAX31855_H

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"
struct sMAX31855 {
  GPIO_TypeDef* GPIOx;		//From HAL library. Port definition (GPIOA, ... , GPIOF)
  uint16_t		GPIO_Pin;	//From HAL library.Pin definition (GPIO_PIN_0, ... , GPIO_PIN_15)
  uint32_t		Data;		//Raw data from IC
  bool	CS;					//1 - CS high. 0 - CS low.
  float TTD;				//Thermocouple Temperature Data.
  float ITD;				//Internal Temperature Data.
  bool  SCV;				//1 - Thermocouple short-circuited to VCC. Default value is 0.
  bool  SCG;				//1 - Thermocouple short-circuited to GND. Default value is 0.
  bool  OC;					//1 - Thermocouple not connected. Default value is 0. 
};

void MAX31855_Read_Data(struct sMAX31855 *pMAX31855);				//Read and Convert all Data from IC. Converted data store in sMAX31855 <your struct name> struct.
bool MAX31855_Set_CS(struct sMAX31855 *pMAX31855, bool CS_State);	//CS_State = 1 - CS High, CS_State = 0 - CS Low.
float MAX31855_Read_TTD(struct sMAX31855 *pMAX31855);				//Thermocouple Temperature in Celsius.
float MAX31855_Read_ITD(struct sMAX31855 *pMAX31855);				//Internal Temperature in Celsius.
bool MAX31855_Read_SCV(struct sMAX31855 *pMAX31855);				//SCV bit
bool MAX31855_Read_SCG(struct sMAX31855 *pMAX31855);				//SCG bit
bool MAX31855_Read_OC(struct sMAX31855 *pMAX31855);					//OC bit



#endif