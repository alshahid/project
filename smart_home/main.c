#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"
#include "keypad.h"
#include "lcd.h"
#include "servo.h"
#include "timer0.h"
#include "DIO_int.h"

#include "common_macros.h"

void closeBuzzer(void)
{
	static int count=0;
	if(count==4)
	{
		count=0;
		MDIO_voidSetPinValue(PORTD,PIN3,LOW);
		TIMER0_deInit();
	}
	count++;
}

int main()
{

	uint32 temp,light;
	uint8 flag=1,failedCount=0;
	uint8 savedPass[]={1,2,3,4};
	uint8 receivedPass[4];

	/* init pin direction for leds*/
	MDIO_voidSetPinDirection(PORTA,PIN2,HIGH); /*led 1*/
	MDIO_voidSetPinDirection(PORTA,PIN3,HIGH);/*led 2*/
	MDIO_voidSetPinDirection(PORTA,PIN4,HIGH);/*led 3*/

	/* init pin dir for motor */
	MDIO_voidSetPinDirection(PORTC,PIN0,HIGH);

	/* init pin dir for button */
	MDIO_voidSetPinDirection(PORTC,PIN1,LOW);

	/* init pin dir for servo motor */
	MDIO_voidSetPinDirection(PORTD,PIN5,HIGH);

	/* init pin dir for buzzer */
	MDIO_voidSetPinDirection(PORTD,PIN3,HIGH);

	ADC_init();
	LCD_init();


	TIMER0_setCallBack(closeBuzzer);

	LCD_clearScreen();

	while(1)
	{
		LCD_goToRowColumn(0,0);
		LCD_displayString("Temp = ");
		LCD_goToRowColumn(0,11);
		LCD_displayString("C");

		LCD_goToRowColumn(1,0);
		LCD_displayString("light = ");
		//LCD_clearScreen();///////////////////////////////////
		LCD_goToRowColumn(0,7);
		temp=ADC_readChannel(0);
		temp = (temp*150*5)/(1023*1.5);
		LCD_integerToString(temp);
		light=ADC_readChannel(1);
		LCD_goToRowColumn(1,8);
		LCD_integerToString(light);

		if(BIT_IS_SET(PINC,1))
		{
			flag=1;
			failedCount=0;

			while(flag==1)
			{
				LCD_clearScreen();
				LCD_displayString("enter the pass:");
				LCD_goToRowColumn(1,0);
				for(int i=0;i<4;i++)
				{

					receivedPass[i]=KeyPad_getPressedKey();
					LCD_integerToString(receivedPass[i]);
					_delay_ms(300);
					LCD_goToRowColumn(1,i);
					LCD_displayString("*");
					_delay_ms(500);
				}
				if(receivedPass[0]==savedPass[0] && receivedPass[1]==savedPass[1] && receivedPass[2]==savedPass[2] && receivedPass[3]==savedPass[3])
				{
					flag=0;
					Timer1_Fast_PWM_Init(250);	/* Set Servo shaft at 90° position by 1.5 ms pulse */
					_delay_ms(1500);
					Timer1_Fast_PWM_Init(187);	/* Set Servo shaft at 0° position by 1 ms pulse */
					LCD_clearScreen();
				}
				else
				{
					failedCount++;
					LCD_clearScreen();
					LCD_displayString("wrong pass ");
					LCD_goToRowColumn(1,0);
					LCD_displayString("trial ");
					LCD_goToRowColumn(1,7);
					LCD_integerToString(failedCount);
					_delay_ms(300);

					if(failedCount>2)
					{
						flag=0;
						/* start timer */
						timer0_init_CTC_mode(250);
						/* turn on buzzer */
						MDIO_voidSetPinValue(PORTD,PIN3,HIGH);
					}
				}
			}
			LCD_clearScreen();
		}

		//_delay_ms(100); /test on hardware/
		if(temp >=30 )
		{
			/* turn on motor */
			MDIO_voidSetPinValue(PORTC,PIN0,HIGH);
		}
		else
		{
			/* turn off motor */
			MDIO_voidSetPinValue(PORTC,PIN0,LOW);
		}

		if(light >=0 && light <300 )
		{
			/* turn on led1 */
			MDIO_voidSetPinValue(PORTA,PIN2,HIGH);
			MDIO_voidSetPinValue(PORTA,PIN3,HIGH);
			MDIO_voidSetPinValue(PORTA,PIN4,HIGH);
		}
		else if ( light >=300 && light <600)
		{
			/* turn on led2 */
			MDIO_voidSetPinValue(PORTA,PIN4,LOW);
		}
		else
		{
			/* turn on led3 */
			MDIO_voidSetPinValue(PORTA,PIN3,LOW);
			MDIO_voidSetPinValue(PORTA,PIN4,LOW);
		}
	}
}

