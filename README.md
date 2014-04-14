XADOW
========================================================================================================

test 1410

Written by Loovee, distributed under LGPL, for more information, please visit http://www.seeedstudio.com

This library is written to manage Xadow. It includes functions to:

* control the LEDs 
* read the charge state
* read the battery voltage
* put the xadow to sleep

FUNCTION
-------------------------------------------------------------------------------------------------------------------
It contains the following functions:

### Initialization
	void init();

### Get the voltage of the battery
	float getBatVol();

### Get the charge state
	unsigned char getChrgState(); 

getChrgState() will return one of the following values:

	#define NOCHARGE            0
	#define CHARGING            1
	#define CHARGDONE           2
		
### User LED
there'are two user LEDs that you can use, a green one and a red one.

	void greenLed(unsigned char state);             // green LED drive
	void redLed(unsigned char state);               // red LED drive
		
To control the LED state, you use:

	#define LEDON               1               	// turn the LED on
	#define LEDOFF              2               	// turn the LED off
	#define LEDCHG              3               	// toggle the LED state

### Power Management
Sometimes you may want to put your xadow to sleep to save power. Use:

	void pwrDown(unsigned long tSleep);             // power down, tSleep milliSeconds to sleep for

It will put your xadow to sleep for sSleep ms, then it will wake. You should use the following function to wake it up:

	void wakeUp();                                  // wake up


APPLICATION
-------------------------------------------------------------------------------------------------------------------
Here are some application examples:

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
		delay(500);                                 // delay 500ms
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
		Xadow.greenLed(LEDON);                  // green led on
		Xadow.redLed(LEDOFF);                   // red led off
		delay(200);
		Xadow.redLed(LEDON);                	// red led on
		Xadow.greenLed(LEDOFF);              	// green led off
		delay(200);
	}
		

OTHERS
--------------------------------------------------------------------

If you have any problems, please send me an email: luweicong@seeedstudio.com
