#include "function.h"

Function function;

Function::Function():
										 mIic(1)
										,mUsart1(1,115200)
										,mUsart3(3,115200)
										,mAdc(2,3,4,5,9)
										,mV4(mAdc.mAdcPrimordialValue,5)
										,mPwmT2(TIM2,1,1,0,0,400)
										,mLeftMotor(mPwmT2,1,false)
										,mRightMotor(mPwmT2,2,false)
										,mCoordinate(mLeftMotor,mRightMotor)
										,mTrig(GPIOA,11,GPIO_Mode_Out_PP)
										,mEcho(GPIOA,8,GPIO_Mode_IPD)
										,mUltrasonic1(mTrig,mEcho,1,0,1)
										,mTrig2(GPIOA,6,GPIO_Mode_Out_PP)
										,mEcho2(GPIOA,7,GPIO_Mode_IPD)
										,mUltrasonic2(mTrig2,mEcho2,1,0,1)
										,mMpu6050_(mIic)
{
			u8 dataSendTemplt[40] = {						//定义发送的40个字节
			0xaa,0xaa														//包头---------------------------2字节
			,0x00,0x00,0x00,0x00								//设备号-------------------------4字节
			,0x00																//电量---------------------------1字节
			,0x00,0x00,0x00,0x00								//里程数-------------------------4字节
			,0x00,0x00,0x00,0x00								//超声波-------------------------4字节
			,0x00,0x00													//两个轮子的速度(左右)-----------2字节
			,0x00,0x00													//四个点的重心坐标---------------2字节
			,0x00,0x00,0x00,0x00								//MPU6050数据--------------------4字节
			,0x00																//单次开机时间-------------------1字节
			,0x00,0x00													//单次出行时间-------------------2字节
			,0x00,0x00													//单次出行距离-------------------2字节
			,0x00																//负载---------------------------1字节
			,0x00																//开锁解锁状态，开关灯-----------1字节
			,0x00																//心跳包-------------------------1字节
			,0x00,0x00,0x00,0x00,0x00,0x00			//保留字节-----------------------6字节
			,0x00,0x00													//固件版本-----------------------2字节
			,0x00																//和校验-------------------------1字节
			};
			///////////////////////////////////////////
			////初始化包头
			//////////////////////////////////////////
			mTransmissionHead[0] = dataSendTemplt[0];
			mTransmissionHead[1] = dataSendTemplt[1];
			///////////////////////////////////////////
			////初始化设备号
			//////////////////////////////////////////						
			mDeviceNumber[0] = dataSendTemplt[2];
			mDeviceNumber[1] = dataSendTemplt[3];
			mDeviceNumber[2] = dataSendTemplt[4];
			mDeviceNumber[3] = dataSendTemplt[5];
			///////////////////////////////////////////
			////初始剩余电量
			//////////////////////////////////////////						
			mDumpEnergy = dataSendTemplt[6];
			///////////////////////////////////////////
			////初始化总里程数
			//////////////////////////////////////////						
			mMileage[0] = dataSendTemplt[7];
			mMileage[1] = dataSendTemplt[8];
			mMileage[2] = dataSendTemplt[9];
			mMileage[3] = dataSendTemplt[10];
			///////////////////////////////////////////
			////初始化超声波测量的距离
			//////////////////////////////////////////
			mUltrasonic[0] = dataSendTemplt[11];
			mUltrasonic[1] = dataSendTemplt[12];
			mUltrasonic[2] = dataSendTemplt[13];
			mUltrasonic[3] = dataSendTemplt[14];
			///////////////////////////////////////////
			////初始化两个轮的速度
			//////////////////////////////////////////
			mWheelSpeed[0] = dataSendTemplt[15];
			mWheelSpeed[1] = dataSendTemplt[16];
			///////////////////////////////////////////
			////初始化重心坐标
			//////////////////////////////////////////
			mCoordinates[0] = dataSendTemplt[17];
			mCoordinates[1] = dataSendTemplt[18];
			///////////////////////////////////////////
			////初始化MPU的数据
			//////////////////////////////////////////
			mMPUdata[0] = dataSendTemplt[19];
			mMPUdata[1] = dataSendTemplt[20];
			mMPUdata[2] = dataSendTemplt[21];
			mMPUdata[3] = dataSendTemplt[22];
			///////////////////////////////////////////
			////初始化单次开机时间
			//////////////////////////////////////////
			mSignalBootTime = dataSendTemplt[23];
			///////////////////////////////////////////
			////初始化单次出行时间
			//////////////////////////////////////////
			mSignalTravelTime[0] = dataSendTemplt[24];
			mSignalTravelTime[1] = dataSendTemplt[25];
			///////////////////////////////////////////
			////初始化单次出行距离
			//////////////////////////////////////////
			mSignalTravelDistance[0] = dataSendTemplt[26];
			mSignalTravelDistance[1] = dataSendTemplt[27];
			///////////////////////////////////////////
			////初始化负载
			//////////////////////////////////////////
			mLoad = dataSendTemplt[28];
			///////////////////////////////////////////
			////初始化各种开关状态
			//////////////////////////////////////////
			mOnOff = dataSendTemplt[29];
			///////////////////////////////////////////
			////初始化心跳包
			//////////////////////////////////////////
			mHeartbaat = dataSendTemplt[30];
			///////////////////////////////////////////
			////初始化保留字节
			//////////////////////////////////////////
			mTheKeepByte[0] = dataSendTemplt[31];
			mTheKeepByte[1] = dataSendTemplt[32];
			mTheKeepByte[2] = dataSendTemplt[33];
			mTheKeepByte[3] = dataSendTemplt[34];
			mTheKeepByte[4] = dataSendTemplt[35];
			mTheKeepByte[5] = dataSendTemplt[36];
			///////////////////////////////////////////
			////初始化固件版本号
			//////////////////////////////////////////
			mFirmwareVersion[0] = dataSendTemplt[37];
			mFirmwareVersion[1] = dataSendTemplt[38];
			///////////////////////////////////////////
			////初始化和校验
			//////////////////////////////////////////
			mAndChick = dataSendTemplt[39];

}

/**
	* 填充包头
	* @param TransmissionHead[2] 包头
	*/
void Function::setMTransmissionHead(u8 TransmissionHead[2])
{
	mTransmissionHead[0] = TransmissionHead[0];
	mTransmissionHead[1] = TransmissionHead[1];
}

/**
	* 填充设备号
	* @param DeviceNumber[4]设备号
	*/
void Function::setMDeviceNumber(u8 DeviceNumber[4])
{
	mDeviceNumber[0] = DeviceNumber[0];
	mDeviceNumber[1] = DeviceNumber[1];
	mDeviceNumber[2] = DeviceNumber[2];
	mDeviceNumber[3] = DeviceNumber[3];
}
/**
	* 填充剩余电量
	* @param DumpEnergy剩余电量
	*/
void Function::setMDumpEnergy(u8 DumpEnergy)
{
	mDumpEnergy = DumpEnergy;
}
/**
	*填充总里程数
	* @param Mileage[4]总里程数
	*/
void Function::setMMileage(u8 Mileage[4])
{
	mMileage[0] = Mileage[0];
	mMileage[1] = Mileage[1];
	mMileage[2] = Mileage[2];
	mMileage[3] = Mileage[3];
}
/**
	*填充超声波测量的距离
	* @param Ultrasonic[4]超声波测量的距离
	*/
void Function::setMUltrasonic(u8 Ultrasonic[4])
{
	mUltrasonic[0] = Ultrasonic[0];
	mUltrasonic[1] = Ultrasonic[1];
	mUltrasonic[2] = Ultrasonic[2];
	mUltrasonic[3] = Ultrasonic[3];
}
/**
	*填充两个轮子的速度
	* @param WheelSpeed[2]左右轮速度
	*/
void Function::setMWheelSpeed(u8 WheelSpeed[2])
{
	mWheelSpeed[0] = WheelSpeed[0];
	mWheelSpeed[1] = WheelSpeed[1];
}
/**
	*填充测量后的重心坐标
	* @param Coordinates[2]重心坐标
	*/
void Function::setMCoordinates(u8 Coordinates[2])
{
	mCoordinates[0] = Coordinates[0];
	mCoordinates[1] = Coordinates[1];
}
/**
	*填充MPU的数据
	* @param MPUdata[4]MPU获取的方位等数据
	*/
void Function::setMMPUdata(u8 MPUdata[4])
{
	mMPUdata[0] = MPUdata[0];
	mMPUdata[1] = MPUdata[1];
	mMPUdata[2] = MPUdata[2];
	mMPUdata[3] = MPUdata[3];
}
/**
	*填充单次开机时间
	* @param SignalBootTime单次开机时间
	*/
void Function::setMSignalBootTime(u8 SignalBootTime)
{
	mSignalBootTime = SignalBootTime;
}
/**
	*填充单次出行时间
	* @param SignalTravelTime[2]填充单次出行时间
	*/
void Function::setMSignalTravelTime(u8 SignalTravelTime[2])
{
	mSignalTravelTime[0] = SignalTravelTime[0];
	mSignalTravelTime[1] = SignalTravelTime[1];
}
/**
	*填充单次出行距离
	* @param SignalTravelDistance[2]填充单次出行距离
	*/
void Function::setMSignalTravelDistance(u8 SignalTravelDistance[2])
{
	mSignalTravelDistance[0] = SignalTravelDistance[0];
	mSignalTravelDistance[1] = SignalTravelDistance[1];
}
/**
	*填充负载（单位kg）
	* @param Load填充负载（单位kg）
	*/
void Function::setMLoad(u8 Load)
{
	mLoad = Load;
}
/**
	*按照协议填写开关状态
	* @param OnOff 开关状态 每位代表一种设备的开关状态
	*/
void Function::setMOnOff(u8 OnOff)
{
	mOnOff = OnOff;
}
/**
	*填写心跳包
	* @param Heartbaat填写心跳包
	*/
void Function::setMHeartbaat(u8 Heartbaat)
{
	mHeartbaat = Heartbaat;
}
/**
	*填写保留字节
	* @param TheKeepByte[6]保留字节
	*/
void Function::setMTheKeepByte(u8 TheKeepByte[6])
{
	mTheKeepByte[0] = TheKeepByte[0];
	mTheKeepByte[1] = TheKeepByte[1];
	mTheKeepByte[2] = TheKeepByte[2];
	mTheKeepByte[3] = TheKeepByte[3];
	mTheKeepByte[4] = TheKeepByte[4];
	mTheKeepByte[5] = TheKeepByte[5];
}
/**
	*填写固件版本
	* @param FirmwareVersion[2]固件版本
	*/
void Function::setMFirmwareVersion(u8 FirmwareVersion[2])
{
	mFirmwareVersion[0] = FirmwareVersion[0];
	mFirmwareVersion[1] = FirmwareVersion[1];
}
/**
	*填写和校验
	* @param AndChick和校验
	*/
void Function::setMAndChick(u8 AndChick)
{
	mAndChick = AndChick;
}







/**
	*获取包头
	* @retval 返回保存的包头-------2个字节
	*/
u8* Function::getMTransmissionHead()
{
	return mTransmissionHead;
}
/**
	*获取设备号
	* @retval 设备号-------4个字节
	*/
u8* Function::getMDeviceNumber()
{
	return mDeviceNumber;
}
/**
	*获取剩余电量
	* @retval 剩余电量-------1个字节
	*/
u8* Function::getMDumpEnergy()
{
	return &mDumpEnergy;
}
/**
	*获取总里程数
	* @retval 总里程数-------4个字节
	*/
u8* Function::getMMileage()
{
	return mMileage;
}
/**
	*获取超声波测量的距离
	* @retval 超声波测量的距离-------4个字节
	*/
u8* Function::getMUltrasonic()
{
	return mUltrasonic;
}
/**
	*获取两个轮子的速度
	* @retval 两个轮子的速度-------2个字节
	*/
u8* Function::getMWheelSpeed()
{
	return mWheelSpeed;
}
/**
	*获取测量后的重心坐标
	* @retval 测量后的重心坐标-------2个字节
	*/
u8* Function::getMCoordinates()
{
	return mCoordinates;
}
/**
	*获取从MPU里面获取的数据
	* @retval 从MPU里面获取的数据-------4个字节
	*/
u8* Function::getMMPUdata()
{
	return mMPUdata;
}
/**
	*获取单次开机时间
	* @retval 单次开机时间-------1个字节
	*/
u8* Function::getMSignalBootTime()
{
	return &mSignalBootTime;
}
/**
	*获取单次出行时间
	* @retval 单次出行时间-------2个字节
	*/
u8* Function::getMSignalTravelTime()
{
	return mSignalTravelTime;
}
/**
	*获取单次出行距离
	* @retval 单次出行距离-------2个字节
	*/
u8* Function::getMSignalTravelDistance()
{
	return mSignalTravelDistance;
}
/**
	*获取负载（单位kg）
	* @retval 获取负载（单位kg）-------1个字节
	*/
u8* Function::getMLoad()
{
	return &mLoad;
}
/**
	*获取按照协议开关状态
	* @retval 开关状态-------1个字节
	*/
u8* Function::getMOnOff()
{
	return &mOnOff;
}
/**
	*获取心跳包
	* @retval 心跳包-------1个字节
	*/
u8* Function::getMHeartbaat()
{
	return &mHeartbaat;
}
/**
	*获取保留字节
	* @retval 保留字节-------6个字节
	*/
u8* Function::getMTheKeepByte()
{
	return mTheKeepByte;
}
/**
	*获取固件版本
	* @retval 固件版本-------2个字节
	*/
u8* Function::getMFirmwareVersion()
{
	return mFirmwareVersion;
}
/**
	*获取和校验
	* @retval 和校验-------1个字节
	*/
u8* Function::getMAndChick()
{
	return &mAndChick;
}

static double temp[4] = {0};
/**
	*	通过ADC测量重心的坐标，范围在0-100
	* @param void
	*/
void Function::UpdateCoordinate(void)
{
	/*ADC的计算*/
	mV4.Converted();
	mAdc1.value = mV4.mConvertedVoltage[0];
	mAdc2.value = mV4.mConvertedVoltage[1];
	mAdc3.value = mV4.mConvertedVoltage[2]*100;											//测量的是电源电压
	mAdc4.value = mV4.mConvertedVoltage[3];
	mAdc5.value = mV4.mConvertedVoltage[4];
//have a test;
	temp[0] = mAdc1.value;
	temp[1] = mAdc2.value;
	temp[2] = mAdc4.value;
	temp[3] = mAdc5.value;
	
	
	mPressure1 = mPressuremodel.VoltageToPressure(1,temp[0]);//压力模型 电压转为压力
	mPressure2 = mPressuremodel.VoltageToPressure(2,temp[1]);
	mPressure3 = mPressuremodel.VoltageToPressure(3,temp[2]);
	mPressure4 = mPressuremodel.VoltageToPressure(4,temp[3]);
	
	mPressureAll = mPressure1+mPressure2+mPressure3+mPressure4;																								//计算重力
	mCoordinate.BuildtheCoordinate(mPressure1,mPressure2,mPressure3,mPressure4);												//构建坐标
	u8 coordinateTemplet[2] = {*mCoordinate.GetCoordinate(),*(mCoordinate.GetCoordinate()+1)};//声明一个暂时的坐标，并且获得坐标
}


/**
	*	PWM控制，输出给电调来控制电机
	* @param void
	*/ 
static u8 leftflag=0;
static u8 rightflag=0;
void Function::PWMControl(void)
{

		if(mPressureAll>5)																//如果负载达到5kg以上表明可以启动
		{
			ManLoad = 1;
			count = 0;
		}
		else
		{
			ManLoad = 0;
		}
	
		if(ManLoad == 1)
		{
			

		if(*(mCoordinate.GetCoordinate()+1)>10)
		{
			if(*(mCoordinate.GetCoordinate()) < 43)
				leftflag++;
			if(leftflag>4)
			{
				mRightMotor.SetRotateSpeeed(14);
				mLeftMotor.SetRotateSpeeed(4);
				leftflag=0;
			}
			if(*mCoordinate.GetCoordinate()>57)								//右转
				rightflag++;
			if(rightflag>4)
			{
				mRightMotor.SetRotateSpeeed(4);
				mLeftMotor.SetRotateSpeeed(14);
				rightflag=0;
			}
			else
			{
				mLeftMotor.SetRotateSpeeed(18);
				mRightMotor.SetRotateSpeeed(18);
			}
		}
		else																							//如果没有达到前倾就停止
		{
			mLeftMotor.SetRotateSpeeed(0);
			mRightMotor.SetRotateSpeeed(0);
		}
	}
	else
	{
		mLeftMotor.SetRotateSpeeed(0);
		mRightMotor.SetRotateSpeeed(0);
	}
}


/**
	*	更新超声波测量的数据
	* @param void
	*/
	
void Function::UpdateUltrasonic(void)
{
		float		ultrasonic = 0;																//超声波的值
		float		ultrasonic2 = 0;															//超声波的值
		ultrasonic= mUltrasonic1.Update();
		ultrasonic2 = mUltrasonic2.Update();
		/////////////////////////////////////
		//////////			把小数和整数部分分离出来
		/////////////////////////////////////
		//		int	FloatValue = *reinterpret_cast<int*>(&ultrasonic);
		//		int	Exp = (FloatValue>>23)&0xff;
		//		int MantissaPart=(FloatValue&0x7fffff)|0x800000;		//尾数字段，23位加一个默认位，共24位。 
		//		u8 theInteger = MantissaPart>>(150-Exp);
		//		u8 theDecimal = MantissaPart&(0xffffff>>(Exp-126));	//取得小数部分
		//		ultInteger = (int)ultrasonic;													//取整数
		//		ultDecimal = (ultrasonic-ultInteger)*100;							//取两位小数
		//		dataSend[5] = ultInteger;															//填充发送的超声波的整数部分
		//		dataSend[6] = ultDecimal;															//填充发送的超声波的小数部分
		mUltrasonicunion1.value = ultrasonic;													//把float传给共用体
		mUltrasonicunion2.value = ultrasonic2;
}


/**
	*	更新MPU6050的数据
	* @param void
	*/
	
void Function::UpdateMPU6050(void)
{
	if(MOD_ERROR== mMpu6050_.Update())
		{
			mUsart1<<"error\n\n\n";
		}	
		mAccrawz = mMpu6050_.GetAccRaw().z;
}

/**
	* 发送数据
	* @param void
	*/
	
void Function::SendData(void)
{
	
								/////////////////////////////////////////////////
								///////					测试从WIFI接收到的数据
								//////////////////////////////////////////////////
								if(mUsart3.ReceiveBufferSize()>0)
								{
									int receivedDataNum=mUsart3.ReceiveBufferSize();
									mUsart3.GetReceivedData(mdataReceived,receivedDataNum);
//									usart1.SendData(dataReceived,receivedDataNum);
									mUsart3.SendData(mdataReceived,receivedDataNum);
								}
								
//								mRightMotor.SetRotateSpeeed(mdataReceived[0]);
//								mLeftMotor.SetRotateSpeeed(mdataReceived[1]);
//								Delay d;
//								d.Ms(2);
//								mPwmT2.SetDuty(1,mdataReceived[1]);
//								mPwmT2.SetDuty(2,mdataReceived[0]);
								///////////////////////////////////////////////
								///						下位机->上位机(暂时发送到USART1)
								//////////////////////////////////////////////
//								usart1<<ultrasonicunion1.value<<"\t"
//											<<ultrasonicunion1.value<<"\t"
//											<<accrawz<<"\r\n";//测试成功，但是整数部分需要2个字节，因为测试的距离最多能达到400cm
								
								/*适配潘哥的上位机*/								
								u8 SendDataofCoordinate[3] = {0xaa,*mCoordinate.GetCoordinate(),*(mCoordinate.GetCoordinate()+1)};
//								usart1.SendData(SendDataofCoordinate,3);
								/*
								mUsart1
								      <<"("<<mPressure1<<") "
											<<"("<<mPressure2<<") "
											<<"("<<mPressure3<<") "
											<<"("<<mPressure4<<") "
											<<"("<<mPressureAll<<")     ("
											<<*mCoordinate.GetCoordinate()<<","
											<<*(mCoordinate.GetCoordinate()+1)
											<<")\r\n";*/
								mUsart1<<mPressure1<<"  "<<mPressure2<<"  "<<mPressure3<<"  "<<mPressure4<<"  "<<*mCoordinate.GetCoordinate()<<"  "<<*mCoordinate.GetCoordinate()+1<<"\r\n";
								
								
//									u8 SendDataofCoordinate[3] = {0xaa,dataReceived[2],dataReceived[3]};
									/*适配潘哥的上位机*/	
/*									mUsart1.SendData(SendDataofCoordinate,3);*/
}

/**
	* 初始化函数，初始化各种器件等
	* @param void
	*/
	
void Function::InitTwoMotor(void)
{
	/////////////////////////////////////////////////////////////////
	/////////初始化电机，先左后右
	/////////////////////////////////////////////////////////////////
//	mLeftMotor.InitMotor();
//	mRightMotor.InitMotor();
	mPwmT2.SetDuty(1,10);
	mPwmT2.SetDuty(2,10);
	tskmgr.DelayMs(2);//初始为2  
	mPwmT2.SetDuty(1,60);
	mPwmT2.SetDuty(2,60);
	tskmgr.DelayS(3);//等待初始化完毕
}

/**
	* 初始化函数，初始化各种器件等
	* @param void
	*/
	
void Function::InitMPU6050(void)
{
		/***		初始化MPU6050		***/
	if(!mMpu6050_.Init())
	{
		if(!mMpu6050_.Init())
			;}
}


void Function::GetRelativeCoordinate(void)
{

	/*ADC的计算*/
	mV4.Converted();
	mAdc1.value = mV4.mConvertedVoltage[0];
	mAdc2.value = mV4.mConvertedVoltage[1];
	mAdc3.value = mV4.mConvertedVoltage[2]*100;											//测量的是电源电压
	mAdc4.value = mV4.mConvertedVoltage[3];
	mAdc5.value = mV4.mConvertedVoltage[4];
	
	mPressure1 = mPressuremodel.VoltageToPressure(1,mAdc1.value);
	mPressure2 = mPressuremodel.VoltageToPressure(2,mAdc2.value);
	mPressure3 = mPressuremodel.VoltageToPressure(3,mAdc4.value);
	mPressure4 = mPressuremodel.VoltageToPressure(4,mAdc5.value);
	
	mPressureAll = mPressure1+mPressure2+mPressure3+mPressure4;																								//计算重力
	mCoordinate.BuildtheCoordinate(mPressure1,mPressure2,mPressure3,mPressure4);												//构建坐标
	u8 coordinateTemplet[2] = {*mCoordinate.GetCoordinate(),*(mCoordinate.GetCoordinate()+1)};//声明一个暂时的坐标，并且获得坐标
}


/**
	* 判断重心是否平稳，即初始化的时候需要使用的
	* @param void
	*/
int Function::InitTheRelativeCoordinate(void)
{
	UpdateCoordinate();																																				  //更新坐标
	
	//当人没有站上去的时候，一直保持不初始化的状态
	while(mPressureAll < 35)
	{;}
		u8 coordinateTemplet[2] = {*mCoordinate.GetCoordinate(),*(mCoordinate.GetCoordinate()+1)};//声明一个暂时的坐标，并且获得坐标
		
	//	bool isReset = false;						//用于确定是否需要重新确定相对重心的标志，如果为true就重新确定，如果为false就继续检测。
		u8	 RelativeCoordinateFlagCount = 0;

		
	//2ms进行一次检测，1.5s的检测时间
	while(RelativeCoordinateFlagCount<75)
	{
		mCurTime = TaskManager::Time();	//获得当前时间
		mDiffTime = mCurTime-mOldTime;	//计算差值时间
		if(mDiffTime > 0.02)//  原值0.02  改为0.002 fail
		{
			//更新记录的时间
			mOldTime = mCurTime;
			//用于判断是否符合范围，不符合就从新开始确认
			if((mRelativeToX - coordinateTemplet[0] > theAcceptLimit) || (mRelativeToY - coordinateTemplet[1]>theAcceptLimit))
			{
	//			isReset = true;
				RelativeCoordinateFlagCount = 0;
			}
			mRelativeToX = coordinateTemplet[0];
			mRelativeToY = coordinateTemplet[1];
			RelativeCoordinateFlagCount++;
	//		isReset = false;
		}
	}

	
	
	
	
	return 1;
}




















