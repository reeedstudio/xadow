/*-----------------------------------------------------------------------------------
** demo of xadow: smile, use OLED, Barometer, Vibrator and AccelerMeter
** you should download ADXL345 Library here: http://www.seeedstudio.com/wiki/Xadow_3-Axis_Accelerometer
** download SeeedOled.h: http://www.seeedstudio.com/wiki/Xadow_OLED
** loovee 2013-6-18
** https://github.com/reeedstudio/xadow
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public
** License along with this library; if not, write to the Free Software
** Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
**--------------------------------------------------------------------------------*/
#include <Wire.h>
#include <ADXL345.h>
#include <SeeedOLED.h>

#include "smile.h"
#include "xadow.h"

#define BAROMETERADDRESS  0x77  // I2C address of BMP085

#define STIDLE          1
#define STSHAKE         2
#define STSMILE         3

unsigned char state = STIDLE;

int cnt_noAcc = 0;
int cnt_Acc   = 0;
int cnt_baro  = 0;


ADXL345 adxl;       //variable adxl is an instance of the ADXL345 library

void adxl_init()
{
    adxl.powerOn();

    //set activity/ inactivity thresholds (0-255)
    adxl.setActivityThreshold(75); //62.5mg per increment
    adxl.setInactivityThreshold(75); //62.5mg per increment
    adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?

    //look of activity movement on this axes - 1 == on; 0 == off
    adxl.setActivityX(1);
    adxl.setActivityY(1);
    adxl.setActivityZ(1);

    //look of inactivity movement on this axes - 1 == on; 0 == off
    adxl.setInactivityX(1);
    adxl.setInactivityY(1);
    adxl.setInactivityZ(1);

    //look of tap movement on this axes - 1 == on; 0 == off
    adxl.setTapDetectionOnX(0);
    adxl.setTapDetectionOnY(0);
    adxl.setTapDetectionOnZ(1);

    //set values for what is a tap, and what is a double tap (0-255)
    adxl.setTapThreshold(50); //62.5mg per increment
    adxl.setTapDuration(15); //625us per increment
    adxl.setDoubleTapLatency(80); //1.25ms per increment
    adxl.setDoubleTapWindow(200); //1.25ms per increment

    //set values for what is considered freefall (0-255)
    adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
    adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment

    //setting all interrupts to take place on int pin 1
    //I had issues with int pin 2, was unable to reset it
    adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
    adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
    adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
    adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
    adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );

    //register interrupt actions - 1 == on; 0 == off
    adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
    adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
    adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  1);
    adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   1);
    adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);
}

void oled_init()
{
    SeeedOled.init();                               // initialze SEEED OLED display
    SeeedOled.setTextXY(0,0);                       // Set the cursor to Xth Page, Yth Column

}

// Read 1 byte from the BMP085 at 'address'
char bmp085Read(unsigned char address)
{
    unsigned char data;
    Wire.beginTransmission(BAROMETERADDRESS);
    Wire.write(address);
    Wire.endTransmission();

    Wire.requestFrom(BAROMETERADDRESS, 1);
    while(!Wire.available());
    return Wire.read();
}

// Read 2 bytes from the BMP085
// First byte will be from 'address'
// Second byte will be from 'address'+1
inline int bmp085ReadInt(unsigned char address)
{
    unsigned char msb, lsb;
    Wire.beginTransmission(BAROMETERADDRESS);
    Wire.write(address);
    Wire.endTransmission();
    Wire.requestFrom(BAROMETERADDRESS, 2);
    while(Wire.available()<2);
    msb = Wire.read();
    lsb = Wire.read();
    return (int) msb<<8 | lsb;
}

long bmp085GetTempPres()
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
    Wire.beginTransmission(BAROMETERADDRESS);
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
    Wire.beginTransmission(BAROMETERADDRESS);
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
unsigned char getAcc()
{
    int x, y, z;
    adxl.readXYZ(&x, &y, &z);                           //read the accelerometer values

    x = abs(x);
    y = abs(y);
    z = abs(z);

    if(x>500 || y>500 || z>500)
    {
        cout << "hello" << endl << x << '\t' << y << '\t' << z << endl;
        return 1;
    }
    
    return 0;
}

void dispSmile()
{
    // add code here, smile
    //SeeedOled.setInverseDisplay();                    // Set Display to inverse mode
    SeeedOled.clearDisplay();
    SeeedOled.drawBitmap(SeeedLogo,1024);               // 1024 = 128 Pixels * 64 Pixels / 8
}

void dispPress(long press)
{

    SeeedOled.setTextXY(3,4);                           // Set the cursor to Xth Page, Yth Column
    
    float fPress = press/1000.0;
    
    SeeedOled.putFloat(fPress, 2);
    SeeedOled.putString("kPa");
    
}

void stateMachine()
{
    switch(state)
    {
        case STIDLE:

        // add code here, refresh baro per second
        cnt_baro++;
        if(cnt_baro > 300)
        {
            long tmp = bmp085GetTempPres();
            cout << "press = " << tmp << endl;
            dispPress(tmp);
            cnt_baro = 0;
        }

        if(getAcc())
        {
            cout << "getAcc"<<endl;
            state = STSHAKE;
        }

        break;

        case STSHAKE:

        // shaking... while stop shake, goto STSMILE
        if(getAcc())
        {
            cnt_Acc++;
            cnt_noAcc = 0;
        }
        else
        {
            cnt_noAcc++;
            if(cnt_noAcc > 20)
            {
                cout << "goto STSMILE"<<endl;

                cout << "cnt_Acc = " << cnt_Acc << endl;

                state = STSMILE;

                state = cnt_Acc>2 ? STSMILE : STIDLE;
                cnt_Acc = 0;
                cnt_noAcc = 0;
            }
        }

        break;

        case STSMILE:

        dispSmile();
        delay(1000);
        state = STIDLE;
        
        SeeedOled.clearDisplay();                               // clear oled

        break;

        default:
        ;
    }
}

void setup()
{
    Serial.begin(115200);
    while(!Serial);
   
    delay(1000);

    Wire.begin();
    adxl_init();
    oled_init();
}

void loop()
{
    stateMachine();
    delay(3);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/