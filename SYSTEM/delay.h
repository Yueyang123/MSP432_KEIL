/*
 * @Author: Once day
 * @Date: 2021-07-28 12:33:48
 * @LastEditors: Once day
 * @LastEditTime: 2021-07-30 09:10:46
 * @Description: 也信美人终作土，不堪幽梦太匆匆！
 * Email:once_day@qq.com
 */
#ifndef __DELAY_H
#define __DELAY_H 			   
#include  "sys.h"	  

extern u32 Delay_count;         //delay延迟函数关键控制量
void SysTick_Handler(void);     //滴答计数器
void delay_init(void);          //延时初始化
void delay_us(u32 nus);         //延时us级别函数
void delay_ms(u32 nms);         //延时ms级别的时间
u32 get_ms(void);               //返回ms级别的时间
u64 get_us(void);               //返回us级别的时间
u64 get_tick(void);             //返回滴答级别时间
u32 myrand(u32 range);            //模拟随机数
#endif

