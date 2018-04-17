#include "STM32F4_I2C.h"


/**************************************************************************************************/
/*																			Static Functions																					*/
/**************************************************************************************************/
static void I2CConfigClockspeed(I2C_TypeDef *I2Cx, uint32_t ClockSpeed){

}

static void I2CConfigDutycycle(I2C_TypeDef *I2Cx, uint32_t DutyCycle){

}

static void I2CConfigAddress(I2C_TypeDef *I2Cx, uint32_t OwnAddress, uint32_t AddressingMode, uint32_t OwnAddress2){

}

static void I2CConfigGenCallMode(I2C_TypeDef *I2Cx, uint32_t GenCallMode){

}

static void I2CConfigStretch(I2C_TypeDef *I2Cx, uint32_t NoStretchMode){

}

static void I2CConfigAck(I2C_TypeDef *I2Cx, uint32_t Ack){

}

static void I2CEnable(I2C_TypeDef *I2Cx){

}

static void I2CDisable(I2C_TypeDef *I2Cx){

}

static void I2CGenerateStart(I2C_TypeDef *I2Cx){

}

static void I2CGenerateStop(I2C_TypeDef *I2Cx){

}

static void I2CBUFFIEnable(I2C_TypeDef *I2Cx){

}

static void I2CERRIEnable(I2C_TypeDef *I2Cx){

}

static void I2CEVTIEnable(I2C_TypeDef *I2Cx){

}

static void I2CBUFFIDisable(I2C_TypeDef *I2Cx){

}

static void I2CERRIDisable(I2C_TypeDef *I2Cx){

}

static void I2CEVTIDisable(I2C_TypeDef *I2Cx){

}

static void I2CDMAEnable(I2C_TypeDef *I2Cx){

}

static void I2CDMADisable(I2C_TypeDef *I2Cx){

}

/**************************************************************************************************/
/*																						APIs																								*/
/**************************************************************************************************/

 /* Initialisation Function.																																			*/
 /** @brief : The function initialises the I2C peripheral according to the passed in peimeter.		*/
 /** @param : *Tasker (aka the I2C_Handler) is the structure which contains the Peripheral,   		*/
 /**					Configuration, Buffers and other perimeters required for the communication					*/
void I2CInit(I2C_Handler *Tasker){
		I2CConfigClockspeed(Tasker ->I2Cx, Tasker ->I2CConf ->ClockSpeed);
		I2CConfigDutycycle(Tasker->I2Cx, Tasker -> I2CConf -> DutyCycle);
		I2CConfigAddress(Tasker -> I2Cx, Tasker -> I2CConf -> OwnAddress1, Tasker -> I2CConf-> AddressingMode, Tasker -> I2CConf -> OwnAddress2);
		I2CConfigGenCallMode(Tasker -> I2Cx, Tasker ->I2CConf -> GeneralCallMode);
		I2CConfigStretch(Tasker -> I2Cx, Tasker -> I2CConf -> NoStretchMode );
		I2CConfigAck(Tasker -> I2Cx, Tasker -> I2CConf -> ackEnable);
}

 /* Master Transfer Function Function.																														*/
 /** @brief : The function transmits the passed ins *string through the I2C peripheral						*/
 /**					configured according to the I2C_Handler.																						*/
 /** @param : *Tasker (aka the I2C_Handler) - is the structure which contains the Peripheral, 		*/
 /**					Configuration, Buffers and other perimeters required for the communication*/
 /** @param : *string - Contains the string to be transmitted through the master.									*/
 /** @param : size - Carries the size of the strig for transmission.															*/
void I2CMasterTransmit(I2C_Handler *Tasker, uint8_t *string, uint8_t size){

}

  /* Master Receive Function Function.																														*/
 /** @brief : The function receives the passed ins *string through the I2C peripheral							*/
 /**					configured according to the I2C_Handler.																						*/
 /** @param : *Tasker (aka the I2C_Handler) - is the structure which contains the Peripheral, 		*/
 /**					Configuration, Buffers and other perimeters required for the communication*/
 /** @param : *string - Contains the string to be received through the master.										*/
 /** @param : size - Carries the size of the strig for reception.																	*/
void I2CMasterReceive(I2C_Handler *Tasker, uint8_t *string, uint8_t size){

}

 /* Slave Transfer Function.																													*/
 /** @brief : The function transmits the passed ins *string through the I2C peripheral						*/
 /**					configured according to the I2C_Handler.																						*/
 /** @param : *Tasker (aka the I2C_Handler) - is the structure which contains the Peripheral, 		*/
 /**					Configuration, Buffers and other perimeters required for the communication*/
 /** @param : *string - Contains the string to be transferred through the master.									*/
 /** @param : size - Carries the size of the strig for transfer.																	*/
void I2CSlaveTransmit(I2C_Handler *Tasker, uint8_t *string, uint8_t size){

}

  /* Slave Receive Function.																																			*/
 /** @brief : The function receives the passed ins *string through the I2C peripheral							*/
 /**					configured according to the I2C_Handler.																						*/
 /** @param : *Tasker (aka the I2C_Handler) - is the structure which contains the Peripheral, 		*/
 /**					Configuration, Buffers and other perimeters required for the communication*/
 /** @param : *string - Contains the string to be received through the master.										*/
 /** @param : size - Carries the size of the strig for reception.																	*/
void I2CSlaveReceive(I2C_Handler *Tasker, uint8_t *string, uint8_t size){

}

 /* I2C Event Interrupt Handler																																		*/
 /** @brief : This handles the inerrupt triger and control for I2C configured by SP_Handler				*/
 /** @param : *Tasker - The I2C handler passes in all the requierd configurational infomation			*/
 /**						to the Interrrupt Handler.																												*/
void I2CEventInterruptHandler(I2C_Handler *Tasker){

}

 /* I2C Error Interrupt Handler																																		*/
 /** @brief : This handles the error inerrupt triger and control for I2C configured by SP_Handler	*/
 /** @param : *Tasker - The I2C handler passes in all the requierd configurational infomation			*/
 /**						to the Interrrupt Handler.																												*/
void I2CErrorInterruptHandler(I2C_Handler *Tasker){

}
