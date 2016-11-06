#include "motor.h"
#include "Delay.h"


/***	 Constructor	***/
//Motor::Motor(PWM &pwm,u8 channel,GPIO &dir,bool isReverse,bool remap):mPwm(pwm),mDir(dir),mIsReverse(isReverse)
//{
//	switch (channel)
//	{
//		case 1:mChannel1=1;break;
//		case 2:mChannel2=2;break;
//		case 3:mChannel3=3;break;
//		case 4:mChannel4=4;break;
//	}
//}
Motor::Motor(PWM &pwm,u8 channel,bool isReverse,bool remap):mPwm(pwm),mIsReverse(isReverse)
{
	switch (channel)
	{
		case 1:mChannel1=1;break;
		case 2:mChannel2=2;break;
		case 3:mChannel3=3;break;
		case 4:mChannel4=4;break;
	}
}

/*** Distructor	***/	
Motor::~Motor()
{

}
void Motor::InitMotor()
{
	
	if(mChannel1)
		mPwm.SetDuty(mChannel1,0);
	if(mChannel2)
		mPwm.SetDuty(mChannel2,0);
	if(mChannel3)
		mPwm.SetDuty(mChannel3,0);
	if(mChannel4)
		mPwm.SetDuty(mChannel4,0);
	
	Delay delayS;		
	delayS.S(1);
	
	if(mChannel1)
		mPwm.SetDuty(mChannel1,70);
	if(mChannel2)
		mPwm.SetDuty(mChannel2,70);
	if(mChannel3)
		mPwm.SetDuty(mChannel3,70);
	if(mChannel4)
		mPwm.SetDuty(mChannel4,70);

}
/***	the map of duty to rotate-speed		***/
void Motor::DutyToRspeed()
{
	
}

/***	Set the rotate speed	***/
void Motor::SetRotateSpeeed(u16 rSpeed)
{
	u16 power=0;
//	if(mIsReverse)
//		power=100-rSpeed;
//	else
		power=rSpeed/4+60;
	
	if(mChannel1)
		mPwm.SetDuty(mChannel1,power);
	if(mChannel2)
		mPwm.SetDuty(mChannel2,power);
	if(mChannel3)
		mPwm.SetDuty(mChannel3,power);
	if(mChannel4)
		mPwm.SetDuty(mChannel4,power);
}

/***	Reload the function of 	SetRotateSpeeed***/
void Motor::SetRotateSpeeed(u8 channel,u16 rSpeed)
{
	u16 power=0;
	if(mIsReverse)
		power=100-rSpeed;
	else
		power=rSpeed;
	
	mPwm.SetDuty(channel,power);
}

/***	Get the rotate speed	***/
u16 Motor::GetRotateSpeed()
{
	return 0;
}

/***	Set the direction of rotation	***/
void Motor::SetDirection(bool dir)
{
//	mDir.SetLevel(dir);
}
