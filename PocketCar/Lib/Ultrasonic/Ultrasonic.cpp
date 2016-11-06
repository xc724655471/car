#include "Ultrasonic.h"
#include "UltrasonicInt.h"

/***	Constructor	***/
Ultrasonic::Ultrasonic(GPIO &Trig,GPIO &Echo,uint8_t NVICPriorityGroup,uint8_t NVICPreemptionPriority,uint8_t NVICSubPriority)
			:mTrig(Trig),mEcho(Echo),mExti(mEcho.mPort,mEcho.mSelectPin,GPIO_Mode_IPD,NVICPriorityGroup,NVICPreemptionPriority,NVICSubPriority,EXTI_Mode_Interrupt,EXTI_Trigger_Rising_Falling)
{
	#if	EXTI0IRQHandler
	if(mEcho.mSelectPin == 0)
		Uexti0=this;
	#endif

	#if	EXTI1IRQHandler
	if(mEcho.mSelectPin == 1)
		Uexti1=this;
	#endif

	#if	EXTI2IRQHandler
	if(mEcho.mSelectPin == 2)
		Uexti2=this;
	#endif

	#if	EXTI3IRQHandler
	if(mEcho.mSelectPin == 3)
		Uexti3=this;
	#endif

	#if	EXTI4IRQHandler
	if(mEcho.mSelectPin == 4)
		Uexti4=this;
	#endif

	#if	EXTI9_5IRQHandler
	switch (mEcho.mSelectPin)
	{
		case 5:if(mEcho.mSelectPin == 5)	Uexti5=this;break;
		case 6:if(mEcho.mSelectPin == 6)	Uexti6=this;break;
		case 7:if(mEcho.mSelectPin == 7)	Uexti7=this;break;;
		case 8:if(mEcho.mSelectPin == 8)	Uexti8=this;break;
		case 9:if(mEcho.mSelectPin == 9)	Uexti9=this;break;
	}
	#endif

	#if	EXTI15_10IRQHandler
	switch (mEcho.mSelectPin)
	{
		case 10:if(mEcho.mSelectPin == 10) Uexti10=this;break;
		case 11:if(mEcho.mSelectPin == 11) Uexti11=this;break;
		case 12:if(mEcho.mSelectPin == 12) Uexti12=this;break;;
		case 13:if(mEcho.mSelectPin == 13) Uexti13=this;break;
		case 14:if(mEcho.mSelectPin == 14) Uexti14=this;break;
		case 15:if(mEcho.mSelectPin == 15) Uexti15=this;break;
	}
	#endif

	//引脚全部初始化为低电平
	mTrig.SetLevel(0);
	mEcho.SetLevel(0);
	
	//变量初始化
	
	mDistance=0;
	
	mIntervalTime=0;
	mFinishFlag=false;
	mTimeOut=false;
}


/***	Destructor	***/
Ultrasonic::~Ultrasonic()
{
	
	mExti.CloseExtiInt();							//Close the interrupt of Exti
}

/*	Start the ultrsonic module	*/
void Ultrasonic::UltrasonicStart()
{
	mStartFlag=false;
	mEcho.SetLevel(0);								//确保接收管脚低电平
	
	mTrig.SetLevel(1);								//拉高Trig引脚，使其高电平保持10us以上即发送超声波
	
	mExti.OpenExtiInt();							//打开相应管脚的外部中断
	
	tskmgr.DelayUs(15);								//使高电平持续10us以上
	
	mTrig.SetLevel(0);								//使Trig引脚变为低电平，方便下次启动
	
}



void Ultrasonic::UltrasonicIrq()
{
	if(mEcho.GetLevel())							//说明是上升沿跳变
	{
		mIntervalTime=tskmgr.Time();
		mStartFlag=true;
	}
	else											//下降沿跳变
	{
		mIntervalTime=tskmgr.Time()-mIntervalTime;	//保存间隔时间
		
		if(mStartFlag)								//mStartFlag每次启动前都会被初始为0，确保不是调用启动函数导致Echo的下降沿
		{
			mExti.CloseExtiInt();					//关闭外部中断线路
			
			mFinishFlag=true;						//将完成标志置1
		}
		else										
		{
			if(mIntervalTime>=0.03)					
				mTimeOut=true;						//超时标志置1
		}
	}
}

/***	Calculate the distance	***/
void Ultrasonic::CalculateDistance()
{
	if(mTimeOut)
	{
		mTimeOut=false;
			mDistance=0xffff;
	}
	else if(mFinishFlag)
	{
		if((mIntervalTime>0.00012)&&(mIntervalTime<0.03))				//测得的距离在有效范围内
		{
			mDistance=mIntervalTime*17000;	
		}
		mIntervalTime=0;
		mFinishFlag=false;
	}
}

/***	Get the distance 	***/
float Ultrasonic::GetDistance()
{
	if(mFinishFlag||mTimeOut)
	{
		CalculateDistance();
	}
	
	return mDistance;
}

/***	Start the Ultrasonic module and get the last distance	***/
float Ultrasonic::Update()
{
	UltrasonicStart();
	return GetDistance();
}
