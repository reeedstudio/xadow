// demo of xadow, test one
#include <Streaming.h>
#include <Wire.h>

#include "xadow.h"
#include "xadowDfs.h"

unsigned char td[] = {13, 6, 18, TUE, 19, 21, 30};  // set time here: year, month ,day, week, hour, minute, second

void setup()
{
    Serial.begin(115200);
    
    while(!Serial);
    
    delay(2000);
    cout << "hello world" << endl;

    Xadow.init();
    
    Xadow.setTime(td);

}


void loop()
{

    Xadow.getTime(td);
    delay(1000);
    
    cout << td[4] << ":" << td[5] << ":" << td[6] << endl;
    
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/