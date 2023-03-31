/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "misc.h"
#include "stm32f401re_rcc.h"
#include "stm32f401re_gpio.h"
#include "stm32f401re_exti.h"
#include "stm32f401re_syscfg.h"
//#include "core_cm4.h"

/*Define Logic GPIO_PIN----------------------------------*/
#define GPIO_PIN_SET						1
#define GPIO_PIN_RESET						0
#define GPIO_PIN_LOW						0
#define GPIO_PIN_HIGH						1

/*Define GPIO_PIN----------------------------------------*/
#define LED_BOARD_GPIO_PORT					GPIOA
#define LED_BOARD_GPIO_PIN					GPIO_Pin_5

#define LED_RED_KIT0_GPIO_PORT				GPIOB
#define LED_RED_KIT0_GPIO_PIN				GPIO_Pin_13
#define LED_GREEN_KIT0_GPIO_PORT			GPIOA
#define LED_GREEN_KIT0_GPIO_PIN				GPIO_Pin_11
#define LED_BLUE_KIT0_GPIO_PORT				GPIOA
#define LED_BLUE_KIT0_GPIO_PIN				GPIO_Pin_10

#define LED_RED_KIT1_GPIO_PORT				GPIOA
#define LED_RED_KIT1_GPIO_PIN				GPIO_Pin_1
#define LED_GREEN_KIT1_GPIO_PORT			GPIOA
#define LED_GREEN_KIT1_GPIO_PIN				GPIO_Pin_0
#define LED_BLUE_KIT1_GPIO_PORT				GPIOC
#define LED_BLUE_KIT1_GPIO_PIN				GPIO_Pin_8

#define BUZZER_GPIO_PORT					GPIOC
#define BUZZER_GPIO_PIN						GPIO_Pin_9
#define BUZZER_PIN9							9

#define BUTTON_B2_GPIO_PORT					GPIOB
#define BUTTON_B2_GPIO_PIN					GPIO_Pin_3
#define BUTTON_B3_GPIO_PORT					GPIOA
#define BUTTON_B3_GPIO_PIN					GPIO_Pin_4
#define BUTTON_B4_GPIO_PORT					GPIOB
#define BUTTON_B4_GPIO_PIN					GPIO_Pin_0

#define GPIOA_SetClock						RCC_AHB1Periph_GPIOA
#define GPIOB_SetClock						RCC_AHB1Periph_GPIOB
#define GPIOC_SetClock						RCC_AHB1Periph_GPIOC

#define SYSCFG_SetClock						RCC_APB2Periph_SYSCFG

#define STATE_ON							Bit_SET
#define STATE_OFF							Bit_RESET

enum LedId_enum{
	LED_BOARD_ID				= 0,
	LED_KIT_ID0			 		= 1,
	LED_KIT_ID1					= 2,
	LED_ALL_ID					= 3
};

enum LedColor_enum{
	LED_RED				= 0,
	LED_GREEN			= 1,
	LED_BLUE			= 2,
};

/*Variables------------------------------------------------------------------------------------------------------------------------------------*/
static uint8_t 		B3Cnt=0;
static uint32_t		B3time = 0;
static uint8_t		B2Cnt=0;
static uint32_t		B2time = 0;
static uint8_t		B4Cnt=0;
static uint32_t 	B4time = 0;
static uint32_t 	miliSecs;


/*Functions------------------------------------------------------------------------------------------------------------------------------------*/
void delay(uint32_t ms);
void LedBuzz_Init(void);
void Button_Init(void);
void InterruptHandler(void);
void LedControl_SetState(uint8_t led_id,uint8_t led_color,uint8_t led_state);
void BuzzerControl_SetBeep();
uint32_t CalculatorTime(uint32_t dwTimeInit, uint32_t dwTimeCurrent);
void Blinkled_StatusPower();
void btnB3Scan();
void btnB2Scan();
void btnB4Scan();
/**
 * @func   	delay
 *
 * @brief  	system will wait unit mili-second
 *
 * @param	[ms] time delay (mili secs)
 *
 * @retval 	none
 */
void delay(uint32_t ms)
{
	uint32_t timeInit;
	timeInit = miliSecs;
	while(CalculatorTime(timeInit,miliSecs)<=ms)
	{

	}
}
/**
 * @func   	LedBuzz_Init
 *
 * @brief  	Initializes module LED & BUZZER
 *
 * @param	none
 *
 * @retval 	none
 */
void LedBuzz_Init(void)
{
	GPIO_InitTypeDef GPIO_Led_Board_InitStructure;

	GPIO_InitTypeDef GPIO_Led_RED_KIT0_InitStructure;
	GPIO_InitTypeDef GPIO_Led_GREEN_KIT0_InitStructure;
	GPIO_InitTypeDef GPIO_Led_BLUE_KIT0_InitStructure;

	GPIO_InitTypeDef GPIO_Led_RED_KIT1_InitStructure;
	GPIO_InitTypeDef GPIO_Led_GREEN_KIT1_InitStructure;
	GPIO_InitTypeDef GPIO_Led_BLUE_KIT1_InitStructure;

	GPIO_InitTypeDef GPIO_Buzz_InitStructure;

	//Enable clock peripheral----------------------------------------------------------------------------------------------------------------
	RCC_AHB1PeriphClockCmd(GPIOA_SetClock, ENABLE);
	RCC_AHB1PeriphClockCmd(GPIOB_SetClock, ENABLE);
	RCC_AHB1PeriphClockCmd(GPIOC_SetClock, ENABLE);

	//GPIO_Led_Board-----------------------------------------------------------------------------------------------------------------------------
	GPIO_Led_Board_InitStructure.GPIO_Pin = LED_BOARD_GPIO_PIN;
	GPIO_Led_Board_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Led_Board_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Led_Board_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Led_Board_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	//GPIO_Led_RED_KIT0-----------------------------------------------------------------------------------------------------------------------------
	GPIO_Led_RED_KIT0_InitStructure.GPIO_Pin = LED_RED_KIT0_GPIO_PIN;
	GPIO_Led_RED_KIT0_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Led_RED_KIT0_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Led_RED_KIT0_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Led_RED_KIT0_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	//GPIO_Led_GREEN_KIT0------------------------------------------------------------------------------------------------------------------------------
	GPIO_Led_GREEN_KIT0_InitStructure.GPIO_Pin = LED_GREEN_KIT0_GPIO_PIN;
	GPIO_Led_GREEN_KIT0_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Led_GREEN_KIT0_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Led_GREEN_KIT0_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Led_GREEN_KIT0_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	//GPIO_Led_BLUE_KIT0------------------------------------------------------------------------------------------------------------------------------
	GPIO_Led_BLUE_KIT0_InitStructure.GPIO_Pin = LED_BLUE_KIT0_GPIO_PIN;
	GPIO_Led_BLUE_KIT0_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Led_BLUE_KIT0_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Led_BLUE_KIT0_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Led_BLUE_KIT0_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/

	//GPIO_Led_RED_KIT1------------------------------------------------------------------------------------------------------------------------------
	GPIO_Led_RED_KIT1_InitStructure.GPIO_Pin = LED_RED_KIT1_GPIO_PIN;
	GPIO_Led_RED_KIT1_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Led_RED_KIT1_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Led_RED_KIT1_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Led_RED_KIT1_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	//GPIO_Led_GREEN_KIT1------------------------------------------------------------------------------------------------------------------------------
	GPIO_Led_GREEN_KIT1_InitStructure.GPIO_Pin = LED_GREEN_KIT1_GPIO_PIN;
	GPIO_Led_GREEN_KIT1_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Led_GREEN_KIT1_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Led_GREEN_KIT1_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Led_GREEN_KIT1_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	//GPIO_Led_BLUE_KIT1------------------------------------------------------------------------------------------------------------------------------
	GPIO_Led_BLUE_KIT1_InitStructure.GPIO_Pin = LED_BLUE_KIT1_GPIO_PIN;
	GPIO_Led_BLUE_KIT1_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Led_BLUE_KIT1_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Led_BLUE_KIT1_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Led_BLUE_KIT1_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	/*------------------------------------------------------------------------------------------------------------------------------------------------------*/

	//GPIO_Buzz----------------------------------------------------------------------------------------------------------------------------------
	GPIO_Buzz_InitStructure.GPIO_Pin = BUZZER_GPIO_PIN;
	GPIO_Buzz_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Buzz_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Buzz_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Buzz_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	//The function initializes all of the above values-------------------------------------------------------------------------------------------
	GPIO_Init(LED_BOARD_GPIO_PORT, &GPIO_Led_Board_InitStructure);

	GPIO_Init(LED_RED_KIT0_GPIO_PORT, &GPIO_Led_RED_KIT0_InitStructure);//red0
	GPIO_Init(LED_GREEN_KIT0_GPIO_PORT, &GPIO_Led_GREEN_KIT0_InitStructure);//green0
	GPIO_Init(LED_BLUE_KIT0_GPIO_PORT, &GPIO_Led_BLUE_KIT0_InitStructure);//blue0

	GPIO_Init(LED_RED_KIT1_GPIO_PORT, &GPIO_Led_RED_KIT1_InitStructure);//red1
	GPIO_Init(LED_GREEN_KIT1_GPIO_PORT, &GPIO_Led_GREEN_KIT1_InitStructure);//green1
	GPIO_Init(LED_BLUE_KIT1_GPIO_PORT, &GPIO_Led_BLUE_KIT1_InitStructure);//blue1

	GPIO_Init(BUZZER_GPIO_PORT, &GPIO_Buzz_InitStructure);
}
/**
 * @func   	Button_Init
 *
 * @brief  	Initializes module Button
 *
 * @param	none
 *
 * @retval 	none
 */
void Button_Init(void)
{
	//Decleare type variable GPIO Struct---------------------------------------------------------------------------------------------------------
	GPIO_InitTypeDef GPIO_B2_InitStructure;
	GPIO_InitTypeDef GPIO_B3_InitStructure;
	GPIO_InitTypeDef GPIO_B4_InitStructure;

	EXTI_InitTypeDef B2_EXTI_Line3_InitStructure;//B2
	EXTI_InitTypeDef B3_EXTI_Line4_InitStructure;//B3
	EXTI_InitTypeDef B4_EXTI_Line0_InitStructure;//B4

	NVIC_InitTypeDef B2_NVIC_EXTI3_InitStructure;//B2
	NVIC_InitTypeDef B3_NVIC_EXTI4_InitStructure;//B3
	NVIC_InitTypeDef B4_NVIC_EXTI0_InitStructure;//B4

	//Button_B2----------------------------------------------------------------------------------------------------------------------------------
	RCC_AHB1PeriphClockCmd(GPIOB_SetClock, ENABLE);
	GPIO_B2_InitStructure.GPIO_Pin = BUTTON_B2_GPIO_PIN;
	GPIO_B2_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_B2_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_B2_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	//Button_B3----------------------------------------------------------------------------------------------------------------------------------
	//RCC_AHB1PeriphClockCmd(GPIOA_SetClock, ENABLE);
	GPIO_B3_InitStructure.GPIO_Pin = BUTTON_B3_GPIO_PIN;
	GPIO_B3_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_B3_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_B3_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	//Button_B4----------------------------------------------------------------------------------------------------------------------------------
	GPIO_B4_InitStructure.GPIO_Pin = BUTTON_B4_GPIO_PIN;
	GPIO_B4_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_B4_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_B4_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	//The function initializes all of the above values-------------------------------------------------------------------------------------------
	GPIO_Init(BUTTON_B2_GPIO_PORT, &GPIO_B2_InitStructure);
	GPIO_Init(BUTTON_B3_GPIO_PORT, &GPIO_B3_InitStructure);
	GPIO_Init(BUTTON_B4_GPIO_PORT, &GPIO_B4_InitStructure);

	//Interrupts---------------------------------------------------------------------------------------------------------------------------------

	//Cấp clock cho ngoại vi Syscfg.
	RCC_APB2PeriphClockCmd(SYSCFG_SetClock,ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource3);//B2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource4);//B3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource0);//B4

	//Configure EXTI Line
	B3_EXTI_Line4_InitStructure.EXTI_Line = EXTI_Line4;
	B3_EXTI_Line4_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	B3_EXTI_Line4_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	B3_EXTI_Line4_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&B3_EXTI_Line4_InitStructure);

	B2_EXTI_Line3_InitStructure.EXTI_Line = EXTI_Line3;
	B2_EXTI_Line3_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	B2_EXTI_Line3_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	B2_EXTI_Line3_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&B2_EXTI_Line3_InitStructure);

	B4_EXTI_Line0_InitStructure.EXTI_Line = EXTI_Line0;
	B4_EXTI_Line0_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	B4_EXTI_Line0_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	B4_EXTI_Line0_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&B4_EXTI_Line0_InitStructure);

	//Enable and set EXTI Line4 Interrupt to the lowest priority
	B3_NVIC_EXTI4_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	B3_NVIC_EXTI4_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	B3_NVIC_EXTI4_InitStructure.NVIC_IRQChannelSubPriority = 0;
	B3_NVIC_EXTI4_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	//Enable and set EXTI Line3 Interrupt to the lowest priority
	B2_NVIC_EXTI3_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	B2_NVIC_EXTI3_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	B2_NVIC_EXTI3_InitStructure.NVIC_IRQChannelSubPriority = 0;
	B2_NVIC_EXTI3_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	//Enable and set EXTI Line0 Interrupt to the lowest priority
	B4_NVIC_EXTI0_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	B4_NVIC_EXTI0_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	B4_NVIC_EXTI0_InitStructure.NVIC_IRQChannelSubPriority = 0;
	B4_NVIC_EXTI0_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&B3_NVIC_EXTI4_InitStructure);
	NVIC_Init(&B2_NVIC_EXTI3_InitStructure);
	NVIC_Init(&B4_NVIC_EXTI0_InitStructure);
}
/**
 * @func   	SysTick_Handler
 *
 * @brief  	Interrupt Systick ( Interrupt every 1 milisecs )
 *
 * @param	none
 *
 * @retval 	none
 */
void SysTick_Handler(void)
{
	miliSecs++;
}
/**
 * @func   	EXTI4_IRQHandler
 *
 * @brief  	Interrupt Handler line 4
 *
 * @param	none
 *
 * @retval 	none
 */
void EXTI4_IRQHandler(void)
{
	if(EXTI_GetFlagStatus(EXTI_Line4)==SET)
	{
		B3Cnt++;
		B3time=miliSecs;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}
/**
 * @func   	EXTI3_IRQHandler
 *
 * @brief  	Interrupt Handler line 3
 *
 * @param	none
 *
 * @retval 	none
 */
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetFlagStatus(EXTI_Line3)==SET)
	{
		B2Cnt++;
		B2time=miliSecs;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
}
/**
 * @func   	EXTI0_IRQHandler
 *
 * @brief  	Interrupt Handler line 0
 *
 * @param	none
 *
 * @retval 	none
 */
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetFlagStatus(EXTI_Line0)==SET)
	{
		B4Cnt++;
		B4time=miliSecs;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}
/**
 * @func   LedControl_SetState
 *
 * @brief  Control board LED & LED RGB on KIT
 *
 * @param  [led_id] id of LED
 * @param  [led_color] color of LED (R-G-B)
 * @param  [led_state] state of LED (ON or OFF)
 *
 * @retval none
 */
//Cách 1 ( tạo mảng )
typedef struct LedGpio{
	GPIO_TypeDef* port;
	uint16_t pinMask;
}LedGpio_t;
void LedControl_SetState1(uint8_t led_id,uint8_t led_color,uint8_t led_state){
	LedGpio_t LedArr0[] =
	{
			{.port = LED_RED_KIT0_GPIO_PORT, .pinMask = LED_RED_KIT0_GPIO_PIN},
			{.port = LED_GREEN_KIT0_GPIO_PORT, .pinMask = LED_GREEN_KIT0_GPIO_PIN},
			{.port = LED_BLUE_KIT0_GPIO_PORT, .pinMask = LED_BLUE_KIT0_GPIO_PIN}
	};
	LedGpio_t LedArr1[] =
	{
		{.port = LED_RED_KIT1_GPIO_PORT, .pinMask = LED_RED_KIT1_GPIO_PIN},
		{.port = LED_GREEN_KIT1_GPIO_PORT, .pinMask = LED_GREEN_KIT1_GPIO_PIN},
		{.port = LED_BLUE_KIT1_GPIO_PORT, .pinMask = LED_BLUE_KIT1_GPIO_PIN}
	};
	switch(led_id)
	{
	case 0:// LED BOARD
		GPIO_WriteBit(LED_BOARD_GPIO_PORT, LED_BOARD_GPIO_PIN, led_state);
		break;

	case 1://LED KIT 0
		GPIO_WriteBit(LedArr0[led_color].port, LedArr0[led_color].pinMask, led_state);
		break;
	case 2://LED KIT 1
		GPIO_WriteBit(LedArr1[led_color].port, LedArr1[led_color].pinMask, led_state);
		break;
	case 3://LED ALL
		GPIO_WriteBit(LedArr0[led_color].port, LedArr0[led_color].pinMask, led_state);
		GPIO_WriteBit(LedArr1[led_color].port, LedArr1[led_color].pinMask, led_state);
		break;
	}

}
////Cách 2 ( gọn hơn cách 3 khi dùng hàm GPIO_WriteBit() )
//void LedControl_SetState(uint8_t led_id,uint8_t led_color,uint8_t led_state){
//	switch(led_id)
//		{
//		case 0:// LED BOARD
//			GPIO_WriteBit(LED_BOARD_GPIO_PORT, LED_BOARD_GPIO_PIN, led_state);
//			break;
//
//		case 1://LED KIT 0
//			if(led_color==0)//LED RED
//			{
//				GPIO_WriteBit(LED_RED_KIT1_GPIO_PORT, LED_RED_KIT1_GPIO_PIN, led_state);
//			}
//			else if(led_color==1)//LED GREEN
//			{
//				GPIO_WriteBit(LED_GREEN_KIT1_GPIO_PORT,LED_GREEN_KIT1_GPIO_PIN, led_state);
//			}
//			else if(led_color==2)//LED BLUE
//			{
//				GPIO_WriteBit(LED_BLUE_KIT1_GPIO_PORT,LED_BLUE_KIT1_GPIO_PIN, led_state);
//			}
//			break;
//
//		case 2://LED KIT 1
//			if(led_color==0)//LED RED
//			{
//				GPIO_WriteBit(LED_RED_KIT1_GPIO_PORT, LED_RED_KIT1_GPIO_PIN, led_state);
//			}
//			else if(led_color==1)//LED GREEN
//			{
//				GPIO_WriteBit(LED_GREEN_KIT1_GPIO_PORT,LED_GREEN_KIT1_GPIO_PIN, led_state);
//			}
//			else if(led_color==2)//LED BLUE
//			{
//				GPIO_WriteBit(LED_BLUE_KIT1_GPIO_PORT,LED_BLUE_KIT1_GPIO_PIN, led_state);
//			}
//			break;
//
//		case 3://LED ALL
//			if(led_color==0)//LED RED
//			{
//				GPIO_WriteBit(LED_RED_KIT0_GPIO_PORT,LED_RED_KIT0_GPIO_PIN, led_state);
//				GPIO_WriteBit(LED_RED_KIT1_GPIO_PORT,LED_RED_KIT1_GPIO_PIN, led_state);
//			}
//			else if(led_color==1)//LED GREEN
//			{
//				GPIO_WriteBit(LED_GREEN_KIT0_GPIO_PORT,LED_GREEN_KIT0_GPIO_PIN, led_state);
//				GPIO_WriteBit(LED_GREEN_KIT0_GPIO_PORT,LED_GREEN_KIT0_GPIO_PIN, led_state);
//			}
//			else if(led_color==2)//LED BLUE
//			{
//				GPIO_WriteBit(LED_BLUE_KIT0_GPIO_PORT,LED_BLUE_KIT0_GPIO_PIN, led_state);
//				GPIO_WriteBit(LED_BLUE_KIT1_GPIO_PORT,LED_BLUE_KIT1_GPIO_PIN, led_state);
//			}
//			break;
//		default:
//			break;
//		}
//}
////Cách 3 ( cách củ chuối nhất )
//void LedControl_SetState2(uint8_t led_id,uint8_t led_color,uint8_t led_state)
//{
//	switch(led_id)
//	{
//	case 0:// LED BOARD
//		if(led_state==STATE_ON)
//		{
//			GPIO_SetBits(LED_BOARD_GPIO_PORT,LED_BOARD_GPIO_PIN);
//		}
//		else//led_state==STATE_OFF
//		{
//			GPIO_ResetBits(LED_BOARD_GPIO_PORT,LED_BOARD_GPIO_PIN);
//		}
//		break;
//
//	case 1://LED KIT 0
//		if(led_color==0)//LED RED
//		{
//			if(led_state==STATE_ON)
//			{
//				GPIO_SetBits(LED_RED_KIT0_GPIO_PORT,LED_RED_KIT0_GPIO_PIN);
//			}
//			else//led_state==STATE_OFF
//			{
//				GPIO_ResetBits(LED_RED_KIT0_GPIO_PORT,LED_RED_KIT0_GPIO_PIN);
//			}
//		}
//		else if(led_color==1)//LED GREEN
//		{
//			if(led_state==STATE_ON)
//			{
//				GPIO_SetBits(LED_GREEN_KIT0_GPIO_PORT,LED_GREEN_KIT0_GPIO_PIN);
//			}
//			else//led_state==STATE_OFF
//			{
//				GPIO_ResetBits(LED_GREEN_KIT0_GPIO_PORT,LED_GREEN_KIT0_GPIO_PIN);
//			}
//		}
//		else if(led_color==2)//LED BLUE
//		{
//			if(led_state==STATE_ON)
//			{
//				GPIO_SetBits(LED_BLUE_KIT0_GPIO_PORT,LED_BLUE_KIT0_GPIO_PIN);
//			}
//			else//led_state==STATE_OFF
//			{
//				GPIO_ResetBits(LED_BLUE_KIT0_GPIO_PORT,LED_BLUE_KIT0_GPIO_PIN);
//			}
//		}
//		break;
//
//	case 2://LED KIT 1
//		if(led_color==0)//LED RED
//		{
//			if(led_state==STATE_ON)
//			{
//				GPIO_SetBits(LED_RED_KIT1_GPIO_PORT,LED_RED_KIT1_GPIO_PIN);
//			}
//			else//led_state==STATE_OFF
//			{
//				GPIO_ResetBits(LED_RED_KIT1_GPIO_PORT,LED_RED_KIT1_GPIO_PIN);
//			}
//		}
//		else if(led_color==1)//LED GREEN
//		{
//			if(led_state==STATE_ON)
//			{
//				GPIO_SetBits(LED_GREEN_KIT1_GPIO_PORT,LED_GREEN_KIT1_GPIO_PIN);
//			}
//			else//led_state==STATE_OFF
//			{
//				GPIO_ResetBits(LED_GREEN_KIT1_GPIO_PORT,LED_GREEN_KIT1_GPIO_PIN);
//			}
//		}
//		else if(led_color==2)//LED BLUE
//		{
//			if(led_state==STATE_ON)
//			{
//				GPIO_SetBits(LED_BLUE_KIT1_GPIO_PORT,LED_BLUE_KIT1_GPIO_PIN);
//			}
//			else//led_state==STATE_OFF
//			{
//				GPIO_ResetBits(LED_BLUE_KIT1_GPIO_PORT,LED_BLUE_KIT1_GPIO_PIN);
//			}
//		}
//		break;
//
//	case 3://LED ALL
//		if(led_color==0)//LED RED
//		{
//			if(led_state==STATE_ON)
//			{
//				GPIO_SetBits(LED_RED_KIT0_GPIO_PORT,LED_RED_KIT0_GPIO_PIN);
//				GPIO_SetBits(LED_RED_KIT1_GPIO_PORT,LED_RED_KIT1_GPIO_PIN);
//			}
//			else//led_state==STATE_OFF
//			{
//				GPIO_ResetBits(LED_RED_KIT0_GPIO_PORT,LED_RED_KIT0_GPIO_PIN);
//				GPIO_ResetBits(LED_RED_KIT1_GPIO_PORT,LED_RED_KIT1_GPIO_PIN);
//			}
//		}
//		else if(led_color==1)//LED GREEN
//		{
//			if(led_state==STATE_ON)
//			{
//				GPIO_SetBits(LED_GREEN_KIT0_GPIO_PORT,LED_GREEN_KIT0_GPIO_PIN);
//				GPIO_SetBits(LED_GREEN_KIT1_GPIO_PORT,LED_GREEN_KIT1_GPIO_PIN);
//			}
//			else//led_state==STATE_OFF
//			{
//				GPIO_ResetBits(LED_GREEN_KIT1_GPIO_PORT,LED_GREEN_KIT1_GPIO_PIN);
//				GPIO_ResetBits(LED_GREEN_KIT0_GPIO_PORT,LED_GREEN_KIT0_GPIO_PIN);
//			}
//		}
//		else if(led_color==2)//LED BLUE
//		{
//			if(led_state==STATE_ON)
//			{
//				GPIO_SetBits(LED_BLUE_KIT0_GPIO_PORT,LED_BLUE_KIT0_GPIO_PIN);
//				GPIO_SetBits(LED_BLUE_KIT1_GPIO_PORT,LED_BLUE_KIT1_GPIO_PIN);
//			}
//			else//led_state==STATE_OFF
//			{
//				GPIO_ResetBits(LED_BLUE_KIT0_GPIO_PORT,LED_BLUE_KIT0_GPIO_PIN);
//				GPIO_ResetBits(LED_BLUE_KIT1_GPIO_PORT,LED_BLUE_KIT1_GPIO_PIN);
//			}
//		}
//		break;
//	default:
//		break;
//	}
//}

/**
 * @func   BuzzerControl_SetBeep
 *
 * @brief  Buzzer set 2 beep
 *
 * @param  none
 *
 * @retval none
 */
void BuzzerControl_SetBeep()
{
	for(int i = 0; i < 2; i ++){
		GPIO_SetBits(BUZZER_GPIO_PORT,BUZZER_GPIO_PIN);
		delay(100);
		GPIO_ResetBits(BUZZER_GPIO_PORT,BUZZER_GPIO_PIN);
		delay(100);
	}
}

/**
 * @func   CalculatorTime
 *
 * @brief  Calculate duration time between 2 point with unit mili-second.
 *
 * @param  [dwTimeInit]: Start point time
 * @param  [dwTimeCurrent]: Stop point time
 *
 * @retval [uint32_t] : return duration time(ms)
 */
uint32_t CalculatorTime(uint32_t dwTimeInit, uint32_t dwTimeCurrent)
{
	uint32_t dwTimeTotal;
	if(dwTimeCurrent >= dwTimeInit)
	{
		dwTimeTotal = dwTimeCurrent - dwTimeInit;
	}
	else
	{
		dwTimeTotal = 0xFFFFFFFFU + dwTimeCurrent - dwTimeInit;
	}
	return dwTimeTotal;
}
/**
 * @func   Blinkled_StatusPower
 *
 * @brief  LED Blink 4 times
 *
 * @param  none
 *
 * @retval none
 */
void Blinkled_StatusPower()
{
	for(uint8_t i=0;i<4;i++)
	{
		LedControl_SetState1(LED_BOARD_ID,LED_GREEN,STATE_ON);
		delay(300);
		LedControl_SetState1(LED_BOARD_ID,LED_GREEN,STATE_OFF);
		delay(300);
	}

}
/**
 * @func   LedControl_SetStatus
 *
 * @brief  Buzzer beep 2 times & LED on KIT Blink 4 times
 *
 * @param  none
 *
 * @retval none
 */
void LedControl_SetStatus()
{
	for(int i = 0; i < 4; i++)
	{
		BuzzerControl_SetBeep();

		LedControl_SetState1(LED_ALL_ID,LED_GREEN,STATE_ON);
		delay(400);
		LedControl_SetState1(LED_ALL_ID,LED_GREEN,STATE_OFF);
		delay(400);
	}
}
//Hàm này để kiểm tra liên tục
static uint32_t B3TimeRelease = 0;
/**
 * @func   btnB3Scan
 *
 * @brief  Scan status Button B3
 *
 * @param  none
 *
 * @retval none
 */
void btnB3Scan()
{
	if(B3Cnt==0) return;
	//giữ 500ms
	if(GPIO_ReadInputDataBit(BUTTON_B3_GPIO_PORT,BUTTON_B3_GPIO_PIN)==0)
	{
		B3TimeRelease = 0;
		if(CalculatorTime(B3time,miliSecs)==500)
		{
			//B3time=0;
		}
	}
	else
	{
		if( B3Cnt != 0)
		{
			//Update release time in the first time release
			if(B3TimeRelease == 0)
			{
				B3TimeRelease = miliSecs;
			}
			//Check timeout release
			if(CalculatorTime(B3TimeRelease,miliSecs) > 500)
			{
				switch(B3Cnt)
				{
					case 1:
//						LedControl_SetState(LED_KIT_ID0,LED_RED,STATE_ON);
//						LedControl_SetState(LED_KIT_ID1,LED_RED,STATE_ON);
//						LedControl_SetState(LED_ALL_ID,LED_BLUE,STATE_ON);
						break;
					case 3:
//						LedControl_SetState(LED_KIT_ID0,LED_RED,STATE_OFF);
//						LedControl_SetState(LED_KIT_ID1,LED_RED,STATE_OFF);
//						LedControl_SetState(LED_ALL_ID,LED_BLUE,STATE_OFF);
						break;
					case 5:
						LedControl_SetStatus();
						break;
				}
				B3Cnt = 0;
				B3TimeRelease = 0;
			}
		}
	}
}

/**
 * @func   btnB2Scan
 *
 * @brief  Scan status Button B2
 *
 * @param  none
 *
 * @retval none
 */
static uint32_t B2TimeRelease = 0;
void btnB2Scan()
{
	if(B2Cnt==0) return;
	//giữ 500ms
	if(GPIO_ReadInputDataBit(BUTTON_B2_GPIO_PORT,BUTTON_B2_GPIO_PIN)==0)
	{
		B2TimeRelease = 0;
		if(CalculatorTime(B2time,miliSecs)==500)
		{
			LedControl_SetState1(LED_KIT_ID0,LED_BLUE,STATE_ON);
		}
	}
	else
	{
		if( B2Cnt != 0)
		{
			//Update release time in the first time release
			if(B2TimeRelease == 0)
			{
				B2TimeRelease = miliSecs;
				LedControl_SetState1(LED_KIT_ID0,LED_BLUE,STATE_OFF);
			}
			//Check timeout release
			if(CalculatorTime(B2TimeRelease,miliSecs) > 500)
			{
				switch(B2Cnt)
				{
					case 1:
						LedControl_SetState1(LED_KIT_ID0,LED_BLUE,STATE_OFF);
						break;
					case 2:
						LedControl_SetState1(LED_KIT_ID0,LED_BLUE,STATE_ON);
						break;
					case 3:
						break;
					case 5:
						break;
				}
				B2Cnt = 0;
				B2TimeRelease = 0;
			}
		}
	}
}
/**
 * @func   btnB4Scan
 *
 * @brief  Scan status Button B4
 *
 * @param  none
 *
 * @retval none
 */
static uint32_t B4TimeRelease = 0;
void btnB4Scan()
{
	if(B4Cnt==0) return;
	//giữ 500ms
	if(GPIO_ReadInputDataBit(BUTTON_B4_GPIO_PORT,BUTTON_B4_GPIO_PIN)==0)
	{
		B4TimeRelease = 0;
		if(CalculatorTime(B4time,miliSecs)==500)
		{
			LedControl_SetState1(LED_KIT_ID1,LED_RED,STATE_ON);
		}
	}
	else
	{
		if( B4Cnt != 0)
		{
			//Update release time in the first time release
			if(B4TimeRelease == 0)
			{
				B4TimeRelease = miliSecs;
				LedControl_SetState1(LED_KIT_ID1,LED_RED,STATE_OFF);
			}
			//Check timeout release
			if(CalculatorTime(B4TimeRelease,miliSecs) > 500)
			{
				switch(B4Cnt)
				{
					case 1:
						LedControl_SetState1(LED_KIT_ID1,LED_RED,STATE_OFF);
						break;
					case 2:
						LedControl_SetState1(LED_KIT_ID1,LED_RED,STATE_ON);
						break;
					case 3:
						break;
					case 5:
						break;
				}
				B4Cnt = 0;
				B4TimeRelease = 0;
			}
		}
	}
}

int main(void)
{
 	SystemCoreClockUpdate();
	SysTick_Config(84000);
	LedBuzz_Init();
	Button_Init();
	Blinkled_StatusPower();
	while(1)
	{
		btnB3Scan();
		btnB2Scan();
		btnB4Scan();
	}
	return 0;
}