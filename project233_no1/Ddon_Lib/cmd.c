#include "cmd.h"

void moveHandle(char* data)
{
	switch ((char)data[1]) {
		case '1': // forward
			strcpy(data, "01100110");
			motorControl(data, PWM);
			break;
		case '2': // backward
      strcpy(data, "10011001");
			motorControl(data, PWM);     
      break;
		case '3': // sideway left
      strcpy(data, "10100101");
			motorControl(data, PWM);     
			break;
		case '4': // sideway right
      strcpy(data, "01011010");
			motorControl(data, PWM);    
			break;
		case '5': // 45
      strcpy(data, "01000010");
			motorControl(data, PWM);      
			break;
		case '6': // 135
      strcpy(data, "00100100");
			motorControl(data, PWM);    
			break;
		case '7': // 225
      strcpy(data, "10000001");
			motorControl(data, PWM); 
			break;
		case '8': // 315
      strcpy(data, "00011000");
			motorControl(data, PWM);
			break;
		case '0': // stop
      strcpy(data, "00000000");
			motorControl(data, PWM);
			break;
		default:     
			break;
    }
}

void setSpeed(char* data)
{
	PWM = 0;
	for (int i = 1; i < strlen(data); i++)
	{
		// PWM from data is string, we must change it to integer, then change the internation variable PWM
		PWM += (data[i] - '0')*pow(10, (strlen(data) - i - 1));
	}
}

void rotateHandle(char* data)
{
	switch ((char)data[1]) {
		case '1': // counter clockwise
			strcpy(data, "10101010");
			motorControl(data, PWM);
			break;
		case '2': // clockwise
      strcpy(data, "01010101");
			motorControl(data, PWM);     
      break;
		default:     
			break;
    }
}

void dataHandle(char* data) {
	switch (data[0]) {
		case 'M':
			moveHandle(data);
			break;
		case 'S':
      setSpeed(data);      
      break;
		case 'R':
      rotateHandle(data);      
			break;
		default:     
			break;
    }
}