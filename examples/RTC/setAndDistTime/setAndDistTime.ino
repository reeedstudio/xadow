/*-----------------------------------------------------------------------------------
** demo of xadow RTC, set time and display
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

#include "debug_x.h"
#include "xadow.h"
#include "xadowDfs.h"

#define ADDRRTC         0x68

#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6
#define SUN 7

unsigned char decToBcd(unsigned char val)
{
    return ( (val/10*16) + (val%10) );
}


unsigned char bcdToDec(unsigned char val)
{
    return ( (val/16*10) + (val%16) );
}

unsigned char setTime(unsigned char *dta)
{

    Wire.beginTransmission(ADDRRTC);
    Wire.write((unsigned char)0x00);
    Wire.write(decToBcd(dta[6]));           // 0 to bit 7 starts the clock
    Wire.write(decToBcd(dta[5]));
    Wire.write(decToBcd(dta[4]));           // If you want 12 hour am/pm you need to set bit 6
    Wire.write(decToBcd(dta[3]));
    Wire.write(decToBcd(dta[2]));
    Wire.write(decToBcd(dta[1]));
    Wire.write(decToBcd(dta[0]));
    Wire.endTransmission();

    return 1;
}

unsigned char getTime(unsigned char *dta)
{
    // Reset the register pointer
    Wire.beginTransmission(ADDRRTC);
    Wire.write((unsigned char)0x00);
    Wire.endTransmission();
    Wire.requestFrom(ADDRRTC, 7);
    // A few of these need masks because certain bits are control bits
    dta[6]  = bcdToDec(Wire.read());
    dta[5]  = bcdToDec(Wire.read());
    dta[4]  = bcdToDec(Wire.read());                // Need to change this if 12 hour am/pm
    dta[3]  = bcdToDec(Wire.read());
    dta[2]  = bcdToDec(Wire.read());
    dta[1]  = bcdToDec(Wire.read());
    dta[0]  = bcdToDec(Wire.read());

    return 1;
}

unsigned char td[] = {13, 6, 18, TUE, 19, 21, 30};  // set time here: year, month ,day, week, hour, minute, second

void setup()
{
    Serial.begin(115200);
    while(!Serial);
    Xadow.init();                                   // init xadow
    Wire.begin();                                   // init I2C
    setTime(td);                                    // set RTC time
    cout << "init over" << endl;

}


void loop()
{

    getTime(td);
    delay(1000);
    
    cout << "20" << td[0] << '/' << td[1] << '/' << td[2] << tabl;
    cout << td[4] << ":" << td[5] << ":" << td[6] << endl;
    
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/