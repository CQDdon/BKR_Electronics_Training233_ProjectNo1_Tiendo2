#include "motor.h"

// Initial motor information (channel PWM, direction pin)
void Motor_Init(Motor* motor, uint32_t PWM_Channel, GPIO_TypeDef* PWM_Port, uint16_t PWM_Pin, GPIO_TypeDef* Dir_Port, uint16_t Dir_Pin) 
{
		motor->PWM_Channel = PWM_Channel;
    motor->PWM_GPIO_Port = PWM_Port;
    motor->PWM_GPIO_Pin = PWM_Pin;
    motor->Direction_GPIO_Port = Dir_Port;
    motor->Direction_GPIO_Pin = Dir_Pin;
}

//define this in main.c
__weak void Motor_SetPWM(Motor motor, uint8_t pwm) 
{
	
}

//set dirrection
void Motor_SetDirection(Motor motor, uint8_t direction) 
{
    if (direction) {
        HAL_GPIO_WritePin(motor.Direction_GPIO_Port, motor.Direction_GPIO_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(motor.Direction_GPIO_Port, motor.Direction_GPIO_Pin, GPIO_PIN_RESET);
    }
}

// control motor by direction and PWM by data that has been decoded after got from UART
void motorControl(char* cmd, uint8_t PWM) {
    Motor motors[4] = {MF_L, MF_R, MR_L, MR_R};
    
    for (int i = 0; i < 4; i++) {
			// the data has index = 8, each 2 adjacent index stand for the direction of each motor from 1 to 4
        Motor motor = motors[i];
        uint8_t a1 = cmd[2*i] - '0';
        uint8_t a2 = cmd[2*i + 1] - '0';
        // 10 motor go forward; 01 backward; 00 or 11 motor stop (PWM = 0)
        if (a1 != a2) {
            if (!a1) Motor_SetDirection(motor, 0);
            else Motor_SetDirection(motor, 1);
            Motor_SetPWM(motor, PWM);
        } else {
            Motor_SetPWM(motor, 100);
        }
    }
}