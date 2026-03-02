#include "led_control.h"

void LED_Init(void) {
    // Configuration déjà faite dans CubeMX
}

void LED_On(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}

void LED_Off(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}
