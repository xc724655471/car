#include "F103_PWM.h"


/**
 *@brief ���ڼ����Psc��ֵ��Arr��ֵ���������������һ�֣�72M�ܱ�frequency�������ڶ��� 72M���ܱ�frequency����
 *@param quo  ��һ�μ���֮�����
 *@param quo2 �ڶ��μ�����̣������ڵ�һ�μ��������Ѿ������ˣ���ֱ�Ӵ������ˣ�
 *@param rem2 ����ͨquo2
 *@param flagBest ��־�Ƿ��ҵ���ѵ�Psc��Arr��ֵ
 */

void PWM::Calcute2(u32 quo,u32 quo2,u32 rem2,bool flagBest)
{
		u16 i;
		for(i = 1;i<=1200;i++)
			{
				if(quo%i == 0 && quo/i < 65535){mPsc = i;mArr = quo/i;flagBest  = true ;break;}
				
			}
		if(flagBest == false)//û���ҵ����ֵ
		{
			for( i = 1;i <= 1200;i++)
			{
				quo2 = quo / i;
				rem2 = quo % i;
				if(quo2 < 65535 && rem2 < 32758){mPsc = i;mArr = quo2;flagBest = true;break;}
			}
		}
}

/**
 *@brief ���ڵ�һ�μ��㣬�ж��Ƿ�������Ƶ��������72M
 *@param frequency ������Ƶ��
 */
void PWM::Calcute(u16 frequency)
{
	
	bool flagBest = false;		   //��־�Ƿ��ҵ����ֵ
	u32  quo = 72000000/frequency;//�������
	u32 rem = 72000000%frequency;//������� 
	
	u32  quo2 = 0;
	u32 rem2 = 0;
	if(rem == 0)//1��F������72M;������quo����1��ʼ������������������£�ȡ
	{
		Calcute2(quo,quo2,rem2,flagBest);
	}
	else
	{
		if(rem > 32768)quo++;
		Calcute2(quo,quo2,rem2,flagBest);
	}
}
	
/**
 *@brief ���캯��
 *@param timer ѡ���ʱ��
 *@param enCh1 ͨ��1�Ƿ��
 *@param enCh2 ͨ��2�Ƿ��
 *@param enCh3 ͨ��3�Ƿ��
 *@param enCh4 ͨ��4�Ƿ��
 *@param frequency ����Ƶ��
 *@param remap �����Ƿ�ӳ��,����汾��û����
 */
void PWM::PWMInit(TIM_TypeDef* timer,bool enCh1,bool enCh2,bool enCh3,bool enCh4,u16 frequency,bool remap)//����ѡ��Ķ�ʱ��,��û�д��������Ĭ��TIM2
{
		/*
			����Ƶ������PSC��ARR��ֵ���Ժ���˵�������ܹ�����Ҫ��
		
//		mPsc = 71;
//		mArr = (u16)((72000000)/((mPsc+1)*frequency))-1;
		*/
	
	
		mTimer = timer;																			//get the TIM of chosen
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//open the PinA Timer
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//open the PinB Timer
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ܽŸ��ô�
	
		//��Ϊswtich��֧��TIM_TypeDef����,ǿ��ת��֮�����null�����Բ��ô�ͳ��if else������GPIO
	
		if(timer == TIM2)
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	
			GPIO_InitStruct.GPIO_Pin = (GPIO_Pin_0 & enCh1)|
																 (GPIO_Pin_1 & enCh2<<1)|
																 (GPIO_Pin_2 & enCh3<<2)|
																 (GPIO_Pin_3 & enCh4<<3);
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_Init(GPIOA,&GPIO_InitStruct);
			
		}
			else{
				if(timer == TIM3)
				{
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	
					GPIO_InitStruct.GPIO_Pin = (GPIO_Pin_6 & enCh1<<6)|
																		 (GPIO_Pin_7 & enCh2<<7);
					GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_Init(GPIOA,&GPIO_InitStruct);
					
					GPIO_InitStruct.GPIO_Pin = (GPIO_Pin_0 & enCh3)|
																		 (GPIO_Pin_1 & enCh4<<1);
					GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_Init(GPIOB,&GPIO_InitStruct);
				}
						else{
							if(timer == TIM4)
							{
								RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);	
								GPIO_InitStruct.GPIO_Pin = (GPIO_Pin_6 & enCh1<<6)|
																					 (GPIO_Pin_7 & enCh2<<7)|
																					 (GPIO_Pin_8 & enCh3<<8)|
																					 (GPIO_Pin_9 & enCh4<<9);
								GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
								GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
								GPIO_Init(GPIOB,&GPIO_InitStruct);
							}
								}
					}
	
					
			//��ʼ����TIM
			TIM_TimeBaseStruct.TIM_Period = mArr-1;//����ARR�Ĵ��������Ǽ������ٴΣ�PSC = 7199�Ļ�����10KHZ����5000�Σ�����5000��0.1ms = 500ms 2HZ
			TIM_TimeBaseStruct.TIM_Prescaler = mPsc-1;//Ԥ��Ƶ�Ĵ�������7200������ʱ��Ϊ10kHZ��72M/7200 = 10K
			TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;//0;
			TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//�м����,�γ��м�����PWM�� TIM_CounterMode_Up;����//TIM_CounterMode_CenterAligned1//�м����
			TIM_TimeBaseInit(timer,&TIM_TimeBaseStruct);//��ʼ��TIM
					
					
			//pwm���ã�����ʼ��
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//ѡ��ʱ��ģʽΪpwm1ģʽ
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//���õ�������ԣ�����Ϊռ�ձ���ֵ�Ǹߵ�ƽֱ��ռ���ǵ͵�ƽ
					
			//ͨ��1---
				TIM_OCInitStructure.TIM_Pulse = mArr/2;//ռ�ձ�ʱ��
				TIM_OC1Init(timer,&TIM_OCInitStructure);//����TIM_OCInitStructure�ṹ���ʼ��TIMͨ��1
				TIM_OC1PreloadConfig(timer,TIM_OCPreload_Enable);//ʹ��Ԥװ����
			//ͨ��2---

				TIM_OCInitStructure.TIM_Pulse = mArr/2;//ռ�ձ�ʱ��
				TIM_OC2Init(timer,&TIM_OCInitStructure);//����TIM_OCInitStructure�ṹ���ʼ��TIMͨ��2
				TIM_OC2PreloadConfig(timer,TIM_OCPreload_Enable);//ʹ��Ԥװ����

			//ͨ��3---
				TIM_OCInitStructure.TIM_Pulse = mArr/2;//ռ�ձ�ʱ��
				TIM_OC3Init(timer,&TIM_OCInitStructure);//����TIM_OCInitStructure�ṹ���ʼ��TIMͨ��3
				TIM_OC3PreloadConfig(timer,TIM_OCPreload_Enable);//ʹ��Ԥװ����
			//ͨ��4---
				TIM_OCInitStructure.TIM_Pulse = mArr/2;//ռ�ձ�ʱ��
				TIM_OC4Init(timer,&TIM_OCInitStructure);//����TIM_OCInitStructure�ṹ���ʼ��TIMͨ��4
				TIM_OC4PreloadConfig(timer,TIM_OCPreload_Enable);//ʹ��Ԥװ����
				TIM_Cmd(timer,ENABLE);
							
}
/**
 *@brief �ı�һ��ͨ����ռ�ձ�
 *@param channel ѡ��ͨ��
 *@param duty    ����ռ�ձ�
 */
 
void PWM::SetDuty(u8 channel,float duty)
{
	u16 arrTemp = (duty/100)*mArr;
	switch(channel)
	{
		case 1:mTimer->CCR1 = arrTemp;break;
		
		case 2:mTimer->CCR2 = arrTemp;break;
		
		case 3:mTimer->CCR3 = arrTemp;break;
		
		case 4:mTimer->CCR4 = arrTemp;break;
		
	}
}
/**
 *@brief �ı�һ��ͨ����ռ�ձ�
 *@param dutyCh1 ����ͨ��1��ռ�ձ�
 *@param dutyCh2 ����ͨ��2��ռ�ձ�
 *@param dutyCh3 ����ͨ��3��ռ�ձ�
 *@param dutyCh4 ����ͨ��4��ռ�ձ�
 */
void PWM::SetDuty(float dutyCh1,float dutyCh2,float dutyCh3,float dutyCh4)
{
	u16 ccr1Temp = (dutyCh1/100)*mArr;
	u16 ccr2Temp = (dutyCh2/100)*mArr;
	u16 ccr3Temp = (dutyCh3/100)*mArr;
	u16 ccr4Temp = (dutyCh4/100)*mArr;
	
	mTimer -> CCR1 = ccr1Temp;
	mTimer -> CCR2 = ccr2Temp;
	mTimer -> CCR3 = ccr3Temp;
	mTimer -> CCR4 = ccr4Temp;

}

