#ifndef _VOLTAGE_H_
#define	_VOLTAGE_H_

#include "stm32f10x.h"


class Voltage
{
	private:
		/**
		 *@param  	mPrimordialVoltage     ��¼ԭ����ѹֵ�ĵ�ַ�������Ժ����
		 *@param  	mToltalChannel     		 ��¼һ���ж��ٸ�ͨ��������ѭ��
		 */
			uint16_t* mPrimordialVoltageAddr;
			uint8_t   mToltalChannel;
	public:
		
	
		/**
		 *@brief		��ԭ��ֵת����һ��float�ĵ�ѹֵ,0~3.3
		 *@param 		primordialVoltage ��ѹ��ԭʼֵ,��Ҫ12λ��
		 */
		void 		Converted();
	////////////////////////////////////////////////////////////////////////////////
	///////���10��ֵ��¼ԭʼֵת����float�ĵ�ѹֵ,��Χ��0~3.3V,���Ǳ����ڵ���Converted����֮����ܸ���ֵ
	///////////////////////////////////////////////////////////////////////////////
		float 		mConvertedVoltage[10];

		/**
		 *@brief��ʼ����ʱ����ADCԭ��ֵ
		 *@param primordialVoltage 	��ѹ��ԭʼֵ,��Ҫ12λ��
		 *@param channelNum					ͨ��������
		 */
		Voltage(uint16_t* primordialVoltage,uint8_t channelNum);

		
};



#endif


