#include "stm32f10x.h"

/////////////////////////////////////////////////////////
////							下位机->上位机
////////////////////////////////////////////////////////

class DataSend
{
	public:
		u8 thedata[40];					//需要传输的数据
		
	
		u8 mHead[2]								//包头
		u8 mId[4];								//设备ID
		u8 mPower;								//电量
		u8 mMileage[4];						//里程数
		u8 mUltrasonic[4];				//超声波
		u8 mLeftspeed;						//左轮速
		u8 mRightspeed;						//右轮速
		u8 mCoordinates[2];				//四个坐标的重心
		u8 mMpudata[4];						//MPU6050的数据	
		u8 mSignalboottime;				//单次开机时间
		u8 mSignaltraveltime[2];	//单次出行时间
		u8 mSignaltripdistance[2];//单次出行时间
		u8 mLoad;									//负载
		u8 mLockorunlock;					//开锁解锁状态
		u8 mHeartbeat;						//心跳包
		u8 mKeepByte[6]						//保留字节
		u8 mFirmwareversion[2];		//固件版本



	
		u8* GetTheAllData();			//得到需要发送的数据
};
	