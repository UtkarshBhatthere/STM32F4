#include "STM32F4_I2C.h"


/**************************************************************************************************/
/*																			Static Functions																					*/
/**************************************************************************************************/
static void I2CConfigClockControl(I2C_TypeDef *I2Cx, I2C_ConfTypeDef *I2CConf){
	// PCLK settings.
	// Peripheral Clock Frequency.
	uint8_t pclk = 0x0A; // Change here, if any other clock frequency is required.
	
	I2Cx -> CR2 &= ~(0x3F); //Resetting all bits of FREQ[5:0].
	I2Cx -> CR2 |= (pclk & 0x3F); //Setting FREQ[5:0].
	
	// CLock control register settings
	I2Cx -> CCR |= I2CConf -> SpeedMode;
	if(I2CConf -> SpeedMode == I2C_CCR_Fast_Mode){
			I2Cx -> CCR |= I2CConf -> DutyCycle;		// Setting up Fast mode's DutyCycle.
			/** @check for errors possibile here **/
			I2Cx -> CCR |= 0x01;										// CCR min val for Fast mode.
	}else{
			/** @check for errors possibile here **/
			I2Cx -> CCR |= 0x32;										// CCR value for 10 Mhz PCLK
	}
}

static void I2CConfigAddress(I2C_TypeDef *I2Cx, uint32_t OwnAddress, uint32_t AddressingMode){
	if(AddressingMode == I2C_OAR1_10BIT_ADDR){
		I2Cx -> OAR1 |= I2C_OAR1_10BIT_ADDR;
		I2Cx -> OAR1 |= 0x3FF & OwnAddress;
	}else{
		I2Cx -> OAR1 &= I2C_OAR1_7BIT_ADDR;
		I2Cx -> OAR1 |= 0x7F & OwnAddress;
	}
}

static void I2CConfigMisc(I2C_TypeDef *I2Cx, I2C_ConfTypeDef *I2CConf){
	I2Cx -> CR1 |= I2CConf -> GeneralCallMode;
	I2Cx -> CR1 |= I2CConf -> NoStretchMode;
	I2Cx -> CR1 |= I2CConf -> ackEnable;	
}

static void I2CEnable(I2C_TypeDef *I2Cx){
	I2Cx -> CR1 |= I2C_CR1_Peripheral_Enable;
}

static void I2CDisable(I2C_TypeDef *I2Cx){
	I2Cx -> CR2 &= ~I2C_CR1_Peripheral_Enable;
}

static void I2CGenerateStart(I2C_TypeDef *I2Cx){
	I2Cx -> CR1 |= I2C_CR1_Generate_Start;
}

static void I2CGenerateStop(I2C_TypeDef *I2Cx){
	I2Cx -> CR1 |= I2C_CR1_Generate_Stop;
}

static void I2CBUFFIEnable(I2C_TypeDef *I2Cx){
	I2Cx -> CR2 |= I2C_CR2_Buffer_Interrupt_Enable;
}

static void I2CERRIEnable(I2C_TypeDef *I2Cx){
	I2Cx -> CR2 |= I2C_CR2_Error_Interrupt_Enable;
}

static void I2CEVTIEnable(I2C_TypeDef *I2Cx){
	I2Cx -> CR2 |= I2C_CR2_Event_Interrupt_Enable;
}

static void I2CBUFFIDisable(I2C_TypeDef *I2Cx){
	I2Cx -> CR2 &= ~I2C_CR2_Buffer_Interrupt_Enable;
}

static void I2CERRIDisable(I2C_TypeDef *I2Cx){
	I2Cx -> CR2 &= ~I2C_CR2_Error_Interrupt_Enable;
}

static void I2CEVTIDisable(I2C_TypeDef *I2Cx){
	I2Cx -> CR2 &= ~I2C_CR2_Event_Interrupt_Enable;
}

static void I2CDMAEnable(I2C_TypeDef *I2Cx){
	I2Cx -> CR2 |= I2C_CR2_DMA_Enable;
}

static void I2CDMADisable(I2C_TypeDef *I2Cx){
	I2Cx -> CR2 &= ~I2C_CR2_DMA_Enable;
}

static void I2CLastDMA(I2C_TypeDef *I2Cx){
	I2Cx -> CR2 |= I2C_CR2_DMA_Last;
}

static void I2CSendSlaveAddress(I2C_TypeDef *I2Cx, uint8_t SlaveAddress){
	I2Cx -> DR = SlaveAddress;

}
static void I2CClearAddr(I2C_TypeDef  *I2Cx){
	//Clear Addr Bit. (For this we'll have to read SR1 And then SR2.)
	uint32_t x = I2Cx -> SR1;
	x = I2Cx -> SR2;
	
}

static void I2CTxEHandler(I2C_Handler *Tasker){
	//  Write 1 byte to Data Register.
	Tasker -> I2Cx -> DR = (*Tasker -> Buffer++) ;
	//  Decrease the counter by 1;
	Tasker -> counter--;
	
	//Counter check.
	if(Tasker -> counter  == 0){
		I2CBUFFIDisable(Tasker -> I2Cx);
	}

}

static void I2CBTFHandler(I2C_Handler *Tasker){
	if(Tasker -> counter){
		//  Write 1 byte to Data Register.
		Tasker -> I2Cx -> DR = (*Tasker -> Buffer++) ;
		//  Decrease the counter by 1;
		Tasker -> counter--;
	}else{
		// Disable Interrupts.
		I2CERRIDisable(Tasker -> I2Cx);
		I2CBUFFIDisable(Tasker -> I2Cx);
		I2CEVTIDisable(Tasker -> I2Cx);
		
		//Generate Stop.
		I2CGenerateStop(Tasker -> I2Cx);
		
		//Put State == Ready!
		Tasker ->  state = I2C_STATE_READY;
		
		//Edit below here with any function to call after completion of I2C Transmit.
	
	}
}

static void I2CRxNEHandler(I2C_Handler *Tasker){
	// Copy 1 Byte from DR to P buffer.
	(*Tasker -> Buffer++) = Tasker -> I2Cx -> DR ;
	//  Decrease the counter by 1;
	Tasker -> counter--;
	
	//Counter check.
	if(Tasker -> counter  == 0){
		I2CBUFFIDisable(Tasker -> I2Cx);
	}
}

/**************************************************************************************************/
/*																						APIs																								*/
/**************************************************************************************************/

 /* Initialisation Function.																																			*/
 /** @brief : The function initialises the I2C peripheral according to the passed in peimeter.		*/
 /** @param : *Tasker (aka the I2C_Handler) is the structure which contains the Peripheral,   		*/
 /**					Configuration, Buffers and other perimeters required for the communication					*/
void I2CInit(I2C_Handler *Tasker){
		I2CConfigClockControl(Tasker-> I2Cx, Tasker -> I2CConf);
		I2CConfigAddress(Tasker -> I2Cx, Tasker -> I2CConf -> OwnAddress1, Tasker -> I2CConf-> AddressingMode);
		I2CConfigMisc(Tasker -> I2Cx, Tasker ->I2CConf);
}

 /* Master Transfer Function Function.																														*/
 /** @brief : The function transmits the passed ins *string through the I2C peripheral						*/
 /**					configured according to the I2C_Handler.																						*/
 /** @param : *Tasker (aka the I2C_Handler) - is the structure which contains the Peripheral, 		*/
 /**					Configuration, Buffers and other perimeters required for the communication*/
 /** @param : *string - Contains the string to be transmitted through the master.									*/
 /** @param : size - Carries the size of the strig for transmission.															*/
void I2CMasterTransmit(I2C_Handler *Tasker, uint8_t SlaveAddress, uint8_t *string, uint8_t size){
		
	// Setting up Handler
	Tasker -> Buffer = string;
	Tasker -> size = size;
	Tasker -> counter = size;
	Tasker -> state = I2C_STATE_BUSY_TX;
	
	// Enable Peripheral
	I2CEnable(Tasker -> I2Cx);
	
	// Enable Interrupt
	I2CEVTIEnable(Tasker -> I2Cx);
	I2CERRIEnable(Tasker -> I2Cx);
	
	// Generate Start
	I2CGenerateStart(Tasker -> I2Cx);
	
	//wait while start bit is set.
	while(Tasker -> I2Cx ->SR1 & I2C_FLAGS_Start_Generated);
	
	//Send Address of the Slave.
	SlaveAddress = (SlaveAddress << 1) + 0x01; 
	I2CSendSlaveAddress(Tasker -> I2Cx, SlaveAddress);
	
	//wait while slave ack sets ADDR Bit.
	while(Tasker -> I2Cx ->SR1 & I2C_FLAGS_ADDR_Set);
	
	//Reaching here means ADDR is set!
	I2CClearAddr(Tasker -> I2Cx);
	
	//Buffer Interrupt Enable.
	I2CBUFFIEnable(Tasker -> I2Cx);
	
}

  /* Master Receive Function Function.																														*/
 /** @brief : The function receives the passed ins *string through the I2C peripheral							*/
 /**					configured according to the I2C_Handler.																						*/
 /** @param : *Tasker (aka the I2C_Handler) - is the structure which contains the Peripheral, 		*/
 /**					Configuration, Buffers and other perimeters required for the communication*/
 /** @param : *string - Contains the string to be received through the master.										*/
 /** @param : size - Carries the size of the strig for reception.																	*/
void I2CMasterReceive(I2C_Handler *Tasker, uint8_t SlaveAddress, uint8_t *string, uint8_t size){
	
	// Setting up Handler
	Tasker -> Buffer = string;
	Tasker -> size = size;
	Tasker -> counter = size;
	Tasker -> state = I2C_STATE_BUSY_RX;
	
	// Enable Peripheral
	I2CEnable(Tasker -> I2Cx);
	
	// Enable Interrupt
	I2CEVTIEnable(Tasker -> I2Cx);
	I2CERRIEnable(Tasker -> I2Cx);
	
	//(N)Ack Settings.
	Tasker-> I2Cx ->CR1 &= ~(I2C_CR1_POS_Enable);
	Tasker-> I2Cx ->CR1 |= I2C_CR1_ACK_Enable;
	
	// Generate Start
	I2CGenerateStart(Tasker -> I2Cx);
	
	//wait while start bit is set.
	while(Tasker -> I2Cx ->SR1 & I2C_FLAGS_Start_Generated);
	
	//Send Address of the Slave.
	SlaveAddress = (SlaveAddress << 1);
	I2CSendSlaveAddress(Tasker -> I2Cx, SlaveAddress);
	
	//wait while slave ack sets ADDR Bit.
	while(!Tasker -> I2Cx ->SR1 & I2C_FLAGS_ADDR_Set);
	
	//Now wait untill the ADDR bit is cleared.
	while(!Tasker -> I2Cx ->SR1 & I2C_FLAGS_ADDR_Set);


	//(N)Ack Settings.
	Tasker-> I2Cx ->CR1 &= ~(I2C_CR1_POS_Enable);
	Tasker-> I2Cx ->CR1 |= I2C_CR1_ACK_Enable;
	
	//Buffer Interrupt Enable.
	I2CBUFFIEnable(Tasker -> I2Cx);

}

 /* Slave Transfer Function.																																	*/
 /** @brief : The function transmits the passed ins *string through the I2C peripheral				*/
 /**					configured according to the I2C_Handler.																				*/
 /** @param : *Tasker (aka the I2C_Handler) - is the structure which contains the Peripheral, */
 /**					Configuration, Buffers and other perimeters required for the communication			*/
 /** @param : *string - Contains the string to be transferred through the master.							*/
 /** @param : size - Carries the size of the strig for transfer.															*/
void I2CSlaveTransmit(I2C_Handler *Tasker, uint8_t *string, uint8_t size){

	// Setting up Handler
	Tasker -> Buffer = string;
	Tasker -> size = size;
	Tasker -> counter = size;
	Tasker -> state = I2C_STATE_BUSY_TX;
	
	// Enable Peripheral
	I2CEnable(Tasker -> I2Cx);
	
	//(N)Ack Settings.
	Tasker-> I2Cx ->CR1 &= ~(I2C_CR1_POS_Enable);
	Tasker-> I2Cx ->CR1 |= I2C_CR1_ACK_Enable;
	
	// Enable Interrupt
	I2CEVTIEnable(Tasker -> I2Cx);
	I2CBUFFIEnable(Tasker -> I2Cx);
	I2CERRIEnable(Tasker -> I2Cx);
	
}

  /* Slave Receive Function.																																			*/
 /** @brief : The function receives the passed ins *string through the I2C peripheral							*/
 /**					configured according to the I2C_Handler.																						*/
 /** @param : *Tasker (aka the I2C_Handler) - is the structure which contains the Peripheral, 		*/
 /**					Configuration, Buffers and other perimeters required for the communication*/
 /** @param : *string - Contains the string to be received through the master.										*/
 /** @param : size - Carries the size of the strig for reception.																	*/
void I2CSlaveReceive(I2C_Handler *Tasker, uint8_t *string, uint8_t size){
	
	// Setting up Handler
	Tasker -> Buffer = string;
	Tasker -> size = size;
	Tasker -> counter = size;
	Tasker -> state = I2C_STATE_BUSY_RX;
	
	// Enable Peripheral
	I2CEnable(Tasker -> I2Cx);
	
	//(N)Ack Settings.
	Tasker-> I2Cx ->CR1 &= ~(I2C_CR1_POS_Enable);
	Tasker-> I2Cx ->CR1 |= I2C_CR1_ACK_Enable;
		
	// Enable Interrupt
	I2CEVTIEnable(Tasker -> I2Cx);
	I2CBUFFIEnable(Tasker -> I2Cx);
	I2CERRIEnable(Tasker -> I2Cx);
	
}

 /* I2C Event Interrupt Handler																																		*/
 /** @brief : This handles the inerrupt triger and control for I2C configured by SP_Handler				*/
 /** @param : *Tasker - The I2C handler passes in all the requierd configurational infomation			*/
 /**						to the Interrrupt Handler.																												*/
void I2CEventInterruptHandler(I2C_Handler *Tasker){
	if(Tasker  -> I2Cx -> CR2 & I2C_CR2_Event_Interrupt_Enable){
			if(Tasker  -> I2Cx -> SR2 & I2C_SR2_Master_Mode){
					if(Tasker -> I2Cx ->SR1 & I2C_FLAGS_Byte_Transfer_Done){
							I2CBTFHandler(Tasker);
					}else if(Tasker -> I2Cx ->SR1 & I2C_FLAGS_TransmitBuffer_Empty){
							I2CTxEHandler(Tasker);
					}else if(Tasker -> I2Cx ->SR1 & I2C_FLAGS_ReceiveBuffer_Not_Empty){
							I2CRxNEHandler(Tasker);
					}else if(Tasker -> I2Cx ->SR1 & I2C_FLAGS_ADDR_Set){
							I2CClearAddr(Tasker -> I2Cx);
					}
			}else{
					if(Tasker -> I2Cx ->SR1 & I2C_FLAGS_Stop_Detected){
						// Disable Interrupts.
						I2CERRIDisable(Tasker -> I2Cx);
						I2CBUFFIDisable(Tasker -> I2Cx);
						I2CEVTIDisable(Tasker -> I2Cx);
					
						//Clear Stop.
						uint32_t x = Tasker -> I2Cx -> SR1;
						I2CGenerateStop(Tasker -> I2Cx);
					
						//Disable Ack.
						Tasker -> I2Cx -> CR1 &= ~I2C_CR1_ACK_Enable;
						Tasker -> state = I2C_STATE_READY;
						
						// Call any application code if required below.
						
					
					}else if(Tasker -> I2Cx ->SR1 & I2C_FLAGS_ADDR_Set){
						I2CClearAddr(Tasker -> I2Cx);
						
					}else if((Tasker -> I2Cx ->SR1 & I2C_FLAGS_TransmitBuffer_Empty)){
						if(Tasker -> counter){
							I2CTxEHandler(Tasker);
						}
					
					}else if((Tasker -> I2Cx ->SR1 & I2C_FLAGS_Byte_Transfer_Done) && (Tasker -> I2Cx ->SR2 & I2C_SR2_Data_Transmitted)){
							if(Tasker -> counter){
							I2CTxEHandler(Tasker);
							}
					}else if((Tasker -> I2Cx ->SR1 & I2C_FLAGS_ReceiveBuffer_Not_Empty)||(Tasker -> I2Cx ->SR1 & I2C_FLAGS_Byte_Transfer_Done)){
							if(Tasker -> counter){
								I2CRxNEHandler(Tasker);
							}
					}
			
			}
	}
}

 /* I2C Error Interrupt Handler																																		*/
 /** @brief : This handles the error inerrupt triger and control for I2C configured by SP_Handler	*/
 /** @param : *Tasker - The I2C handler passes in all the requierd configurational infomation			*/
 /**						to the Interrrupt Handler.																												*/
void I2CErrorInterruptHandler(I2C_Handler *Tasker){

	if(Tasker ->I2Cx -> SR1 & I2C_FLAGS_Bus_Error){
		Tasker -> ErrorCode = I2C_ERROR_BERR;
		Tasker ->I2Cx -> SR1 &= ~I2C_FLAGS_Bus_Error;
	}else if(Tasker ->I2Cx -> SR1 & I2C_FLAGS_Arbitration_Lost){
		Tasker -> ErrorCode = I2C_ERROR_ARLO;
		Tasker ->I2Cx -> SR1 &= ~I2C_FLAGS_Arbitration_Lost;
	}else if(Tasker ->I2Cx -> SR1 & I2C_FLAGS_Acknowledge_Failure){
		Tasker -> ErrorCode = I2C_ERROR_AF;
		Tasker ->I2Cx -> SR1 &= ~I2C_FLAGS_Acknowledge_Failure;
	}else if(Tasker ->I2Cx -> SR1 & I2C_FLAGS_OUrun_Failure){
		Tasker -> ErrorCode = I2C_ERROR_OVR;
		Tasker ->I2Cx -> SR1 &= ~I2C_FLAGS_OUrun_Failure;
	}else if(Tasker ->I2Cx -> SR1 & I2C_ERROR_TIMEOUT){
		Tasker -> ErrorCode = I2C_ERROR_TIMEOUT;
		Tasker ->I2Cx -> SR1 &= ~I2C_ERROR_TIMEOUT;
	}else{
		Tasker -> ErrorCode = I2C_ERROR_NONE;
	}
}
  