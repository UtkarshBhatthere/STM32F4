#ifndef _STM32F4_GPIO_H
#define _STM32F4_GPIO_H

// Device Specific Header File inclusion.
#include "stm32f429xx.h"					//Device Header

// GPIO Programming specific Macros.

// MODER MACROS
#define GPIO_MODER_INPUT					((uint32_t)0x00)
#define GPIO_MODER_OUTPTUT					((uint32_t)0x01)
#define GPIO_MODER_ALTERNATE				((uint32_t)0x02)
#define GPIO_MODER_ANALOG					((uint32_t)0x03)

//OTYPER MACROS
#define GPIO_OTYPER_PP						((uint32_t)0x00)
#define GPIO_OTYPER_OD						((uint32_t)0x01)

//OSPEEDR MACROS
#define GPIO_OSPEEDR_LOW					((uint32_t)0x00)
#define GPIO_OSPEEDR_MEDIUM					((uint32_t)0x01)
#define GPIO_OSPEEDR_HIGH					((uint32_t)0x02)
#define GPIO_OSPEEDR_VERYHIGH				((uint32_t)0x03)

//PUPDR MACROS
#define GPIO_PUPDR_NONE						((uint32_t)0x00)
#define GPIO_PUPDR_PU						((uint32_t)0x01)
#define GPIO_PUPDR_PD						((uint32_t)0x02)

// CLOCK ENABLE MACROS

#define ENABLE_GPIOA						(RCC -> AHB1ENR |= ( 1 << 0 ))
#define ENABLE_GPIOB						(RCC -> AHB1ENR |= ( 1 << 1 ))
#define ENABLE_GPIOC						(RCC -> AHB1ENR |= ( 1 << 2 ))
#define ENABLE_GPIOD						(RCC -> AHB1ENR |= ( 1 << 3 ))
#define ENABLE_GPIOE						(RCC -> AHB1ENR |= ( 1 << 4 ))
#define ENABLE_GPIOF						(RCC -> AHB1ENR |= ( 1 << 5 ))
#define ENABLE_GPIOG						(RCC -> AHB1ENR |= ( 1 << 6 ))
#define ENABLE_GPIOH						(RCC -> AHB1ENR |= ( 1 << 7 ))
#define ENABLE_GPIOI						(RCC -> AHB1ENR |= ( 1 << 8 ))
#define ENABLE_GPIOJ						(RCC -> AHB1ENR |= ( 1 << 9 ))
#define ENABLE_GPIOK						(RCC -> AHB1ENR |= ( 1 << 10))

// AFRL STATE MACROS
#define  AFRL_STATE_SYSTEM										((uint16_t)0x00)
#define  AFRL_STATE_TIM1_2										((uint16_t)0x01)
#define  AFRL_STATE_TIM3_4_5									((uint16_t)0x02)
#define  AFRL_STATE_TIM8_9_10_11								((uint16_t)0x03)
#define  AFRL_STATE_I2C1_2_3									((uint16_t)0x04)
#define  AFRL_STATE_SPI1_2										((uint16_t)0x05)
#define  AFRL_STATE_SPI3										((uint16_t)0x06)
#define  AFRL_STATE_USART1_2_3									((uint16_t)0x07)
#define  AFRL_STATE_USART4_5_6_7_8								((uint16_t)0x08)
#define  AFRL_STATE_CAN1_2										((uint16_t)0x09)
#define  AFRL_STATE_TIM12_13_14									((uint16_t)0x09)
#define  AFRL_STATE_OTG_FS_HS									((uint16_t)0x0A)
#define  AFRL_STATE_ETH											((uint16_t)0x0B)
#define  AFRL_STATE_FMC											((uint16_t)0x0C)
#define  AFRL_STATE_SDIO										((uint16_t)0x0C)
#define  AFRL_STATE_OTG_HS										((uint16_t)0x0C)
#define  AFRL_STATE_DCMI										((uint16_t)0x0D)
#define  AFRL_STATE_14											((uint16_t)0x0E)
#define  AFRL_STATE_EVENTOUT									((uint16_t)0x0F)

// AFRH STATE MACROS
#define  AFRH_STATE_SYSTEM										((uint16_t)0x00)
#define  AFRH_STATE_TIM1_2										((uint16_t)0x01)
#define  AFRH_STATE_TIM3_4_5									((uint16_t)0x02)
#define  AFRH_STATE_TIM8_9_10_11								((uint16_t)0x03)
#define  AFRH_STATE_I2C1_2_3									((uint16_t)0x04)
#define  AFRH_STATE_SPI1_2_3_4_5_6								((uint16_t)0x05)
#define  AFRH_STATE_SAI1										((uint16_t)0x06)
#define  AFRH_STATE_USART1_2_3									((uint16_t)0x07)
#define  AFRH_STATE_USART4_5_6_7_8								((uint16_t)0x08)
#define  AFRH_STATE_CAN1_2										((uint16_t)0x09)
#define  AFRH_STATE_TIM12_13_14									((uint16_t)0x09)
#define  AFRH_STATE_OTG_FS_HS									((uint16_t)0x0A)
#define  AFRH_STATE_ETH											((uint16_t)0x0B)
#define  AFRH_STATE_FSMC										((uint16_t)0x0C)
#define  AFRH_STATE_SDIO										((uint16_t)0x0C)
#define  AFRH_STATE_OTG_HS										((uint16_t)0x0C)
#define  AFRH_STATE_DCMI										((uint16_t)0x0D)
#define  AFRH_STATE_14											((uint16_t)0x0E)
#define  AFRH_STATE_EVENTOUT									((uint16_t)0x0F)

/************************************************************************************
 *																		TYPEDEF																				*
 ************************************************************************************/
	
typedef enum{
	SUCCESS = 1,
	FAIL = !SUCCESS
}Status;

typedef struct Pin_TypeDef{
	uint16_t pin;						// To set the Pin for desired configuration.
	uint32_t mode;						// To set the direction for desired configuration.
	uint32_t otype;						// To set the output type for desired configuration.
	uint32_t ospeed;					// To set the output speed for desired configuration.
	uint32_t pupd;						// To set the Pull state for desired configuration.
	uint32_t alternate;					// To set the alternate settings for desired configuration.

}Pin_TypeDef;

typedef enum {
	RISING_EDGE,
	FALLING_EDGE,
	RISING_FALLING_EDGE
} Edge_Selection;

/************************************************************************
 *										 GPIO Functions 																	*
 ************************************************************************/


/** Init Function.
	* @brief : This function Initialises the provided GPIO pin with the Parameters passed in through the Configuration structure.
  * @param : GPIOx is the GPIO Port being Operated upon.
	* @param : *pin_ConfTypedef is the pin configuration Structure.
  */

void GpioInit(GPIO_TypeDef *GPIOx, Pin_TypeDef *pin);

/** Read Pin Function.
	* @brief : This function reads the value of a specific pin on the GPIO port.
  * @param : GPIOx is the GPIO Port being Operated upon.
	* @param : pin is the number of pin being referenced here, (0 <= pin <= 15).
  */

uint8_t GpioReadPin(GPIO_TypeDef *GPIOx, uint8_t pin);

/** Write Pin Function.
	* @brief : This function.
  * @param : GPIOx is the GPIO Port being Operated upon.
	* @param : Pin is the number of the pin being referenced here.
  */
void GpioWritePin(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t val);

/** Interrupt configure Function.
	* @brief : This function.
  * @param : GPIOx is the GPIO Port being Operated upon.
	* @param : Pin is the number of the pin being referenced here.
  */
Status ConfigureGPIOInterrupt(uint8_t pin, Edge_Selection val);

/** Interrupt Enable Function.
	* @brief : This function.
  * @param : GPIOx is the GPIO Port being Operated upon.
	* @param : Pin is the number of the pin being referenced here.
  */
void EnableGPIOInterrupt(uint8_t pin, IRQn_Type irqn);

/** Clear Pending Function.
	* @brief : This function.
  * @param : GPIOx is the GPIO Port being Operated upon.
	* @param : Pin is the number of the pin being referenced here.
  */
void ClearPendingInterrupt(uint8_t pin);

#endif
