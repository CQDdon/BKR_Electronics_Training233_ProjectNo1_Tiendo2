#include "button.h"

uint8_t check = 0;

__weak void buttonPress(ButtonTypedef *ButtonData)
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}
__weak void buttonPressShort(ButtonTypedef *ButtonData)
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}
__weak void buttonRelease(ButtonTypedef *ButtonData)
{
	
}
__weak void buttonPressTimeout(ButtonTypedef *ButtonData)
{
	
}

// set data san cho struct
void setButtonData(ButtonTypedef *ButtonData)
{
	ButtonData->buttonCurrentStat = 1;
	ButtonData->buttonLastStat = 1;
	ButtonData->buttonFilter = 1;
}

void buttonHandle(ButtonTypedef *ButtonData)
{
	//set data ban dau
	if(check == 1) goto checkDone;
	
	setButtonData(ButtonData);
	check = 1;
	checkDone:;
	
	// loc nhieu
	uint8_t stat = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0); 
	// reset timeDebounce khi nhan ra co su thay doi trang thai
	if(stat != ButtonData->buttonFilter) 
	{
		ButtonData->buttonFilter = stat;
		ButtonData->isDebouncing = 1;
		ButtonData->timeDebounce = HAL_GetTick();
	}
	// sau 15ms ko xuat hien nhieu thi xac nhan trang thai hien tai
	if(ButtonData->isDebouncing && (HAL_GetTick() - ButtonData->timeDebounce >= 15)) 
	{
		ButtonData->buttonCurrentStat = ButtonData->buttonFilter;
		ButtonData->isDebouncing = 0;
	}
	// xu ly cac truong hop nhan nha
	if(ButtonData->buttonCurrentStat != ButtonData->buttonLastStat)
	{
		// nhan xuong
		if(ButtonData->buttonCurrentStat == 0)
		{
			// xac nhan da nhan xuong
			ButtonData->isPressTimeOut = 1; 
			//thuc hien ham buttonPress khi nhan nut
			buttonPress(ButtonData);
			// tinh thoi gian nhan
			ButtonData->timeStartPress = HAL_GetTick();
		}
		// nha nut
		else 
		{
			// nhan nha ngay lap tuc (<1000)
			if(HAL_GetTick() - ButtonData->timeStartPress <= 1000)
				// ham cho lenh nhan nha nhan
				buttonPressShort(ButtonData);
			//thuc hien ham nha nut
			buttonRelease(ButtonData);
			ButtonData->isPressTimeOut = 0;
		}
		ButtonData->buttonLastStat = ButtonData->buttonCurrentStat;
	}
	//
	if(ButtonData->isPressTimeOut && (HAL_GetTick() - ButtonData->timeStartPress >= 3000))
	{
		buttonPressTimeout(ButtonData);
		ButtonData->isPressTimeOut = 0;
	}
}

void buttonInit(ButtonTypedef *ButtonData, GPIO_TypeDef *buttonGPIO, uint16_t GPIO_Pin)
{
	ButtonData->buttonGPIO = buttonGPIO;
	ButtonData->GPIO_Pin = GPIO_Pin;
}
