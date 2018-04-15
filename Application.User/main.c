#if 0
#include "STM32F4_GPIO.h"


#define PIN		13

uint32_t time=0;
void ledInit(void);
void toggle(GPIO_TypeDef GPIOx,uint8_t pin);
void SysTick_Handler(void){
	time++;
}
void delay(void){
	uint32_t value = time;
	while((time - value)<2000);
}

int main(){
	
SysTick_Config(SystemCoreClock/1000);
	ledInit();
	
	while(1){
		GpioWritePin(GPIOG, 13, 0);
		delay();
		GpioWritePin(GPIOG, 13, 1);
		delay();
	}
	
}

void ledInit(void){
	ENABLE_GPIOG;
	Pin_TypeDef led;
	Pin_TypeDef *pin = &led;
	pin -> mode = GPIO_MODER_OUTPTUT;
	pin -> otype = GPIO_OTYPER_PP;
	pin -> ospeed = GPIO_OSPEEDR_MEDIUM;
	pin -> pupd = GPIO_PUPDR_NONE;
	pin -> pin = 13;
	GpioInit(GPIOG, pin);
}

void toggle(GPIO_TypeDef GPIOx,uint8_t pin){
	if(GpioReadPin(GPIOG, 13) == 1){
		GpioWritePin(GPIOG, 13, 0);
	}else if(GpioReadPin(GPIOG, 13) == 0){
		GpioWritePin(GPIOG, 13, 1);
	}
}

#endif
