/*
  xadowDfs.h
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-6-17
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __XADOWDFS_H__
#define __XADOWDFS_H__

#define __Debug         1

// enable of function, if you don't want some function, you can change
// value of the folowing define
#define EN_BARO         1
#define EN_RTC          1
#define EN_ACC          1
#define EN_OLED         1
#define EN_LED          1
#define EN_VIB          1

// I2C address
#define ADDRBARO        0x77
#define ADDRACC         0x53
#define ADDRRTC         0x68

// PIN define
#define PINBAT          A4
#define PINCHRGDONE     A3
#define PINCHRGING      A2

// about charge
#define CHRGbit 0x10
#define DONEbit 0x20
#define CHRGdir DDRF
#define DONEdir DDRF
#define CHRGpin PINF
#define DONEpin PINF
#define CHRGport PORTF
#define DONEport PORTF

// charge state
#define NOCHARGE        0
#define CHARGING        1
#define CHARGDONE       2

// address for acceler...
#define Register_ID     0
#define Register_2D     0x2D
#define Register_X0     0x32
#define Register_X1     0x33
#define Register_Y0     0x34
#define Register_Y1     0x35
#define Register_Z0     0x36
#define Register_Z1     0x37

// week name of RTC
#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6
#define SUN 7

// vibrator
#define MOVE    0
#define STOP    -1

#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/