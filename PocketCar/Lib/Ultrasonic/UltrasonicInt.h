/*
*****************************************************************************************************
*																									*
*									用户中断函数配置文件											*
*																									*
*****************************************************************************************************
*/


#ifndef _UlTRASOINCINT_H
#define _UlTRASOINCINT_H

/***	include header files	***/

//C header files
extern "C"{
	
	/***	库函数头文件		***/
	#include <stm32f10x.h>
	
}
//CPP	header	files
#include "Ultrasonic.h"


/***		外部中断函数开关（0无效，1有效）	***/
#define			EXTI0IRQHandler				1
#define			EXTI1IRQHandler				0
#define			EXTI2IRQHandler				0
#define			EXTI3IRQHandler				0
#define			EXTI4IRQHandler				0
#define			EXTI9_5IRQHandler			1
#define			EXTI15_10IRQHandler			0

/***		定时器中断函数开关					***/
#define 		USE_TIM1_IRQ   				0		
#define 		USE_TIM2_IRQ				0
#define 		USE_TIM3_IRQ				0	
#define 		USE_TIM4_IRQ				0
#define 		USE_CAPTURE   				0	    
#define 		USE_SERVE    				1		



/***		外部变量声明		***/	


/***	函数声明		***/

//用户外部中断函数声明
#if EXTI0IRQHandler
	extern Ultrasonic *Uexti0;
	
	void Exti0_IRQ();
#endif

#if EXTI1IRQHandler
	extern Ultrasonic *Uexti1;
	
	void Exti1_IRQ();
#endif 

#if EXTI2IRQHandler
	extern Ultrasonic *Uexti2;
	
	void Exti2_IRQ();
#endif 

#if EXTI3IRQHandler
	extern Ultrasonic *Uexti3;
	
	void Exti3_IRQ();
#endif

#if EXTI4IRQHandler
	extern Ultrasonic *Uexti4;
	
	void Exti4_IRQ();
#endif

#if EXTI9_5IRQHandler
	extern Ultrasonic *Uexti5;
	extern Ultrasonic *Uexti6;
	extern Ultrasonic *Uexti7;
	extern Ultrasonic *Uexti8;
	extern Ultrasonic *Uexti9;
	
	void Exti5_IRQ();
	void Exti6_IRQ();
	void Exti7_IRQ();
	void Exti8_IRQ();
	void Exti9_IRQ();
#endif

#if EXTI15_10IRQHandler
	
	extern Ultrasonic *Uexti10;
	extern Ultrasonic *Uexti11;
	extern Ultrasonic *Uexti12;
	extern Ultrasonic *Uexti13;
	extern Ultrasonic *Uexti14;
	extern Ultrasonic *Uexti15;
	
	void Exti10_IRQ();
	void Exti11_IRQ();
	void Exti12_IRQ();
	void Exti13_IRQ();
	void Exti14_IRQ();
	void Exti15_IRQ();
#endif


//用户定时器中断函数声明
#if USE_TIM1_IRQ	
  #if USE_SERVE
	void Timer1_IRQ();
  #endif
#endif

#if USE_TIM2_IRQ	
  #if USE_SERVE
	void Timer2_IRQ();
  #endif
#endif

#if USE_TIM3_IRQ	
  #if USE_SERVE
	void Timer3_IRQ();
  #endif
#endif

#if USE_TIM4_IRQ	
  #if USE_SERVE
	void Timer4_IRQ();
  #endif
#endif


#endif
