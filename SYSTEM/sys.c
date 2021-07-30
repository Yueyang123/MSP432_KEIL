#include "sys.h"
#include "delay.h"



//设置NVIC分组
//NVIC_Group:NVIC分组 0~4 总共5组
//该分组只在所有可分组中断失效时才会执行一次
//注意优先级不能超过设定的组的范围!否则会有意想不到的错误
//组划分:
//组0:0位抢占优先级,4位响应优先级
//组1:1位抢占优先级,3位响应优先级
//组2:2位抢占优先级,2位响应优先级
//组3:3位抢占优先级,1位响应优先级
//组4:4位抢占优先级,0位响应优先级
void NVIC_group_init(void)
{ 
	u32 last,now;	  
	now=0;//不管有多少分组情况，统一只有抢占优先级
	//例如0位，实际代表分组优先级位数下限在7位。
	now<<=8;
	//右移8位，因为分组位段位于AIRCR寄存器的8~10位。
	last=SCB->AIRCR;  //读取先前的设置
	//需要读取指示端设置,这是为了兼容，你很难分辨当前机器是大端还是小端
	last&=0X0000F8FF; //清空先前分组
	//此时保存了一些设置信息，但关键的是端设置
	now|=0X05FA0000; //写入钥匙
	//必须写入钥匙才能访问
	now|=last;	   
	//导入之前的一些设置信息	   
	SCB->AIRCR=now;  //设置分组	    	  				   
}

//设置NVIC 
//NVIC_Priority:抢占优先级;0~15
//NVIC_Priority的原则是,数值越小,越优先	
//请注意，低于os系统优先级的中断受限于OS管理
//高于os系统优先级的中断不受限制，但不能使用OSAPI函数。 
//初始化NVIC分组，该装置最大支持16个优先级 ,也就是4位分组优先级	
//4位分组，即中断优先级寄存器只有高四位有效
//为了适配FreeRTOS的使用，分组建议设置为四位分组优先级
//这里强制设置为3位分组优先级，没有选择。
//MSP432只有四位优先级
void NVIC_enable(u8 NVIC_Priority,u8 NVIC_Channel)	 
{ 
	NVIC->ISER[NVIC_Channel/32]|=1<<NVIC_Channel%32;//使能中断位(要清除的话,设置ICER对应位为1即可)
	//ISER有多个寄存器,表示选择。
	NVIC->IP[NVIC_Channel]|=NVIC_Priority<<4;	//设置响应优先级和抢断优先级
	//IP 有80个，其中67个可用，每个有32位，每八位控制一个中断向量。   	    	  				   
} 
void NVIC_disable(u8 NVIC_Channel)
{
	NVIC->ICER[NVIC_Channel/32]|=(1<<NVIC_Channel%32);//关闭对应中断
} 