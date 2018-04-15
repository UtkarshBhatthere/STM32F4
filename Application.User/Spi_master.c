#include  "STM32F4_GPIO.h"
#include  "STM32F4_SPI.h"

#define SPI2_MOSI		15
#define SPI2_MISO		14
#define SPI2_SCK		13
#define SPI2_SSEL		12

#define SPI_MOSI		7
#define SPI_MISO		6
#define SPI_SCK			5
#define SPI_SSEL		4

void PinInit(void);
void CommInit(void);
void ledInit(void);
void toggle(GPIO_TypeDef GPIOx,uint8_t pin);
uint8_t check=0;
uint32_t time=0;
SPI_Handler Tasker;

void SysTick_Handler(void){
	time++;
}

void delay(void){
	uint32_t value = time;
	while((time - value)<500);
}
//  State ready nahi ho rhi wapas./*

int main(){
	SysTick_Config(SystemCoreClock/1000);
	ledInit();
	PinInit();
	CommInit();
	while(check != 1){
		toggle(*GPIOG, 13);
		delay();
	}
	GpioWritePin(GPIOG, 13, 0);
	uint8_t string[] = "My name is Utkarsh and I play FPS games.";
	while(1){
			while(Tasker.state != SPI_State_Ready);
			SPIMasterTransmit(&Tasker, string, 40);
			while(Tasker.state != SPI_State_Ready);
			delay();
			GpioWritePin(GPIOG, 13, 1);
	}
}


void PinInit(void){
	ENABLE_GPIOA;
	Pin_TypeDef SpiPin;
	
	SpiPin.pin = SPI_MOSI;
	SpiPin.mode = GPIO_MODER_ALTERNATE;
	SpiPin.otype = GPIO_OTYPER_PP;
	SpiPin.ospeed = GPIO_OSPEEDR_MEDIUM;
	SpiPin.pupd = GPIO_PUPDR_NONE;
	SpiPin.alternate = AFRH_STATE_SPI1_2_3_4_5_6;
	// INITIALISING MOSI PIN
	GpioInit(GPIOA, &SpiPin);
	
	SpiPin.pin = SPI_SCK;
	// INITIALISING SCK PIN
	GpioInit(GPIOA, &SpiPin);
	
	SpiPin.pin = SPI_MISO;
	// INITIALISING MISO PIN
	GpioInit(GPIOA, &SpiPin);
	

}

void CommInit(void){
	SPI1_ENABLE;
	Tasker.SPIx = SPI1;
	SPI_ConfTypedef SPIc;
	SPIc.size = SPI_CR1_DFF_8BIT;
	SPIc.position = SPI_CR1_MASTER_ENABLE;
	SPIc.baudrate = prescalar128 ;
	SPIc.cpha = SPI_CR1_CPHA_0;
	SPIc.cpol = SPI_CR1_CPOL_0;
	SPIc.firstBit = SPI_CR1_FRAME_MSBFIRST;
	SPIc.NSS = SPI_CR1_SSM_ENABLE;
	SPIc.mode = SPI_CR1_BIDI_UNIDIRECTIONAL;
	//SPIc.CRCval = SPI_CR1_CRC_ENABLED;
	Tasker.state = SPI_State_Ready;
	Tasker.SPIConf = &SPIc;
	Tasker.IRQn = SPI1_IRQn;
	// Initialising the SPI configuration.
	SPIinit(&Tasker);
	
	// Enable interrupts
	//NVIC_EnableIRQ(SPI2_IRQn);
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
	//Enabling the interrupts
	ConfigureGPIOInterrupt(0, RISING_EDGE);
	EnableGPIOInterrupt(0, EXTI0_IRQn);
	
}

void toggle(GPIO_TypeDef GPIOx,uint8_t pin){
	if(GpioReadPin(GPIOG, 13) == 1){
		GpioWritePin(GPIOG, 13, 0);
	}else if(GpioReadPin(GPIOG, 13) == 0){
		GpioWritePin(GPIOG, 13, 1);
	}
}

void EXTI0_IRQHandler(void){
		check = 1;		
		ClearPendingInterrupt(13);
}
void SPI1_IRQHandler(void){
	SPI_InterruptHandler(&Tasker);

}
