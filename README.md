XADOW
========================================================================================================

test 1410

Written by Loovee, distributed under LGPL, for more information, please visit http://www.seeedstudio.com

This library is written for manage Xadow, include :

* user led
* charge state read
* battery voltage read
* sleep mode operation

FUNCTION
-------------------------------------------------------------------------------------------------------------------
you can use the folowing function, it's useful in some way.

### Initialization
	void init();

### Get Voltage of battery
	float getBatVol();

### Get Charge State
	unsigned char getChrgState(); 

it'll return the folowing value:

	#define NOCHARGE            0
	#define CHARGING            1
	#define CHARGDONE           2
		
### User Led
there'are two user led that you can use, a green one and a read one.

	void greenLed(unsigned char state);             // green Led drive
	void redLed(unsigned char state);               // red led drive
		
about the input value, you can use:

	#define LEDON               1               	// led on
	#define LEDOFF              2               	// led off
	#define LEDCHG              3               	// change led state		

### Power Manage
of curse, sometimes you want your xadow goto sleep to save some power, then you can use this function:

	void pwrDown(unsigned long tSleep);             // power down, tSleep ms

it'll let your xadow goto sleep for sSleep ms, then it'll wake, you shourld use the folowing function to awake it:

	void wakeUp();                                  // wake up


APPLICATION
-------------------------------------------------------------------------------------------------------------------
there'are some application here, for more applicaton you can refer to examples

### POWER DOWN MODE

	#include <Wire.h>

	#include "xadow.h"

	void setup()
	{

		Serial.begin(115200);
		// while(!Serial);
		Xadow.init();
			
		delay(2000);
		cout << "init over" << endl;
	}

	void loop()
	{
		cout << "begin to sleep for 1s" << endl;
		Xadow.pwrDown(1000);                        // sleep for 1000ms
		Xadow.wakeUp();                             // wake up
		cout << "wake up" << endl;
		delay(500);                                 // delay 500 ms
	}


### READ VOLTAGE OF BATTERY

	#include <Wire.h>

	#include "xadow.h"

	void setup()
	{
		Serial.begin(115200);
			
		while(!Serial);
		Xadow.init();
			
		delay(1000);
		cout << "init over" << endl;
	}

	void loop()
	{
		cout << "vol: " << Xadow.getBatVol() << endl;
		delay(500);
	}

### USER LED

	#include <Wire.h>

	#include "xadow.h"

	void setup()
	{
		Xadow.init();
	}


	void loop()
	{
		Xadow.greenLed(LEDON);					// green led on
		Xadow.redLed(LEDOFF);                   // red led off
		delay(200);
		Xadow.redLed(LEDON);                	// red led on
		Xadow.greenLed(LEDOFF);              	// green led off
		delay(200);
	}
		

OTHERS
--------------------------------------------------------------------

anymore problem, please send me a email: luweicong@seeedstudio.com
