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
	ConfigureGPIOInterrupt(0, RISING_EDGE);
	EnableGPIOInterrupt(0, EXTI0_IRQn);
	
	while(1){

	}
	
}

void ledInit(void){
	ENABLE_GPIOG;
	ENABLE_GPIOA;
	Pin_TypeDef led;
	Pin_TypeDef switchit;
	Pin_TypeDef *pin = &led;
	Pin_TypeDef *sw = &switchit;
	pin -> mode = GPIO_MODER_OUTPTUT;
	pin -> otype = GPIO_OTYPER_PP;
	pin -> ospeed = GPIO_OSPEEDR_MEDIUM;
	pin -> pupd = GPIO_PUPDR_NONE;
	pin -> pin = 13;
	sw -> mode = GPIO_MODER_INPUT;
	sw -> otype = GPIO_OTYPER_PP;
	sw -> ospeed = GPIO_OSPEEDR_MEDIUM;
	sw -> pupd = GPIO_PUPDR_NONE;
	sw -> pin = 0;
	GpioInit(GPIOG, pin);
	GpioInit(GPIOA, sw);
}

void toggle(GPIO_TypeDef GPIOx,uint8_t pin){
	if(GpioReadPin(GPIOG, 13) == 1){
		GpioWritePin(GPIOG, 13, 0);
	}else if(GpioReadPin(GPIOG, 13) == 0){
		GpioWritePin(GPIOG, 13, 1);
	}
}

void EXTI0_IRQHandler(void){
		toggle(*GPIOG, 13);
		ClearPendingInterrupt(13);
}
