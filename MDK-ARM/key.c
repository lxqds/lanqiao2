#include "key.h"
#include "gpio.h"
void key_scan(uint8_t *key)
{
	uint8_t B1,B2,B3,B4;
	static uint8_t last_B1,last_B2,last_B3,last_B4,return_val;
	B1=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0);
	B2=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
	B3=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2);
	B4=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
	static uint8_t down_count1,down_count2,down_count3,down_count4;
	uint8_t release;
	if(last_B1==0&&B1==0)
	{
		release = 0;
		down_count1 ++;
	}
	else if(last_B1==1&&B1==1)
	{
		release = 1;
		down_count1 = 0;
	}
	if(last_B2==0&&B2==0)
	{
		down_count2 ++;
	}
	else if(last_B2==1&&B2==1)
	{
		down_count2 = 0;
	}
	
	if(last_B3==0&&B3==0)
	{
		down_count3 ++;
	}
	else if(last_B3==1&&B3==1)
	{
		down_count3 = 0;
	}
	
	if(last_B4==0&&B4==0)
	{
		down_count4 ++;
	}
	else if(last_B4==1&&B4==1)
	{
		down_count4 = 0;
	}
	
	last_B1=B1;
	last_B2=B2;
	last_B3=B3;
	last_B4=B4;
	
	if(release)
	{
		if(down_count1>5&&down_count1<50)
		{
			*key = 11;
		}else if(down_count1>100)
		{
			*key = 12;
		}
		
		if(down_count2>2&&down_count2<50)
		{
			*key = 21;
		}else if(down_count2>100)
		{
			*key = 22;
		}
		
		if(down_count3>2&&down_count3<50)
		{
			*key = 31;
		}else if(down_count3>100)
		{
			*key = 32;
		}
		
		if(down_count4>2&&down_count4<50)
		{
			*key = 41;
		}else if(down_count4>100)
		{
			*key = 42;
		}
	}
	
} 
void key_scan2(uint8_t *key_value)
{
	static uint8_t lastB1,lastB2,lastB3,lastB4;
	static uint8_t down_count,down_count2,down_count3,down_count4;
	uint8_t B1,B2,B3,B4;
	uint8_t release,release2,release3,release4;
	B1 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0);
	B2 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
	B3 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2);
	B4 = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
	
	if(B1==0&&lastB1==0)
	{
		release = 0;
		down_count++;
	}else if(B1==1&&lastB1==1)
	{
		down_count =0;
		release = 1;
	}
	if(B2==0&&lastB2==0)
	{
		release2 = 0;
		down_count2++;
	}else if(B2==1&&lastB2==1)
	{
		down_count2 =0;
		release2 = 1;
	}
	if(B3==0&&lastB3==0)
	{
		release3 = 0;
		down_count3++;
	}else if(B3==1&&lastB3==1)
	{
		down_count3 =0;
		release3 = 1;
	}
	if(B4==0&&lastB4==0)
	{
		release4 = 0;
		down_count4++;
	}else if(B4==1&&lastB4==1)
	{
		down_count4 =0;
		release4 = 1;
	}
	
	lastB1 = B1;
	lastB2 = B2;
	lastB3 = B3;
	lastB4 = B4;
	if(release)
	{
		if(down_count>2&&down_count<50)
		{
			*key_value = 11;
		}else if(down_count>100)
		{
			*key_value = 12;
		}
	}
	if(release2)
	{
		if(down_count2>2&&down_count2<50)
		{
			*key_value = 21;
		}else if(down_count2>100)
		{
			*key_value = 22;
		}
	}
	if(release3)
	{
		if(down_count3>2&&down_count3<50)
		{
			*key_value = 31;
		}else if(down_count3>100)
		{
			*key_value = 32;
		}
	}
	if(release4)
	{ 
		if(down_count4>2&&down_count4<50)
		{
			*key_value = 41;
		}else if(down_count4>100)
		{
			*key_value = 42;
		}
	}
}

void key_scan3(uint8_t *key_value)
{
	uint8_t B1,B2,B3,B4;
	uint8_t release,release2,release3,release4;
	static uint8_t last_B1,last_B2,last_B3,last_B4;
	static uint8_t down_count,down_count2,down_count3,down_count4;
	
	B1 =HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0);
	B2 =HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
	B3 =HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2);
	B4 =HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
	
	if(B1==0&&last_B1==0)
	{
		down_count++;
		release=0;
	}else if(B1==1&&last_B1==1)
	{
		down_count=0;
		release=1;
	}
	
	if(B2==0&&last_B2==0)
	{
		down_count2++;
		release2=0;
	}else if(B2==1&&last_B2==1)
	{
		down_count2=0;
		release2=1;
	}
	
	if(B3==0&&last_B3==0)
	{
		down_count3++;
		release3=0;
	}else if(B3==1&&last_B3==1)
	{
		down_count3=0;
		release3=1;
	}
	
	if(B4==0&&last_B4==0)
	{
		down_count4++;
		release4=0;
	}else if(B4==1&&last_B4==1)
	{
		down_count4=0;
		release4=1;
	}

	last_B1=B1;
	last_B2=B2;
	last_B3=B3;
	last_B4=B4;
	
	if(release)
	{
		if(down_count>3&&down_count<50)
		{
			*key_value = 11;
		}else if(down_count>100)
		{
			*key_value = 12;
		}
	}
	
	if(release2)
	{
		if(down_count2>3&&down_count2<50)
		{
			*key_value = 21;
		}else if(down_count2>100)
		{
			*key_value = 22;
		}
	}
	if(release3)
	{
		if(down_count3>3&&down_count3<50)
		{
			*key_value = 31;
		}else if(down_count3>100)
		{
			*key_value = 32;
		}
	}
	if(release4)
	{
		if(down_count4>3&&down_count4<50)
		{
			*key_value = 41;
		}else if(down_count4>100)
		{
			*key_value = 42;
		}
	}
}

void key_scan4(uint8_t *key_value)
{
	uint8_t B1,B2,B3,B4;
	uint8_t release,release2,release3,release4;
	static uint8_t last_B1,last_B2,last_B3,last_B4;
	static uint8_t down_count,down_count2,down_count3,down_count4;
	
	B1 =HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0);
	B2 =HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
	B3 =HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2);
	B4 =HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
	
	if(B1==0&&last_B1==0)
	{
		release =0;
		down_count++;
	}else if(B1==1&&last_B1==1)
	{
		release = 1;
		down_count = 0;
	}
	
	if(B2==0&&last_B2==0)
	{
		release2 =0;
		down_count2++;
	}else if(B2==1&&last_B2==1)
	{
		release2 = 1;
		down_count2 = 0;
	}
	
	if(B3==0&&last_B3==0)
	{
		release3 =0;
		down_count3++;
	}else if(B3==1&&last_B3==1)
	{
		release3 = 1;
		down_count3 = 0;
	}
	
	
	if(B4==0&&last_B4==0)
	{
		release4 =0;
		down_count4++;
	}else if(B4==1&&last_B4==1)
	{
		release4 = 1;
		down_count4 = 0;
	}
	
	last_B1 = B1;
	last_B2 = B2;
	last_B3 = B3;
	last_B4 = B4;

	
	if(release)
	{
		if(down_count >2&&down_count<50)
		{
			*key_value =11;
		}else if(down_count >100)
		{
			*key_value =12;
		}
	}
	if(release2)
	{
		if(down_count2 >2&&down_count2<50)
		{
			*key_value =21;
		}else if(down_count2 >100)
		{
			*key_value =22;
		}
	}
	if(release3)
	{
		if(down_count3 >2&&down_count3<50)
		{
			*key_value =31;
		}else if(down_count3 >100)
		{
			*key_value =32;
		}
	}
	if(release4)
	{
		if(down_count4 >2&&down_count4<50)
		{
			*key_value =41;
		}else if(down_count4 >100)
		{
			*key_value =42;
		}
	}
}

void key_scan5(uint8_t *key_value)
{
	uint8_t B1[4];
	uint8_t release[4];
	static uint8_t last_B1[4];
	static uint8_t down_count[4];
	
	B1[0] = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0);
	B1[1] = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
	B1[2] = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2);
	B1[3] = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
	
	for(uint8_t i=0;i<4;i++)
	{
		if(B1[i]==0&&last_B1[i] ==0)
	{
		down_count[i] ++;
		release[i] = 0;
	}else if(B1[i]==1&&last_B1[i] ==1)
	{
		down_count[i] =0;
		release[i] = 1;
	}
	
	last_B1[i] = B1[i];

	if(release[i])
	{
		if(down_count[i]>2&&down_count[i] <50)
		{
			*key_value = 11+i*10;
		}else if(down_count[i] >100)
		{
			*key_value = 12+i*10;
		}
	}
	}
}