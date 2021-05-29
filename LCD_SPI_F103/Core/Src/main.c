/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "lcd.h"
#include "string.h"
#include "ILI9488_SPI.h"
#include <stdio.h>
#include "TouchPanel.h"
#include "BULENTFONT.h"
#include "buton.h"
#include "geri.h"
#include "resim3.h"
//#include "Hangle.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
struct bitstructure1 {
	unsigned int basildi_1 :1;
	unsigned int basildi_2 :1;
	unsigned int basildi_3 :1;
	unsigned int basildi_4 :1;
	unsigned int basildi_5 :1;
	unsigned int basildi_6 :1;
	unsigned int basildi_7 :1;
	unsigned int basildi_8 :1;
};
union data1 {
	int bytedataA;
	struct bitstructure1 bits;
} FLAG_BASILDI;
//******
struct bitstructure2 {
	unsigned int birakildi_1 :1;
	unsigned int birakildi_2 :1;
	unsigned int birakildi_3 :1;
	unsigned int birakildi_4 :1;
	unsigned int birakildi_5 :1;
	unsigned int birakildi_6 :1;
	unsigned int birakildi_7 :1;
	unsigned int birakildi_8 :1;
};
union data2 {
	int bytedataA;
	struct bitstructure2 bits;
} FLAG_BIRAKILDI;
//*************
typedef struct {
	char     *p_resim; //resmin adresi
	uint16_t resim_korx;
	uint16_t resim_kory;
	uint16_t resim_w;
	uint16_t resim_h;
	uint8_t  resim_type;//0 PUSH,1 TOGLE
	uint8_t  resim_value;
}RESIM;

#define toucharea_adeti    32
#define sayfa_adeti         4
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
RESIM T_RESIM[toucharea_adeti]; // her sayfa için toucadeti/sayfaedeti

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN PV */
volatile uint16_t xx;
volatile uint16_t yy;
char yazi[64];
uint8_t sayfa_no=0;
uint8_t sayfa_touch_adeti=toucharea_adeti/sayfa_adeti;
volatile uint8_t son_basilan;
uint8_t sayac;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */
void SAYFA();
void TOUCH_KONTROL();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */



  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  // LCD_Init();
  ILI9488_Init();

  ILI9488_Fill_Screen(RED);
 // HAL_Delay(50);
  ILI9488_Fill_Screen(GREEN);
 // HAL_Delay(50);
  ILI9488_Fill_Screen(BLUE);
 // HAL_Delay(50);
  ILI9488_Fill_Screen(YELLOW);
  //HAL_Delay(50);
  ILI9488_Fill_Screen(WHITE);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  //Touch_Calibre();
/*
  ILI9488_LCD_RESIM(180,160,(char *)gImage_resim1,0);
*/
//*****BIRINCI SAYFA RESIMLERI
  T_RESIM[0].p_resim=(char*)gImage_buton;
  T_RESIM[0].resim_korx=20;
  T_RESIM[0].resim_kory=80;
  T_RESIM[0].resim_type=0;
  T_RESIM[0].resim_value=0;

  T_RESIM[1].p_resim=(char*)gImage_buton;
  T_RESIM[1].resim_korx=20;
  T_RESIM[1].resim_kory=180;
  T_RESIM[1].resim_type=0;
  T_RESIM[1].resim_value=1;

  T_RESIM[2].p_resim=(char*)gImage_buton;
  T_RESIM[2].resim_korx=310;
  T_RESIM[2].resim_kory=80;
  T_RESIM[2].resim_type=1;
  T_RESIM[2].resim_value=0;

  T_RESIM[3].p_resim=(char*)gImage_buton;
  T_RESIM[3].resim_korx=310;
  T_RESIM[3].resim_kory=180;
  T_RESIM[3].resim_type=1;
  T_RESIM[3].resim_value=1;

  T_RESIM[4].p_resim=(char*)gImage_resim3;
  T_RESIM[4].resim_korx=190;
  T_RESIM[4].resim_kory=130;
  T_RESIM[4].resim_type=0;
  T_RESIM[4].resim_value=0;

  T_RESIM[7].p_resim=(char*)gImage_geri;
  T_RESIM[7].resim_korx=420;
  T_RESIM[7].resim_kory=265;
  T_RESIM[7].resim_type=0;
  T_RESIM[7].resim_value=0;
//****IKINCI SAYFA RESIMLERI
  T_RESIM[8].p_resim=(char*)gImage_resim3;
  T_RESIM[8].resim_korx=10;
  T_RESIM[8].resim_kory=250;
  T_RESIM[8].resim_type=0;
  T_RESIM[8].resim_value=0;

  T_RESIM[9].p_resim=(char*)gImage_buton;
  T_RESIM[9].resim_korx=20;
  T_RESIM[9].resim_kory=100;
  T_RESIM[9].resim_type=0;
  T_RESIM[9].resim_value=0;

  T_RESIM[10].p_resim=(char*)gImage_buton;
  T_RESIM[10].resim_korx=310;
  T_RESIM[10].resim_kory=100;
  T_RESIM[10].resim_type=1;
  T_RESIM[10].resim_value=0;

  T_RESIM[15].p_resim=(char*)gImage_geri;
  T_RESIM[15].resim_korx=420;
  T_RESIM[15].resim_kory=265;
  T_RESIM[15].resim_type=0;
  T_RESIM[15].resim_value=0;

ILI9488_Set_Rotation(0);
sayfa_no=0;
SAYFA();
HAL_Delay(2000);

ILI9488_Set_Rotation(1);
sayfa_no=0;
SAYFA();
HAL_Delay(2000);

ILI9488_Set_Rotation(2);
sayfa_no=0;
SAYFA();
HAL_Delay(2000);

ILI9488_Set_Rotation(3);
sayfa_no=0;
SAYFA();
HAL_Delay(2000);

ILI9488_Set_Rotation(1);
sayfa_no=0;
SAYFA();
HAL_Delay(2000);

sayfa_no=1;
SAYFA();
HAL_Delay(2000);
sayfa_no=0;
SAYFA();
  while (1)
  {
//	  ILI9488_Fill_Screen(WHITE);

	 if(GetTouchStatus(0) !=0){
		 TOUCH_KONTROL();
		 /*
		 sprintf(yazi,"%d %d  BULENT ASLANTURK\n",xx,yy);
		 ILI9488_LCD_Font(5,5,yazi ,(char *) Times_New_Roman20x24,WHITE, BLUE);
		 HAL_Delay(200);
		 if(sayfa_no==1) {SAYFA1();sayfa_no=2;}
		 else if(sayfa_no==2) {SAYFA2();sayfa_no=1;}
		 */
	 }
	 else{
		 if(son_basilan !=0){
			 if(T_RESIM[son_basilan-1].resim_type==0){  //eger buton tipi puspul ise tus bırakıldımı esik haline dönüyor
				 T_RESIM[son_basilan-1].resim_value=!T_RESIM[son_basilan-1].resim_value;
				 ILI9488_LCD_RESIM(son_basilan-1,(char *)T_RESIM[son_basilan-1].p_resim,T_RESIM[son_basilan-1].resim_value);
			 }
			 son_basilan=0;
			 sayac=0;
		 }


	 }
	 HAL_Delay(100);

/*
	 ILI9488_LCD_Font(0, 10, "SD KART BULUNDU DOSYALAR KAYDEDILIYOR\n",(char *)Segoe_Script21x21,0xffff, 0xf800);
	 HAL_Delay(200);
	 ILI9488_LCD_Font(0, 30, "BULENT ASLANTURK...\n", (char *)Times_New_Roman19x23,GREEN, BLUE);
	 HAL_Delay(200);
	 ILI9488_LCD_RESIM(180,160,(char *)gImage_resim1);
	 HAL_Delay(200);
	 uint8_t i;
	 for (i = 0; i < 100; ++i) {
		 char yazi[4];
		 sprintf(yazi,"%d\n",i);
		 ILI9488_LCD_Font(50,150,yazi ,(char *) Segoe_Script21x21,GREEN, BLUE);
		HAL_Delay(200);
	}
	 ILI9488_Fill_Screen(GREEN);
*/
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_1LINE;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_DC_Pin|LCD_RST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TOUCH_CS_GPIO_Port, TOUCH_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LCD_CS_Pin */
  GPIO_InitStruct.Pin = LCD_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LCD_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_DC_Pin LCD_RST_Pin */
  GPIO_InitStruct.Pin = LCD_DC_Pin|LCD_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : TOUCH_CS_Pin */
  GPIO_InitStruct.Pin = TOUCH_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TOUCH_CS_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void TOUCH_KONTROL(){
	uint8_t ts=sayfa_no*sayfa_touch_adeti;
	uint8_t i;
	for (i = ts; i < ts+sayfa_touch_adeti; i++) {
		if(xx > T_RESIM[i].resim_korx && yy > T_RESIM[i].resim_kory && xx < T_RESIM[i].resim_korx+T_RESIM[i].resim_w && yy < T_RESIM[i].resim_kory+T_RESIM[i].resim_h){
			sprintf(yazi,"sayfa no=%d resim no=%d type=%d value=%d sayac=%d \n",sayfa_no,i,T_RESIM[i].resim_type,T_RESIM[i].resim_value,sayac);
			ILI9488_LCD_Font(5,5,yazi ,(char *) Times_New_Roman20x24,WHITE, BLUE);
	//		HAL_Delay(500);
			//********************
			if(son_basilan==0){
				T_RESIM[i].resim_value=!T_RESIM[i].resim_value; //resmin tersi gösteriliyor
			    ILI9488_LCD_RESIM(i,(char *)T_RESIM[i].p_resim,T_RESIM[i].resim_value);
			}
			sayac++;
			son_basilan=i+1;
			switch (i) {
				case 0:

					break;
				case 1:

				   break;
				case 2:

					break;
				case 3:

				   break;
				case 7: //sayfa 0 geri komutu
					sayfa_no=1;
					SAYFA();
					break;
				//ikinci sayfa komutları
				case 8:

				   break;
				case 9:

					break;
				case 10:

				   break;
				case 11:

					break;
				case 15:  //sayfa 1 geri komutu
					sayfa_no=0;
					SAYFA();
				   break;
				default:
					break;
			}

		}
	}

}
void SAYFA(){
	ILI9488_Fill_Screen(WHITE);
	uint8_t ts=sayfa_no*sayfa_touch_adeti;
	uint8_t i;
	for (i = ts; i < ts+sayfa_touch_adeti; i++) {
		if((char *)T_RESIM[i].p_resim !=0){ //resim boş degilse
			ILI9488_LCD_RESIM(i,(char *)T_RESIM[i].p_resim,T_RESIM[i].resim_value);
		}
		sprintf(yazi,"SAYFA NO=%d \n",sayfa_no);
		ILI9488_LCD_Font(180,40,yazi ,(char *) Helvetica21x21,WHITE, GREEN);
		sprintf(yazi,"BULENT ASLANTURK\n");
		ILI9488_LCD_Font(140,290,yazi ,(char *) Helvetica21x21,WHITE, RED);
	}
//	 ILI9488_LCD_RESIM(0,(char *)gImage_buton,0);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
