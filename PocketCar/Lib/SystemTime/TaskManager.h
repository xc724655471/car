#ifndef _TASK_MANAGER_H_
#define _TASK_MANAGER_H_

extern "C"{
#include "stm32f10x.h"
void SysTick_Handler(void);
}

class TaskManager
{
public:
	volatile static u32 _it_cnt;      //SysTick interrupt counter
public:		
	TaskManager();
	static double Time(void);
	void DelayUs(u16 nus);
	void DelayMs(u16 nms);
	void DelayS(u16 ns);
};

extern TaskManager tskmgr;
#define	MOD_ERROR  0x00
#define	MOD_READY  0x01
#define	MOD_BUSY   0x02
#define	MOD_LOCK   0x04
#define	MOD_UNLOCK 0x08
#endif
