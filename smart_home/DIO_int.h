/*
 *  DIO_int.c
 *  Description: DIO driver For ATMEGA32
 *  
 *  Created on: May 17, 2022
 *  Author    : ahmed khaled
 *  Version   : 02
 */ 
#ifndef _DIO_INT_H
#define _DIO_INT_H

/*---------------------------------- Definitions and configurations ---------------------------------*/

/* Port Defines */
#define PORTA    0
#define PORTB    1
#define PORTC    2
#define PORTD    3

/* PIN Defines */
#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7

/* PIN Directions */
#define INPUT  0
#define OUTPUT 1
#define INPUT_PULL_UP 2

/* PIN Value Options */
#define HIGH   1
#define LOW    0
#define TOGGLE 2 

/*----------------------------------- FUNCTION DECLARATIONS --------------------------------*/

/* IO Pins */
void MDIO_voidSetPinDirection (uint8 copy_uint8PORT, uint8 copy_uint8PIN, uint8 copy_uint8MODE);

void MDIO_voidSetPinValue(uint8 copy_uint8PORT , uint8 copy_uint8PIN, uint8 copy_uint8Value);

uint8   MDIO_uint8GetPinValue(uint8 copy_uint8PORT, uint8 copy_uint8PIN);


/* IO Full Value Of Ports */
void MDIO_voidSetPortDirection (uint8 copy_uint8PortId, uint8 copy_uint8MODE);

void MDIO_voidSetPortValue     (uint8 copy_uint8PortId, uint8 copy_uint8PortVal);

#endif