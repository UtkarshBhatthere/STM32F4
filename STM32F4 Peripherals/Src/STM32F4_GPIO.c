
#include "STM32F4_GPIO.h"

/************************************************************************
 *										 Static Functions 																*
 ************************************************************************/

static void SetMode(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t mode){
		GPIOx -> MODER |= ( mode << (2*pin));
}

static void SetOType(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t type){
		GPIOx -> OTYPER |= ( type << pin ); 
}

static void SetSpeed(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t speed){
		GPIOx -> OSPEEDR |= ( speed << (2*pin) );
}

static void SetPullState(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t state){
		GPIOx -> PUPDR |= ( state << (2*pin) );
}
static void SetAlternate(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t state){
		if(pin <= 7){
			GPIOx -> AFR[0] |= ( state << (4*pin) );
		}else {
			GPIOx -> AFR[1] |= ( state << (4*(pin-8)));
		}
}

/************************************************************************
 *										 Library Functions 																*
 ************************************************************************/

/** Init Function.
	* @brief : This function Initialises the provided GPIO pin with the Parameters passed in through the Configuration structure.
  * @param : GPIOx is the GPIO Port being Operated upon.
	* @param : *pin_ConfTypedef is the pin configuration Structure.
  */

void GpioInit(GPIO_TypeDef *GPIOx, Pin_TypeDef *pin){
		SetMode(GPIOx, pin->pin, pin->mode);
		SetOType(GPIOx, pin->pin, pin->otype);
		SetSpeed(GPIOx, pin->pin, pin->ospeed);
		SetPullState(GPIOx, pin->pin, pin->pupd);
		SetAlternate(GPIOx, pin->pin, pin->alternate);
}


/** Read Pin Function.
	* @brief : This function reads the value of a specific pin on the GPIO port.
  * @param : GPIOx is the GPIO Port being Operated upon.
	* @param : pin is the number of pin being referenced here, (0 <= pin <= 15).
  */

uint8_t GpioReadPin(GPIO_TypeDef *GPIOx, uint8_t pin){
	uint8_t value;
	value = ((GPIOx->IDR >> pin) & 0x00000001);
	return value;
}


/** Write Pin Function.
	* @brief : This function.
  * @param : GPIOx is the GPIO Port being Operated upon.
	* @param : Pin is the number of pin being referenced here.
	* @param : val, for non zero values of val bit is set.
  */

void GpioWritePin(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t val){
		if(val){
			GPIOx -> ODR |= (1 << pin);
		}else {
			GPIOx -> ODR &= ~(1 << pin);
		}
}

/*******************************************************************************************
 *																	Interrupts 																						 *
 *******************************************************************************************/

/** Interrupt configure Function.
	* @brief : This function.
  * @param : GPIOx is the GPIO Port being Operated upon.
	* @param : Pin is the number of the pin being referenced here.
  */
Status ConfigureGPIOInterrupt(uint8_t pin, Edge_Selection val){
	if(val == RISING_EDGE){
		EXTI -> RTSR |= (1 << pin);
		return SUCCESS;
	}else if(val == FALLING_EDGE){
		EXTI -> FTSR  |= (1 << pin);
		return SUCCESS;
	}else if(val == RISING_FALLING_EDGE){
		EXTI -> FTSR |= (1 << pin);
		EXTI -> RTSR |= (1 << pin);
		return SUCCESS;
	}else{
		return FAIL;
	}
}

/** Interrupt Enable Function.
	* @brief : This function.
  * @param : GPIOx is the GPIO Port being Operated upon.
	* @param : Pin is the number of the pin being referenced here.
  */
void EnableGPIOInterrupt(uint8_t pin, IRQn_Type irqn){
	EXTI -> IMR |= ( 1 << pin);
	NVIC_EnableIRQ(irqn);
}

/** Clear Pending Function.
	* @brief : This function.
  * @param : GPIOx is the GPIO Port being Operated upon.
	* @param : Pin is the number of the pin being referenced here.
  */
void ClearPendingInterrupt(uint8_t pin){
	if(EXTI -> PR & ~(1 << pin)){
		EXTI -> PR |= (1 << pin);
	}else{
		// Do nothing.
	}
}
