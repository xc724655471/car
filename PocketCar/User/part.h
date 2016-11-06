


#ifndef	_PART_H
#define _PART_H

//#include "F103_PWM.h"
//#include "F103_ADC_S.h"
//#include "USART.h"
//#include "Voltage.h"
//#include "TaskManager.h"
//#include "Ultrasonic.h"
//#include "Transmission.h"
//#include "CtrlDir.h"
//#include "PressureModel.h"														//压力模型头文件

///*----------------2016-01-20-----------------*/
//#include "I2C.h"
//#include "Delay.h"
//#include "mpu6050.h"
//#include "GPIO.h"
///*----------------2016-01-20-----------------*/
//#include "Coordinate.h"
//#include "stdio.h"
/*----------------2016-02-27-----------------*/
#include "function.h"






#define X_1 30
#define X_2 60

volatile double curTime=0, oldTime=0, deltaT=0;				//定义时间
volatile uint8_t flagCount = 0;												//定义循环标志，2ms自增




////////////////////////////////u8 dataReceived[50];																	//定义的接收到的数据长度的大小



////////////////////////////////Float_Union adc1,adc2,adc3,adc4,adc5;									//定义一个共联体，存储ADC的值
////////////////////////////////Float_Union ultrasonicunion1,ultrasonicunion2;				//定义一个存储超声波数值的共用体

////////////////////////////////I2C iic(1);
////////////////////////////////mpu6050 mpu6050_(iic);
////////////////////////////////USART usart1(1,115200);																//使用中断
////////////////////////////////USART usart3(3,115200);																//使用中断
////////////////////////////////									
////////////////////////////////GPIO Trig(GPIOA,11,GPIO_Mode_Out_PP);									//定义一个GPIO的结构体，用于定义超声波的Trig引脚
////////////////////////////////GPIO Echo(GPIOA,8,GPIO_Mode_IPD);											//定义超声波的接收引脚
////////////////////////////////Ultrasonic u1(Trig,Echo,1,0,1);												//定义一个超声波对象

////////////////////////////////GPIO Trig2(GPIOA,6,GPIO_Mode_Out_PP);									//定义一个GPIO的结构体，用于定义超声波的Trig引脚
////////////////////////////////GPIO Echo2(GPIOA,7,GPIO_Mode_IPD);										//定义超声波的接收引脚
////////////////////////////////Ultrasonic u2(Trig2,Echo2,1,0,1);											//定义一个超声波对象

									
//GPIO leftDir (GPIOA,12,GPIO_Mode_Out_PP);							//定义一个GPIO用于控制左轮的正反转
//GPIO rightDir(GPIOB,12,GPIO_Mode_Out_PP);							//定义一个GPIO用于控制右轮的正反转
//PWM pwmT2(TIM2,1,1,0,0,400);													//define a PWM use TIM2,2 Channels 400HZ
//Motor leftMotor(pwmT2,1,leftDir,false);								//定义电机类，用于控制左轮
//Motor rightMotor(pwmT2,2,rightDir,false);							//用于定义右轮
//CoordinateControl coordinate(leftMotor,rightMotor);		//定义坐标类


//GPIO leftDir (GPIOA,12,GPIO_Mode_Out_PP);							//定义一个GPIO用于控制左轮的正反转
//GPIO rightDir(GPIOB,12,GPIO_Mode_Out_PP);							//定义一个GPIO用于控制右轮的正反转
////////////////////////////////PWM pwmT2(TIM2,1,1,0,0,400);													//define a PWM use TIM2,2 Channels 400HZ
////////////////////////////////Motor leftMotor(pwmT2,1,false);								//定义电机类，用于控制左轮
////////////////////////////////Motor rightMotor(pwmT2,2,false);							//用于定义右轮
////////////////////////////////CoordinateControl coordinate(leftMotor,rightMotor);		//定义坐标类

/////////////////////////////////*ADC测试*/
////////////////////////////////ADC adc(2,3,4,5,9);																		//初始化ADC通道，传入需要的通道，按照数组顺序输出
////////////////////////////////Voltage v4(adc.mAdcPrimordialValue,5);								//初始化一个Voltage类，用于计算和转换原始值.
////////////////////////////////PressureModel pressuremodel;													//设置一个压力模型，通过输入adc，得到压力

////////////////////////////////CtrlDir car(leftMotor,rightMotor);


////////////////////////////////u8 pwmLeft = 100;
////////////////////////////////u8 pwmRight = 100;
////////////////////////////////u8 power=10,leftDegree=0,rightDegree=0;




/////////////////////////////////////////////////////////////////////////////////
//////////////声明函数
/////////////////////////////////////////////////////////////////////////////////
void Control(void);
////////////////////////////////////////void updateCoordinate(void);			//ADC -> Coordinate
////////////////////////////////////////void PWMControl(void);						//for PWM Control
////////////////////////////////////////void updateUltrasonic(void);			//ultrasonic update
////////////////////////////////////////void updateMPU6050(void);					//MPU6050 update
////////////////////////////////////////void SendData(void);							//send message to upper machine

///////////////////////////////////////////////////////////////////////////////
/////////////用于测试的变量以及函数在这下面声明
////////////////////////////////////////////////////////////////////////////////
//u16 ultInteger;
//u8 ultDecimal;
//////////////////////////////////////////int accrawz;

//////////////////////////////////////////float p1;													//1号传感器测得的压力
//////////////////////////////////////////float p2;													//2号传感器测得的压力
//////////////////////////////////////////float p3;													//3号传感器测得的压力
//////////////////////////////////////////float p4;													//4号传感器测得的压力
//////////////////////////////////////////float pall;												//所有的重量


////////////////////////////////////////////////////
///@param:无
///@Description:更新重心坐标
////////////////////////////////////////////////////
////////////////////////////////////void updateCoordinate(void)
////////////////////////////////////{
////////////////////////////////////	/*ADC的计算*/
////////////////////////////////////	v4.Converted();
////////////////////////////////////	adc1.value = v4.mConvertedVoltage[0];
////////////////////////////////////	adc2.value = v4.mConvertedVoltage[1];
////////////////////////////////////	adc3.value = v4.mConvertedVoltage[2]*100;
////////////////////////////////////	adc4.value = v4.mConvertedVoltage[3];
////////////////////////////////////	adc5.value = v4.mConvertedVoltage[4];
////////////////////////////////////	
////////////////////////////////////	p1 = pressuremodel.VoltageToPressure(1,adc1.value);
////////////////////////////////////	p2 = pressuremodel.VoltageToPressure(2,adc2.value);
////////////////////////////////////	p3 = pressuremodel.VoltageToPressure(3,adc4.value);
////////////////////////////////////	p4 = pressuremodel.VoltageToPressure(4,adc5.value);
////////////////////////////////////	
////////////////////////////////////	pall = p1+p2+p3+p4;																								//计算重力
////////////////////////////////////	coordinate.BuildtheCoordinate(p1,p2,p3,p4);												//构建坐标
////////////////////////////////////	u8 coordinateTemplet[2] = {*coordinate.GetCoordinate(),*(coordinate.GetCoordinate()+1)};//声明一个暂时的坐标，并且获得坐标
////////////////////////////////////}









////////////////////////////////////////////////////
///@param:无
///@Description:控制PWM波
////////////////////////////////////////////////////
////////////////////////////////////////void PWMControl(void)
////////////////////////////////////////{

////////////////////////////////////////	if(pall>15)
////////////////////////////////////////	{
//////////////////////////////////////////		coordinate.mRemoteMode = 3;																				//设置成竞速模式
//////////////////////////////////////////		coordinate.Controlcar();																					//按照坐标来控制小车
////////////////////////////////////////		if(*coordinate.GetCoordinate()<30)//左转
////////////////////////////////////////		{
////////////////////////////////////////			leftMotor.SetRotateSpeeed(0);
////////////////////////////////////////			rightMotor.SetRotateSpeeed(16);
////////////////////////////////////////		}
////////////////////////////////////////		if(*coordinate.GetCoordinate()>80)//右转
////////////////////////////////////////		{
////////////////////////////////////////			leftMotor.SetRotateSpeeed(16);
////////////////////////////////////////			rightMotor.SetRotateSpeeed(0);
////////////////////////////////////////		}
////////////////////////////////////////		else
////////////////////////////////////////		{
////////////////////////////////////////			leftMotor.SetRotateSpeeed(8);
////////////////////////////////////////			rightMotor.SetRotateSpeeed(8);
////////////////////////////////////////		}
////////////////////////////////////////	}
////////////////////////////////////////	else
////////////////////////////////////////	{
////////////////////////////////////////		leftMotor.SetRotateSpeeed(0);
////////////////////////////////////////		rightMotor.SetRotateSpeeed(0);
////////////////////////////////////////	}
////////////////////////////////////////}

/////////////////////////////////////////////////////////////
///@param:无
///@Description:				更新超声波的数据，并且重新启动超声波
/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////void updateUltrasonic(void)
////////////////////////////////////////////////////{
////////////////////////////////////////////////////		float		ultrasonic = 0;																//超声波的值
////////////////////////////////////////////////////		float		ultrasonic2 = 0;															//超声波的值
////////////////////////////////////////////////////		ultrasonic= u1.Update();
////////////////////////////////////////////////////		ultrasonic2 = u2.Update();
////////////////////////////////////////////////////		/////////////////////////////////////
////////////////////////////////////////////////////		//////////			把小数和整数部分分离出来
////////////////////////////////////////////////////		/////////////////////////////////////
////////////////////////////////////////////////////		//		int	FloatValue = *reinterpret_cast<int*>(&ultrasonic);
////////////////////////////////////////////////////		//		int	Exp = (FloatValue>>23)&0xff;
////////////////////////////////////////////////////		//		int MantissaPart=(FloatValue&0x7fffff)|0x800000;		//尾数字段，23位加一个默认位，共24位。 
////////////////////////////////////////////////////		//		u8 theInteger = MantissaPart>>(150-Exp);
////////////////////////////////////////////////////		//		u8 theDecimal = MantissaPart&(0xffffff>>(Exp-126));	//取得小数部分
////////////////////////////////////////////////////		//		ultInteger = (int)ultrasonic;													//取整数
////////////////////////////////////////////////////		//		ultDecimal = (ultrasonic-ultInteger)*100;							//取两位小数
////////////////////////////////////////////////////		//		dataSend[5] = ultInteger;															//填充发送的超声波的整数部分
////////////////////////////////////////////////////		//		dataSend[6] = ultDecimal;															//填充发送的超声波的小数部分
////////////////////////////////////////////////////		ultrasonicunion1.value = ultrasonic;													//把float传给共用体
////////////////////////////////////////////////////		ultrasonicunion2.value = ultrasonic2;

////////////////////////////////////////////////////}


/////////////////////////////////////////////////////////////
///@param:无
///@Description:				更新MPU6050的数据
/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////void updateMPU6050(void)
////////////////////////////////////////////////////////{
////////////////////////////////////////////////////////		if(MOD_ERROR== mpu6050_.Update())
////////////////////////////////////////////////////////		{
////////////////////////////////////////////////////////			usart1<<"error\n\n\n";
////////////////////////////////////////////////////////		}	
////////////////////////////////////////////////////////		accrawz = mpu6050_.GetAccRaw().z;
////////////////////////////////////////////////////////}



/////////////////////////////////////////////////////////////
///@param:无
///@Description:				向上位机发送数据
/////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////void SendData(void)
//////////////////////////////////////////////////////{

//////////////////////////////////////////////////////							/////////////////////////////////////////////////
//////////////////////////////////////////////////////							///////					测试从WIFI接收到的数据
//////////////////////////////////////////////////////							//////////////////////////////////////////////////
//////////////////////////////////////////////////////							if(usart3.ReceiveBufferSize()>0)
//////////////////////////////////////////////////////							{
//////////////////////////////////////////////////////								int receivedDataNum=usart3.ReceiveBufferSize();
//////////////////////////////////////////////////////								usart3.GetReceivedData(dataReceived,receivedDataNum);
////////////////////////////////////////////////////////									usart1.SendData(dataReceived,receivedDataNum);
//////////////////////////////////////////////////////								usart3.SendData(dataReceived,receivedDataNum);
//////////////////////////////////////////////////////							}
//////////////////////////////////////////////////////							///////////////////////////////////////////////
//////////////////////////////////////////////////////							///						下位机->上位机(暂时发送到USART1)
//////////////////////////////////////////////////////							//////////////////////////////////////////////
////////////////////////////////////////////////////////								usart1<<ultrasonicunion1.value<<"\t"
////////////////////////////////////////////////////////											<<ultrasonicunion1.value<<"\t"
////////////////////////////////////////////////////////											<<accrawz<<"\r\n";//测试成功，但是整数部分需要2个字节，因为测试的距离最多能达到400cm
//////////////////////////////////////////////////////							
//////////////////////////////////////////////////////							
//////////////////////////////////////////////////////							u8 SendDataofCoordinate[3] = {0xaa,*coordinate.GetCoordinate(),*(coordinate.GetCoordinate()+1)};
////////////////////////////////////////////////////////								usart1.SendData(SendDataofCoordinate,3);
//////////////////////////////////////////////////////							usart1<<p1<<" "
//////////////////////////////////////////////////////										<<p2<<" "
//////////////////////////////////////////////////////										<<p3<<" "
//////////////////////////////////////////////////////										<<p4<<" "
//////////////////////////////////////////////////////										<<pall<<"     ("
//////////////////////////////////////////////////////										<<*coordinate.GetCoordinate()<<"."
//////////////////////////////////////////////////////										<<*(coordinate.GetCoordinate()+1)
//////////////////////////////////////////////////////										<<")\r\n";
////////////////////////////////////////////////////////								char sp[100];
////////////////////////////////////////////////////////								sprintf(sp,"%f,%f,%f,%f",p1,p2,p3,p4);
////////////////////////////////////////////////////////								usart1<<sp;
//////////////////////////////////////////////////////							
////////////////////////////////////////////////////////									u8 SendDataofCoordinate[3] = {0xaa,dataReceived[2],dataReceived[3]};
////////////////////////////////////////////////////////									usart1.SendData(SendDataofCoordinate,3);
//////////////////////////////////////////////////////							
//////////////////////////////////////////////////////}






















































//////////////////////////////////////////////////////////////////////////////
//////////////传输字符串，不是按照十六进制传输的
//////////////////////////////////////////////////////////////////////////////
//								usart1
//								<<"\tadc1:"<<adc1.value<<"\tadc2:"<<adc2.value<<"\tadc3:"<<adc3.value
//								<<"\tadc4:"<<adc4.value<<"\tadc5:"<<adc5.value
////								<<"\tUltrasonic:"<<ultrasonic
////								<<"\n"
//								;
////								tskmgr.DelayMs(2);
//								usart1
//								<<"\tUltrasonic:"<<ultrasonic
//								
//								<<"\n"
//								;
//////////////////////////////////////////////////////////////////////////////
//////////////按照通信协议传输，即16进制
////////////////////////////////////////////////////////////////////////////////
//								usart1
//								<<"adc1:"<<adc1.float_byte.high_byte<<adc1.float_byte.mhigh_byte<<adc1.float_byte.mlow_byte<<adc1.float_byte.low_byte
//								<<"\tadc2:"<<adc2.float_byte.high_byte<<adc2.float_byte.mhigh_byte<<adc2.float_byte.mlow_byte<<adc2.float_byte.low_byte
//								<<"\tadc3:"<<adc3.float_byte.high_byte<<adc3.float_byte.mhigh_byte<<adc3.float_byte.mlow_byte<<adc3.float_byte.low_byte
//								<<"\tadc4:"<<adc4.float_byte.high_byte<<adc4.float_byte.mhigh_byte<<adc4.float_byte.mlow_byte<<adc4.float_byte.low_byte
//								<<"\tadc5:"<<adc5.float_byte.high_byte<<adc5.float_byte.mhigh_byte<<adc5.float_byte.mlow_byte<<adc5.float_byte.low_byte
////								<<"\tUltrasonic:"<<ultrasonic
//								<<"\n";
//								tskmgr.DelayMs(2);
//								if(usart1.ReceiveBufferSize()>0)
//								{
//									int receivedDataNum=usart1.ReceiveBufferSize();
//									usart1.GetReceivedData(dataReceived,receivedDataNum);
//									usart1.SendData(dataReceived,receivedDataNum);
//								}








#endif






