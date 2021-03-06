#include "as32m0_ssd1306.h"

static uint8_t ssd1306_buffer[SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x80, 0x80, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80,
0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0xFF
#if (SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH > 96*16)
,
0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00,
0x80, 0xFF, 0xFF, 0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x8C, 0x8E, 0x84, 0x00, 0x00, 0x80, 0xF8,
0xF8, 0xF8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x80,
0x00, 0xE0, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xC7, 0x01, 0x01,
0x01, 0x01, 0x83, 0xFF, 0xFF, 0x00, 0x00, 0x7C, 0xFE, 0xC7, 0x01, 0x01, 0x01, 0x01, 0x83, 0xFF,
0xFF, 0xFF, 0x00, 0x38, 0xFE, 0xC7, 0x83, 0x01, 0x01, 0x01, 0x83, 0xC7, 0xFF, 0xFF, 0x00, 0x00,
0x01, 0xFF, 0xFF, 0x01, 0x01, 0x00, 0xFF, 0xFF, 0x07, 0x01, 0x01, 0x01, 0x00, 0x00, 0x7F, 0xFF,
0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0xFF,
0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x03, 0x0F, 0x3F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xC7, 0xC7, 0x8F,
0x8F, 0x9F, 0xBF, 0xFF, 0xFF, 0xC3, 0xC0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xFC,
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF8, 0xF0, 0xF0, 0xE0, 0xC0, 0x00, 0x01, 0x03, 0x03, 0x03,
0x03, 0x03, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01,
0x03, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x00, 0x00,
0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0x01, 0x00, 0x00, 0x00, 0x03,
0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#if (SSD1306_LCDHEIGHT == 64)
,
0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x1F, 0x0F,
0x87, 0xC7, 0xF7, 0xFF, 0xFF, 0x1F, 0x1F, 0x3D, 0xFC, 0xF8, 0xF8, 0xF8, 0xF8, 0x7C, 0x7D, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x0F, 0x07, 0x00, 0x30, 0x30, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xC0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xC0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x1F,
0x0F, 0x07, 0x1F, 0x7F, 0xFF, 0xFF, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF8, 0xE0,
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00,
0x00, 0xFC, 0xFE, 0xFC, 0x0C, 0x06, 0x06, 0x0E, 0xFC, 0xF8, 0x00, 0x00, 0xF0, 0xF8, 0x1C, 0x0E,
0x06, 0x06, 0x06, 0x0C, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xFC,
0xFE, 0xFC, 0x00, 0x18, 0x3C, 0x7E, 0x66, 0xE6, 0xCE, 0x84, 0x00, 0x00, 0x06, 0xFF, 0xFF, 0x06,
0x06, 0xFC, 0xFE, 0xFC, 0x0C, 0x06, 0x06, 0x06, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00, 0xC0, 0xF8,
0xFC, 0x4E, 0x46, 0x46, 0x46, 0x4E, 0x7C, 0x78, 0x40, 0x18, 0x3C, 0x76, 0xE6, 0xCE, 0xCC, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F, 0x03,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00,
0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x03, 0x07, 0x0E, 0x0C,
0x18, 0x18, 0x0C, 0x06, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x01, 0x0F, 0x0E, 0x0C, 0x18, 0x0C, 0x0F,
0x07, 0x01, 0x00, 0x04, 0x0E, 0x0C, 0x18, 0x0C, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00,
0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x07,
0x07, 0x0C, 0x0C, 0x18, 0x1C, 0x0C, 0x06, 0x06, 0x00, 0x04, 0x0E, 0x0C, 0x18, 0x0C, 0x0F, 0x07,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#endif
#endif
};

void init_I2C_SSD1306(uint8_t taddr, uint8_t Speed, I2C_LOC i2c_loc){
	PIN_INFO pin_info;
	switch (i2c_loc){
		case (I2C_PB45):
			pin_info.pin_func = GIO_FUNC1;
			pin_info.pin_stat = GIO_PU;
			PinCtrl_GIOSet(PIN_CTL_GPIOB, GPIO_Pin_4|GPIO_Pin_5, &pin_info);	
			break;
		case (I2C_PC01):
			pin_info.pin_func = GIO_FUNC3;
			pin_info.pin_stat = GIO_PU;
			PinCtrl_GIOSet(PIN_CTL_GPIOC, GPIO_Pin_0|GPIO_Pin_1, &pin_info);	
			break;		
		case (I2C_PC67):
			pin_info.pin_func = GIO_FUNC1;
			pin_info.pin_stat = GIO_PU;
			PinCtrl_GIOSet(PIN_CTL_GPIOC, GPIO_Pin_6|GPIO_Pin_7, &pin_info);	
			break;
		case (I2C_PD23):
			pin_info.pin_func = GIO_FUNC3;
			pin_info.pin_stat = GIO_PU;
			PinCtrl_GIOSet(PIN_CTL_GPIOD, GPIO_Pin_2|GPIO_Pin_3, &pin_info);	
			break;		
	}
	I2C_MasterConfig(APB_I2C,taddr,1,Speed,1,8,8,0); // Slave address : 0x3D-128x64 pixels
}

void I2C_SSD1306_command(uint8_t command){
	uint8_t data[2];
	data[0] = 0x00;
	data[1] = command;
	I2CWirteBytes(APB_I2C, data, 2);
}

void I2C_SSD1306_data(uint8_t value){
	uint8_t data[2];
	data[0] = 0x40;
	data[1] = value;
	I2CWirteBytes(APB_I2C, data, 2);
}

void I2C_SSD1306_display_on(void){
	I2C_SSD1306_command(SSD1306_DISPLAYON);
}
void I2C_SSD1306_display_off(void){
	I2C_SSD1306_command(SSD1306_DISPLAYOFF);
}

void I2C_SSD1306_chargepump_on(void){
	I2C_SSD1306_command(SSD1306_CHARGEPUMP);
	I2C_SSD1306_command(0x14);
}

void I2C_SSD1306_chargepump_off(void){
	I2C_SSD1306_command(SSD1306_CHARGEPUMP);
	I2C_SSD1306_command(0x10);
}

void I2C_SSD1306_set_precharge_period(uint8_t value){
	I2C_SSD1306_command(SSD1306_SETPRECHARGE);
	I2C_SSD1306_command(value);	
}

void I2C_SSD1306_set_contrast(uint8_t value){
	I2C_SSD1306_command(SSD1306_SETCONTRAST);
	I2C_SSD1306_command(value);		
}

void I2C_SSD1306_setAddrmode(uint8_t value){
	I2C_SSD1306_command(SSD1306_MEMORYMODE);
	I2C_SSD1306_command(value & 0x03);			
}

void I2C_SSD1306_setPageaddr(uint8_t start, uint8_t end){
	I2C_SSD1306_command(SSD1306_PAGEADDR);
	I2C_SSD1306_command(start & 0x07);			
	I2C_SSD1306_command(end & 0x07);	
}

void I2C_SSD1306_setColaddr(uint8_t start, uint8_t end){
	I2C_SSD1306_command(SSD1306_COLUMNADDR);
	I2C_SSD1306_command(start & 0x7F);			
	I2C_SSD1306_command(end & 0x7F);	
}

void I2C_SSD1306_display_clear(void){
	uint8_t i, j;
	I2C_SSD1306_setPageaddr(0, 7);
	I2C_SSD1306_setColaddr(0, 127);
	for(i=0;i<8;i++)
		for(j=0;j<128;j++)
			I2C_SSD1306_data(0x00);
	//I2C_SSD1306_setPageaddr(0, 7);
	//I2C_SSD1306_setColaddr(0, 127);
}

void I2C_SSD1306_display_rotate(uint8_t r){
	if(r == 0){
		I2C_SSD1306_command(SSD1306_SEGREMAP);
		I2C_SSD1306_command(SSD1306_COMSCANINC);
	} else {
		I2C_SSD1306_command(SSD1306_SEGREMAP_INV);
		I2C_SSD1306_command(SSD1306_COMSCANDEC);
	}
}

void I2C_SSD1306_initOLED(void){
	I2C_SSD1306_display_off();
	I2C_SSD1306_chargepump_on();
	I2C_SSD1306_set_precharge_period(0x22);
	I2C_SSD1306_set_contrast(180);
	I2C_SSD1306_display_rotate(1);
	I2C_SSD1306_setAddrmode(0x00);
	I2C_SSD1306_display_clear();
	__NOP;
	I2C_SSD1306_display_on();
}

void I2C_SSD1306_drawBitMap(uint8_t Bitmap []){
	uint8_t i, j;
	I2C_SSD1306_display_off();
	I2C_SSD1306_setPageaddr(0, 7);
	for(i=0;i<8;i++)
		for(j=0;j<128;j++)
			I2C_SSD1306_data(Bitmap[j+128*(i)]);
	I2C_SSD1306_setPageaddr(0, 7);
	I2C_SSD1306_display_on();
}

void I2C_SSD1306_drawBuffer(void){
	uint8_t i, j;
	uint8_t height = SSD1306_LCDHEIGHT/8;
	I2C_SSD1306_display_off();
	I2C_SSD1306_setPageaddr(0, 7);
	for(i=0;i<height;i++)
		for(j=0;j<SSD1306_LCDWIDTH;j++)
			I2C_SSD1306_data(ssd1306_buffer[j+SSD1306_LCDWIDTH*(i)]);
	I2C_SSD1306_setPageaddr(0, 7);
	I2C_SSD1306_display_on();
}

void I2C_SSD1306_LeftHScrol(uint8_t start_page, uint8_t frame, uint8_t end_page){
	I2C_SSD1306_command(SSD1306_LEFT_HORIZONTAL_SCROLL);
	I2C_SSD1306_command(0x00);
	I2C_SSD1306_command(start_page & 0x7);
	I2C_SSD1306_command(frame & 0x7);
	I2C_SSD1306_command(end_page & 0x7);
	I2C_SSD1306_command(0x00);
	I2C_SSD1306_command(0xFF);
	I2C_SSD1306_command(SSD1306_ACTIVATE_SCROLL);
}

void I2C_SSD1306_RightHScrol(uint8_t start_page, uint8_t frame, uint8_t end_page){
	I2C_SSD1306_command(SSD1306_RIGHT_HORIZONTAL_SCROLL);
	I2C_SSD1306_command(0x00);
	I2C_SSD1306_command(start_page & 0x7);
	I2C_SSD1306_command(frame & 0x7);
	I2C_SSD1306_command(end_page & 0x7);
	I2C_SSD1306_command(0x00);
	I2C_SSD1306_command(0xFF);
	I2C_SSD1306_command(SSD1306_ACTIVATE_SCROLL);
}

void I2C_SSD1306_StopScrol(void){
	I2C_SSD1306_command(SSD1306_DEACTIVATE_SCROLL);
}

/**
on = 1 : Enable Inverse Display
on = 0 : Disable Inverse Display
**/

void I2C_SSD1306_InverseDisplay(uint8_t on){
	if(on == 1)
		I2C_SSD1306_command(SSD1306_INVERTDISPLAY);
	else
		I2C_SSD1306_command(SSD1306_NORMALDISPLAY);
}
