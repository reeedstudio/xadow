/*
  xadow.cpp
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-6-17

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Arduino.h>
#include <Wire.h>
#include <Streaming.h>

#include "xadowDfs.h"
#include "xadow.h"

/*********************************************************************************************************
** Function name:           init
** Descriptions:            init
*********************************************************************************************************/
void xadow::init()
{
#if EN_BARO || EN_ACC || EN_OLED
    Wire.begin();
#endif

#if EN_ACC
    adxl_init();
#endif

#if EN_OLED
    OLED.init();
#endif
}

/*********************************************************************************************************
** Function name:           init_io
** Descriptions:            init_io
*********************************************************************************************************/
void xadow::init_io()
{

}


/*********************************************************************************************************
** Function name:           bmp085Read
** Descriptions:            bmp085Read
*********************************************************************************************************/
#if EN_BARO
char xadow::bmp085Read(unsigned char address)
{
    unsigned char data;

    Wire.beginTransmission(ADDRBARO);
    Wire.write(address);
    Wire.endTransmission();

    Wire.requestFrom(ADDRBARO, 1);
    while(!Wire.available());
    return Wire.read();
}
#endif

/*********************************************************************************************************
** Function name:           bmp085ReadInt
** Descriptions:            bmp085ReadInt
*********************************************************************************************************/
#if EN_BARO
int xadow::bmp085ReadInt(unsigned char address)
{
    unsigned char msb, lsb;

    Wire.beginTransmission(ADDRBARO);
    Wire.write(address);
    Wire.endTransmission();
    Wire.requestFrom(ADDRBARO, 2);

    while(Wire.available()<2);
    msb = Wire.read();
    lsb = Wire.read();

    return (int) msb<<8 | lsb;
}
#endif

/*********************************************************************************************************
** Function name:           getBaro
** Descriptions:            getBaro
*********************************************************************************************************/
#if EN_BARO
long xadow::getBaro()
{

    long b5;
    long x1, x2;
    unsigned int ac5 = bmp085ReadInt(0xB2);
    int ac6 = bmp085ReadInt(0xB4);
    int mc = bmp085ReadInt(0xBC);
    int md = bmp085ReadInt(0xBE);

    // make ut
    unsigned int ut;
    // Write 0x2E into Register 0xF4
    // This requests a temperature reading
    Wire.beginTransmission(ADDRBARO);
    Wire.write(0xF4);
    Wire.write(0x2E);
    Wire.endTransmission();
    // Wait at least 4.5ms
    delay(5);
    // Read two bytes from registers 0xF6 and 0xF7
    ut = bmp085ReadInt(0xF6);

    x1 = (((long)ut - (long)ac6)*(long)ac5) >> 15;
    x2 = ((long)mc << 11)/(x1 + md);
    b5 = (x1 + x2);

    long x3, b3, b6, p;
    unsigned long b4, b7;

    int ac1 = bmp085ReadInt(0xAA);
    int ac2 = bmp085ReadInt(0xAC);
    int ac3 = bmp085ReadInt(0xAE);
    unsigned int ac4 = bmp085ReadInt(0xB0);
    int b1 = bmp085ReadInt(0xB6);
    int b2 = bmp085ReadInt(0xB8);

    b6 =  b5-4000;
    // Calculate B3
    x1 = (b2 * (b6 * b6)>>12)>>11;
    x2 = (ac2 * b6)>>11;
    x3 = x1 + x2;
    b3 = (((((long)ac1)*4 + x3)<<0) + 2)>>2;

    // Calculate B4
    x1 = (ac3 * b6)>>13;
    x2 = (b1 * ((b6 * b6)>>12))>>16;
    x3 = ((x1 + x2) + 2)>>2;
    b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;

    unsigned char msb, lsb, xlsb;
    unsigned long up = 0;
    // Request a pressure reading w/ oversampling setting
    Wire.beginTransmission(ADDRBARO);
    Wire.write(0xF4);
    Wire.write(0x34 + (0<<6));
    Wire.endTransmission();
    // Wait for conversion, delay time dependent on 0
    delay(2 + (3<<0));
    // Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
    msb     = bmp085Read(0xF6);
    lsb     = bmp085Read(0xF7);
    xlsb    = bmp085Read(0xF8);
    up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-0);

    b7 = ((unsigned long)(up - b3) * (50000>>0));

    p = (b7<0x80000000) ? (b7<<1)/b4 : (b7/b4)<<1;
    x1 = (p>>8) * (p>>8);
    x1 = (x1 * 3038)>>16;
    x2 = (-7357 * p)>>16;
    p += (x1 + x2 + 3791)>>4;

    return p;

}
#endif

/*********************************************************************************************************
** Function name:           adxl_init
** Descriptions:            adxl_init
*********************************************************************************************************/
#if EN_ACC
void xadow::adxl_init()
{
    //--------------X
    Wire.beginTransmission(ADDRACC);
    Wire.write(Register_2D);
    Wire.write(8); //measuring enable
    Wire.endTransmission(); // stop transmitting
}
#endif

/*********************************************************************************************************
** Function name:           readAcc
** Descriptions:            readAcc
*********************************************************************************************************/
#if EN_ACC
unsigned char xadow::readAcc(double *Xg, double *Yg, double *Zg)
{
    int X_out;
    int Y_out;
    int Z_out;
    Wire.beginTransmission(ADDRACC); // transmit to device
    Wire.write(Register_X0);
    Wire.write(Register_X1);
    Wire.endTransmission();
    Wire.requestFrom(ADDRACC,2);
    if(Wire.available()<=2)
    {
        int X0 = Wire.read();
        int X1 = Wire.read();
        X1=X1<<8;
        X_out=X0+X1;
    }
    //------------------Y
    Wire.beginTransmission(ADDRACC); // transmit to device
    Wire.write(Register_Y0);
    Wire.write(Register_Y1);
    Wire.endTransmission();
    Wire.requestFrom(ADDRACC,2);
    if(Wire.available()<=2)
    {
        int Y0 = Wire.read();
        int Y1 = Wire.read();
        Y1=Y1<<8;
        Y_out=Y0+Y1;
    }
    //------------------Z
    Wire.beginTransmission(ADDRACC); // transmit to device
    Wire.write(Register_Z0);
    Wire.write(Register_Z1);
    Wire.endTransmission();
    Wire.requestFrom(ADDRACC,2);
    if(Wire.available()<=2)
    {
        int Z0 = Wire.read();
        int Z1 = Wire.read();
        Z1=Z1<<8;
        Z_out=Z0+Z1;
    }
    *Xg=X_out/256.0;
    *Yg=Y_out/256.0;
    *Zg=Z_out/256.0;
}
#endif

xadow Xadow;

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/