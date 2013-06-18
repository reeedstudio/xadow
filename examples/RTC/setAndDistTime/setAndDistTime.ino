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

unsigned char td[] = {13, 6, 18, TUE, 19, 21, 30};  // set time here: year, month ,day, week, hour, minute, second

void setup()
{
    Serial.begin(115200);
    while(!Serial);
    Xadow.init();                                   // init xadow
    Xadow.setTime(td);                              // set RTC time
    cout << "init over" << endl;

}


void loop()
{

    Xadow.getTime(td);
    delay(1000);
    
    cout << "20" << td[0] << '/' << td[1] << '/' << td[2] << tabl;
    cout << td[4] << ":" << td[5] << ":" << td[6] << endl;
    
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/