#include "functions.h"
#include "ADXL345.h"
#include <Wire.h>
#include <SeeedOLED.h>
#include <avr/pgmspace.h>
#include <Sleep_n0m1.h>
#include "sleep.h"
float lastXg=0.0;
float lastYg=0.0;
float lastZg=0.0;

void setup(void)
{
  Wire.begin();	
  SeeedOled.init();  //initialze SEEED OLED display
  SeeedOled.clearDisplay();  // clear the screen and set start position to top left corner
  Serial.begin(115200);
  Serial1.begin(38400);
  initIOs();
  initADXL345();//init ADXL345 for auto restart
  analogReference(INTERNAL);
  analogRead(4);
}
void loop(void)
{
  static unsigned char count=0;
  //for(;;)
  {
    unsigned char ChS=readCharge();
    if(ChS == DONE)
    {
      rLEDport &=~ rLEDbit;
    }
    else if(ChS == CHARGE)
    {
      rLEDport ^= rLEDbit;
    }
    else
    {
      rLEDport |= rLEDbit;
    }
    if(count>10)
    {
      count=0;
      readBat();      
      gLEDport &=~ gLEDbit;
      delay(50);
      gLEDport |= gLEDbit;
    }
    count++;
    ADXL();
  }
}

//=========================================
unsigned char readCharge(void)
{
  unsigned char Temp = CHRGpin & CHRGbit;
  if(!Temp)
  {
    return CHARGE;
  }
  Temp = DONEpin & DONEbit;
  if(!Temp)
  {
    return DONE;
  }
  return NONE;
}

//=========================================
unsigned char readBat(void)
{
  unsigned int rAD4 = analogRead(4);
  float Vabt = rAD4/200;
  Serial.println(Vabt);
  SeeedOled.setTextXY(0,0);
  SeeedOled.putString("VBat: ");
  SeeedOled.setTextXY(0,6);
  SeeedOled.putFloat(Vabt,2);
}

//=========================================
void initIOs(void)
{
  rLEDport |= rLEDbit;
  gLEDport |= gLEDbit;
  rLEDdir |= rLEDbit;
  gLEDdir |= gLEDbit;

  CHRGdir &=~ CHRGbit;
  CHRGport |= CHRGbit;
  DONEdir &=~ DONEbit;
  DONEport |= DONEbit;

  DDRF |= 0x01;
  DDRB |= 0x04;//vibrator
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
#define sen 1
  static float tempGL=0;
  static float tempGH=0;
  unsigned char vib=0;
  readAcc();//get new Acc
  tempGL = Xg-sen;
  tempGH = Xg+sen;
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

  tempGL = Yg-sen;
  tempGH = Yg+sen;
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

  tempGL = Zg-sen;
  tempGH = Zg+sen;
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



  if(vib) //changed
  {
    Serial.print("X = ");
    Serial.print(Xg);
    Serial.print(", Y = ");
    Serial.print(Yg);
    Serial.print(", Z = ");
    Serial.println(Zg);

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
  //SeeedOled.setTextXY(4,0);
  //SeeedOled.putString("BLE Connected");
}
























