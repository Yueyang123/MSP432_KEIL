/*
 * @Author: Once day
 * @Date: 2021-07-28 12:33:48
 * @LastEditors: Once day
 * @LastEditTime: 2021-07-30 09:10:46
 * @Description: Ҳ����������������������̫�Ҵң�
 * Email:once_day@qq.com
 */
#ifndef __DELAY_H
#define __DELAY_H 			   
#include  "sys.h"	  

extern u32 Delay_count;         //delay�ӳٺ����ؼ�������
void SysTick_Handler(void);     //�δ������
void delay_init(void);          //��ʱ��ʼ��
void delay_us(u32 nus);         //��ʱus������
void delay_ms(u32 nms);         //��ʱms�����ʱ��
u32 get_ms(void);               //����ms�����ʱ��
u64 get_us(void);               //����us�����ʱ��
u64 get_tick(void);             //���صδ𼶱�ʱ��
u32 myrand(u32 range);            //ģ�������
#endif

