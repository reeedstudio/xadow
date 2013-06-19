/*-----------------------------------------------------------------------------------
** demo of smile, use oled, barometer and accelermeter
** when you shake, a smile logo wile be printed in oled, normal time, display barometer
**
** loovee 2013-6-19
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
#include "smile.h"

#define STIDLE          1
#define STSHAKE         2
#define STSMILE         3

unsigned char state = STIDLE;

int cnt_noAcc = 0;
int cnt_Acc   = 0;
int cnt_baro  = 0;

unsigned char getAcc()
{
    double x, y, z;
    
    Xadow.readAcc(&x, &y, &z);
    
    x = abs(x);
    y = abs(y);
    z = abs(z);
    
    if(x>1.2 || y>1.2 || z>1.2)
    {
        cout << "hello : "<< x << '\t' << y << '\t' << z << endl;
        return 1;
    }
    
    return 0;

}

void dispSmile()
{
    // add code here, smile
    Xadow.OLED.clearDisplay();
    Xadow.OLED.drawBitmap(SeeedLogo,1024);   // 1024 = 128 Pixels * 64 Pixels / 8
}

void dispPress(long press)
{
    Xadow.OLED.setTextXY(3,4);          //Set the cursor to Xth Page, Yth Column
    float fPress = press/1000.0;
    Xadow.OLED.putFloat(fPress, 2);
    Xadow.OLED.putString("kPa");
    
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
            long tmp = Xadow.getBaro();
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
        Xadow.OLED.clearDisplay();                  // clear oled

        break;

        default:
        ;
    }
}

void setup()
{
    Serial.begin(38400);
    while(!Serial);
    delay(2000);
    Xadow.init();
    cout << "Smile demo init ok!" << endl;
}

void loop()
{
    stateMachine();
    delay(3);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/