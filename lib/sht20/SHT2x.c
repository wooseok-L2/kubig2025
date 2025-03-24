//==============================================================================
//    S E N S I R I O N   AG,  Laubisruetistr. 50, CH-8712 Staefa, Switzerland
//==============================================================================
// Project   :  SHT2x Sample Code (V1.2)
// File      :  SHT2x.c
// Author    :  MST
// Controller:  AVR
// Compiler  :  AVRStudio
// Brief     :  Sensor layer. Functions for sensor access
//==============================================================================

//---------- Includes ----------------------------------------------------------
#include "SHT2x.h"
#include <util/delay.h>

//  CRC
const uint16_t POLYNOMIAL = 0x131; // P(x)=x^8+x^5+x^4+1 = 100110001
//==============================================================================
uint8_t SHT2x_CheckCrc(uint8_t *data, uint8_t nbrOfBytes, uint8_t checksum)
//==============================================================================
{
    uint8_t crc = 0;
    uint8_t byteCtr;
    // calculates 8-Bit checksum with given polynomial
    for (byteCtr = 0; byteCtr < nbrOfBytes; ++byteCtr)
    {
        crc ^= (data[byteCtr]);
        for (uint8_t bit = 8; bit > 0; --bit)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ POLYNOMIAL;
            else
                crc = (crc << 1);
        }
    }
    if (crc != checksum)
        return CHECKSUM_ERROR;
    else
        return 0;
}

//===========================================================================
uint8_t SHT2x_ReadUserRegister(uint8_t *pRegisterValue)
//===========================================================================
{
    uint8_t checksum;  // variable for checksum byte
    uint8_t error = 0; // variable for error code

    error = Send_start();
    error |= Send_adr(I2C_ADR_W);
    error |= Send_byte(USER_REG_R);
    error |= Send_start();
    error |= Send_adr(I2C_ADR_R);
    error |= Get_byte(pRegisterValue, FALSE);
    error |= Get_byte(&checksum, TRUE);
    error |= SHT2x_CheckCrc(pRegisterValue, 1, checksum);
    Send_stop();

    return error;
}

//===========================================================================
uint8_t SHT2x_WriteUserRegister(uint8_t *pRegisterValue)
//===========================================================================
{
    uint8_t error = 0; // variable for error code

    error = Send_start();
    error |= Send_adr(I2C_ADR_W);
    error |= Send_byte(USER_REG_W);
    error |= Send_byte(*pRegisterValue);
    Send_stop();

    return error;
}

//===========================================================================
uint8_t SHT2x_MeasureHM(etSHT2xMeasureType eSHT2xMeasureType, nt16 *pMeasurand)
//===========================================================================
{
    uint8_t checksum;  // checksum
    uint8_t data[2];   // data array for checksum verification
    uint8_t error = 0; // error variable

    //-- write I2C sensor address and command --
    error = Send_start();
    error |= Send_adr(I2C_ADR_W); // I2C Adr
    switch (eSHT2xMeasureType)
    {
    case HUMIDITY:
        error |= Send_byte(TRIG_RH_MEASUREMENT_HM);
        break;
    case TEMP:
        error |= Send_byte(TRIG_T_MEASUREMENT_HM);
        break;
    default:
        break;
    }
    //-- wait until hold master is released --
    error |= Send_start();
    error |= Send_adr(I2C_ADR_R);
    //-- read two data bytes and one checksum byte --
    error |= Get_byte(&data[0], FALSE);
    error |= Get_byte(&data[1], FALSE);
    pMeasurand->s16.u8H = data[0];
    pMeasurand->s16.u8L = data[1];
    error |= Get_byte(&checksum, TRUE);
    error |= SHT2x_CheckCrc(data, 2, checksum);
    Send_stop();

    return error;
}

//===========================================================================
uint8_t SHT2x_MeasurePoll(etSHT2xMeasureType eSHT2xMeasureType, nt16 *pMeasurand)
//===========================================================================
{
    uint8_t checksum;  // checksum
    uint8_t data[2];   // data array for checksum verification
    uint8_t error = 0; // error variable
    uint8_t i = 0;     // counting variable

    //-- write I2C sensor address and command --
    error = Send_start();
    error |= Send_adr(I2C_ADR_W); // I2C Adr
    switch (eSHT2xMeasureType)
    {
    case HUMIDITY:
        error |= Send_byte(TRIG_RH_MEASUREMENT_POLL);
        break;
    case TEMP:
        error |= Send_byte(TRIG_T_MEASUREMENT_POLL);
        break;
    default:
        break;
    }
    //-- poll every 10ms for measurement ready. Timeout after 20 retries (200ms)--
    do
    {
        error = Send_start();
        _delay_ms(10); // delay 10ms
        if (i++ >= 20)
            break;
    } while (Send_adr(I2C_ADR_R) != SUCCESS);
    if (i >= 20)
        error |= TIME_OUT_ERROR;

    //	error = Send_start();
    //	error |= Send_adr(I2C_ADR_R);
    //-- read two data bytes and one checksum byte --
    error |= Get_byte(&data[0], FALSE);
    error |= Get_byte(&data[1], FALSE);
    pMeasurand->s16.u8H = data[0];
    pMeasurand->s16.u8L = data[1];
    error |= Get_byte(&checksum, TRUE);
    error |= SHT2x_CheckCrc(data, 2, checksum);
    Send_stop();

    return error;
}

//===========================================================================
uint8_t SHT2x_SoftReset()
//===========================================================================
{
    uint8_t error = 0; // error variable

    error = Send_start();
    error |= Send_adr(I2C_ADR_W);
    error |= Send_byte(SOFT_RESET);
    Send_stop();

    _delay_ms(15); // wait till sensor has restarted

    return error;
}

//==============================================================================
float SHT2x_CalcRH(uint16_t u16sRH)
//==============================================================================
{
    float humidityRH; // variable for result

    u16sRH &= ~0x0003; // clear bits [1..0] (status bits)
    //-- calculate relative humidity [%RH] --

    humidityRH = -6.0 + 125.0 / 65536 * (float)u16sRH; // RH= -6 + 125 * SRH/2^16
    return humidityRH;
}

//==============================================================================
float SHT2x_CalcTemperatureC(uint16_t u16sT)
//==============================================================================
{
    float temperatureC; // variable for result

    u16sT &= ~0x0003; // clear bits [1..0] (status bits)

    //-- calculate temperature [�C] --
    temperatureC = -46.85 + 175.72 / 65536 * (float)u16sT; // T= -46.85 + 175.72 * ST/2^16
    return temperatureC;
}

//==============================================================================
uint8_t SHT2x_GetSerialNumber(uint8_t *u8SerialNumber)
//==============================================================================
{
    uint8_t error = 0; // error variable
    uint8_t data;

    /// Read from memory location 1
    error = Send_start();
    error |= Send_adr(I2C_ADR_W); // I2C address
    error |= Send_byte(0xFA);     // Command for readout on-chip memory
    error |= Send_byte(0x0F);     // on-chip memory address
    error = Send_start();
    error |= Send_adr(I2C_ADR_R);                 // I2C address
    error |= Get_byte(&u8SerialNumber[5], FALSE); // Read SNB_3

    error |= Get_byte(&data, FALSE);              // Read CRC SNB_3 (CRC is not analyzed)
    error |= Get_byte(&u8SerialNumber[4], FALSE); // Read SNB_2
    error |= Get_byte(&data, FALSE);              // Read CRC SNB_2 (CRC is not analyzed)
    error |= Get_byte(&u8SerialNumber[3], FALSE); // Read SNB_1
    error |= Get_byte(&data, FALSE);              // Read CRC SNB_1 (CRC is not analyzed)
    error |= Get_byte(&u8SerialNumber[2], FALSE); // Read SNB_0

    error |= Get_byte(&data, TRUE); // Read CRC SNB_0 (CRC is not analyzed)
    Send_stop();

    // Read from memory location 2
    error = Send_start();
    error |= Send_adr(I2C_ADR_W); // I2C address
    error |= Send_byte(0xFC);     // Command for readout on-chip memory
    error |= Send_byte(0xC9);     // on-chip memory address
    error = Send_start();
    error |= Send_adr(I2C_ADR_R);                 // I2C address
    error |= Get_byte(&u8SerialNumber[1], FALSE); // Read SNC_1
    error |= Get_byte(&u8SerialNumber[0], FALSE); // Read SNC_0
    error |= Get_byte(&data, FALSE);              // Read CRC SNC0/1 (CRC is not analyzed)
    error |= Get_byte(&u8SerialNumber[7], FALSE); // Read SNA_1
    error |= Get_byte(&u8SerialNumber[6], FALSE); // Read SNA_0
    error |= Get_byte(&data, TRUE);               // Read CRC SNA0/1 (CRC is not analyzed)
    Send_stop();

    return error;
}

//==============================================================================
uint8_t SHT2x_Init(void)
//==============================================================================
{
    uint8_t error = 0;             // error variable
    uint8_t userRegister;          // variable for user register
    uint8_t SerialNumber_SHT2x[8]; // 64bit serial number

    error = 0; // reset error status
    // --- Reset sensor by command ---
    error |= SHT2x_SoftReset();

    // --- Read the sensors serial number (64bit) ---
    error |= SHT2x_GetSerialNumber(SerialNumber_SHT2x);

    // --- Set Resolution e.g. RH 10bit, Temp 13bit ---
    error |= SHT2x_ReadUserRegister(&userRegister); // get actual user reg
    userRegister = (userRegister & ~SHT2x_RES_MASK) | SHT2x_RES_10_13BIT;
    error |= SHT2x_WriteUserRegister(&userRegister); // write changed user reg

    // --- check end of battery status (eob)---
    if ((userRegister & SHT2x_EOB_MASK) == SHT2x_EOB_ON)
        return LOW_BAT_ERROR;

    return error;
}