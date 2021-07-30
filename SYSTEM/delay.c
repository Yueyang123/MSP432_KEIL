/*
 * @Author: Once day
 * @Date: 2021-07-28 12:33:40
 * @LastEditors: Once day
 * @LastEditTime: 2021-07-28 12:33:40
 * @Description: 也信美人终作土，不堪幽梦太匆匆！
 * 
 * Email:once_day@qq.com
 */
#include "msp432p401r.h"
#include "delay.h"
#include "sys.h"


u32 Delay_count=0;

//该系统滴答计数器，输入频率sysclk=48Mhz不做分频，计数480000，即每10ms一次中断。	   
void delay_init(void)//采用滴答计时器计时
{
	SysTick->LOAD=480000;   //48000000Hz 数480000次，频率100Hz
	SysTick->VAL=0;         //清零计数器
	SysTick->CTRL|=3;       //启动计数器并且使能中断
    //注意MSP432的滴答计时器只有CPU时钟即频率48Mhz
}
//滴答计时器中断
void SysTick_Handler(void)
{
	Delay_count++;//10ms加一次，总计时为2400万秒
}
u32 get_ms(void)
{
	return (480000-SysTick->VAL)/48000+Delay_count*10;//返回ms级别时间
}

u64 get_us(void)
{
	return (480000-SysTick->VAL)/48+Delay_count*10000;//返回us级别时间
}

u64 get_tick(void)
{
    return (480000-SysTick->VAL)+Delay_count*480000;//返回cpu滴答级别时间
}

//不可以超过10s
void delay_ms(u32 nms)
{
	delay_us(nms*1000);
}
//延时nus,
//nus:要延时的us数.	
//nus:不能超过10,000,000us,变量类型限制住了	    								   
void delay_us(u32 nus)
{		
	u32 last_count=Delay_count;
	u32 last_cnt=SysTick->VAL;
	//SYSTICK向下计数，计算可得当前公式
	while(((Delay_count-last_count)*480000-SysTick->VAL+last_cnt)<nus*48);						    
}  
			 
u32 l2=55465445;
//线性同余法第二种参数随机数
double randL2(void)
{ 
	static unsigned int a = 214013;
	static unsigned int b = 2531011;
	l2 = l2 * a + b;
	return (double)l2 / 4294967296;
}
//返回一定范围的随机数
u32 myrand(u32 range)
{
	double rd=randL2();
	return (u32)(rd*range);
}
