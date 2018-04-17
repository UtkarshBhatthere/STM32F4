#include "STM32F4_SPI.h"

/**********************************************************************************************
 *										 							Static Functions 																					*
 **********************************************************************************************/
 
 static void SPIConfigCommMode(SPI_TypeDef *SPIx, uint16_t position){
		if( position ){
				SPIx -> CR1 |= SPI_CR1_MASTER_ENABLE;
		}else{
				SPIx -> CR1 &= ~(SPI_CR1_MASTER_ENABLE);
		}
 }
 
 static void SPIConfigClock(SPI_TypeDef *SPIx, uint16_t polarity, uint16_t phase){
	
	 if(polarity == SPI_CR1_CPOL_1){
			SPIx -> CR1 |= SPI_CR1_CPOL_1;
	 }else{
			SPIx -> CR1 |= SPI_CR1_CPOL_0;
	 }
	 
	 if(phase == SPI_CR1_CPHA_1){
			SPIx -> CR1 |= SPI_CR1_CPHA_1;
	 }else{
			SPIx -> CR1 |= SPI_CR1_CPHA_0;
	 }
 }
 
 static void SPIConfigData(SPI_TypeDef *SPIx, uint16_t data, uint16_t firstbit){
		if(data == SPI_CR1_DFF_16BIT){
					SPIx -> CR1 |= SPI_CR1_DFF_16BIT;
		}else {
					SPIx -> CR1 |= SPI_CR1_DFF_8BIT;
		}
		
		if(firstbit == SPI_CR1_LSBFIRST){
					SPIx -> CR1 |= SPI_CR1_FRAME_LSBFIRST;
		}else{
					SPIx -> CR1 |= SPI_CR1_FRAME_MSBFIRST;
		}
 }
 
 static void SPIConfigBaud(SPI_Handler *Tasker){
		Tasker -> SPIx -> CR1 |= (Tasker -> SPIConf -> baudrate);
 }
 
 static void SPIConfigSlaveManagement(SPI_TypeDef *SPIx, uint16_t nssval, uint16_t ssival){
		if(nssval){
				SPIx -> CR1 |= SPI_CR1_SSM_ENABLE;
				SPIx -> CR1 |= ssival;
		}else{
				SPIx -> CR1 &= ~SPI_CR1_SSM_ENABLE;
		}
 }
 
 static void SPIConfigPosition(SPI_TypeDef *SPIx, uint16_t position){
		SPIx -> CR1 |= position;
 }
 
 static void SPIEnable(SPI_TypeDef *SPIx){
		SPIx -> CR1 |= (1 << 6);		//SPI_CR1_ENABLE;
 }

 static void SPITXIEnable(SPI_TypeDef *SPIx){
		SPIx -> CR2 |= (1 << 7);		//SPI_CR2_TXEI_ENABLED;
 }
 
 static void SPITXIDisable(SPI_TypeDef *SPIx){
		SPIx -> CR2 &= ~SPI_CR2_TXEI_ENABLED;
 }
 
 static void SPIRXIEnable(SPI_TypeDef *SPIx){
		SPIx -> CR2 |= SPI_CR2_RXNEI_ENABLED;
 }
	
 static void SPIRXIDisable(SPI_TypeDef *SPIx){
		SPIx -> CR2 &= ~SPI_CR2_RXNEI_ENABLED;
 }
 
 static void SPICRCEnable(SPI_TypeDef *SPIx){
		SPIx-> CR1 |= SPI_CR1_CRC_ENABLED;
 }
	 
 static void SPICRCDisable(SPI_TypeDef *SPIx){
 		SPIx-> CR1 &= ~SPI_CR1_CRC_ENABLED;
 }
 
 static void SPITxHandler(SPI_Handler *Tasker){
		// Checking if the Data frame is set to 16 bits.
		Tasker-> SPIx-> DR;
	 if(Tasker -> SPIConf -> size == SPI_CR1_DFF_16BIT){
			//  Copy 2 bytes of data from  tx buffer to the DR.
			Tasker ->  SPIx -> DR = *((uint16_t *)Tasker ->TXbuffer);
			// Change the index of the Tx buffer by 2 bytes.
			Tasker ->TXbuffer+= 2;
			// Decrease the Tx counter by 2.
			Tasker -> TXcounter-= 2;
		}else {
			//  Copy 1 byte of data from  tx buffer to the DR.
			Tasker ->  SPIx -> DR = *(Tasker ->TXbuffer++);
			//	Decrease the counter by 1.
			Tasker -> TXcounter--;
		}
		if(Tasker -> TXcounter ==  0){
			// Changing the state to ready, for further transmissions.
			if((Tasker ->  SPIConf -> position) && (Tasker -> state != SPI_State_Busy_RX))
			Tasker ->  state = SPI_State_Ready;
			// Disable the TX interrupt.
			SPITXIDisable(Tasker -> SPIx);

		}
 }
 static void SPIRxHandler(SPI_Handler *Tasker){
		//  Checking Frame format to be 8 bit.
		if(Tasker -> SPIConf -> size == SPI_CR1_DFF_16BIT){
				// String available check
				if(*Tasker -> RXbuffer){
					// Copying 2 bytes of data
					*((uint16_t *)Tasker -> RXbuffer) = Tasker -> SPIx -> DR;
					// Decreasing the counter by 2.
					Tasker -> RXcounter-= 2;
					// Increasing the buffer by 2;
					Tasker -> RXbuffer+=2;
					
				}
			}else{
				//String available check
				if(*Tasker -> RXbuffer){
				//  Copy 1 byte of data from  rx buffer to the DR.
				*Tasker -> RXbuffer++ = Tasker -> SPIx -> DR;
				//	Decrease the counter by 1.
				Tasker -> TXcounter--;
			}
			if(Tasker -> RXcounter == 0){
				Tasker -> state = SPI_State_Ready;
				SPIRXIDisable(Tasker -> SPIx);
 }
} 
}
/**********************************************************************************************
  * 																Functions Definitions																			*
  *********************************************************************************************/
 
 /* Initialisation Function.																																	*/
 /** @brief : The function initialises the SPI peripheral according to the passed in peimeter.*/
 /** @param : *Tasker (aka the SPI_Handler) is the structure which contains the Peripheral,   */
 /**					Configuration, RX-TX Buffers and other perimeters required for the communication*/
 void SPIinit(SPI_Handler *Tasker){
		SPIConfigCommMode((Tasker -> SPIx), (Tasker -> SPIConf -> position));
	  SPIConfigClock(Tasker -> SPIx, Tasker -> SPIConf -> cpol, Tasker -> SPIConf -> cpha);
	  SPIConfigData(Tasker -> SPIx, Tasker -> SPIConf -> size, Tasker -> SPIConf -> firstBit);
		SPIConfigBaud(Tasker);
	  SPIConfigPosition(Tasker -> SPIx, Tasker -> SPIConf -> position);
	  if(Tasker -> SPIConf -> CRCval == SPI_CR1_CRC_ENABLED){
			SPICRCEnable(Tasker->SPIx);
		}else{
			SPICRCDisable(Tasker->SPIx);
		}
	  if(Tasker -> SPIConf -> position == SPI_CR1_SLAVE_ENABLE){
			SPIConfigSlaveManagement(Tasker -> SPIx, Tasker -> SPIConf -> NSS, SPI_CR1_SSI_LOW);
		}else{
			SPIConfigSlaveManagement(Tasker -> SPIx, Tasker -> SPIConf -> NSS, SPI_CR1_SSI_HIGH);
		}
		NVIC_EnableIRQ(Tasker->IRQn);
 }

 /* Master Transfer Function Function.																												*/
 /** @brief : The function transmits the passed ins *string through the SPI peripheral				*/
 /**					configured according to the SPI_Handler.																				*/
 /** @param : *Tasker (aka the SPI_Handler) - is the structure which contains the Peripheral, */
 /**					Configuration, RX-TX Buffers and other perimeters required for the communication*/
 /** @param : *string - Contains the string to be transmitted through the master.							*/
 /** @param : size - Carries the size of the strig for transmission.													*/
 void SPIMasterTransmit(SPI_Handler *Tasker, uint8_t *string, uint16_t size){
		// Setting up the Data for handler.
		Tasker -> TXbuffer = string;
	  Tasker -> TXcounter = size;
	  Tasker -> TXsize = size;
	 
	 // Changing the state of SPI to busy;
	  Tasker ->state = SPI_State_Busy_TX;
	 
	 // Enabling SPI.
	 SPIEnable(Tasker -> SPIx);
	 
	 // Enabling Interrup to take over.
	 SPITXIEnable(Tasker -> SPIx);
 }
 
  /* Master Receive Function Function.																												*/
 /** @brief : The function receives the passed ins *string through the SPI peripheral					*/
 /**					configured according to the SPI_Handler.																				*/
 /** @param : *Tasker (aka the SPI_Handler) - is the structure which contains the Peripheral, */
 /**					Configuration, RX-TX Buffers and other perimeters required for the communication*/
 /** @param : *string - Contains the string to be received through the master.								*/
 /** @param : size - Carries the size of the strig for reception.															*/
 void SPIMasterReceive(SPI_Handler *Tasker, uint8_t *string, uint16_t size){
		// Setting up dummy data for SPI to send so as to receive any data.
	  Tasker -> TXbuffer = string;
	  Tasker -> TXcounter = size;
	  Tasker -> TXsize = size;
	 
	  // Now for the Actual setup of Read operation.
	  Tasker -> RXbuffer = string;
	  Tasker -> RXcounter = size;
	  Tasker -> RXsize = size;
	 
	  // Setting up busy state for Receive operation.
	  Tasker -> state = SPI_State_Busy_RX;
	 
	  // Enabling SPI peripheral.
	  SPIEnable(Tasker -> SPIx);
	 
	  //Sanity Check, to make sure DR register is empty.
	  int val = Tasker -> SPIx -> DR;
	 
	  //Enabling Interrupts to takeover.
	  SPITXIEnable(Tasker -> SPIx);
	  SPIRXIEnable(Tasker -> SPIx);
 }
 
 /* Slave Transfer Function.																													*/
 /** @brief : The function transmits the passed ins *string through the SPI peripheral				*/
 /**					configured according to the SPI_Handler.																				*/
 /** @param : *Tasker (aka the SPI_Handler) - is the structure which contains the Peripheral, */
 /**					Configuration, RX-TX Buffers and other perimeters required for the communication*/
 /** @param : *string - Contains the string to be transferred through the master.							*/
 /** @param : size - Carries the size of the strig for transfer.															*/
 void SPISlaveTransmit(SPI_Handler *Tasker, uint8_t *string, uint16_t size){
		//For the Actual setup of Write operation.	  
	  Tasker -> TXbuffer = string;
	  Tasker -> TXcounter = size;
	  Tasker -> TXsize = size;
	 
	  // For dummy rx.
	  Tasker -> RXbuffer = string;
	  Tasker -> RXcounter = size;
	  Tasker -> RXsize = size;
	 
	  // Setting up busy state for Receive operation.
	  Tasker -> state = SPI_State_Busy_TX;
	 
	  // Enabling SPI peripheral.
	  SPIEnable(Tasker -> SPIx);
	 
	  //Enabling Interrupts to takeover.
	  SPITXIEnable(Tasker -> SPIx);
	  SPIRXIEnable(Tasker -> SPIx);
 }
 
  /* Slave Receive Function.																																	*/
 /** @brief : The function receives the passed ins *string through the SPI peripheral					*/
 /**					configured according to the SPI_Handler.																				*/
 /** @param : *Tasker (aka the SPI_Handler) - is the structure which contains the Peripheral, */
 /**					Configuration, RX-TX Buffers and other perimeters required for the communication*/
 /** @param : *string - Contains the string to be received through the master.								*/
 /** @param : size - Carries the size of the strig for reception.															*/
 void SPISlaveReceive(SPI_Handler *Tasker, uint8_t *string, uint16_t size){
	  //For the setup of Read operation.
	  Tasker -> RXbuffer = string;
	  Tasker -> RXcounter = size;
	  Tasker -> RXsize = size;
	 
	  // Setting up busy state for Receive operation.
	  Tasker -> state = SPI_State_Busy_RX;
	 
	  // Enabling SPI peripheral.
	  SPIEnable(Tasker -> SPIx);
	 
	  //Enabling Interrupts to takeover.
	  SPIRXIEnable(Tasker -> SPIx);
 }
 
  /* SPI Interrupt Handler																																		*/
	/** @brief : This handles the inerrupt triger and control for SPI configured by SP_Handler	*/
	/** @param : *Tasker - The SPI handler passes in all the requierd configurational infomation*/
	/**						to the Interrrupt Handler.																										*/
 void SPI_InterruptHandler(SPI_Handler *Tasker){
	 // Check the cause of the interrupt.
	 uint16_t  check1 = Tasker  ->  SPIx -> SR;
	 uint16_t  check2 = Tasker  ->  SPIx -> CR2;
	 
	 if((check1 & SPI_FLAGS_TX_EMPTY) && (check2 & SPI_CR2_TXEI_ENABLED)){
		 // DO tx
		 SPITxHandler(Tasker);
	 }else if((check1 & SPI_FLAGS_RX_NOTEMPTY) && (check2 & SPI_CR2_RXNEI_ENABLED)){
		 // Do rx
		 SPIRxHandler(Tasker);

	 }
 }


 