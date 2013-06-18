/*-----------------------------------------------------------------------------------
** demo of xadow oled, horizontal addressing mode
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
    Xadow.OLED.setHorizontalMode();      // Set addressing mode to Horizontal Mode
    Xadow.OLED.putString("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");  //Print String (ASCII 32 - 126 )

}

void loop()
{
    // do nothing
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/