#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"

// motor struct: 3 for PWM, 2 for direction
typedef struct __attribute__((packed,aligned(4))) {
		uint32_t PWM_Channel;
    GPIO_TypeDef* PWM_GPIO_Port;
    uint16_t PWM_GPIO_Pin;
    GPIO_TypeDef* Direction_GPIO_Port;
    uint16_t Direction_GPIO_Pin;
} Motor;

extern Motor MF_L;
extern Motor MF_R;
extern Motor MR_L;
extern Motor MR_R;

void Motor_Init(Motor* motor, uint32_t PWM_Channel, GPIO_TypeDef* PWM_Port, uint16_t PWM_Pin, GPIO_TypeDef* Dir_Port, uint16_t Dir_Pin);

void Motor_SetPWM(Motor motor, uint8_t pwm);

void Motor_SetDirection(Motor motor, uint8_t direction);

void motorControl(char* cmd, uint8_t PWM);

#endif