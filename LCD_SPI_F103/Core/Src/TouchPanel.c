/* Includes ------------------------------------------------------------------*/
#include "TouchPanel.h"
#include "ILI9488_SPI.h"



/* Private variables ---------------------------------------------------------*/

Matrix 		matrix ;
Point  display;


Point ScreenSample[3];

Point DisplaySample[3] = {
                                 	{  30,  45 },
                                 	{ 380,  45 },
                                 	{ 200, 210 }
	                          };

/* Private define ------------------------------------------------------------*/
extern SPI_HandleTypeDef hspi2;
#define THRESHOLD 		2
#define TP_hspi 		hspi2

volatile int MIN_X=180;
volatile int MAX_X=3860;
volatile int MIN_Y=190;
volatile int MAX_Y=3850;

/*******************************************************************************
* Function Name  : TP_Init
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void TP_Init(void)
{
}

/*******************************************************************************
* Function Name  : DelayUS
* Description    :
* Input          : - cnt:
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void DelayUS(uint32_t cnt)
{
	volatile uint32_t i;
	i = cnt * 10;
	while(i--);
}


/*******************************************************************************
* Function Name  : WR_CMD
* Description    :
* Input          : - cmd:
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void WR_CMD (uint8_t cmd)
{
	HAL_SPI_Transmit(&TP_hspi, &cmd, 1, 1000);
}


/*******************************************************************************
* Function Name  : RD_AD
* Description    :
* Input          : None
* Output         : None
* Return         :
* Attention		 : None
*******************************************************************************/
static uint16_t RD_AD(void)
{
	uint8_t buf[2] = {0, 0 };
	int value;

	HAL_SPI_Receive(&TP_hspi, buf, 2, 1000);
	value = (((uint16_t)buf[0] * 256 +  buf[1]) >> 3) & 0x0FFF;

	return value;
}


/*******************************************************************************
* Function Name  : Read_X
* Description    : Read ADS7843 ADC X
* Input          : None
* Output         : None
* Return         :
* Attention		 : None
*******************************************************************************/
uint16_t Read_X(void)
{
  uint16_t i;

  TP_CS(0);
  DelayUS(1);
  WR_CMD(CHX);
  DelayUS(1);
  i = RD_AD();
  TP_CS(1);

  return i;
}

/*******************************************************************************
* Function Name  : Read_Y
* Description    : Read ADS7843 ADC Y
* Input          : None
* Output         : None
* Return         :
* Attention		 : None
*******************************************************************************/
uint16_t Read_Y(void)
{
	uint16_t i;

  TP_CS(0);
  DelayUS(1);
  WR_CMD(CHY);
  DelayUS(1);
  i = RD_AD();
  TP_CS(1);

  return i;
}


/*******************************************************************************
* Function Name  : TP_GetXY
* Description    : Read ADS7843
* Input          : None
* Output         : None
* Return         :
* Attention		 : None
*******************************************************************************/
void TP_GetXY(uint16_t *x, uint16_t *y)
{
	uint16_t tpx, tpy;

  tpx = Read_X();
  DelayUS(1);
  tpy = Read_Y();
  *x = tpx;
  *y = tpy;
}

/*******************************************************************************
* Function Name  : Read_XPT2046
* Description    : Get TouchPanel X Y
* Input          : None
* Output         : None
* Return         : Point *
* Attention		 : None
*******************************************************************************/
Point *Read_XPT2046(void)
{
  static Point screen;
  uint16_t m0, m1, m2, TP_X[1], TP_Y[1], temp[3];
  uint8_t count = 0;
  int buffer[2][9] = {{0}, {0}};

  do
  {
    TP_GetXY(TP_X, TP_Y);
    buffer[0][count] = TP_X[0];
    buffer[1][count] = TP_Y[0];
    count++;
  }
  while((GPIO_PIN_RESET == TP_INT_IN()) && (count < 9));  /* TP_INT_IN()  */

	if(count == 9)   /* Average X Y  */
  {
		/* Average X  */
		temp[0] = (buffer[0][0] + buffer[0][1] + buffer[0][2]) / 3;
		temp[1] = (buffer[0][3] + buffer[0][4] + buffer[0][5]) / 3;
		temp[2] = (buffer[0][6] + buffer[0][7] + buffer[0][8]) / 3;

		m0=temp[0] - temp[1];
		m1=temp[1] - temp[2];
		m2=temp[2] - temp[0];

		m0 = m0 > 0 ? m0 : (-m0);
		m1 = m1 > 0 ? m1 : (-m1);
		m2 = m2 > 0 ? m2 : (-m2);

		if( m0 > THRESHOLD  &&  m1 > THRESHOLD  &&  m2 > THRESHOLD ) return 0;

		if(m0 < m1)
		{
			if(m2 < m0)
				screen.x = (temp[0] + temp[2]) / 2;
			else
				screen.x = (temp[0] + temp[1]) / 2;
		}
		else if(m2 < m1)
			screen.x = (temp[0] + temp[2]) / 2;
		else
			screen.x = (temp[1] + temp[2]) / 2;

		/* Average Y  */
		temp[0] = (buffer[1][0] + buffer[1][1] + buffer[1][2]) / 3;
		temp[1] = (buffer[1][3] + buffer[1][4] + buffer[1][5]) / 3;
		temp[2] = (buffer[1][6] + buffer[1][7] + buffer[1][8]) / 3;
		m0 = temp[0] - temp[1];
		m1 = temp[1] - temp[2];
		m2 = temp[2] - temp[0];
		m0 = m0 > 0 ? m0 : (-m0);
		m1 = m1 > 0 ? m1 : (-m1);
		m2 = m2 > 0 ? m2 : (-m2);
		if((m0 > THRESHOLD) && (m1 > THRESHOLD) && (m2>THRESHOLD)) return 0;

		if(m0 < m1)
		{
			if(m2 < m0)
				screen.y = (temp[0] + temp[2]) / 2;
			else
				screen.y = (temp[0] + temp[1]) / 2;
			}
		else if(m2 < m1)
			 screen.y = (temp[0] + temp[2]) / 2;
		else
			 screen.y = (temp[1] + temp[2]) / 2;

		return &screen;
  }

  return 0;
}

void Touch_Calibre(){
	uint16_t x, y,x1,x2,x3,x4,y1,y2,y3,y4;

ILI9488_Draw_Circle(10, 10, 5, RED);
x=0;y=0;
while((x > MAX_X) || (x < MIN_X) || (y > MAX_Y) || (y < MIN_Y)){
	TP_GetXY(&x, &y);
}
x1=x;
y1=y;
ILI9488_Draw_Circle(10, 10, 5, WHITE);
HAL_Delay(3000);
//**********
ILI9488_Draw_Circle(470, 10, 5, RED);
x=0;y=0;
while((x > MAX_X) || (x < MIN_X) || (y > MAX_Y) || (y < MIN_Y)){
	TP_GetXY(&x, &y);
}
x2=x;
y2=y;
ILI9488_Draw_Circle(470, 10, 5, WHITE);
HAL_Delay(3000);
//***********
ILI9488_Draw_Circle(10, 310, 5, RED);
x=0;y=0;
while((x > MAX_X) || (x < MIN_X) || (y > MAX_Y) || (y < MIN_Y)){
	TP_GetXY(&x, &y);
}
x3=x;
y3=y;
ILI9488_Draw_Circle(10, 310, 5, WHITE);
HAL_Delay(3000);
//***********
ILI9488_Draw_Circle(470, 310, 5, RED);
x=0;y=0;
while((x > MAX_X) || (x < MIN_X) || (y > MAX_Y) || (y < MIN_Y)){
	TP_GetXY(&x, &y);
}
x4=x;
y4=y;
ILI9488_Draw_Circle(470, 310, 5, WHITE);
HAL_Delay(3000);

MIN_X=(x1+x3)/2 - ((x1+x3)/20);
MAX_X=(x2+x4)/2 + ((x2+x4)/100);
MIN_Y=(y1+y2)/2 - ((y1+y2)/20);
MAX_Y=(y3+y4)/2 + ((y3+y4)/100);
}
int GetTouchStatus(Point * pos)
{
	uint16_t x, y, tmpx, tmpy;

//	if(GPIO_PIN_SET == TP_INT_IN()) return 0;

	TP_GetXY(&x, &y);

	if((x > MAX_X) || (x < MIN_X)) return 0;
	if((y > MAX_Y) || (y < MIN_Y)) return 0;

//	pos->x = (x - 180) / ((3860 - 190) / 480);
//	pos->y = (y - 190) / ((3850 - 190) / 480);
	tmpx = (x - MIN_X) * 480 / (MAX_X - MIN_X);
	tmpy = (y - MIN_Y) * 320 / (MAX_Y - MIN_Y);



	switch(ILI9488_GetDirection())
	{
		case 0:
			pos->x = tmpy;
			pos->y = tmpx;
			break;

		case 1:
			pos->x = tmpx;
			pos->y = 319 - tmpy;
			break;

		case 2:
			pos->x = 319 - tmpy;
			pos->y = 479 - tmpx;
			break;

		case 3:
			pos->x = 479 - tmpx;
			pos->y = tmpy;
			break;
	}

	xx=tmpx;
	yy=tmpy;
	return 1;
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
