/**
*@file function.h
*@author 2016-2-226 Allen
*@version v0.1
*@brief 主要抽象地实现小车的功能，用于整合片上的ADC，IIC，PWM，USART，Systick，Interrupt
			等功能，实现片外的MPU6050，Moter，Ultrasonic等功能；调动具体的底层代码的实现
*@copyright CQUTIOTLIB all right reserved
*
*/



#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include "F103_PWM.h"
#include "F103_ADC_S.h"
#include "USART.h"
#include "Voltage.h"
#include "TaskManager.h"
#include "Ultrasonic.h"
#include "Transmission.h"
#include "CtrlDir.h"
#include "PressureModel.h"														//压力模型头文件

/*----------------2016-01-20-----------------*/
#include "I2C.h"
#include "Delay.h"
#include "mpu6050.h"
#include "GPIO.h"
/*----------------2016-01-20-----------------*/
#include "Coordinate.h"
#include "stdio.h"


/**
 *坐标变化的可接受范围
 */
#define theAcceptLimit 5										


class Function
{
	private:
/*******************************各种功能的成员变量***************************************************/	
		I2C mIic;
		USART mUsart1;																//使用中断的USART
		USART mUsart3;																//使用中断的USART
/****************************************************************************************************/
	
/****************************************************************************************************/
/*******************************传输的数据成员变量***************************************************/	
		u8 mdataReceived[50];																//定义的接收到的数据长度的大小
		u8 mTransmissionHead[2];														//包头---------------------------2字节							
		u8 mDeviceNumber[4];																//设备号-------------------------4字节							
		u8 mDumpEnergy;																			//剩余电量-----------------------1字节
		u8 mMileage[4];																			//里程数-------------------------4字节
		u8 mUltrasonic[4];																	//超声波-------------------------4字节
		u8 mWheelSpeed[2];																	//两个轮子的速度(左右)-----------2字节
		u8 mCoordinates[2];																	//四个点的重心坐标---------------2字节
		u8 mMPUdata[4];																			//MPU6050数据--------------------4字节
		u8 mSignalBootTime;																	//单次开机时间-------------------1字节
		u8 mSignalTravelTime[2];														//单次出行时间-------------------2字节
		u8 mSignalTravelDistance[2];												//单次出行距离-------------------2字节
		u8 mLoad;																						//负载---------------------------1字节
		u8 mOnOff;																					//开锁解锁状态，开关灯-----------1字节
		u8 mHeartbaat;																			//心跳包-------------------------1字节
		u8 mTheKeepByte[6];																	//保留字节-----------------------6字节
		u8 mFirmwareVersion[2];															//固件版本-----------------------2字节
		u8 mAndChick;																				//和校验-------------------------1字节
/****************************************************************************************************/	
	
	
/****************************************************************************************************/
/*******************************测量重心的成员变量***************************************************/	

		Float_Union mAdc1,mAdc2,mAdc3,mAdc4,mAdc5;					//定义一个共联体，存储ADC的值
		ADC mAdc;																						//定义ADC通道，传入需要的通道，按照数组顺序输出
		Voltage mV4;																				//定义一个Voltage类，用于计算和转换原始值
		float mPressure1;																		//编号1的压力传感器测出的压力值
		float mPressure2;																		//编号2的压力传感器测出的压力值
		float mPressure3;																		//编号3的压力传感器测出的压力值
		float mPressure4;																		//编号4的压力传感器测出的压力值
		float mPressureAll;																	//所有的压力值总和
		PressureModel mPressuremodel;												//设置一个压力模型，通过输入adc，得到压力
/****************************************************************************************************/	



/****************************************************************************************************/
/*******************************控制电机的成员变量***************************************************/	

//		GPIO leftDir (GPIOA,12,GPIO_Mode_Out_PP);							//定义一个GPIO用于控制左轮的正反转
//		GPIO rightDir(GPIOB,12,GPIO_Mode_Out_PP);							//定义一个GPIO用于控制右轮的正反转
		PWM mPwmT2;																					//define a PWM use TIM2,2 Channels 400HZ
		Motor mLeftMotor;																		//定义电机类，用于控制左轮
		Motor mRightMotor;																	//用于定义右轮
		CoordinateControl mCoordinate;											//定义坐标类
/****************************************************************************************************/


/****************************************************************************************************/
/*******************************超声测距的成员变量***************************************************/	

		GPIO mTrig;											//定义一个GPIO的结构体，用于定义超声波的Trig引脚
		GPIO mEcho;											//定义超声波的接收引脚
		Ultrasonic mUltrasonic1;				//定义一个超声波对象

		GPIO mTrig2;										//定义一个GPIO的结构体，用于定义超声波的Trig引脚
		GPIO mEcho2;										//定义超声波的接收引脚
		Ultrasonic mUltrasonic2;				//定义一个超声波对象
		Float_Union mUltrasonicunion1,mUltrasonicunion2;				//定义一个存储超声波数值的共用体
/****************************************************************************************************/	


		
	




/****************************************************************************************************/	
/*******************************MPU6050的成员变量****************************************************/	
		
		mpu6050 mMpu6050_;
		int mAccrawz;
/****************************************************************************************************/	


/****************************************************************************************************/	
/*****************************存储获取到的时间的成员变量*********************************************/	
/**
 * @在这里比较想说明一下，因为主函数里面有控制时间的变量；但是这里的记录时间的变量是为了判断初始化重心
 *	是否达到平稳的状态；所以也在纠结是否能够把这些东西都独立出去，特别是之前的发送数据那一块，能作为
 *	成员变量的形式发出去吗？
 */
		double mCurTime;		//
		double mOldTime;
		double mDiffTime;
/****************************************************************************************************/	


/****************************************************************************************************/	
/******************************相对坐标差值的成员变量************************************************/	
		u8 mRelativeToX;
		u8 mRelativeToY;
		
/****************************************************************************************************/	


/****************************************************************************************************/	
/**************************计算相对坐标差值的成员函数************************************************/	
		void GetRelativeCoordinate(void);
/****************************************************************************************************/	

/****************************************************************************************************/	
/**************************各种状态***********************************************/	
		u8 ManLoad;
		u8 MotorIDEL;
		int count;					//计数
/****************************************************************************************************/	

	
	
	public:
		Function();
	
		void setMTransmissionHead(u8 TransmissionHead[2]);					//填充包头
		void setMDeviceNumber(u8 DeviceNumber[4]);									//填充设备号
		void setMDumpEnergy(u8 DumpEnergy);													//填充剩余电量
		void setMMileage(u8 Mileage[4]);														//填充总里程数
		void setMUltrasonic(u8 Ultrasonic[4]);											//填充超声波测量的距离
		void setMWheelSpeed(u8 WheelSpeed[2]);											//填充两个轮子的速度
		void setMCoordinates(u8 Coordinates[2]);										//填充测量后的重心坐标
		void setMMPUdata(u8 MPUdata[4]);														//填充从MPU里面获取的数据
		void setMSignalBootTime(u8 SignalBootTime);									//填充单次开机时间
		void setMSignalTravelTime(u8 SignalTravelTime[2]);					//填充单次出行时间
		void setMSignalTravelDistance(u8 SignalTravelDistance[2]);	//填充单次出行距离
		void setMLoad(u8 Load);																			//填充负载（单位kg）
		void setMOnOff(u8 OnOff);																		//按照协议填写开关状态
		void setMHeartbaat(u8 Heartbaat);														//填写心跳包
		void setMTheKeepByte(u8 TheKeepByte[6]);										//填写保留字节
		void setMFirmwareVersion(u8 FirmwareVersion[2]);						//填写固件版本
		void setMAndChick(u8 AndChick);															//填写和校验
	
		u8* getMTransmissionHead();																	//获取包头
		u8* getMDeviceNumber();																			//获取设备号
		u8* getMDumpEnergy();																				//获取剩余电量
		u8* getMMileage();																					//获取总里程数
		u8* getMUltrasonic();																				//获取超声波测量的距离
		u8* getMWheelSpeed();																				//获取两个轮子的速度
		u8* getMCoordinates();																			//获取测量后的重心坐标
		u8* getMMPUdata();																					//获取从MPU里面获取的数据
		u8* getMSignalBootTime();																		//获取单次开机时间
		u8* getMSignalTravelTime();																	//获取单次出行时间
		u8* getMSignalTravelDistance();															//获取单次出行距离
		u8* getMLoad();																							//获取负载（单位kg）
		u8* getMOnOff();																						//获取按照协议开关状态
		u8* getMHeartbaat();																				//获取心跳包
		u8* getMTheKeepByte();																			//获取保留字节
		u8* getMFirmwareVersion();																	//获取固件版本
		u8* getMAndChick();																					//获取 和校验
		
		



/**
	* 初始化函数，初始化各种器件等
	* @param void
	*/
	
int InitTheRelativeCoordinate(void);


/**
	* 初始化函数，初始化各种器件等
	* @param void
	*/
	
	void InitTwoMotor(void);

/**
	* 初始化函数，初始化各种器件等
	* @param void
	*/
	
	void InitMPU6050(void);
		
/**
	*	通过ADC测量重心的坐标，范围在0-100
	* @param void
	*/
	
	void UpdateCoordinate(void);
	
/**
	*	PWM控制，输出给电调来控制电机
	* @param void
	*/
	
	void PWMControl(void);	
	
/**
	*	更新超声波测量的数据
	* @param void
	*/
	
	void UpdateUltrasonic(void);	

/**
	*	更新MPU6050的数据
	* @param void
	*/
	
	void UpdateMPU6050(void);	

/**
	* 发送数据
	* @param void
	*/
	
	void SendData(void);
};



extern Function function;








#endif



