/*-----------------------------------------------------------------------------------
** demo of xadow oled, print number
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

#include "xadow.h"
#include "xadowDfs.h"

void setup()
{
    Xadow.init();

    Xadow.OLED.clearDisplay();           // clear the screen and set start position to top left corner
    Xadow.OLED.setNormalDisplay();       // Set display to Normal mode
    Xadow.OLED.setPageMode();            // Set addressing mode to Page Mode
    Xadow.OLED.setTextXY(0, 0);          // Set the cursor to 0th Page, 0th Column
    Xadow.OLED.putNumber(123);           // Print number
    Xadow.OLED.setTextXY(1, 0);          // Set the cursor to 1st Page, 0th Column
    Xadow.OLED.putNumber(0xFFFF);        // Print number
    Xadow.OLED.setTextXY(2, 0);          // Set the cursor to 2nd Page, 0th Column
    Xadow.OLED.putNumber(0xFFFFFFFF);    // Print number
    Xadow.OLED.setTextXY(3, 0);          // Set the cursor to 3rd Page, 0th Column
    Xadow.OLED.putNumber(-12345);        // Print number
}

void loop()
{
    // do nothing
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/