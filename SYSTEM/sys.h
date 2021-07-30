#ifndef _SYS__H
#define _SYS__H
#include "msp432p401r.h"
#include "driverlib.h"
typedef unsigned char 			u8;
typedef unsigned short int  u16;
typedef unsigned int  			u32;
typedef long int 						u64;

void NVIC_group_init(void);//默认分组优化函数
void NVIC_enable(u8 NVIC_Priority,u8 NVIC_Channel);//中断使能函数
void NVIC_disable(u8 NVIC_Channel);//中断清除函数
void System_Init(void);

#endif