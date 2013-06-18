// demo of xadow, test one
#include <Streaming.h>
#include <Wire.h>

#include "xadow.h"
#include "xadowDfs.h"

void setup()
{
    Serial.begin(115200);
    
    while(!Serial);
    
    delay(2000);
    cout << "hello world" << endl;
    Xadow.init();
    
}

double ax, ay, az;
void loop()
{
    Xadow.readAcc(&ax, &ay, &az);
    
    cout << "ax = " << ax << '\t';
    delay(500);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/