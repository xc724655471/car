/*
*****************************************************************************
*																			*
*							用户自定义中断函数								*
*																			*
*****************************************************************************
*/

#include "UltrasonicInt.h"

/***	外部中断函数	***/

/***	变量定义	***/


/***	函数定义	***/
#if EXTI0IRQHandler
Ultrasonic *Uexti0=0;
void Exti0_IRQ()
{
	if(Uexti0)
		Uexti0->UltrasonicIrq();
	
}
#endif

#if EXTI1IRQHandler
Ultrasonic *Uexti1=0;
void Exti1_IRQ()
{
	if(Uexti1)
		Uexti1->UltrasonicIrq();
	
}
#endif

#if EXTI2IRQHandler
Ultrasonic *Uexti2=0;
void Exti2_IRQ()
{
	if(Uexti2)
		Uexti2->UltrasonicIrq();
	
}
#endif

#if EXTI3IRQHandler
Ultrasonic *Uexti3=0;
void Exti3_IRQ()
{
	if(Uexti3)
		Uexti3->UltrasonicIrq();
	
}
#endif

#if EXTI4IRQHandler
Ultrasonic *Uexti4=0;
void Exti4_IRQ()
{
	if(Uexti4)
		Uexti4->UltrasonicIrq();
}
#endif

#if EXTI9_5IRQHandler
Ultrasonic *Uexti5=0;
Ultrasonic *Uexti6=0;
Ultrasonic *Uexti7=0;
Ultrasonic *Uexti8=0;
Ultrasonic *Uexti9=0;
void Exti5_IRQ()
{
	if(Uexti5)
		Uexti5->UltrasonicIrq();
}

void Exti6_IRQ()
{
	if(Uexti6)
		Uexti6->UltrasonicIrq();
}

void Exti7_IRQ()
{
	if(Uexti7)
		Uexti7->UltrasonicIrq();
}

void Exti8_IRQ()
{
	if(Uexti8)
		Uexti8->UltrasonicIrq();
}

void Exti9_IRQ()
{
	if(Uexti9)
		Uexti9->UltrasonicIrq();
}
#endif

#if EXTI15_10IRQHandler
Ultrasonic *Uexti10=0;
Ultrasonic *Uexti11=0;
Ultrasonic *Uexti12=0;
Ultrasonic *Uexti13=0;
Ultrasonic *Uexti14=0;
Ultrasonic *Uexti15=0;
void Exti10_IRQ()
{
	if(Uexti10)
		Uexti10->UltrasonicIrq();
}

void Exti11_IRQ()
{
	if(Uexti11)
		Uexti11->UltrasonicIrq();
}

void Exti12_IRQ()
{
	if(Uexti12)
		Uexti12->UltrasonicIrq();
}

void Exti13_IRQ()
{
	if(Uexti13)
		Uexti13->UltrasonicIrq();
}

void Exti14_IRQ()
{
	if(Uexti14)
		Uexti14->UltrasonicIrq();
}

void Exti15_IRQ()
{
	if(Uexti15)
		Uexti15->UltrasonicIrq();
}
#endif

/***	定时器中断服务函数	***/
#if USE_TIM1_IRQ
void Timer1_IRQ()
{

}
#endif

#if USE_TIM2_IRQ
void Timer2_IRQ()
{

}
#endif

#if USE_TIM3_IRQ
void Timer3_IRQ()
{

}
#endif

#if USE_TIM4_IRQ
void Timer4_IRQ()
{

}
#endif
