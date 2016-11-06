#ifndef _PRESSUREMODEL
#define _PRESSUREMODEL

class PressureModel
{
	private:
		float mPressure;
	
		float mCubicTermCoefficient;					//三次项系数
		float mQuadraticTermCoefficient;				//二次项系数
		float mMonomialcoefficient;						//一次项系数
		float mConstantTerm;							//常数项
	
	public:
		/**
		* @brief The constructor of PressureModel
		*/
		PressureModel(float a = -20.14,float b = 176.74,float c = -530.62,float d = 550.24);
	
		/**
		* @brief The distructor of PressureModel
		*/
		~PressureModel();
	
		/**
		* @brief  电压到压力的转换
		* @param  voltage :输入的电压值
		* @retval 转换后的压力值
		*/
		float VoltageToPressure(float voltage);
	
		/**
		* @brief  重载函数
		* @param  channel :输入的通道号
		* @param  voltage :输入的电压值
		* @retval 转换后的压力值
		*/
		float VoltageToPressure(unsigned char channel,float voltage);
	
		/**
		* @brief 返回三次项系数
		* @retval 三次项系数
		*/
		float GetmCubicTermCoefficient();
	
		/**
		* @brief 返回二次项系数
		* @retval 二次项系数
		*/
		float GetmQuadraticTermCoefficient();
	
		/**
		* @brief 返回一次项系数
		* @retval 一次项系数
		*/
		float GetmMonomialcoefficient();
		
		/**
		* @brief 返回常数项
		* @retval 常数项
		*/
		float GetmConstantTerm();
		
		
		/**
		* @brief 重新构建模型
		* @param  CubicTermCoefficient :三次项系数
		* @param  QuadraticTermCoefficient :二次项系数
		* @param  Monomialcoefficient :一次项系数
		* @param  GetmConstantTerm :常数项
		*/
		void  ReConstructModel(float CubicTermCoefficient,float QuadraticTermCoefficient,float Monomialcoefficient,float GetmConstantTerm);

};

#endif

