#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#define X_LEFT 35
#define X_RIGHT 65
#define Y_BACK 1


/***		include header files		***/
#include "stm32f10x.h"
#include "motor.h"
#include "math.h"






/***		CoordinateControl class		***/
class CoordinateControl
{
	private:
		u8 mCoordinate[2];																		//(x,y)(0~100,0~100)坐标
		Motor &mLeft;																					//左电机
		Motor &mRight;																				//右电机
		u16 mStartCount;																			//人最开始站上去时初始化的时候的次数计数
		bool mStartFlag;																			//压力模式开关状态

	
		void PressureControl();																//To control car by pressure mode
		void RemoteControl();																	//To control car by remote mode
		void RaceControl();																		//change speed by pressure mode
		void SetMotor(bool ml,bool mr,u16 lspeed,u16 rspeed);	//设置电机的函数
	public:
		
		u8 mRemoteMode;																				//控制模式
	
	
	
	
		/**
		 *@brife	The constructor of CoordinateControl class.
		 *@param	leftMotor: The reference of Motor,control the left motor.
		 *@param	rightMotor: The reference of Motor,control the right motor.
		 */
		CoordinateControl(Motor &leftMotor,Motor &rightMotor);
		
	
		/**
		 *@brife	to set the coordinate of center of gravity
		 *@param	coordinate: The coordinate of center of gravity
		 */
		void SetCoordinate(u8 coordinate[2]);
		
		
		/**
		 *@brife	to get the coordinate of center of gravity
		 *@return	the coordinate of center of gravity
		 */
		u8* GetCoordinate();

	
		/**
		 *@brife	To conrtol car by coordinate
		 */
		void Controlcar();

		/**
		 *@brife	To build the coordinate by gravity and set the coordinate
		 *@param	gravity_ch1: The gravity of channel1
		 *@param	gravity_ch2: The gravity of channel2
		 *@param	gravity_ch3: The gravity of channel3
		 *@param	gravity_ch4: The gravity of channel4
		 */
		void BuildtheCoordinate(float gravity_ch1,float gravity_ch2,float gravity_ch3,float gravity_ch4);
		
		
		
		
		
		
		
		
		
		
		
		
			
	
		/**
		 *@brife	Distructor.
		 */
		~CoordinateControl();
	
	
};

#endif

