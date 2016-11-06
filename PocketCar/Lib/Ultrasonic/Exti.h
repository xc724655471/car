/*
*********************************************************************************************************
*
*                                      Exti CALSS HEADER FILE                                
*
* Filename      : Exti.h
* Version       : V1.0
* Programmer(s) : Jason Xie
* note			: 默认关闭外部中断             
*********************************************************************************************************
*/

#ifndef _EXTI_H
#define _EXTI_H

/**	include header files	**/
extern "C"
{
	/*	库函数头文件	*/
	#include <stm32f10x.h>
	#include <misc.h>
	#include <stdbool.h>

	/*	用户自定义头文件	*/
	//#include "interrupt.h"
}

/*
*	PA0，PB0，PC0，PD0，PE0，PF0，PG0为第一组,依此类推，我们能得出一共有16 组，
*	STM32 规定，每一组中同时只能有一个中断触发源工作，那么，最多工作的也就是16个外部中断。
*/

/**
  *	@brief  The class of Exti.
  *	@param  mEXTILine[16]: The array of EXTILine num,such as EXTI_Line0,etc.  
  *	@param  mPin[16]: The array of GPIO_Pin_x.
  *	@param  mSelectPort:The port of GPIO which you are using,such as GPIOA,etc.  
  * @param  mSelectPin:The pin you want to use.									 	 
  */
class Exti
{
	private:
		static const uint32_t	mEXTILine[16];
		static const uint16_t     	 mPin[16];
		GPIO_TypeDef				*mSelectPort;
		uint16_t					mSelectPin;
	
		/*	The function to configure the RCC of EXTI	*/
		void RCC_Configuration();
		
		/*	The function to configure the GPIO of EXTI	*/	
		void GPIO_Configuration(GPIOMode_TypeDef gpioMode);
	
		/*	The function to configure the EXTI	*/		
		void EXTI_Configuration(EXTIMode_TypeDef extiMode,EXTITrigger_TypeDef extiTrigger);
	
		/*	The function to configure the NVIC_	*/	
		void NVIC_Configuration(uint8_t NVICPriorityGroup,uint8_t NVICPreemptionPriority,uint8_t NVICSubPriority);
	
	public:
		/*	The Constructor of the Class	*/
		Exti(GPIO_TypeDef *port,uint16_t pin,GPIOMode_TypeDef gpioMode,uint8_t NVICPriorityGroup,uint8_t NVICPreemptionPriority,uint8_t NVICSubPriority,EXTIMode_TypeDef extiMode=EXTI_Mode_Interrupt,EXTITrigger_TypeDef extiTrigger=EXTI_Trigger_Rising);
		
		/*	Close the EXTI	*/
		void CloseExtiInt();
	
		/*	Open the EXTI	*/
		void OpenExtiInt();
	
		/*	destructor	*/
		~Exti();
};

#endif
