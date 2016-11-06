#ifndef _STM32F103XINT_H
#define _STM32F103XINT_H

/***	include header files	***/

//C header files
extern "C"{
	
	/***	库函数头文件		***/
	#include <stm32f10x.h>
	
	/***	用户自定义头文件	***/
}

//CPP header files
/***	用户自定义头文件	***/
//#include "UserIRQConf.h"
#include "UltrasonicInt.h"

/***		外部变量声明		***/	



/***	函数声明		***/
extern "C"{
	
#if	EXTI0IRQHandler
	void EXTI0_IRQHandler(void);
#endif

#if	EXTI1IRQHandler	
	void EXTI1_IRQHandler(void);
#endif
	
#if	EXTI2IRQHandler
	void EXTI2_IRQHandler(void);
#endif

#if	EXTI3IRQHandler
	void EXTI3_IRQHandler(void);
#endif
	
#if	EXTI4IRQHandler	
	void EXTI4_IRQHandler(void);
#endif
	
#if	EXTI9_5IRQHandler
	void EXTI9_5_IRQHandler(void);
#endif

#if	EXTI15_10IRQHandler
	void EXTI15_10_IRQHandler(void);
#endif	
}
	

/*捕获------------------------------------------*/
#if USE_CAPTURE
#include "Capture.h"
#endif

#if USE_CAPTURE
extern Capture *pTimer1;
extern Capture *pTimer2;
extern Capture *pTimer3;
extern Capture *pTimer4;	
#endif


/*中断入口函数-----------------------------------*/
extern "C"{

#if USE_TIM1_IRQ
	void TIM1_UP_IRQHandler(void);		//tim1的刷新中断和通讯中断。

	void TIM1_BRK_IRQHandler(void); 	//tim1的暂停中断
	void TIM1_TRG_COM_IRQHandler(void);	//tim1的触发

	#if USE_CAPTURE
		void TIM1_CC_IRQHandler(void);		//tim1的捕获比较中断
	#endif
#endif

//定时器2中断函数
#if USE_TIM2_IRQ
	void TIM2_IRQHandler(void);
#endif

//定时器三中断函数
#if USE_TIM3_IRQ
	void TIM3_IRQHandler(void);
#endif

//定时器四中断函数
#if USE_TIM4_IRQ
	void TIM4_IRQHandler(void);
#endif
}




#endif
