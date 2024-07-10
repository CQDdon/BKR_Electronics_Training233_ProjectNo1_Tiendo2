#include "PWM.h"

void PWMdutyChange(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t dutyCycle) {
    // duty cycle 0 -> 100
    if (dutyCycle > 100) {
        dutyCycle = 100;
    }
    
    // calculate pulse 
    uint32_t pulse = (htim->Init.Period + 1) * dutyCycle / 100;
    
    // update CCR corresponding channel
    switch (channel) {
        case TIM_CHANNEL_1:
            htim->Instance->CCR1 = pulse;
            break;
        case TIM_CHANNEL_2:
            htim->Instance->CCR2 = pulse;
            break;
        case TIM_CHANNEL_3:
            htim->Instance->CCR3 = pulse;
            break;
        case TIM_CHANNEL_4:
            htim->Instance->CCR4 = pulse;
            break;
        default:
            break;
    }
    
    HAL_TIM_PWM_Start(htim, channel);
}
