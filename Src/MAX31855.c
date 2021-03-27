#include "MAX31855.h"
#include "gpio.h"
#include "spi.h"

/*---------------------------------------------------------------------------------------------------------------------
		|     Thermocouple Temperature     |                 |       Internal Temperature       |
+-------+------+----------+-----+----------+-----+-----------+------+----------+-----+----------+----+-----+-----+----+
|  BIT  | D31  |    D30   | ... |    D18   | D17 |    D16    | D15  |    D14   | ... |    D4    | D3 |  D2 |  D1 | D0 |
+-------+------+----------+-----+----------+-----+-----------+------+----------+-----+----------+----+-----+-----+----+
| VALUE | Sign | MSB 2^10 | ... | LSB 2^-2 |  0  | 1 = Fault | Sign | MSB 2^16 | ... | LSB 2^-4 |  0 | SCV | SCG | OC |
+-------+------+----------+-----+----------+-----+-----------+------+----------+-----+----------+----+-----+-----+----+
-----------------------------------------------------------------------------------------------------------------------*/

/******************************************************************************
**		1. Temperature measurements is carried out only when CS pin of IC is
**	high (not selected).
**		2. Temperature measurement is carried out not more often then 1 time in
**	200 ms. So do not call MAX31855_Read_Data more often.
**
** P.S	Descriprion of variables and functions in header file.
******************************************************************************/

void MAX31855_Read_Data(struct sMAX31855 *pMAX31855) {
  MAX31855_Set_CS(pMAX31855, 0);												//Selecting chip.
  HAL_SPI_Receive(&hspi1, (uint8_t*)&(*pMAX31855).Data, 2, 5000);				//Reading raw data.
  (*pMAX31855).Data = (*pMAX31855).Data<<16 | (*pMAX31855).Data >> 16;			//Need to swap fist 16 bits and last 16 bits to get data in default format due to datasheet.
  MAX31855_Set_CS(pMAX31855, 1);												//Deselecting chip.
  MAX31855_Read_TTD(pMAX31855);
  MAX31855_Read_ITD(pMAX31855);
  MAX31855_Read_SCV(pMAX31855);
  MAX31855_Read_SCG(pMAX31855);
  MAX31855_Read_OC (pMAX31855);
}

bool MAX31855_Set_CS(struct sMAX31855 *pMAX31855, bool CS_State) {
  if (CS_State == 1) {
	HAL_GPIO_WritePin((*pMAX31855).GPIOx, (*pMAX31855).GPIO_Pin, GPIO_PIN_SET);
	(*pMAX31855).CS = 1;
	return (*pMAX31855).CS;
  }
  else {
	HAL_GPIO_WritePin((*pMAX31855).GPIOx, (*pMAX31855).GPIO_Pin, GPIO_PIN_RESET);
	(*pMAX31855).CS = 0;
	return (*pMAX31855).CS;
  }
}

float MAX31855_Read_TTD(struct sMAX31855 *pMAX31855) {
  if ((*pMAX31855).Data & 0x80000000)
	(*pMAX31855).TTD = (0xFFFFC000 | (((*pMAX31855).Data >> 18) & 0x00003FFF)) * 0.25;
  else
	(*pMAX31855).TTD = ((*pMAX31855).Data >> 18) * 0.25;
  return (*pMAX31855).TTD;
}

float MAX31855_Read_ITD(struct sMAX31855 *pMAX31855) {
  if ((*pMAX31855).Data & 0x8000)
	(*pMAX31855).ITD = (0xF800 | ((((*pMAX31855).Data >> 4) & 0x7FF) & 0x7FF)) * 0.0625;
  else 
	(*pMAX31855).ITD = ((((*pMAX31855).Data >> 4) & 0x7FF)*0.0625);
  return (*pMAX31855).ITD;
}

bool MAX31855_Read_SCV(struct sMAX31855 *pMAX31855) {
  (*pMAX31855).SCV = ((*pMAX31855).Data & 0xF) >> 2;
  return 0;
}

bool MAX31855_Read_SCG(struct sMAX31855 *pMAX31855) {
  (*pMAX31855).SCG = (((*pMAX31855).Data & 0xF) >> 1) & 0x1;
  return (*pMAX31855).SCG;
}

bool MAX31855_Read_OC(struct sMAX31855 *pMAX31855) {
  (*pMAX31855).OC = ((*pMAX31855).Data & 0xF) & 0x1;
  return (*pMAX31855).OC;
}
