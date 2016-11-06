#ifndef _F103_PWM_H_
#define _F103_PWM_H_
 
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
 
class PWM{
    public:
			
			/**
			 *@brief 构造函数
			 *@param timer 选择的时钟
			 *@param enCh1 通道1是否打开
			 *@param enCh2 通道2是否打开
			 *@param enCh3 通道3是否打开
			 *@param enCh4 通道4是否打开
			 *@param frequency 期望频率
			 *@param remap 引脚是否映射,这个版本还没有做
			 */
       PWM(TIM_TypeDef* timer,bool enCh1,bool enCh2,bool enCh3,bool enCh4,u16 frequency,bool remap = false)
				{
						mPsc = 0;
						mArr = 0;
						Calcute(frequency);
            PWMInit(timer,enCh1,enCh2,enCh3,enCh4,frequency,remap);
        };
//			/**
//			 *@brief 重载构造函数,用于初始化一个通道，但是用户需要注意注意同一个时钟下的频率是一样的；
//			 *@param timer 选择的时钟
//			 *@param channel 通道数值
//			 *@param frequency 期望频率
//			 *@param remap 引脚是否映射,这个版本还没有做
//			 */
//			 PWM(TIM_TypeDef* timer,u8 channel,u16 frequency,bool remap = false)
//			 {
//				mPsc = 0;
//				mArr = 0;
//				Calcute(frequency);
//				 switch (channel)
//				 {
//						case 1:PWMInit(timer,1,0,0,0,frequency,remap);;break;
//						case 2:PWMInit(timer,0,1,0,0,frequency,remap);;break;
//						case 3:PWMInit(timer,0,0,1,0,frequency,remap);;break;
//						case 4:PWMInit(timer,0,0,0,1,frequency,remap);;break;
//				 }
//			 };
				
				/**
				 *@brief 改变一个通道的占空比
				 *@param channel 选择通道
				 *@param duty    设置占空比
				 */
				void SetDuty(u8 channel,float duty);
				/**
				 *@brief 改变一个通道的占空比
				 *@param dutyCh1 设置通道1的占空比
				 *@param dutyCh2 设置通道2的占空比
				 *@param dutyCh3 设置通道3的占空比
				 *@param dutyCh4 设置通道4的占空比
				 */
				void SetDuty(float dutyCh1,float dutyCh2,float dutyCh3,float dutyCh4);//重载
				
    private:
				TIM_TypeDef* mTimer;
				u16 mPsc;
				u16 mArr;

				GPIO_InitTypeDef GPIO_InitStruct;						//GPIO结构体
				TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;	//时钟结构体
				TIM_OCInitTypeDef TIM_OCInitStructure;	//定义输出结构体
				void PWMInit(TIM_TypeDef* timer,bool enCh1,bool enCh2,bool enCh3,bool enCh4,u16 frequency,bool remap = false);
				void Calcute(u16 frequency);//逐步毕竟频率，计算PSC和ARR；
				void Calcute2(u32 quo,u32 quo2,u32 rem2,bool flagBest);//重复的代码在一起；
};
 

/**
	TIM1 CH1 ---------------- PA8
	TIM1 CH2 ---------------- PA9
	TIM1 CH3 ---------------- PA10
	TIM1 CH4 ---------------- PA11

	TIM2 CH1 ---------------- PA0
	TIM2 CH2 ---------------- PA1
	TIM2 CH3 ---------------- PA2
	TIM2 CH4 ---------------- PA3

	TIM3 CH1 ---------------- PA8
	TIM3 CH2 ---------------- PA9
	TIM3 CH3 ---------------- PA8
	TIM3 CH4 ---------------- PA9

	TIM4 CH1 ---------------- PA6
	TIM4 CH2 ---------------- PA7
	TIM4 CH3 ---------------- PB0
	TIM4 CH4 ---------------- PB1
 */









 
#endif
