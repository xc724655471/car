#include "Voltage.h"



/**
 *@brief��ʼ����ʱ����ADCԭ��ֵ
 *@param primordialVoltage ��ѹ��ԭʼֵ,��Ҫ12λ��
 */
 
Voltage::Voltage(uint16_t* primordialVoltage,uint8_t channelNum)
{
	mPrimordialVoltageAddr = primordialVoltage;
	mToltalChannel = channelNum;
	mConvertedVoltage[0] = 0;
	mConvertedVoltage[1] = 0;
	mConvertedVoltage[2] = 0;
	mConvertedVoltage[3] = 0;
	mConvertedVoltage[4] = 0;
	mConvertedVoltage[5] = 0;
	mConvertedVoltage[6] = 0;
	mConvertedVoltage[7] = 0;
	mConvertedVoltage[8] = 0;
	mConvertedVoltage[9] = 0;
}

/**
 *@brief		��ԭ��ֵת����һ��float�ĵ�ѹֵ,0~3.3
 *@param 		primordialVoltage ��ѹ��ԭʼֵ,��Ҫ12λ��
 */

void Voltage::Converted()
{
	uint8_t i = 0;
	uint32_t tempPri[10] = {0};
	
	///////////////////////////////////////////////
	//////////�����ۼӼ���
	///////////////////////////////////////////////
	for(;i<50;i++)
	{
		switch(mToltalChannel)
		{
			case 10:tempPri[9] += *(mPrimordialVoltageAddr+9);
			case  9:tempPri[8] += *(mPrimordialVoltageAddr+8);
			case  8:tempPri[7] += *(mPrimordialVoltageAddr+7);
			case  7:tempPri[6] += *(mPrimordialVoltageAddr+6);
			case  6:tempPri[5] += *(mPrimordialVoltageAddr+5);
			case  5:tempPri[4] += *(mPrimordialVoltageAddr+4);
			case  4:tempPri[3] += *(mPrimordialVoltageAddr+3);
			case  3:tempPri[2] += *(mPrimordialVoltageAddr+2);
			case  2:tempPri[1] += *(mPrimordialVoltageAddr+1);
			case  1:tempPri[0] += *(mPrimordialVoltageAddr);break;
			
			default:;
		}
	}
	
	///////////////////////////////////////////////
	//////////ȡƽ��ֵ
	///////////////////////////////////////////////
		switch(mToltalChannel)
		{
			case 10:tempPri[9] = tempPri[9]/50;
			case  9:tempPri[8] = tempPri[8]/50;
			case  8:tempPri[7] = tempPri[7]/50;
			case  7:tempPri[6] = tempPri[6]/50;
			case  6:tempPri[5] = tempPri[5]/50;
			case  5:tempPri[4] = tempPri[4]/50;
			case  4:tempPri[3] = tempPri[3]/50;
			case  3:tempPri[2] = tempPri[2]/50;
			case  2:tempPri[1] = tempPri[1]/50;
			case  1:tempPri[0] = tempPri[0]/50;break;
			
			default:;
		}
	///////////////////////////////////////////////
	//////////����ɵ�ѹֵ����Χ��0~3.3֮��d��float
	///////////////////////////////////////////////
		
		switch(mToltalChannel)
		{
			case 10:mConvertedVoltage[9] = (3.3/4095*tempPri[9]);
			case  9:mConvertedVoltage[8] = (3.3/4095*tempPri[8]);
			case  8:mConvertedVoltage[7] = (3.3/4095*tempPri[7]);
			case  7:mConvertedVoltage[6] = (3.3/4095*tempPri[6]);
			case  6:mConvertedVoltage[5] = (3.3/4095*tempPri[5]);
			case  5:mConvertedVoltage[4] = (3.3/4095*tempPri[4]);
			case  4:mConvertedVoltage[3] = (3.3/4095*tempPri[3]);
			case  3:mConvertedVoltage[2] = (3.3/4095*tempPri[2]);
			case  2:mConvertedVoltage[1] = (3.3/4095*tempPri[1]);
			case  1:mConvertedVoltage[0] = (3.3/4095*tempPri[0]);break;
			
			default:;
		}
}

