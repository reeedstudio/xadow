xadow
================

Written by Loovee, distributed under LGPL, for more information, please visit http://www.seeedstudio.com

This library is written for manage Xadow, include :

* user led
* charge state read
* battery voltage read
* sleep mode operation

function
------------------
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
		
## User Led
there'are two user led that you can use, a green one and a read one.
		void greenLed(unsigned char state);			// green Led drive
		void redLed(unsigned char state);   		// red led drive
about the input value, you can use:
		#define LEDON               1               // led on
		#define LEDOFF              2               // led off
		#define LEDCHG              3               // change led state		

## Power Manage
of curse, sometimes you want your xadow goto sleep to save some power, then you can use this function:
		void pwrDown(unsigned long tSleep);                 // power down, tSleep ms

it'll let your xadow goto sleep for sSleep ms, then it'll wake, you shourld use the folowing function to awake it:
		void wakeUp();                                      // wake up

