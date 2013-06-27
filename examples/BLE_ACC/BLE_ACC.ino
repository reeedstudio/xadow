/*-----------------------------------------------------------------------------------
** demo of ble and accelermeter
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
#include <SeeedOLED.h>

#include "xadow.h"

float lastXg = 0.0;
float lastYg = 0.0;
float lastZg = 0.0;

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
    Wire.write(8);                                              // measuring enable
    Wire.endTransmission();                                     // stop transmitting
}

unsigned char readAcc(double *Xg, double *Yg, double *Zg)
{
    int X_out;
    int Y_out;
    int Z_out;
    Wire.beginTransmission(ADDRACC);                            // transmit to device
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
    Wire.beginTransmission(ADDRACC);                            // transmit to device
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
    Wire.beginTransmission(ADDRACC);                            // transmit to device
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

unsigned char dispBat(void)
{

    float Vabt = Xadow.getBatVol();
    cout << Vabt << endl;
    SeeedOled.setTextXY(0,0);
    SeeedOled.putString("VBat: ");
    SeeedOled.setTextXY(0,6);
    SeeedOled.putFloat(Vabt,2);
}

void vibrate(unsigned char OnOff)
{
    if(OnOff)
    {
        PORTB |= 0x04;
        PORTF |= 0x01;
    }
    else
    {
        PORTB &=~ 0x04;
        PORTF &=~ 0x01;
    }
}

void ADXL(void)
{

    double Xg, Yg, Zg;
    
    static float tempGL=0;
    static float tempGH=0;
    unsigned char vib=0;
    readAcc(&Xg, &Yg, &Zg);//get new Acc
    
    tempGL = Xg-1;
    tempGH = Xg+1;
    if((lastXg>tempGH)||(lastXg<tempGL))
    {
        lastXg=Xg;
        SeeedOled.setTextXY(1,0);
        SeeedOled.putString("X= ");
        SeeedOled.setTextXY(1,3);
        SeeedOled.putFloat(Xg);
        SeeedOled.putString("    ");
        vib|=0x01;
    }

    tempGL = Yg-1;
    tempGH = Yg+1;
    if((lastYg>tempGH)||(lastYg<tempGL))
    {
        lastYg=Yg;
        SeeedOled.setTextXY(2,0);
        SeeedOled.putString("Y= ");
        SeeedOled.setTextXY(2,3);
        SeeedOled.putFloat(Yg);
        SeeedOled.putString("    ");
        vib|=0x02;
    }

    tempGL = Zg-1;
    tempGH = Zg+1;
    if((lastZg>tempGH)||(lastZg<tempGL))
    {
        lastZg=Zg;
        SeeedOled.setTextXY(3,0);
        SeeedOled.putString("Z= ");
        SeeedOled.setTextXY(3,3);
        SeeedOled.putFloat(Zg);
        SeeedOled.putString("    ");
        vib|=0x04;
    }

    if(vib)
    {
        cout << "X = " << Xg << '\t';
        cout << "Y = " << Yg << '\t';
        cout << "Z = " << Zg << endl;

        Serial1.print("X = ");
        Serial1.print(Xg);
        Serial1.print(", Y = ");
        Serial1.print(Yg);
        Serial1.print(", Z = ");
        Serial1.println(Zg);
        vibrate(1);
    }
    delay(100);
    vibrate(0);
}

void setup(void)
{
    Wire.begin();

    SeeedOled.init();                               //initialze SEEED OLED display
    SeeedOled.clearDisplay();                       // clear the screen and set start position to top left corner

    Serial.begin(115200);
    Serial1.begin(38400);
    adxl_init();
    
    DDRF |= 0x01;
    DDRB |= 0x04;                                   //vibrator io init
	
	Xadow.init();
}

void loop(void)
{
    static unsigned char count=0;

    unsigned char stateChg = Xadow.getChrgState();
    
    if(NOCHARGE == stateChg)
    {
        Xadow.redLed(LEDON);
    }
    else if(CHARGING == stateChg)
    {
        Xadow.redLed(LEDCHG);
    }
    else
    {
        Xadow.redLed(LEDOFF);
    }

    if(count>10)
    {
        count=0;
        dispBat();
    }
    count++;
    ADXL();
	
	BluetoothDtaProc();
	
}


bool cmpLvc(char *a, char *b, int len)
{
	if(!a || !b)return 0;
	for(int i = 0; i<len; i++)
	{
		if(a[i] == b[i])continue;
		else return 0;
	}
	return 1;
}
// you can send "LEDON" and "LEDOFF" to control the green LED on main board
void BluetoothDtaProc()
{
	char getDta 		= 0;
	unsigned char len 	= 0;
	char dta[20];
	while(Serial1.available())
	{
		char c = Serial1.read();
		
		dta[len++] = c;
		getDta = 1;
	}
	
	if(getDta)
	{
		//if(len == 5 && dta[0] == 'L' && dta[1] == 'E' && dta[2] == 'D' && dta[3] == 'O' && dta[4] == 'N')
		if(len == 5 && (cmpLvc(dta, "ledon", len) || cmpLvc(dta, "LEDON", len)))
		{
			Serial1.println("LEDON");
			Xadow.greenLed(LEDON);
		}
		//else if(len == 6 && dta[0] == 'L' && dta[1] == 'E' && dta[2] == 'D' && dta[3] == 'O' && dta[4] == 'F' && dta[5] == 'F')
		if(len == 6 && (cmpLvc(dta, "ledoff", len) || cmpLvc(dta, "LEDOFF", len)))
		{
			Serial1.println("LEDOFF");
			Xadow.greenLed(LEDOFF);
		}
		else 
		{
			Serial1.println("OK");
		}
		getDta = 0;
	}
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/