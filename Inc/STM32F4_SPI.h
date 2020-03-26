#ifndef _STM32F4_SPI_H
#define _STM32F4_SPI_H

// Device Specific Header File inclusion.
#include "stm32f429xx.h"					//Device Header


/*******************************************************************
 **	SPI Driver																										 *
 ** @author : UTKARSH BHATT																				 *
 ** @date		: 24-03-2018																					 *
 ** @comment: Have Fun!																						 *
 *******************************************************************/


/*******************************************************************
 *									SPI DRIVER MACRO DEFINITION										 *
 *******************************************************************/
 
 // SPI CLOCK ENABLE
  #define SPI1_ENABLE														(RCC -> APB2ENR |= 0x01 << 12)
	#define SPI2_ENABLE														(RCC -> APB1ENR |= 0x01 << 14)
  #define SPI3_ENABLE														(RCC -> APB1ENR |= 0x01 << 15)
  #define SPI4_ENABLE														(RCC -> APB2ENR |= 0x01 << 13)
	#define SPI5_ENABLE														(RCC -> APB2ENR |= 0x01 << 20)
	#define SPI6_ENABLE														(RCC -> APB2ENR |= 0x01 << 21)
	
	
	
// SPIx CR1 
// BIDI MODE MACROS
 #define SPI_CR1_BIDI_ENABLE										((uint16_t) 1 << 15)
 #define SPI_CR1_BIDI_UNIDIRECTIONAL						((uint16_t) 0x00 << 14)
 #define SPI_CR1_BIDI_BIDIRECTIONAL							((uint16_t) 0x01 << 14)
 
// CRC MACROS
 #define SPI_CR1_CRC_DISABLED										((uint16_t) 0x00 << 13)
 #define SPI_CR1_CRC_ENABLED										((uint16_t) 0x01 << 13)
 
// CRCNEXT MACROS
 #define SPI_CR1_CRCNEXT_FALSE									((uint16_t) 0x00 << 12)
 #define SPI_CR1_CRCNEXT_TRUE										((uint16_t) 0x01 << 12)

// Data Frame Format Macros
 #define SPI_CR1_DFF_8BIT												((uint16_t) 0x00 << 11)
 #define SPI_CR1_DFF_16BIT											((uint16_t) 0x01 << 11)
 
// RXONLY mode Macros
 #define SPI_CR1_TXRX														((uint16_t) 0x00 << 10)
 #define SPI_CR1_RX_ONLY												((uint16_t) 0x01 << 10)
 
// Software Slave Management
 #define SPI_CR1_SSM_DISABLE										((uint16_t) 0x00 << 9)
 #define SPI_CR1_SSM_ENABLE											((uint16_t) 0x01 << 9)
 
// SSI Bit macros
 #define SPI_CR1_SSI_LOW												((uint16_t) 0x00 << 8)
 #define SPI_CR1_SSI_HIGH												((uint16_t) 0x01 << 8)
 
// Frame Format 
 #define SPI_CR1_FRAME_MSBFIRST									((uint16_t) 0x00 << 7)
 #define SPI_CR1_FRAME_LSBFIRST									((uint16_t) 0x01 << 7)
 
// SPIx Enable
 #define SPI_CR1_ENABLE													((uint16_t) 0x01 << 6)
 #define SPI_CR1_DISABLE												((uint16_t) 0x00 << 6)
 
// Baud Rate Controller
 #define SPI_CR1_CLK_PRESCALAR_2								((uint16_t) 0x00 << 3)
 #define SPI_CR1_CLK_PRESCALAR_4								((uint16_t) 0x01 << 3)
 #define SPI_CR1_CLK_PRESCALAR_8								((uint16_t) 0x02 << 3)
 #define SPI_CR1_CLK_PRESCALAR_16								((uint16_t) 0x03 << 3)
 #define SPI_CR1_CLK_PRESCALAR_32								((uint16_t) 0x04 << 3)
 #define SPI_CR1_CLK_PRESCALAR_64								((uint16_t) 0x05 << 3)
 #define SPI_CR1_CLK_PRESCALAR_128							((uint16_t) 0x06 << 3)
 #define SPI_CR1_CLK_PRESCALAR_256							((uint16_t) 0x07 << 3)
 
// Master mode Selection Macros
 #define SPI_CR1_SLAVE_ENABLE										((uint16_t) 0x00 << 2)
 #define SPI_CR1_MASTER_ENABLE									((uint16_t) 0x01 << 2)
 
// Clock Polarity Macros
 #define SPI_CR1_CPOL_0													((uint16_t) 0x00 << 1)
 #define SPI_CR1_CPOL_1													((uint16_t) 0x01 << 1)
 
// Clock Phase Macros
 #define SPI_CR1_CPHA_0													((uint16_t) 0x00)
 #define SPI_CR1_CPHA_1													((uint16_t) 0x01)
 
// SPI CR2
// Interrupt Enable Flags

// TX Buffer Interrupt
 #define SPI_CR2_TXEI_DISABLED									((uint16_t) 0x00 << 7)
 #define SPI_CR2_TXEI_ENABLED										((uint16_t) 0x01 << 7)
 
// RX Buffer Interrupt
 #define SPI_CR2_RXNEI_DISABLED									((uint16_t) 0x00 << 6)
 #define SPI_CR2_RXNEI_ENABLED									((uint16_t) 0x01 << 6)
  
// ERROR INTERRUPT
 #define SPI_CR2_ERRORI_DISABLED								((uint16_t) 0x00 << 5)
 #define SPI_CR2_ERRORI_ENABLED									((uint16_t) 0x01 << 5)
  
// SS output 
 #define SPI_CR2_SS_DISABLED										((uint16_t) 0x00 << 2)
 #define SPI_CR2_SS_ENABLED											((uint16_t) 0x01 << 2)
 
// TX DMA ENABLE
 #define SPI_CR2_TX_DMA_DISABLE									((uint16_t) 0x00 << 1)
 #define SPI_CR2_TX_DMA_ENABLE									((uint16_t) 0x01 << 1)
 
// RX DMA ENABLE
 #define SPI_CR2_RX_DMA_DISABLED								((uint16_t) 0x00)
 #define SPI_CR2_RX_DMA_ENABLED									((uint16_t) 0x01)
 
 
// SPI STATUS REGISTER

// ERROR and EVENT FLAGS

// BUSY FLAG
 #define SPI_FLAGS_IDLE												((uint16_t) 0x00 << 7)
 #define SPI_FLAGS_BUSY												((uint16_t) 0x01 << 7)

// Overrun FLAG
 #define SPI_FLAGS_OVERRUN_FALSE								((uint16_t) 0x00 << 6)
 #define SPI_FLAGS_OVERRUN_TRUE									((uint16_t) 0x00 << 6)

// Mode Fault FLAG
 #define SPI_FLAGS_MODEFAULT_FALSE							((uint16_t) 0x00 << 5)
 #define SPI_FLAGS_MODEFAULT_TRUE 							((uint16_t) 0x01 << 5)
 
// CRC FLAG
 #define SPI_FLAGS_CRCERROR_FALSE								((uint16_t) 0x00 << 4)
 #define SPI_FLAGS_CRCERROR_TRUE								((uint16_t) 0x01 << 4)
 
// TX FLAGS
 #define SPI_FLAGS_TX_NOTEMPTY									((uint16_t) 0x00 << 1)
 #define SPI_FLAGS_TX_EMPTY											((uint16_t) 0x01 << 1)
 
// TX FLAGS
 #define SPI_FLAGS_RX_EMPTY											((uint16_t) 0x00)
 #define SPI_FLAGS_RX_NOTEMPTY									((uint16_t) 0x01)
 
/**********************************************************************************
 *													Structures and Enums																	*
 **********************************************************************************/
 
 // Clock Prescalar enum
 typedef enum{
	prescalar2		=		((uint32_t)0x00 << 3),
	prescalar4 		=		((uint32_t)0x01 << 3),
	prescalar8 		=		((uint32_t)0x02 << 3),
	prescalar16 	= 	((uint32_t)0x03 << 3),
	prescalar32 	= 	((uint32_t)0x04 << 3),
	prescalar64 	= 	((uint32_t)0x05 << 3),
	prescalar128 	= 	((uint32_t)0x06 << 3),
	prescalar256 	= 	((uint32_t)0x07 << 3)
 }clk;
 
 // Enum initialisation to hnadle the SPI states.
 typedef enum{
	 SPI_State_Reset			= 0x00,								//SPI not Yet initialised.
	 SPI_State_Ready			= 0x01,								//SPI ready for communication.
	 SPI_State_Busy				= 0x02,								//SPI busy is SPI processes.
	 SPI_State_Busy_RX		= 0x22,								//SPI busy in receiveing.
	 SPI_State_Busy_TX		= 0x12,								//SPI busy in transmitting.
	 SPI_State_Busy_RX_TX = 0x32,								//SPI busy in both transmitting and receiving.
	 SPI_State_Error 			= 0x03								//SPI encountered some error.
 }SPI_state;
 
 // configurational structure to initialise the SPI peripheral.
 typedef struct{
	uint16_t mode;																// Whether the operation will be Bidirectional or not.
	uint16_t position;														// Master / Slave.
	uint16_t size;																// 8 Bit / 16 Bit.
	uint16_t cpol;																// CPOL 0 or CPOL 1.
	uint16_t cpha;																// CPHA 0 or CPHA 1.
	clk baudrate;																	// SPI PCLK Prescalar be 2, 4, 8, 16, 32, 64, 128, 256.
	uint16_t NSS;																	// Hardware controller or Software Controlled.
	uint16_t firstBit;	 													// MSB or LSB
	uint16_t CRCval;	 														// Whether Cyclic redundancy check is to be done or not.
 }SPI_ConfTypedef;
 
 /********************************************************************************************
  *	@brief : The Handler structure to maintain the RX/TX processess along with the SPIx 		 *
	* 				 peripheral management.																													 *
	* @param : *SPIx - (ex - SPI1, SPI2 etc) Incorporated to enable the register access to 		 *
	*					 the SPI handler.																															   *
	* @param : *SPIConf - For the initialisation of the SPI peripheral through the SPI handler *
  * @param : Rest are explanatory through the inline comments.															 *
	********************************************************************************************/
 typedef struct{
	SPI_TypeDef 		*SPIx;												// SPI peripheral for register access.
	SPI_ConfTypedef *SPIConf;											// SPI Initialisation typedef.
	SPI_state 			 state;												// The current state of SPI.
	
	// Communication Buffer.
	uint8_t 				*TXbuffer;										// Pointer to the Transfer pending buffer.
	uint8_t					*RXbuffer;										// Pointer to the Receive pending buffer.
	 
	// Counters and Size holders for Comm.
	uint16_t				TXcounter;										// Counter to count the Bytes transferred.
	uint16_t				RXcounter;										// Counter to count the Bytes received.
	uint16_t				TXsize;												// Size holder for TX buffer.
	uint16_t				RXsize;												// Size holder for RX buffer.
	IRQn_Type				IRQn;													// Set this for automatic interrupt enabling.
 }SPI_Handler;
 
 /*********************************************************************************************
  * 										Prototypes and Internal Functions																			*
  *********************************************************************************************/
 
 /* Initialisation Function.																																	*/
 /** @brief : The function initialises the SPI peripheral according to the passed in peimeter.*/
 /** @param : *Tasker (aka the SPI_Handler) is the structure which contains the Peripheral,   */
 /**					Configuration, RX-TX Buffers and other perimeters required for the communication*/
 void SPIinit(SPI_Handler *Tasker);

 /* Master Transfer Function Function.																												*/
 /** @brief : The function transmits the passed ins *string through the SPI peripheral				*/
 /**					configured according to the SPI_Handler.																				*/
 /** @param : *Tasker (aka the SPI_Handler) - is the structure which contains the Peripheral, */
 /**					Configuration, RX-TX Buffers and other perimeters required for the communication*/
 /** @param : *string - Contains the string to be transmitted through the master.							*/
 /** @param : size - Carries the size of the strig for transmission.													*/
 void SPIMasterTransmit(SPI_Handler *Tasker, uint8_t *sring, uint16_t size);
 
  /* Master Receive Function Function.																												*/
 /** @brief : The function receives the passed ins *string through the SPI peripheral					*/
 /**					configured according to the SPI_Handler.																				*/
 /** @param : *Tasker (aka the SPI_Handler) - is the structure which contains the Peripheral, */
 /**					Configuration, RX-TX Buffers and other perimeters required for the communication*/
 /** @param : *string - Contains the string to be received through the master.								*/
 /** @param : size - Carries the size of the strig for reception.															*/
 void SPIMasterReceive(SPI_Handler *Tasker, uint8_t *sring, uint16_t size);
 
 /* Slave Transfer Function.																													*/
 /** @brief : The function transmits the passed ins *string through the SPI peripheral				*/
 /**					configured according to the SPI_Handler.																				*/
 /** @param : *Tasker (aka the SPI_Handler) - is the structure which contains the Peripheral, */
 /**					Configuration, RX-TX Buffers and other perimeters required for the communication*/
 /** @param : *string - Contains the string to be transferred through the master.							*/
 /** @param : size - Carries the size of the strig for transfer.															*/
 void SPISlaveTransmit(SPI_Handler *Tasker, uint8_t *sring, uint16_t size);
 
  /* Slave Receive Function.																																	*/
 /** @brief : The function receives the passed ins *string through the SPI peripheral					*/
 /**					configured according to the SPI_Handler.																				*/
 /** @param : *Tasker (aka the SPI_Handler) - is the structure which contains the Peripheral, */
 /**					Configuration, RX-TX Buffers and other perimeters required for the communication*/
 /** @param : *string - Contains the string to be received through the master.								*/
 /** @param : size - Carries the size of the strig for reception.															*/
 void SPISlaveReceive(SPI_Handler *Tasker, uint8_t *sring, uint16_t size);
 
  /* SPI Interrupt Handler																																		*/
	/** @brief : This handles the inerrupt triger and control for SPI configured by SP_Handler	*/
	/** @param : *Tasker - The SPI handler passes in all the requierd configurational infomation*/
	/**						to the Interrrupt Handler.																										*/
 void SPI_InterruptHandler(SPI_Handler *Tasker);

#endif
