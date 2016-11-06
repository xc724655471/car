#include "part.h"






int main(void){

	SystemInit();																	//open the system timer
	
	function.InitTheRelativeCoordinate();
	
	function.InitTwoMotor();													//初始化电机
//	function.InitMPU6050();												//初始化MPU6050
	
	Control();
	return 0;
}



/////////////////////////////////////////////////////////////
///@param:无
///@Description:				控制周期
/////////////////////////////////////////////////////////////
void Control(void)
{
	while(1)
	{
		curTime = TaskManager::Time();
		deltaT = curTime-oldTime;	
		if(deltaT >= 0.002)																								//2ms计算一次ADC的值，并且发送出去；如果没有2ms就不进行任何操作
		{
			oldTime = curTime;
			function.UpdateCoordinate();																		//更新重心坐标
			flagCount++;																										//控制标志自增
		}

		switch(flagCount)
		{
			case 2 :																												//4ms一次-------------PWM控制
							function.PWMControl();																	//PWM波控制
							break;
			case 30:																												//60ms一次----------------超声波启动
//							function.UpdateUltrasonic();														//更新超声波
							break;			
			case 50:																												//100ms一次----------------MPU数据获得
//							function.UpdateMPU6050();																//更新MPU6050的数据
							break;
			default:
							if(flagCount >= 199)																			//200ms周期更新一次
							{
								flagCount = 0;
								function.SendData();																	//下位机 -> 上位机
							}break;
		}
	}	
}


/////////////////////////////////////////////////////////////
///@param:无
///@Description:				控制初始化坐标
/////////////////////////////////////////////////////////////


