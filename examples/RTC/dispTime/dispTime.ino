// demo of xadow, display time

#include <Streaming.h>
#include <Wire.h>

#include "xadow.h"
#include "xadowDfs.h"

unsigned char td[7] = {0, 0, 0, 0, 0, 0, 0};

void setup()
{
    Serial.begin(115200);
    
    while(!Serial);
    
    delay(2000);
    cout << "hello world" << endl;

    Xadow.init();

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