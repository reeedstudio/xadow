/*-----------------------------------------------------------------------------------
** demo of RTC, display time
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

unsigned char bcdToDec(unsigned char val)
{
    return ( (val/16*10) + (val%16) );
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
    dta[4]  = bcdToDec(Wire.read());        // Need to change this if 12 hour am/pm
    dta[3]  = bcdToDec(Wire.read());
    dta[2]  = bcdToDec(Wire.read());
    dta[1]  = bcdToDec(Wire.read());
    dta[0]  = bcdToDec(Wire.read());

    return 1;
}


void setup()
{
    Serial.begin(115200);
    
    while(!Serial);
    Xadow.init();
    Wire.begin();
    
    delay(1000);
    cout << "hello world" << endl;
}

void loop()
{
    unsigned char td[7] = {0, 0, 0, 0, 0, 0, 0};            // td[] = {year, month, day, week, hour, min, sec};
    getTime(td);
    delay(1000);

    cout << "20" << td[0] << '/' << td[1] << '/' << td[2] << tabl;
    cout << td[4] << ":" << td[5] << ":" << td[6] << endl;
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/