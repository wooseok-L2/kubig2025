/********************** AVR155 : Accessing I2C LCD display using the AVR TWI ***********************

Device      : ATmega163

File name   : TWI_driver.h

Ver nr.     : 1.0

Description : Header file for TWI_driver.c

Author      : Asmund Saetre

Change log  : Created 01.05.2000  AS

;**************************************************************************************************/
#ifndef TWI_DRIVER_H
#define TWI_DRIVER_H
/****************************************************************************
    Include Files
****************************************************************************/
#include <avr/io.h>

/****************************************************************************
    Function definitions
****************************************************************************/
unsigned char Send_byte(unsigned char);        // Send one byte
unsigned char Get_byte(unsigned char *, char); // Receive one byte
unsigned char Send_start(void);                // Send a Start condition
unsigned char Send_adr(unsigned char);         // Send a Slave adr.
void Send_stop(void);                          // Send a Stop condition
void Wait_TWI_int(void);                       // Wait for TWI interrupt to occur
void Reset_TWI(void);                          // Reset the TWI module and
                                               // release the bus
void Init_TWI(void);                           // Initilaize TWI

#define TRUE 1
#define FALSE 0
/****************************************************************************
Bit and byte definitions
****************************************************************************/
#define W 0 // Data transfer direction WRITE
#define R 1 // Data transfer direction READ
#define SUCCESS 0xFF

/****************************************************************************
I2C acknowledge
****************************************************************************/
#define LAST 0
#define NO_LAST 1

/****************************************************************************
TWI Stautus register definitions
****************************************************************************/
// General Master staus codes
#define START 0x08     // START has been transmitted
#define REP_START 0x10 // Repeated START has been
                       // transmitted
// Master Transmitter staus codes
#define MTX_ADR_ACK 0x18   // SLA+W has been tramsmitted
                           // and ACK received
#define MTX_ADR_NACK 0x20  // SLA+W has been tramsmitted
                           // and NACK received
#define MTX_DATA_ACK 0x28  // Data byte has been tramsmitted
                           // and ACK received
#define MTX_DATA_NACK 0x30 // Data byte has been tramsmitted
                           // and NACK received
#define MTX_ARB_LOST 0x38  // Arbitration lost in SLA+W or
                           // data bytes
// Master Receiver staus codes
#define MRX_ARB_LOST 0x38  // Arbitration lost in SLA+R or
                           // NACK bit
#define MRX_ADR_ACK 0x40   // SLA+R has been tramsmitted
                           // and ACK received
#define MRX_ADR_NACK 0x48  // SLA+R has been tramsmitted
                           // and NACK received
#define MRX_DATA_ACK 0x50  // Data byte has been received
                           // and ACK tramsmitted
#define MRX_DATA_NACK 0x58 // Data byte has been received
                           // and NACK tramsmitted

#endif