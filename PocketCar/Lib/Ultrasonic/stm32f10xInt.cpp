/*
*****************************************************************************************************
*																									*
*							本文件包含STM32的中断服务函数，用户不宜更改								*
*																									*
*****************************************************************************************************
*/

#include "stm32f10xInt.h"

/***				外部中断服务函数			***/
#if EXTI0IRQHandler
void EXTI0_IRQHandler(void) 	
{
	if(EXTI_GetITStatus(EXTI_Line0))
	{
		EXTI_ClearITPendingBit(EXTI_Line0);
		Exti0_IRQ();
	}
}
#endif


#if EXTI1IRQHandler
void EXTI1_IRQHandler(void) 
{
	if(EXTI_GetITStatus(EXTI_Line1))
	{
		EXTI_ClearITPendingBit(EXTI_Line1);
		Exti1_IRQ();
	}
}
#endif


#if EXTI2IRQHandler
void EXTI2_IRQHandler(void) 
{
	if(EXTI_GetITStatus(EXTI_Line2))
	{
		EXTI_ClearITPendingBit(EXTI_Line2);
		Exti2_IRQ();
	}
}
#endif


#if EXTI3IRQHandler
void EXTI3_IRQHandler(void) 
{
	if(EXTI_GetITStatus(EXTI_Line3))
	{
		EXTI_ClearITPendingBit(EXTI_Line3);
		Exti3_IRQ();
	}
}
#endif



#if EXTI4IRQHandler
void EXTI4_IRQHandler(void) 
{
	if(EXTI_GetITStatus(EXTI_Line4))
	{
		EXTI_ClearITPendingBit(EXTI_Line4);
		Exti4_IRQ();
	}
}
#endif


#if EXTI9_5IRQHandler
void EXTI9_5_IRQHandler(void) 	//外线路5-9的中断处理程序
{
	if(EXTI_GetITStatus(EXTI_Line5))
	{
		EXTI_ClearITPendingBit(EXTI_Line5);
		Exti5_IRQ();
	}
	
	if(EXTI_GetITStatus(EXTI_Line6))
	{
		EXTI_ClearITPendingBit(EXTI_Line6);
		Exti6_IRQ();
	}
	
	if(EXTI_GetITStatus(EXTI_Line7))
	{
		EXTI_ClearITPendingBit(EXTI_Line7);
		Exti7_IRQ();
	}
	
	if(EXTI_GetITStatus(EXTI_Line8))
	{
		EXTI_ClearITPendingBit(EXTI_Line8);
		Exti8_IRQ();
	}
	
	if(EXTI_GetITStatus(EXTI_Line9))
	{
		EXTI_ClearITPendingBit(EXTI_Line9);
		Exti9_IRQ();
	}
	
}
#endif


#if EXTI15_10IRQHandler
void EXTI15_10_IRQHandler(void) 	
{
	if(EXTI_GetITStatus(EXTI_Line10))
	{
		EXTI_ClearITPendingBit(EXTI_Line10);
		Exti10_IRQ();
	}
	
	if(EXTI_GetITStatus(EXTI_Line11))
	{
		EXTI_ClearITPendingBit(EXTI_Line11);
		Exti11_IRQ();
	}
	
	if(EXTI_GetITStatus(EXTI_Line12))
	{
		EXTI_ClearITPendingBit(EXTI_Line12);
		Exti12_IRQ();
	}
	
	if(EXTI_GetITStatus(EXTI_Line13))
	{
		EXTI_ClearITPendingBit(EXTI_Line13);
		Exti13_IRQ();
	}
	
	if(EXTI_GetITStatus(EXTI_Line14))
	{
		EXTI_ClearITPendingBit(EXTI_Line14);
		Exti14_IRQ();
	}
	
	if(EXTI_GetITStatus(EXTI_Line15))
	{
		EXTI_ClearITPendingBit(EXTI_Line15);
		Exti15_IRQ();
	}
}
#endif


/***				定时器中断服务函数			***/

#if USE_CAPTURE
Capture *pTimer1 = 0;
Capture *pTimer2 = 0;
Capture *pTimer3 = 0;
Capture *pTimer4 = 0;
#endif

#if USE_TIM1_IRQ
void TIM1_UP_IRQHandler(void)
{ 
	TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update); //清除中断标识
	#if USE_SERVE
	Timer1_IRQ(); //中断服务程序，用户自行编写
	#endif
}


	#if 	USE_CAPTURE 
	void TIM1_CC_IRQHandler(void)		//tim1的捕获比较中断
	{
		pTimer1->IRQ();
	}
	#endif

	
	void TIM1_TRG_COM_IRQHandler(void)	//tim1的触发
	{}
	void TIM1_BRK_IRQHandler(void)		//tim1的暂停中断
	{}
#endif


#if USE_TIM2_IRQ
void TIM2_IRQHandler(void)  
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM2更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIM2更新中断标志 
			#if USE_SERVE
			Timer2_IRQ();
			#endif
		}
	#if USE_CAPTURE
	 if(pTimer2)
	 pTimer2->IRQ();
	#endif
		
}
#endif

#if USE_TIM3_IRQ
void TIM3_IRQHandler(void)  
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIM3更新中断标志 
		#if USE_SERVE
		Timer3_IRQ();
		#endif
	}
	
	#if USE_CAPTURE
	 if(pTimer3)
	 pTimer3->IRQ();
	#endif
	 
}
#endif

#if USE_TIM4_IRQ
void TIM4_IRQHandler(void)  
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM4更新中断发生与否
	{
	 TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIM4更新中断标志
		
	 #if USE_SERVE
	 Timer4_IRQ();
	 #endif		
	}
	
	#if USE_CAPTURE
	 if(pTimer4)
	 pTimer4->IRQ();
	#endif	
}
#endif	



