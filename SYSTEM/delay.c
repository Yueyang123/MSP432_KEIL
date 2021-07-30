/*
 * @Author: Once day
 * @Date: 2021-07-28 12:33:40
 * @LastEditors: Once day
 * @LastEditTime: 2021-07-28 12:33:40
 * @Description: Ҳ����������������������̫�Ҵң�
 * 
 * Email:once_day@qq.com
 */
#include "msp432p401r.h"
#include "delay.h"
#include "sys.h"


u32 Delay_count=0;

//��ϵͳ�δ������������Ƶ��sysclk=48Mhz������Ƶ������480000����ÿ10msһ���жϡ�	   
void delay_init(void)//���õδ��ʱ����ʱ
{
	SysTick->LOAD=480000;   //48000000Hz ��480000�Σ�Ƶ��100Hz
	SysTick->VAL=0;         //���������
	SysTick->CTRL|=3;       //��������������ʹ���ж�
    //ע��MSP432�ĵδ��ʱ��ֻ��CPUʱ�Ӽ�Ƶ��48Mhz
}
//�δ��ʱ���ж�
void SysTick_Handler(void)
{
	Delay_count++;//10ms��һ�Σ��ܼ�ʱΪ2400����
}
u32 get_ms(void)
{
	return (480000-SysTick->VAL)/48000+Delay_count*10;//����ms����ʱ��
}

u64 get_us(void)
{
	return (480000-SysTick->VAL)/48+Delay_count*10000;//����us����ʱ��
}

u64 get_tick(void)
{
    return (480000-SysTick->VAL)+Delay_count*480000;//����cpu�δ𼶱�ʱ��
}

//�����Գ���10s
void delay_ms(u32 nms)
{
	delay_us(nms*1000);
}
//��ʱnus,
//nus:Ҫ��ʱ��us��.	
//nus:���ܳ���10,000,000us,������������ס��	    								   
void delay_us(u32 nus)
{		
	u32 last_count=Delay_count;
	u32 last_cnt=SysTick->VAL;
	//SYSTICK���¼���������ɵõ�ǰ��ʽ
	while(((Delay_count-last_count)*480000-SysTick->VAL+last_cnt)<nus*48);						    
}  
			 
u32 l2=55465445;
//����ͬ�෨�ڶ��ֲ��������
double randL2(void)
{ 
	static unsigned int a = 214013;
	static unsigned int b = 2531011;
	l2 = l2 * a + b;
	return (double)l2 / 4294967296;
}
//����һ����Χ�������
u32 myrand(u32 range)
{
	double rd=randL2();
	return (u32)(rd*range);
}
