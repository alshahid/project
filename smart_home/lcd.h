#include"std_types.h"
#include"common_macros.h"
#include"micro_config.h"
/***********************************************************************************
 *                                      Macros                                     *
 ***********************************************************************************/
/*HW Pins*/
#define LCD_CTRL_PORT_DIR DDRD
#define LCD_CTRL_PORT PORTD
#define LCD_DATA_PORT_DIR DDRC
#define LCD_DATA_PORT PORTC

#define RS PD0
#define RW PD1
#define E  PD2

#define LCD_BIT_MODE 4
#define UPPER_PORT_PIN

/*LCD Command*/
#define CLEAR_SCREEN                 0x01
#define RETURN_HOME                  0x02
#define CURSOR_OFF                   0x0C
#define TWO_LINES_LCD_EIGHT_BIT_MODE 0x38
#define TWO_LINES_LCD_FOUR_BIT_MODE  0x28


/***********************************************************************************
 *                                Function Prototypes                              *
 * ********************************************************************************/
void LCD_init();
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *ptr);
void LCD_GoToRowColumn(uint8 row,uint8 column);
void LCD_integerToString(int data);
void LCD_clearScreen();
