#ifndef __PULSE_SENSOR_H__
#define __PULSE_SENSOR_H__

#include "stm32l4xx_hal.h"

void PulseSensor_Init(void);
uint32_t PulseSensor_Read(void);

#endif
