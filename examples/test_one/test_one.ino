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

void loop()
{
    cout << Xadow.getBaro()/1000 << " kPa" << endl;
   
    cout << "hello" << endl;
    delay(500);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/