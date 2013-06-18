/*-----------------------------------------------------------------------------------
** demo of xadow oled, Inverse Display
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
  
  Xadow.OLED.clearDisplay();                // clear the screen and set start position to top left corner
  Xadow.OLED.setNormalDisplay();            // Set display to normal mode (i.e non-inverse mode)
  Xadow.OLED.setPageMode();                 // Set addressing mode to Page Mode
  Xadow.OLED.setTextXY(0,0);                // Set the cursor to Xth Page, Yth Column  
  Xadow.OLED.putString("Hello World!");     // Print the String
}

void loop()
{
    // do nothing
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/