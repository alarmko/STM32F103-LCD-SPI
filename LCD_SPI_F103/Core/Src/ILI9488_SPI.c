/**
  * @brief  ILI9488 Registers
  */

/* Level 1 Commands */
#define LCD_SWRESET             0x01   /* Software Reset */
#define LCD_READ_DISPLAY_ID     0x04   /* Read display identification information */
#define LCD_RDDST               0x09   /* Read Display Status */
#define LCD_RDDPM               0x0A   /* Read Display Power Mode */
#define LCD_RDDMADCTL           0x0B   /* Read Display MADCTL */
#define LCD_RDDCOLMOD           0x0C   /* Read Display Pixel Format */
#define LCD_RDDIM               0x0D   /* Read Display Image Format */
#define LCD_RDDSM               0x0E   /* Read Display Signal Mode */
#define LCD_RDDSDR              0x0F   /* Read Display Self-Diagnostic Result */
#define LCD_SPLIN               0x10   /* Enter Sleep Mode */
#define LCD_SLEEP_OUT           0x11   /* Sleep out register */
#define LCD_PTLON               0x12   /* Partial Mode ON */
#define LCD_NORMAL_MODE_ON      0x13   /* Normal Display Mode ON */
#define LCD_DINVOFF             0x20   /* Display Inversion OFF */
#define LCD_DINVON              0x21   /* Display Inversion ON */
#define LCD_GAMMA               0x26   /* Gamma register */
#define LCD_DISPLAY_OFF         0x28   /* Display off register */
#define LCD_DISPLAY_ON          0x29   /* Display on register */
#define LCD_COLUMN_ADDR         0x2A   /* Colomn address register */
#define LCD_PAGE_ADDR           0x2B   /* Page address register */
#define LCD_GRAM                0x2C   /* GRAM register */
#define LCD_RGBSET              0x2D   /* Color SET */
#define LCD_RAMRD               0x2E   /* Memory Read */
#define LCD_PLTAR               0x30   /* Partial Area */
#define LCD_VSCRDEF             0x33   /* Vertical Scrolling Definition */
#define LCD_TEOFF               0x34   /* Tearing Effect Line OFF */
#define LCD_TEON                0x35   /* Tearing Effect Line ON */
#define LCD_MAC                 0x36   /* Memory Access Control register*/
#define LCD_VSCRSADD            0x37   /* Vertical Scrolling Start Address */
#define LCD_IDMOFF              0x38   /* Idle Mode OFF */
#define LCD_IDMON               0x39   /* Idle Mode ON */
#define LCD_PIXEL_FORMAT        0x3A   /* Pixel Format register */
#define LCD_WRITE_MEM_CONTINUE  0x3C   /* Write Memory Continue */
#define LCD_READ_MEM_CONTINUE   0x3E   /* Read Memory Continue */
#define LCD_SET_TEAR_SCANLINE   0x44   /* Set Tear Scanline */
#define LCD_GET_SCANLINE        0x45   /* Get Scanline */
#define LCD_WDB                 0x51   /* Write Brightness Display register */
#define LCD_RDDISBV             0x52   /* Read Display Brightness */
#define LCD_WCD                 0x53   /* Write Control Display register*/
#define LCD_RDCTRLD             0x54   /* Read CTRL Display */
#define LCD_WRCABC              0x55   /* Write Content Adaptive Brightness Control */
#define LCD_RDCABC              0x56   /* Read Content Adaptive Brightness Control */
#define LCD_WRITE_CABC          0x5E   /* Write CABC Minimum Brightness */
#define LCD_READ_CABC           0x5F   /* Read CABC Minimum Brightness */
#define LCD_READ_ID1            0xDA   /* Read ID1 */
#define LCD_READ_ID2            0xDB   /* Read ID2 */
#define LCD_READ_ID3            0xDC   /* Read ID3 */

/* Level 2 Commands */
#define LCD_RGB_INTERFACE       0xB0   /* RGB Interface Signal Control */
#define LCD_FRMCTR1             0xB1   /* Frame Rate Control (In Normal Mode) */
#define LCD_FRMCTR2             0xB2   /* Frame Rate Control (In Idle Mode) */
#define LCD_FRMCTR3             0xB3   /* Frame Rate Control (In Partial Mode) */
#define LCD_INVTR               0xB4   /* Display Inversion Control */
#define LCD_BPC                 0xB5   /* Blanking Porch Control register */
#define LCD_DFC                 0xB6   /* Display Function Control register */
#define LCD_ETMOD               0xB7   /* Entry Mode Set */
#define LCD_BACKLIGHT1          0xB8   /* Backlight Control 1 */
#define LCD_BACKLIGHT2          0xB9   /* Backlight Control 2 */
#define LCD_BACKLIGHT3          0xBA   /* Backlight Control 3 */
#define LCD_BACKLIGHT4          0xBB   /* Backlight Control 4 */
#define LCD_BACKLIGHT5          0xBC   /* Backlight Control 5 */
#define LCD_BACKLIGHT7          0xBE   /* Backlight Control 7 */
#define LCD_BACKLIGHT8          0xBF   /* Backlight Control 8 */
#define LCD_POWER1              0xC0   /* Power Control 1 register */
#define LCD_POWER2              0xC1   /* Power Control 2 register */
#define LCD_VCOM1               0xC5   /* VCOM Control 1 register */
#define LCD_VCOM2               0xC7   /* VCOM Control 2 register */
#define LCD_NVMWR               0xD0   /* NV Memory Write */
#define LCD_NVMPKEY             0xD1   /* NV Memory Protection Key */
#define LCD_RDNVM               0xD2   /* NV Memory Status Read */
#define LCD_READ_ID4            0xD3   /* Read ID4 */
#define LCD_PGAMMA              0xE0   /* Positive Gamma Correction register */
#define LCD_NGAMMA              0xE1   /* Negative Gamma Correction register */
#define LCD_DGAMCTRL1           0xE2   /* Digital Gamma Control 1 */
#define LCD_DGAMCTRL2           0xE3   /* Digital Gamma Control 2 */
#define LCD_INTERFACE           0xF6   /* Interface control register */

/* Extend register commands */
#define LCD_POWERA               0xCB   /* Power control A register */
#define LCD_POWERB               0xCF   /* Power control B register */
#define LCD_DTCA                 0xE8   /* Driver timing control A */
#define LCD_DTCB                 0xEA   /* Driver timing control B */
#define LCD_POWER_SEQ            0xED   /* Power on sequence register */
#define LCD_3GAMMA_EN            0xF2   /* 3 Gamma enable register */
#define LCD_PRC                  0xF7   /* Pump ratio control register */


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ILI9488_SPI.h"
#include "string.h"

extern SPI_HandleTypeDef hspi1;
#define HSPI_INSTANCE	&hspi1
#define ABS(x)   ((x) > 0 ? (x) : -(x))


/* Global Variables ------------------------------------------------------------------*/
volatile uint16_t LCD_HEIGHT = ILI9488_SCREEN_HEIGHT;
volatile uint16_t LCD_WIDTH	 = ILI9488_SCREEN_WIDTH;
uint16_t POINT_COLOR = 0x0000, BACK_COLOR = 0xFFFF;
static uint8_t Direction;

typedef struct {
	char     *p_resim; //resmin adresi
	uint16_t resim_korx;
	uint16_t resim_kory;
	uint16_t resim_w;
	uint16_t resim_h;
	uint8_t  resim_type;//0 PUSH,1 TOGLE
	uint8_t  resim_value;
}RESIM;

extern RESIM T_RESIM[];

uint8_t ILI9488_GetDirection(void)
{
	return Direction;
}

/*Send data (char) to LCD*/
void ILI9488_SPI_Send(unsigned char SPI_Data)
{
	HAL_SPI_Transmit(HSPI_INSTANCE, &SPI_Data, 1, 1);
}

/* Send command (char) to LCD */
void ILI9488_Write_Command(uint8_t Command)
{
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
	ILI9488_SPI_Send(Command);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

/* Send Data (char) to LCD */
void ILI9488_Write_Data(uint8_t Data)
{
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	ILI9488_SPI_Send(Data);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

/* Set Address - Location block - to draw into */
void ILI9488_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2)
{
	ILI9488_Write_Command(0x2A);
	ILI9488_Write_Data(X1 >> 8);
	ILI9488_Write_Data(X1);
	ILI9488_Write_Data(X2 >> 8);
	ILI9488_Write_Data(X2);

	ILI9488_Write_Command(0x2B);
	ILI9488_Write_Data(Y1 >> 8);
	ILI9488_Write_Data(Y1);
	ILI9488_Write_Data(Y2 >> 8);
	ILI9488_Write_Data(Y2);

	ILI9488_Write_Command(0x2C);
}

/*HARDWARE RESET*/
void ILI9488_Reset(void)
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
}

/*Ser rotation of the screen - changes x0 and y0*/
void ILI9488_Set_Rotation(uint8_t Rotation)
{
	Direction = Rotation;

	ILI9488_Write_Command(0x36);
	HAL_Delay(1);

	switch(Direction)
	{
		case SCREEN_VERTICAL_1:
			ILI9488_Write_Data((1<<3));
			LCD_WIDTH = 320;
			LCD_HEIGHT = 480;
			break;
		case SCREEN_HORIZONTAL_1:
			ILI9488_Write_Data((1<<6)|(1<<5)|(1<<4)|(1<<3));
			LCD_WIDTH  = 480;
			LCD_HEIGHT = 320;
			break;
		case SCREEN_VERTICAL_2:
			ILI9488_Write_Data((1<<7)|(1<<6)|(1<<3));
			LCD_WIDTH  = 320;
			LCD_HEIGHT = 480;
			break;
		case SCREEN_HORIZONTAL_2:
			ILI9488_Write_Data((1<<7)|(1<<5)|(1<<3));
			LCD_WIDTH  = 480;
			LCD_HEIGHT = 320;
			break;
		default:
			//EXIT IF SCREEN ROTATION NOT VALID!
			break;
	}
}

void ILI9488_Init(void)
{
	ILI9488_Reset();

	//SOFTWARE RESET
	ILI9488_Write_Command(0x01);
	HAL_Delay(100);

	ILI9488_Write_Command(0xF7);
	ILI9488_Write_Data(0xA9);
	ILI9488_Write_Data(0x51);
	ILI9488_Write_Data(0x2C);
	ILI9488_Write_Data(0x82);

	ILI9488_Write_Command(0xC0);
	ILI9488_Write_Data(0x11);
	ILI9488_Write_Data(0x09);

	ILI9488_Write_Command(0xC1);
	ILI9488_Write_Data(0x41);

	ILI9488_Write_Command(0xC5);
	ILI9488_Write_Data(0x00);
	ILI9488_Write_Data(0x0A);
	ILI9488_Write_Data(0x80);

	ILI9488_Write_Command(0xB1);
	ILI9488_Write_Data(0xB0);
	ILI9488_Write_Data(0x11);

	ILI9488_Write_Command(0xB4);
	ILI9488_Write_Data(0x02);

	ILI9488_Write_Command(0xB6);
	ILI9488_Write_Data(0x02);
	ILI9488_Write_Data(0x42);

	ILI9488_Write_Command(0xB7);
	ILI9488_Write_Data(0xC6);

	ILI9488_Write_Command(0xBE);
	ILI9488_Write_Data(0x00);
	ILI9488_Write_Data(0x04);

	ILI9488_Write_Command(0xE9);
	ILI9488_Write_Data(0x00);

	ILI9488_Write_Command(0x36);
	ILI9488_Write_Data((1<<3)|(0<<7)|(1<<6)|(1<<5));

	ILI9488_Write_Command(0x3A);
	ILI9488_Write_Data(0x66);  //24 BIT COZUNURLUK ICIN

	//POSITIVE GAMMA CORRECTION
	ILI9488_Write_Command(0xE0);
	ILI9488_Write_Data(0x00);
	ILI9488_Write_Data(0x07);
	ILI9488_Write_Data(0x0f);
	ILI9488_Write_Data(0x0D);
	ILI9488_Write_Data(0x1B);
	ILI9488_Write_Data(0x0A);
	ILI9488_Write_Data(0x3c);
	ILI9488_Write_Data(0x78);
	ILI9488_Write_Data(0x4A);
	ILI9488_Write_Data(0x07);
	ILI9488_Write_Data(0x0E);
	ILI9488_Write_Data(0x09);
	ILI9488_Write_Data(0x1B);
	ILI9488_Write_Data(0x1e);
	ILI9488_Write_Data(0x0f);

	//NEGATIVE GAMMA CORRECTION
	ILI9488_Write_Command(0xE1);
	ILI9488_Write_Data(0x00);
	ILI9488_Write_Data(0x22);
	ILI9488_Write_Data(0x24);
	ILI9488_Write_Data(0x06);
	ILI9488_Write_Data(0x12);
	ILI9488_Write_Data(0x07);
	ILI9488_Write_Data(0x36);
	ILI9488_Write_Data(0x47);
	ILI9488_Write_Data(0x47);
	ILI9488_Write_Data(0x06);
	ILI9488_Write_Data(0x0a);
	ILI9488_Write_Data(0x07);
	ILI9488_Write_Data(0x30);
	ILI9488_Write_Data(0x37);
	ILI9488_Write_Data(0x0f);

	//EXIT SLEEP
	ILI9488_Write_Command(0x11);
	HAL_Delay(120);

	//TURN ON DISPLAY
	ILI9488_Write_Command(0x29);

	//STARTING ROTATION
	ILI9488_Set_Rotation(SCREEN_HORIZONTAL_1);
	//ILI9488_Set_Rotation(SCREEN_VERTICAL_1);
}

//INTERNAL FUNCTION OF LIBRARY, USAGE NOT RECOMENDED, USE Draw_Pixel INSTEAD
/*Sends single pixel colour information to LCD*/

void ILI9488_Draw_Colour(uint16_t Colour)
{
//SENDS COLOUR
	unsigned char TempBuffer[3] = {(Colour>>8)&0xF8, (Colour>>3)&0xFC, Colour<<3};

	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(HSPI_INSTANCE, TempBuffer, 3, 1);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

//INTERNAL FUNCTION OF LIBRARY
/*Sends block colour information to LCD*/
void ILI9488_Draw_Colour_Burst_18BIT(uint16_t Colour, uint32_t Size)
{
//SENDS COLOUR
	uint32_t Buffer_Size = 0;

	if((Size * 3) < BURST_MAX_SIZE)
	{
		Buffer_Size = Size;
	}
	else
	{
		Buffer_Size = BURST_MAX_SIZE;
	}

	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

	unsigned char Byte1 = (Colour>>8)&0xF8;	//RED
	unsigned char Byte2 = (Colour>>3)&0xFC;	//GREEN
	unsigned char Byte3 = (Colour<<3);			//BLUE

	unsigned char burst_buffer[Buffer_Size];

	for(uint32_t j = 0; j < Buffer_Size; j+=3)
		{
			burst_buffer[j] = 	Byte1;
			burst_buffer[j+1] = Byte2;
			burst_buffer[j+2] = Byte3;
		}
	
	uint32_t Sending_Size = Size * 3;
	uint32_t Sending_in_Block = Sending_Size / Buffer_Size;
	uint32_t Remainder_from_block = Sending_Size % Buffer_Size;

	if(Sending_in_Block != 0)
	{
		for(uint32_t j = 0; j < (Sending_in_Block); j++)
		{
			HAL_SPI_Transmit(HSPI_INSTANCE, (unsigned char *)burst_buffer, Buffer_Size, 10);
		}
	}

	//REMAINDER!
	HAL_SPI_Transmit(HSPI_INSTANCE, (unsigned char *)burst_buffer, Remainder_from_block, 10);

	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

//FILL THE ENTIRE SCREEN WITH SELECTED COLOUR (either #define-d ones or custom 16bit)
/*Sets address (entire screen) and Sends Height*Width ammount of colour information to LCD*/
void ILI9488_Fill_Screen(uint16_t Colour)
{
	ILI9488_Set_Address(0,0,LCD_WIDTH-1,LCD_HEIGHT-1);
	ILI9488_Draw_Colour_Burst_18BIT(Colour, LCD_WIDTH * LCD_HEIGHT);
}

void ILI9488_Draw_Pixel(uint16_t X,uint16_t Y,uint16_t Colour) 
{
	if((X >=LCD_WIDTH) || (Y >=LCD_HEIGHT)) return;	//OUT OF BOUNDS!

	//ADDRESS
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	ILI9488_SPI_Send(0x2A);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);

	//XDATA
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	unsigned char Temp_Buffer[4] = {X>>8,X, (X+1)>>8, (X+1)};
	HAL_SPI_Transmit(HSPI_INSTANCE, Temp_Buffer, 4, 1);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);

	//ADDRESS
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	ILI9488_SPI_Send(0x2B);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);

	//YDATA
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	unsigned char Temp_Buffer1[4] = {Y>>8,Y, (Y+1)>>8, (Y+1)};
	HAL_SPI_Transmit(HSPI_INSTANCE, Temp_Buffer1, 4, 1);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
	
	//ADDRESS
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	ILI9488_SPI_Send(0x2C);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
	
	//COLOUR
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	unsigned char Temp_Buffer2[3] = {(Colour>>8)&0xF8, (Colour>>3)&0xFC, Colour<<3};
	HAL_SPI_Transmit(HSPI_INSTANCE, Temp_Buffer2, 3, 1);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

//DRAW RECTANGLE OF SET SIZE AND HEIGTH AT X and Y POSITION WITH CUSTOM COLOUR
//
//Rectangle is hollow. X and Y positions mark the upper left corner of rectangle
//As with all other draw calls x0 and y0 locations dependant on screen orientation
//

void ILI9488_Draw_Fill_Rectangle(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height, uint16_t Colour)
{
	if((X >= LCD_WIDTH) || (Y >= LCD_HEIGHT)) return;

	if((X + Width - 1) >= LCD_WIDTH)
	{
			Width = LCD_WIDTH - X;
	}
	if((Y + Height - 1) >= LCD_HEIGHT)
	{
			Height = LCD_HEIGHT - Y;
	}

	ILI9488_Set_Address(X, Y, X + Width - 1, Y + Height - 1);
	ILI9488_Draw_Colour_Burst_18BIT(Colour, Height * Width);
}

//DRAW LINE FROM X,Y LOCATION to X+Width,Y LOCATION
void ILI9488_Draw_Horizontal_Line(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Colour)
{
	if((X >= LCD_WIDTH) || (Y >= LCD_HEIGHT)) return;

	if((X+Width-1)>=LCD_WIDTH)
	{
			Width=LCD_WIDTH-X;
	}
	ILI9488_Set_Address(X, Y, X+Width-1, Y);
	ILI9488_Draw_Colour_Burst_18BIT(Colour, Width);
}

//DRAW LINE FROM X,Y LOCATION to X,Y+Height LOCATION
void ILI9488_Draw_Vertical_Line(uint16_t X, uint16_t Y, uint16_t Height, uint16_t Colour)
{
	if((X >= LCD_WIDTH) || (Y >= LCD_HEIGHT)) return;
	if((Y+Height-1)>=LCD_HEIGHT)
	{
			Height=LCD_HEIGHT-Y;
	}
	ILI9488_Set_Address(X, Y, X, Y+Height-1);
	ILI9488_Draw_Colour_Burst_18BIT(Colour, Height);
}

/* ==========================================================================================================================
 *
 */
void ILI9488_Draw_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
  ILI9488_Draw_line(x1,y1,x1,y2,color);
  ILI9488_Draw_line(x1,y2,x2,y2,color);
  ILI9488_Draw_line(x2,y2,x2,y1,color);
  ILI9488_Draw_line(x2,y1,x1,y1,color);
}

void ILI9488_Draw_Circle(uint16_t x, uint16_t y, uint16_t radian, uint16_t color)
{
  int a, b;
  int di;

  a = 0;
  b = radian;
  di = 3 - (radian << 1);

  while(a <= b)
  {
  	ILI9488_Draw_Pixel(x-b,y-a,color); //3
  	ILI9488_Draw_Pixel(x+b,y-a,color); //0
  	ILI9488_Draw_Pixel(x-a,y+b,color); //1
  	ILI9488_Draw_Pixel(x-b,y-a,color); //7
  	ILI9488_Draw_Pixel(x-a,y-b,color); //2
  	ILI9488_Draw_Pixel(x+b,y+a,color); //4
  	ILI9488_Draw_Pixel(x+a,y-b,color); //5
  	ILI9488_Draw_Pixel(x+a,y+b,color); //6
  	ILI9488_Draw_Pixel(x-b,y+a,color);
    a++;
    //Bresenham
    if(di<0)
    {
      di +=4*a+6;
    }
    else
    {
      di+=10+4*(a-b);
      b--;
    }
    ILI9488_Draw_Pixel(x+a,y+b,color);
  }
}


void ILI9488_LCD_Font(uint16_t x, uint16_t y, char *text, const char *p_font,
	uint32_t backcolor, uint32_t color565) {
	int16_t cursor_x = x;
	int16_t cursor_y = y;
	uint8_t karekter_start = p_font[2];
	uint8_t karekter_end = p_font[4];
	uint8_t satir_sayisi = p_font[6];
	uint16_t karekter_adresi;
	char sutun_sayisi;
	uint16_t i,ii;


uint32_t Data;

	for (uint16_t text_pos = 0; text_pos < strlen(text); text_pos++) {
		char c = text[text_pos];
		if (c == '\n') {
			cursor_x = x;
		} else if (c >= karekter_start && c <= karekter_end && c != '\n') {
			sutun_sayisi = p_font[(c - karekter_start) * 4 + 8];
			ILI9488_Set_Address(cursor_x, cursor_y, cursor_x + sutun_sayisi-1,cursor_y + satir_sayisi);
			karekter_adresi = p_font[(c - karekter_start) * 4 + 9]+ p_font[(c - karekter_start) * 4 + 10] * 256;
			for (i = 0; i < satir_sayisi; i++) {
				Data = p_font[karekter_adresi+3] << 24 | p_font[karekter_adresi+2] << 16 |p_font[karekter_adresi+1] << 8 | p_font[karekter_adresi];

				if((sutun_sayisi%8) == 0){
					karekter_adresi +=sutun_sayisi/8;
				}else{
					karekter_adresi +=sutun_sayisi/8 +1;
				}

				for (ii = 0; ii < sutun_sayisi; ii++) {
					if (Data & 0x000001)
						ILI9488_Draw_Colour(color565);
					else //karekterin background resmi basiliyor
					{

						ILI9488_Draw_Colour(backcolor);
					}

					Data = Data >> 1;

				}
			}

			cursor_x += sutun_sayisi;
		}
	}
}
//void ILI9488_LCD_RESIM(uint16_t x, uint16_t y,char *p_font,char renk){
void ILI9488_LCD_RESIM(uint8_t kor_secim,char *p_resimadi,char renk){
	uint16_t Colour;
	uint32_t Top_Adet;
	uint8_t w=(p_resimadi[2]*256+p_resimadi[3]);
	uint8_t h = (p_resimadi[4]*256+p_resimadi[5]);
    uint16_t x=T_RESIM[kor_secim].resim_korx;
    uint16_t y=T_RESIM[kor_secim].resim_kory;
    T_RESIM[kor_secim].resim_w=w;
    T_RESIM[kor_secim].resim_h=h;
	ILI9488_Set_Address(x,y,(x+w-1),(y+h-1));

	Top_Adet=w*h*2;
	unsigned char burst_buffer[BURST_MAX_SIZE];


	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

	uint16_t adet=0;

	char temp;

	for(uint32_t j = 0; j < Top_Adet; j+=2)
		{
		    Colour=p_resimadi[j+8];
			Colour=Colour << 8 | p_resimadi[j+9];

			burst_buffer[adet] = (Colour>>8) & 0xF8;	//RED

			adet++;
			burst_buffer[adet] = (Colour>>3) & 0xFC;   //GREEN


			adet++;
			burst_buffer[adet] = (Colour<<3);		   //BLUE


			if(renk >0){ //tusa basıldımı yesille kırmızı yer degiştiriyor
			temp=burst_buffer[adet-1];
			burst_buffer[adet-1]=burst_buffer[adet-2];
			burst_buffer[adet-2]=temp;
			}
			adet++;
			if(adet >= BURST_MAX_SIZE-1){
				HAL_SPI_Transmit(HSPI_INSTANCE,burst_buffer, BURST_MAX_SIZE, 10000);
				adet=0;
			}

		}
	HAL_SPI_Transmit(HSPI_INSTANCE, (unsigned char *)burst_buffer, adet, 1000);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);


}
