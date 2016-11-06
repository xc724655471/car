#ifndef _CTRLDIR_H
#define _CTRLDIR_H


/***		include header files		***/
#include <stm32f10x.h>

#include "F103_PWM.h"
#include "motor.h"
#include "GPIO.h"


#define MinPower 10
#define MaxPower 100

/***	CtrlDir Class		***/
class CtrlDir
{
	private:
		Motor &mLeft;
		Motor &mRight;
	
		u8	  mLpower;
		u8	  mRpower;
		
	public:
		bool	mDir;					//direction(user can set it forward at 0 or 1)
	
		/**
		*	@brief  The constructor of Motor class.
		*	@param  leftMotor: The reference of Motor,control the left motor.
		*	@param  rightMotor: The reference of Motor,control the right motor.
		*/
		CtrlDir(Motor &leftMotor,Motor &rightMotor);
	
		/***	Distructor		***/
		~CtrlDir();
	
		/**
		*	@brief  The motor to control forward.
		*	@param  power: the forward power.
		*/
		void Forward(u8 power=10);
	
		/**
		*	@brief  The motor to control turn left.
		*	@param  Ldegree: the degree of turn left,it will increase the power of right motor or decrease the power of left motor .
		*/
		void TurnLeft(u8 Ldegree=5);
		
		/**
		*	@brief  The motor to control turn right.
		*	@param  Rdegree: the degree of turn right,it will increase the power of left motor or decrease the power of right motor .
		*/
		void TurnRight(u8 Rdegree=5);
		
		/**
		*	@brief  The motor to control back.
		*	@param  power: the back power.
		*/
		void Back(u8 power=10);
};


#endif
