#include "CtrlDir.h"

CtrlDir::CtrlDir(Motor &leftMotor,Motor &rightMotor):mLeft(leftMotor),mRight(rightMotor)
{
	mLpower=0;
	mRpower=0;
	mDir=1;
}

CtrlDir::~CtrlDir()
{

}

void CtrlDir::Forward(u8 power)
{
	mLpower=power;							//make the left and the right motor same power 
	mRpower=power;
	
	mLeft.SetDirection(mDir);				//left motor rotate forward
	mLeft.SetRotateSpeeed(mLpower);
	
	mRight.SetDirection(mDir);				//right motor rotate forward
	mRight.SetRotateSpeeed(mRpower);
}

void CtrlDir::TurnLeft(u8 Ldegree)
{
	if(mLpower-Ldegree>MinPower)
		mLpower-=Ldegree;					//left motor decrease the power
	else if(mRpower+Ldegree<MaxPower)
		mRpower+=Ldegree;					//right motor increase the power
	
	mLeft.SetDirection(mDir);				//left motor rotate forward
	mLeft.SetRotateSpeeed(mLpower);
	
	mRight.SetDirection(mDir);				//right motor rotate forward
	mRight.SetRotateSpeeed(mRpower);
			
}

void CtrlDir::TurnRight(u8 Rdegree)
{
	if(mRpower-Rdegree>MinPower)
		mRpower-=Rdegree;					//right motor decrease the power
	else if(mLpower+Rdegree<MaxPower)
		mLpower+=Rdegree;					//left motor increase the power
	
	mLeft.SetDirection(mDir);				//left motor rotate forward
	mLeft.SetRotateSpeeed(mLpower);
	
	mRight.SetDirection(mDir);				//right motor rotate forward
	mRight.SetRotateSpeeed(mRpower);
}
void CtrlDir::Back(u8 power)
{
	mLpower=power;
	mRpower=power;
	
	mLeft.SetDirection(!mDir);				//left motor rotate backward
	mLeft.SetRotateSpeeed(mLpower);
	
	mRight.SetDirection(!mDir);				//right motor rotate backward
	mRight.SetRotateSpeeed(mRpower);
}
