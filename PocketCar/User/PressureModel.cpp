#include "PressureModel.h"

//constructor
PressureModel::PressureModel(float a,float b,float c,float d)
{
	mPressure = 0;
	mCubicTermCoefficient = a;
	mQuadraticTermCoefficient = b;
	mMonomialcoefficient = c;
	mConstantTerm = d;
}

//distructor
PressureModel::~PressureModel()
{
	
}

//电压转压力模型
float PressureModel::VoltageToPressure(float voltage)
{
	mPressure = mCubicTermCoefficient*voltage*voltage*voltage + mQuadraticTermCoefficient*voltage*voltage + mMonomialcoefficient*voltage + mConstantTerm;
	return mPressure;
}

//电压转压力模型（重载）
float PressureModel::VoltageToPressure(unsigned char channel,float voltage)
{
//	switch (channel)					//对通道2,4进行校正，因为建模时是以通道1为样本建立的
//	{
//		case 2:voltage -= 0.1;break;
//		case 4:voltage -= 0.2;break;
//	}
	mPressure = mCubicTermCoefficient*voltage*voltage*voltage + mQuadraticTermCoefficient*voltage*voltage + mMonomialcoefficient*voltage + mConstantTerm;
	return mPressure;
}

//重新构造模型
void  PressureModel::ReConstructModel(float CubicTermCoefficient,float QuadraticTermCoefficient,float Monomialcoefficient,float GetmConstantTerm)
{
	mCubicTermCoefficient = CubicTermCoefficient;
	mQuadraticTermCoefficient = QuadraticTermCoefficient;
	mMonomialcoefficient = Monomialcoefficient;
	mConstantTerm = GetmConstantTerm;
}


//得到模型的三次项系数
float PressureModel::GetmCubicTermCoefficient()
{
	return mCubicTermCoefficient;
}

//得到模型的二次项系数
float PressureModel::GetmQuadraticTermCoefficient()
{
	return mQuadraticTermCoefficient;
}

//得到模型的一次项系数
float PressureModel::GetmMonomialcoefficient()
{
	return mMonomialcoefficient;
}

//得到常数项
float PressureModel::GetmConstantTerm()
{
	return mConstantTerm;
}

