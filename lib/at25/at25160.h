#ifndef _AT25160_H_
#define _AT25160_H_

#include <avr/io.h>

#define AT25160_CS_LOW (PORTB &= 0xFE)
#define AT25160_CS_HIGH (PORTB |= 0x01)

#define WPB_MASK 0x1C
#define NONE (0x00 << 2)
#define ALL (0x01 << 2)

/* Instruction Codes */
#define WREN 0x06
#define WRDI 0x04
#define RDSR 0x05
#define WRSR 0x01
#define READ 0x03
#define PROGRAM 0x02

/* Status Register Bit */
#define RDY 0  /* Busy Indicator Bit */
#define WEN 1  /* Write Enable Bit */
#define BP0 2  /* Block Write Protect Bit */
#define WPEN 7 /* Software Write Protect Enable Bit */

/* Interrupt Service Status */
#define INSTRUCTION 0x01   /* The op_code has been transferred */
#define ADDRESS 0x02       /* One of the address bytes has been transferred */
#define DATA 0x04          /* The current data byte has been transferred */
#define READY_TO_SEND 0x00 /* The SPI interface is ready to send */

/*Access Status */
#define TRANSFER_STARTED 0x00   /* The write access is started whithout error */
#define TRANSFER_COMPLETED 0x01 /* The read access is completed whithout error */
#define OUT_OF_RANGE 0xFD       /* The address is out of range of available memory */
#define DATA_WR_PROTECTED 0xFE  /* The write access aborted due to write protection */
#define BUSY 0xFF               /* The SPI memory or the SPI interface is busy */

/* Error code */
#define WRITE_PROTECTED 0x1 /* The address matches a write protected location. */
#define WRITE_ALLOWED 0x0   /* The address does not matche a write protected location. */
#define HW_PROTECTED 0x2    /* The serial memory is hardware write protected. */

void SPI_Init();
void at25160_WREN();
void at25160_Ready(); // 다음일할 준비가 되는고?
void at25160_Write_Byte(unsigned int addr, unsigned char data);
unsigned char at25160_Read_Byte(unsigned int addr);
void at25160_Write_Arry(unsigned int addr, unsigned char *BPdata, unsigned char size);
void at25160_Read_Arry(unsigned int addr, unsigned char *BPbuf, unsigned char size);

#endif