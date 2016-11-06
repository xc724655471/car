/*
*********************************************************************************************************
*
*                                      Ultrasonic CALSS HEADER FILE                                
*
* Filename      : Ultrasonic.h
* Version       : V1.2
* Test module	: HC-SR04
* Programmer(s) : Jason Xie
*              
*********************************************************************************************************
*/

#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H

/*****	include header files	*****/

//C Header File
extern "C"
{
	/*	库函数头文件	*/
	#include <stm32f10x.h>
	#include <misc.h>
	#include <stdbool.h>
	#include <math.h>
	/*	用户自定义头文件	*/
	
}

//CPP Header File

//#include "Delay.h"
#include "Exti.h"
#include "TaskManager.h"
#include "GPIO.h"



/*****	Class Declarations	*****/
/**
  *	@brief  The class of Ultrasonic.									 				 		 
 **/
class Ultrasonic
{
	private:
		GPIO	&mTrig;						//Trig引脚
		GPIO	&mEcho;						//Echo引脚
		Exti	mExti;						//外部中断
		
		float	mIntervalTime;				//保存超声波从发射到接收所用时间
	
		bool	mStartFlag;
		bool	mFinishFlag;				//距离计算完成标志
		bool	mTimeOut;					//超时标志
	
		/**	@brief  Calculate the distance by mIntervalTime.*/
		void CalculateDistance();
	
	public:
		float mDistance;					//超声波所测得的距离
	
		/**
		*	@brief  The constructor of Ultrasonic class.
		*	@param  Trig: The Trig's pin of Ultrasonic,type:GPIO &.
		*	@param  Echo: The Echo's pin of Ultrasonic,type:GPIO &.
		*	@param  timer: The timer to get the time from  start to receive,type:Timer &.
		*	@param  NVICPriorityGroup:中断向量分组,type:uint8_t.
		*	@param  NVICPreemptionPriority:抢占优先级,type:uint8_t.
		*	@param  NVICSubPriority:响应优先级,type:uint8_t.
		*/
		Ultrasonic(GPIO &Trig,GPIO &Echo,uint8_t NVICPriorityGroup,uint8_t NVICPreemptionPriority,uint8_t NVICSubPriority);
		
		/**
		*	@brief  The destructor of Ultrasonic class.
		*/
		~Ultrasonic();
		
		/**
		*	@brief  This function is to judge the Ultrasonic if start or end .
		*/
		void UltrasonicIrq();
	
		/**
		*	@brief  Start the Ultrasonic.
		*/
		void UltrasonicStart(); 
		
		/**
		*	@brief  Get the distance .
		*	@retval the distance,type:float.
		*/
		float GetDistance();
		
		/**
		*	@brief  Start the Ultrasonic Get the distance .
		*	@retval the distance,type:float.
		*/
		float Update();
};

#endif
