#include "at25160.h"
#include <avr/io.h>
#include <util/delay.h>

void SPI_Init()
{
    DDRB |= 0x07;  // ��Ʈ�� ����, miso �Է¼���
    PORTB |= 0x01; // ~cs = 1

    SPCR = 0x50;
    SPSR = 0x00;
}

void at25160_WREN()
{
    AT25160_CS_LOW; // Ĩ����Ʈ
    SPDR = WREN;    // wren����
    while ((SPSR & 0x80) == 0x00)
        ;            // ����Ÿ ���ۿϷ�?
    AT25160_CS_HIGH; // cs high �� �Ǿ�� �������� ���� ����
}

void at25160_Ready()
{
    unsigned char data;

    do
    {
        AT25160_CS_LOW;
        SPDR = RDSR;
        while ((SPSR & 0x80) == 0x00)
            ;

        SPDR = 0;
        while ((SPSR & 0x80) == 0x00)
            ;

        data = SPDR;
        SPDR = 0;
        while ((SPSR & 0x80) == 0x00)
            ;

        AT25160_CS_HIGH;

    } while ((data & 1 << (RDY))); // �������͸� �о�� �غ���°� �Ǿ����������� ����
}

void at25160_Write_Byte(unsigned int addr, unsigned char data)
{
    at25160_WREN();

    AT25160_CS_LOW;
    SPDR = PROGRAM; // ���� ����
    while ((SPSR & 0x80) == 0x00)
        ;

    SPDR = ((addr >> 8) & 0xff); // �ּ�
    while ((SPSR & 0x80) == 0x00)
        ;

    SPDR = ((addr) & 0xff);
    while ((SPSR & 0x80) == 0x00)
        ;

    SPDR = data; // ����Ÿ
    while ((SPSR & 0x80) == 0x00)
        ;

    AT25160_CS_HIGH; // cs high �� �Ǿ�� �Է��� ������ ����
    at25160_Ready();
}

unsigned char at25160_Read_Byte(unsigned int addr)
{
    unsigned char data = 0;
    AT25160_CS_LOW;

    SPDR = READ; // �б⼱��
    while ((SPSR & 0x80) == 0x00)
        ;

    SPDR = ((addr >> 8) & 0xff); // �ּ�
    while ((SPSR & 0x80) == 0x00)
        ;

    SPDR = ((addr) & 0xff); // �ּ�
    while ((SPSR & 0x80) == 0x00)
        ;

    SPDR = 0;
    while ((SPSR & 0x80) == 0x00)
        ;

    data = SPDR; // ����Ÿ

    AT25160_CS_HIGH;
    return data;
}

void at25160_Write_Arry(unsigned int addr, unsigned char *BPdata, unsigned char size)
{
    at25160_WREN();

    AT25160_CS_LOW;
    SPDR = PROGRAM; // ���� ����
    while ((SPSR & 0x80) == 0x00)
        ;

    SPDR = ((addr >> 8) & 0xff); // �ּ�
    while ((SPSR & 0x80) == 0x00)
        ;

    SPDR = ((addr) & 0xff);
    while ((SPSR & 0x80) == 0x00)
        ;

    for (; size > 0; size--, BPdata++)
    {
        SPDR = *BPdata; // ����Ÿ
        while ((SPSR & 0x80) == 0x00)
            ;
        if (!((++addr) & 0xFF))
            break; // ������ �������̸� ���̻� �����ʰ� ����
    }

    AT25160_CS_HIGH;
    at25160_Ready();
}

void at25160_Read_Arry(unsigned int addr, unsigned char *BPbuf, unsigned char size)
{
    AT25160_CS_LOW;
    SPDR = READ; // ���� ����
    while ((SPSR & 0x80) == 0x00)
        ;

    SPDR = ((addr >> 8) & 0xff); // �ּ�
    while ((SPSR & 0x80) == 0x00)
        ;

    SPDR = ((addr) & 0xff);
    while ((SPSR & 0x80) == 0x00)
        ;

    for (; size > 0; size--, BPbuf++)
    {
        SPDR = 0; // ����Ÿ
        while ((SPSR & 0x80) == 0x00)
            ;
        *BPbuf = SPDR; //*BPbuf = BPbuf[] �� ����. *�� ���� ������ �߸𸦻�...
        if (!((++addr) & 0xFF))
            break;
    }

    AT25160_CS_HIGH;
}