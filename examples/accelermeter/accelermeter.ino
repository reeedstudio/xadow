/*-----------------------------------------------------------------------------------
** demo xadow accelermeter
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

#define ADDRACC         0x53

#define Register_ID     0
#define Register_2D     0x2D
#define Register_X0     0x32
#define Register_X1     0x33
#define Register_Y0     0x34
#define Register_Y1     0x35
#define Register_Z0     0x36
#define Register_Z1     0x37

void adxl_init()
{
    Wire.beginTransmission(ADDRACC);
    Wire.write(Register_2D);
    Wire.write(8);                          //measuring enable
    Wire.endTransmission();                 // stop transmitting
}

unsigned char readAcc(double *Xg, double *Yg, double *Zg)
{
    int X_out;
    int Y_out;
    int Z_out;
    Wire.beginTransmission(ADDRACC);        // transmit to device
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
    Wire.beginTransmission(ADDRACC);        // transmit to device
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
    Wire.beginTransmission(ADDRACC);        // transmit to device
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

void setup()
{
    Serial.begin(115200);
    while(!Serial);
    Xadow.init();
    Wire.begin();
    adxl_init();
    cout << "init accelermeter over!" << endl;
}

void loop()
{
    double ax, ay, az;
    
    readAcc(&ax, &ay, &az);                   // get acc
    
    cout << "ax = " << ax << '\t';
    cout << "ay = " << ay << '\t';
    cout << "az = " << az << endl;
    delay(100);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
