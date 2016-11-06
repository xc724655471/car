#ifndef	_MOTOR_H
#define _MOTOR_H


/***		include header files		***/
#include <stm32f10x.h>

#include "F103_PWM.h"
#include "GPIO.h"


/***			  The pwm output pin				  ***/
/******TIM2：CH1:PA0, CH2:PA1, CH3:PA2, CH4:PA3	*********/
/******TIM3：CH1:PA6, CH2:PA7, CH3:PB0, CH4:PB1	*********/
/******TIM4：CH1:PB6, CH2:PB7, CH3:PB8, CH4:PB9	*********/



/***	Motor Class	***/	
class Motor
{
	private:
		PWM  &mPwm;

//		GPIO &mDir;							//the pin to control the rotate direction
		u16  mRotateSpeed;			
		bool mIsReverse;
	
		u8  mChannel1;						//the pwm output channel
		u8  mChannel2;
		u8  mChannel3;
		u8  mChannel4;
	
		/***	the map of duty to rotate-speed		***/
		void DutyToRspeed();
	public:
		/**
		*	@brief  The constructor of Motor class.
		*	@param  timer: The timer to make pwm.
		*	@param  channel: The pwm output channel.
		*	@param  frequence: The pwm's frequence.
		*	@param  dir:The GPIO object to control the motor's rotate direction.
		*	@param  isReverse:decide the pwm if inverse,default state is not inverse.
		*	@param  remap:remaping or not.
		
		Motor(TIM_TypeDef* timer,u8 channel,u16 frequency,GPIO &dir,bool isReverse=false,bool remap = false);*/
	
		/**
		*	@brief :the constructor of Motor class.
		*	@param  pwm: The reference of PWM's object.
		*	@param  channel: The pwm output channel.
		*	@param  dir:The GPIO object to control the motor's rotate direction.
		*	@param  isReverse:decide the pwm if inverse,default state is not inverse.
		*	@param  remap:remaping or not.
		*/
		Motor(PWM &pwm,u8 channel,GPIO &dir,bool isReverse=false,bool remap = false);
		Motor(PWM &pwm,u8 channel,bool isReverse=false,bool remap = false);
	
		/***	Distructor		***/
		~Motor();
		/***	
		*	@brief  初始化电机
		*/
		void InitMotor(void);
		/***	
		*	@brief  Set the rotate speed	
		*/
		void SetRotateSpeeed(u16 rSpeed);
		
		/***	
		*	@brief  Reload the 	SetRotateSpeeed
		*	@param  channel:the pwm channel.
		*	@param  rSpeed:the rotate speed.
		*/
		void SetRotateSpeeed(u8 channel,u16 rSpeed);
	
	
		/***	
		*	@brief  Change the direction of rotation	
		*/
		void SetDirection(bool dir);
	
		/***	
		*	@brief  Get the speed of rotation	
		*/
		u16 GetRotateSpeed();

};

#endif
