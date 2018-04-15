#ifndef _STM32F4_I2C_H
#define _STM32F4_I2C_H

// Device Specific Header File inclusion.
#include "stm32f429xx.h"					//Device Header

typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;


/************************************************ I2C Library Macros ***********************************************************************/

/******* I2C CR1 Bit definition *******/

#define I2C_CR1_Peripheral_Enable											((uint16_t) 0x0001 << 0)
#define I2C_CR1_Peripheral_Disable										((uint16_t) 0x0000 << 0)

#define I2C_CR1_PEC_Enable														((uint16_t) 0x0001 << 5)
#define I2C_CR1_PEC_Disable														((uint16_t) 0x0000 << 5)

#define I2C_CR1_Clock_Stretching_Enable								((uint16_t) 0x0000 << 7)
#define I2C_CR1_Clock_Stretching_Disable							((uint16_t) 0x0001 << 7)

#define I2C_CR1_Generate_Start												((uint16_t) 0x0001 << 8)
#define I2C_CR1_Generate_Stop													((uint16_t) 0x0001 << 9)

#define I2C_CR1_ACK_Enable														((uint16_t) 0x0001 << 10)

#define I2C_CR1_PEC_Next															((uint16_t) 0x0001 << 11)

#define I2C_CR1_PEC_Transferred												((uint16_t) 0x0001 << 12)

//#define I2C_CR1_SWRST																	((uint16_t) 0x0001 << 15) Already defined

/******* I2C CR2 Bit definition *******/

#define I2C_CR2_Error_Interrupt_Enable								((uint16_t) 0x0001 << 8)

#define I2C_CR2_Event_Interrupt_Enable								((uint16_t) 0x0001 << 9)

#define I2C_CR2_Buffer_Interrupt_Enable								((uint16_t) 0x0001 << 10)

#define I2C_CR2_DMA_Enable														((uint16_t) 0x0001 << 11)

#define I2C_CR2_DMA_Last															((uint16_t) 0x0001 << 12)

/******* I2C Own Address register 1 Bit definition *******/

#define I2C_OAR1_10BIT_ADDR														((uint16_t) 0x0001 << 15)
#define I2C_OAR1_7BIT_ADDR															~I2C_OAR_10BIT_ADDR

/******* I2C Own Address register 2, Bit definition *******/

//#define I2C_OAR2_ENDUAL																((uint16_t) 0x0001 << 0) Already defined.

/******* I2C Status Register 1 Definition *******/

#define I2C_FLAGS_Start_Generated											((uint16_t) 0x0001 << 0)

#define I2C_FLAGS_Master_Address_Sent									((uint16_t) 0x0001 << 1)
#define I2C_FLAGS_Slave_Address_Received							((uint16_t) 0x0001 << 1)

#define I2C_FLAGS_Byte_Transfer_Done									((uint16_t) 0x0001 << 2)

#define I2C_FLAGS_10Bit_Address_Sent									((uint16_t) 0x0001 << 3)

#define I2C_FLAGS_Stop_Detected												((uint16_t) 0x0001 << 4)

#define I2C_FLAGS_ReceiveBuffer_Not_Empty							((uint16_t) 0x0001 << 6)

#define I2C_FLAGS_TransmitBuffer_Empty								((uint16_t) 0x0001 << 7)

#define I2C_FLAGS_Bus_Error														((uint16_t) 0x0001 << 8)

#define I2C_FLAGS_Arbitration_Lost										((uint16_t) 0x0001 << 9)

#define I2C_FLAGS_Acknowledge_Failure									((uint16_t) 0x0001 << 10)

#define I2C_FLAGS_OUrun_Failure												((uint16_t) 0x0001 << 11)

#define I2C_FLAGS_PEC_Error														((uint16_t) 0x0001 << 12)

#define I2C_FLAGS_Timeout															((uint16_t) 0x0001 << 14)

#define I2C_FLAGS_SMBus_Alert													((uint16_t) 0x0001 << 15)

/******* I2C Status Register 2 Definition *******/
#define I2C_SR2_Master_Mode														((uint16_t) 0x0001 << 0)
#define I2C_SR2_Slave_Mode														((uint16_t) 0x0000 << 0)
#define I2C_SR2_Channel_Busy													((uint16_t) 0x0001 << 1)
#define I2C_SR2_Channel_Ready													((uint16_t) 0x0000 << 1)
#define I2C_SR2_Data_Transmitted											((uint16_t) 0x0001 << 2)
#define I2C_SR2_Data_received													((uint16_t) 0x0000 << 2)
#define I2C_SR2_General_CallAddr_Received							((uint16_t) 0x0001 << 4)
#define I2C_SR2_Dual_Flag_OAR1_Matched								((uint16_t) 0x0000 << 7)
#define I2C_SR2_Dual_Flag_OAR2_Matched								((uint16_t) 0x0001 << 7)
#define I2C_SR2_Packet_Error_Check										((uint16_t) 0xff00)


/******* I2C Clock Control Register Definition *******/
#define I2C_CCR_Slow_Mode															((uint16_t) 0x00 << 15)
#define I2C_CCR_Fast_Mode															((uint16_t) 0x01 << 15)

#define I2C_CCR_Duty_Cycle_2													((uint16_t) 0x01 << 14)
#define I2C_CCR_Duty_Cycle_169												((uint16_t) 0x01 << 14)


/******************************************************************************/
/*																Structures																	*/
/******************************************************************************/

typedef enum{
	I2C_STATE_RESET																			= 0x00, //`I2C disabled
	I2C_STATE_READY																			= 0x01, // Initialised and ready to use.
	I2C_STATE_BUSY																			= 0x02, // I2C Busy
	I2C_STATE_BUSY_RX																		= 0x03, // I2C Busy in TX
	I2C_STATE_BUSY_TX																		= 0x04, // I2C Busy in RX
	I2C_STATE_ERROR																			= 0x05 	// Error State.
} I2C_State;

typedef struct{
	uint32_t ClockSpeed;												// Whether to use FM or SM.
	uint32_t DutyCycle;													// The ON and OFF positions can have different time durations in FM, use this to configure the duty cycle.
	uint32_t OwnAddress1;												// Specifies the first own address of the device.
	uint32_t AddressingMode;										// Whether to use 7-Bit or 10-Bit Addressing.
	uint32_t DualAddressMode;										// Whether or not two own addresses are to be used.
	uint32_t OwnAddress2;												// Configure second own address.
	uint32_t GeneralCallMode;										// Specify if general calls on address 0 are legal.
	uint32_t NostretchMode;											// Specify if slave can stretch clock low if need be.
	uint32_t ackEnable;													// Handles ACK enable/disable.
}I2C_ConfTypeDef;


typedef struct{
	I2C_TypeDef			*I2Cx;
	I2C_ConfTypeDef SPIConf;
	uint8_t					*Buffer;
	uint32_t				counter;
	uint32_t				size;
	I2C_State				state;
	uint32_t				ErrorCode;
	
}I2C_Handler;

typedef enum{
	SET = 1,
	RESET  =!SET
}bitStatus;


#endif  