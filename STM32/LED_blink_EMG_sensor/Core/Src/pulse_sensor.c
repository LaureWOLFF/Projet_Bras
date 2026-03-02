#include "pulse_sensor.h"

extern ADC_HandleTypeDef hadc1;

void PulseSensor_Init(void) {
    HAL_ADC_Start(&hadc1);
}

uint32_t PulseSensor_Read(void) {
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    return HAL_ADC_GetValue(&hadc1);
}
