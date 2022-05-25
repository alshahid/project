#include"lcd.h"

void LCD_init(){
	LCD_CTRL_PORT_DIR|=(1<<RS) | (1<<RW ) | (1<<E);
#if(LCD_BIT_MODE==8)
	LCD_DATA_PORT_DIR=0xFF;
	LCD_sendCommand(TWO_LINES_LCD_EIGHT_BIT_MODE);
#elif(LCD_BIT_MODE==4)
#ifdef UPPER_PORT_PIN
	LCD_DATA_PORT_DIR|=0xF0;
#else
	LCD_DATA_PORT_DIR|=0x0F;
#endif
	LCD_sendCommand(RETURN_HOME);/*LAZM tktb al2mr da alawl som tktb TWO_LINE b3doh*/
	LCD_sendCommand(TWO_LINES_LCD_FOUR_BIT_MODE);
#endif
	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_SCREEN);
}

void LCD_sendCommand(uint8 command){
	CLEAR_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
#if(LCD_BIT_MODE==8)
	LCD_DATA_PORT=command;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
#elif(LCD_BIT_MODE==4)
#ifdef UPPER_PORT_PIN
	LCD_DATA_PORT=(LCD_DATA_PORT & 0x0F) | (command & 0xF0);
#else
	LCD_DATA_PORT=(LCD_DATA_PORT & 0xF0) | ((command & 0xF0)>>4);
#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
#ifdef UPPER_PORT_PIN
	LCD_DATA_PORT=(LCD_DATA_PORT & 0x0F) | ((command & 0x0F)<<4);
#else
	LCD_DATA_PORT=(LCD_DATA_PORT & 0xF0) | (command & 0x0F);
#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
#endif
}

void LCD_displayCharacter(uint8 data){
	SET_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
#if(LCD_BIT_MODE==8)
	LCD_DATA_PORT=data;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
#elif(LCD_BIT_MODE==4)
#ifdef UPPER_PORT_PIN
	LCD_DATA_PORT=(LCD_DATA_PORT & 0x0F) | (data & 0xF0);
#else
	LCD_DATA_PORT=(LCD_DATA_PORT & 0xF0) | ((data & 0xF0)>>4);
#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
#ifdef UPPER_PORT_PIN
	LCD_DATA_PORT=(LCD_DATA_PORT & 0x0F) | ((data & 0x0F)<<4);
#else
	LCD_DATA_PORT=(LCD_DATA_PORT & 0xF0) | (data & 0x0F);
#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
#endif
}

void LCD_displayString(const char *ptr){
	uint8 i=0;
	while(ptr[i]!='\0'){
		LCD_displayCharacter(ptr[i]);
		i++;
	}
}

void LCD_goToRowColumn(uint8 row,uint8 col){
	uint8 address;
	switch(row){
	case 0:
		address=col;
		break;
	case 1:
		address=col+0x40;
		break;
	case 2:
		address=col+0x10;
		break;
	case 3:
		address=col+0x50;
		break;
	}
	LCD_sendCommand(address | 0x80);
}

void LCD_integerToString(int data)
{
	char buff[16]; /* String to hold the ascii result */
	itoa(data,buff,10); /* 10 for decimal */
	LCD_displayString(buff);
}

void LCD_clearScreen(){
	LCD_sendCommand(CLEAR_SCREEN);
}
