
//include the header file containing the class declaration. 
#include "Exti.h"


//Initialize the static member constants
const  uint16_t  Exti::mPin[16]={GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7,
								GPIO_Pin_8,GPIO_Pin_9,GPIO_Pin_10,GPIO_Pin_11,GPIO_Pin_12,GPIO_Pin_13,GPIO_Pin_14,GPIO_Pin_15};

				
const uint32_t	 Exti::mEXTILine[16]={EXTI_Line0,EXTI_Line1,EXTI_Line2,EXTI_Line3,EXTI_Line4,EXTI_Line5,EXTI_Line6,EXTI_Line7,
								EXTI_Line8,EXTI_Line9,EXTI_Line10,EXTI_Line11,EXTI_Line12,EXTI_Line13,EXTI_Line14,EXTI_Line15};
	
								
//The Constructor of the Class
Exti::Exti(GPIO_TypeDef *port,uint16_t pin,GPIOMode_TypeDef gpioMode,uint8_t NVICPriorityGroup,uint8_t NVICPreemptionPriority,uint8_t NVICSubPriority,EXTIMode_TypeDef extiMode,EXTITrigger_TypeDef extiTrigger)
{
	/*	初始化成员变量	*/	
	mSelectPort=port;	
	mSelectPin=pin;
	
	/*	时钟配置	*/
	RCC_Configuration();
	
	/*	外部管脚配置	*/
	GPIO_Configuration(gpioMode);
	
	/*	中断向量管理配置	*/
	NVIC_Configuration(NVICPriorityGroup,NVICPreemptionPriority,NVICSubPriority);
	
	/*	外部中断配置		*/
	EXTI_Configuration(extiMode,extiTrigger);
}

//destructor
Exti::~Exti()
{
	CloseExtiInt();
}

//The function to configure the RCC of GPIO
void Exti::RCC_Configuration()
{
	//SystemInit();	//系统设置初始化
	if(mSelectPort==GPIOA)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	}
	else if(mSelectPort==GPIOB)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	}
	else if(mSelectPort==GPIOC)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	}
	else if(mSelectPort==GPIOD)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	}
	else if(mSelectPort==GPIOE)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	}
	else if(mSelectPort==GPIOF)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
	}
	else if(mSelectPort==GPIOG)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
	}
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
}

/*	外部管脚配置	*/	
void Exti::GPIO_Configuration(GPIOMode_TypeDef gpioMode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	uint8_t GPIO_PortSource;
	
	if(mSelectPort==GPIOA)
	{
		GPIO_PortSource=0x00;
	}
	else if(mSelectPort==GPIOB)
	{
		GPIO_PortSource=0x01;
	}
	else if(mSelectPort==GPIOC)
	{
		GPIO_PortSource=0x02;
	}
	else if(mSelectPort==GPIOD)
	{
		GPIO_PortSource=0x03;
	}
	else if(mSelectPort==GPIOE)
	{
		GPIO_PortSource=0x04;
	}
	else if(mSelectPort==GPIOF)
	{
		GPIO_PortSource=0x05;
	}
	else if(mSelectPort==GPIOG)
	{
		GPIO_PortSource=0x06;
	}
		
	GPIO_InitStructure.GPIO_Pin=mPin[mSelectPin];
	GPIO_InitStructure.GPIO_Mode=gpioMode;
	GPIO_Init(mSelectPort,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSource,(uint8_t)mSelectPin);			   //选择GPIO管脚用作外部中断线路
}

/*	中断向量管理配置	*/	
void Exti::NVIC_Configuration(uint8_t NVICPriorityGroup,uint8_t NVICPreemptionPriority,uint8_t NVICSubPriority)
{
	static const uint32_t priorityGroup[5]={0x700,0x600,0x500,0x400,0x300};
	NVIC_InitTypeDef NVIC_InitStructure;
	uint8_t					EXTIx_IRQn;			//外部中断号
	
	/*	用于给外部中断号进行初始化	*/
	switch (mSelectPin)
	{
		case 0:EXTIx_IRQn=6;break;
		case 1:EXTIx_IRQn=7;break;
		case 2:EXTIx_IRQn=8;break;
		case 3:EXTIx_IRQn=9;break;
		case 4:EXTIx_IRQn=10;break;
		case 5:;
		case 6:;
		case 7:;
		case 8:;
		case 9:EXTIx_IRQn=23;break;
		case 10:;
		case 11:;
		case 12:;
		case 13:;
		case 14:;
		case 15:EXTIx_IRQn=40;break;
		default:EXTIx_IRQn=23;
	}
	
	NVIC_PriorityGroupConfig(priorityGroup[NVICPriorityGroup]);		/*	一个工程中只能有一种分组方式	*/
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTIx_IRQn;	/*	外部中断号	*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVICPreemptionPriority; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVICSubPriority; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}

/*	外部中断配置	*/
void Exti::EXTI_Configuration(EXTIMode_TypeDef extiMode,EXTITrigger_TypeDef extiTrigger)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	
	EXTI_ClearITPendingBit(mEXTILine[mSelectPin]);							//清除外部线路中断位
	EXTI_InitStructure.EXTI_Line=mEXTILine[mSelectPin];						//选择外部中断线路
	EXTI_InitStructure.EXTI_Mode=extiMode;
	EXTI_InitStructure.EXTI_Trigger = extiTrigger;							//触发方式
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	
	
	EXTI_Init(&EXTI_InitStructure);
	
	CloseExtiInt();															//先关闭外部中断
}


/*	关闭外部中断	*/
void Exti::CloseExtiInt()
{
	EXTI->PR=mEXTILine[mSelectPin];			//清除相应线路的中断标志位
	EXTI->IMR&=~mEXTILine[mSelectPin];
}

/*	打开外部中断	*/
void Exti::OpenExtiInt()
{
	EXTI->PR=mEXTILine[mSelectPin];			//清除相应线路的中断标志位
	EXTI->IMR|=mEXTILine[mSelectPin];
}
