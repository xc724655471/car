#ifndef _TRANSMISSION_H_
#define _TRANSMISSION_H_


#include "stm32f10x.h"
//定义结构和联合
typedef union
{
	struct
	{
		unsigned char low_byte;
		unsigned char mlow_byte;
		unsigned char mhigh_byte;
		unsigned char high_byte;
	}float_byte;
	float value;
	
}Float_Union;


#endif
