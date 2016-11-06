#include "Coordinate.h"

/**
 *@brife	初始化函数
 *@param	leftMotor: The reference of Motor,control the left motor.
 *@param	rightMotor: The reference of Motor,control the right motor.
 */
CoordinateControl::CoordinateControl(Motor &leftMotor,Motor &rightMotor):mLeft(leftMotor),mRight(rightMotor)
{
	mStartFlag = false;						//开始标志位为false
	mStartCount = 0;							//从零开始计数
}

/**
 *@brife	设置坐标值
 */
void CoordinateControl::SetCoordinate(u8 coordinate[2])
{
	mCoordinate[0] = coordinate[0];
	mCoordinate[1] = coordinate[1];
}

/**
 *@brife	获得当前用于控制的坐标值
 */
u8* CoordinateControl::GetCoordinate()
{
	return mCoordinate;
}

/**
 *@brife	通过各个通道的重力构建坐标,暂时以正方形为坐标区域，（x，y）（0~100,0~100）
 *				根据公式：
 *						  m1*x1+m2*x2+m3*x3+m4*x4
 *				x = ——————————————————————————
 *									m1+m2+m3+m4
 *
 *
 * 						  m1*y1+m2*y2+m3*y3+m4*y4
 *				y = ——————————————————————————
 *									m1+m2+m3+m4
 *				来确定坐标。
 *@param	gravity_ch1: The gravity of channel1
 *@param	gravity_ch2: The gravity of channel2
 *@param	gravity_ch3: The gravity of channel3
 *@param	gravity_ch4: The gravity of channel4
 */
void CoordinateControl::BuildtheCoordinate(float gravity_ch1,float gravity_ch2,float gravity_ch3,float gravity_ch4)
{
	 mCoordinate[0] = (100*gravity_ch2+100*gravity_ch3)/(gravity_ch1+gravity_ch2+gravity_ch3+gravity_ch4);
	 mCoordinate[1] = (100*gravity_ch1+100*gravity_ch2)/(gravity_ch1+gravity_ch2+gravity_ch3+gravity_ch4);
}


/**
 *@brife	通过调用这个函数控制小车的前后左右停，2ms调用一次
 */
void CoordinateControl::Controlcar()
{
	switch(mRemoteMode)
	{
		case 1:PressureControl();break;
		case 2:RemoteControl();break;
		case 3:RaceControl();break;
	}
}





/**
 *@brife	压力控制模式，确定重心不偏移250次计数之后才启动
 */
void CoordinateControl::PressureControl()
{	
//	if(!mStartFlag)		//判断是否启动
//	{
//		if(mCoordinate[0]>=X_LEFT && mCoordinate[0]<=X_LEFT && mCoordinate[1]>=Y_BACK && mCoordinate[1]<=100)
//		{
//			mStartCount++;
//			if(mStartCount>250)		//500ms内确定状态稳定
//			{
//				mStartCount = 0;
//				mStartFlag = true;
//			}
//		}
//		else 
//			mStartCount = 0;
//		return ;
//	}
	
	if(mCoordinate[0]>=X_LEFT && mCoordinate[0]<=X_RIGHT && mCoordinate[1]>=Y_BACK && mCoordinate[1]<=100)		//前进范围内
	{
		mLeft.SetRotateSpeeed(50);
		mRight.SetRotateSpeeed(50);
	}
	else if(mCoordinate[0]<X_LEFT && mCoordinate[1]>=Y_BACK && mCoordinate[1]<=100)		//左转范围
	{
		mLeft.SetRotateSpeeed(20);
		mRight.SetRotateSpeeed(50);
	}
	else if(mCoordinate[0]<=100 && mCoordinate[0]>X_RIGHT && mCoordinate[1]>=Y_BACK && mCoordinate[1]<=100)	//右转范围
	{
		mLeft.SetRotateSpeeed(50);
		mRight.SetRotateSpeeed(20);
	}
	else if(mCoordinate[0]<=100 && mCoordinate[1]<Y_BACK)	//后退范围
	{
//暂定停止
		mLeft.SetRotateSpeeed(0);
		mRight.SetRotateSpeeed(0);
	}
	else		//非范围内停止
	{
		mStartFlag = false;
		mLeft.SetRotateSpeeed(0);
		mRight.SetRotateSpeeed(0);
	}
}

/**
 *@brife	压力控制竞速模式
 */

void CoordinateControl::RaceControl()
{
	u16 speed;
	
	u16 k_left = (100*mCoordinate[0])/X_LEFT*80/2;
	u16 k_right = 100*(100-mCoordinate[0])/(100-X_RIGHT)*80/2;
	
//	if(!mStartFlag)		//判断是否启动
//	{
//		if(mCoordinate[0]>=X_LEFT && mCoordinate[0]<=X_LEFT && mCoordinate[1]>=Y_BACK && mCoordinate[1]<=100)
//		{
//			mStartCount++;
//			if(mStartCount>250)		//500ms内确定状态稳定
//			{
//				mStartCount = 0;
//				mStartFlag = true;
//			}
//		}
//		else 
//			mStartCount = 0;
//		return ;
//	}
	
	if(mCoordinate[0]>=X_LEFT && mCoordinate[0]<=X_RIGHT && mCoordinate[1]>=Y_BACK && mCoordinate[1]<=100)		//前进
	{
		speed = ((100-Y_BACK)*(mCoordinate[1]-Y_BACK))/100;
		mLeft.SetRotateSpeeed(speed);
		mRight.SetRotateSpeeed(speed);
	}
	else if(mCoordinate[0]<X_LEFT && mCoordinate[1]>Y_BACK && mCoordinate[1]<=100)		//左转范围
	{
		speed = k_left/100;
		mLeft.SetRotateSpeeed(speed);
		mRight.SetRotateSpeeed(80);
	}
	else if(mCoordinate[0]<=100 && mCoordinate[0]>=X_RIGHT && mCoordinate[1]>=Y_BACK && mCoordinate[1]<=100)	//右转范围
	{
		speed = k_right/100; 
		mLeft.SetRotateSpeeed(80);
		mRight.SetRotateSpeeed(speed);
	}
	else if(mCoordinate[0]<=100 && mCoordinate[1]<Y_BACK)	//后退范围
	{
//暂定停止
		mLeft.SetRotateSpeeed(0);
		mRight.SetRotateSpeeed(0);
	}
	else		//非范围内停止
	{
		mStartFlag = false;
		mLeft.SetRotateSpeeed(0);
		mRight.SetRotateSpeeed(0);
	}
}


/**
 *@brife	遥控模式
 */
void CoordinateControl::RemoteControl()
{
	u16 k = 173;			//斜率 偏离y轴30度
	u16 k_forward = 0;
	u16 k_back = 0;
	u16 radius = 50;
	u8 x = mCoordinate[0];
	u8 y = mCoordinate[1];
	
	if(x==50 && y==50)																						//停止
	{
		mLeft.SetRotateSpeeed(0);
		mRight.SetRotateSpeeed(0);
		return ;
	}
	if(x>50)
	{
		k_forward = (y-50)*100/(x-50);
		k_back = (50-y)*100/(x-50);
	}
	else if(x<50)
	{
		k_forward = (y-50)*100/(50-x);
		k_back = ((50-y)*100)/(50-x);
	}
	
	if(((x-50)*(x-50)+(y-50)*(y-50))>radius*radius)										//非范围内停止
	{
		mLeft.SetRotateSpeeed(0);
		mRight.SetRotateSpeeed(0);
		return ;
	}
	else if((x==50 && y>50)||(y>50 && k_forward>=k))							//前进范围
	{
		SetMotor(true,true,(y-50)*2,(y-50)*2);
	}
	else if((y>=50 && x>50) && k_forward<k)												//右前进范围
	{
		radius = (u16)sqrt((float)((x-50)*(x-50)+(y-50)*(y-50)));
		SetMotor(true,true,radius*2,(radius*2*(100-(k-k_forward)*100/k))/100);
	}
	else if((y>=50 && x<50) && k_forward<k)												//左前进范围
	{
		radius = (u16)sqrt((float)((50-x)*(50-x)+(y-50)*(y-50)));
		SetMotor(true,true,(radius*2*(100-(k-k_forward)*100/k))/100,radius*2);
	}
	else if((x==50 && y<50) || (y<50 && k_back>=k))							//后退范围
	{
		SetMotor(false,false,(50-y)*2,(50-y)*2);
	}
	else if((y<50 && x>50) && k_back<k)														//右后退范围	
	{
		radius = (u16)sqrt((float)((x-50)*(x-50)+(50-y)*(50-y)));
		SetMotor(false,false,radius*2,(radius*2*(100-(k-k_back)*100/k))/100);
	}
	else if((y<50 && x<50) && k_back<k)														//左后退范围
	{
		radius = (u16)sqrt((float)((50-x)*(50-x)+(50-y)*(50-y)));
		SetMotor(false,false,(radius*2*(100-(k-k_back)*100/k))/100,radius*2);
	}
}



/**
 *@brife	设置电机的函数
 *@param	ml: 左电机方向
 *@param	mr: 右电机方向
 *@param	lspeed: 左电机速度
 *@param	rspeed: 右电机速度
 */
void CoordinateControl::SetMotor(bool ml,bool mr,u16 lspeed,u16 rspeed)
{
	mLeft.SetDirection(ml);
	mRight.SetDirection(mr);
	mLeft.SetRotateSpeeed(lspeed);
	mRight.SetRotateSpeeed(rspeed);
}


/**
 *@brife	Distructor.
 */
CoordinateControl::~CoordinateControl()
{}
