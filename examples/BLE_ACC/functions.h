#ifndef functions_h
#define functions_h

extern double Xg,Yg,Zg;


#define CHARGE 0x01
#define DONE   0x02
#define NONE   0x00

#define CHRGbit 0x10
#define DONEbit 0x20
#define CHRGdir DDRF
#define DONEdir DDRF
#define CHRGpin PINF
#define DONEpin PINF
#define CHRGport PORTF
#define DONEport PORTF

#define rLEDbit  0x01
#define gLEDbit  0x80
#define rLEDdir  DDRB
#define gLEDdir  DDRB
#define rLEDport PORTB
#define gLEDport PORTB
#define rLEDpin  PINB
#define gLEDpin  PINB

#endif
