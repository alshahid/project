/*
 *  DIO_prog.c
 *  Description: DIO driver For ATMEGA32
 *
 *  Created on: May 17, 2022
 *  Author	  : Ahmed khaled
 *  Version   : 02
 */ 

/*--------------------------------------------- INCLUDES -----------------------------------------------*/

#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "DIO_int.h"
#include "DIO_reg.h"

/*------------------------------------- FUNCTION Definitions ----------------------------------------*/


/* IO Pins */

/*************************************************************************************************
 *
 * FUNCTION    :  MDIO_voidSetPinDirection (uint8 copy_uint8PORT, uint8 copy_uint8PIN, uint8 copy_uint8MODE)
 *
 * DESCRIBTION :  function which init the register (DDR) and pin of DIO as:
 *                - OUTPUT
 * 				  - INPUT
 *				  - INPUT_PULL_UP	
 * PARAMETER   : number of port , pin and mode ( OUTPUT , INPUT , INPUT_PULL_UP )
 *
 * OUTPUT      : none (void)
 *
 **************************************************************************************************/

void MDIO_voidSetPinDirection (uint8 copy_uint8PORT, uint8 copy_uint8PIN, uint8 copy_uint8MODE)
{
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((copy_uint8PORT <= PORTD) && (copy_uint8PIN <= PIN7))
	{
		if ( copy_uint8MODE == OUTPUT )
		{
			/* Check on the Required PORT Number */
			switch (copy_uint8PORT)
			{
				case PORTA: SET_BIT(DDRA_Register,copy_uint8PIN); break;
				case PORTB: SET_BIT(DDRB_Register,copy_uint8PIN); break;
				case PORTC: SET_BIT(DDRC_Register,copy_uint8PIN); break;
				case PORTD: SET_BIT(DDRD_Register,copy_uint8PIN); break;
			}
		}
		
		else if ( copy_uint8MODE == INPUT )
		{
			/* Check on the Required PORT Number */
			switch (copy_uint8PORT)
			{
				case PORTA: CLR_BIT(DDRA_Register,copy_uint8PIN); break;
				case PORTB: CLR_BIT(DDRB_Register,copy_uint8PIN); break;
				case PORTC: CLR_BIT(DDRC_Register,copy_uint8PIN); break;
				case PORTD: CLR_BIT(DDRD_Register,copy_uint8PIN); break;
			}
		}
		else if ( copy_uint8MODE == INPUT_PULL_UP )
		{
			/* Check on the Required PORT Number */
			switch (copy_uint8PORT)
			{
				case PORTA: CLR_BIT(DDRA_Register,copy_uint8PIN); SET_BIT(PORTA_Register,copy_uint8PIN); break;
				case PORTB: CLR_BIT(DDRB_Register,copy_uint8PIN); SET_BIT(PORTB_Register,copy_uint8PIN); break;
				case PORTC: CLR_BIT(DDRC_Register,copy_uint8PIN); SET_BIT(PORTD_Register,copy_uint8PIN); break;
				case PORTD: CLR_BIT(DDRD_Register,copy_uint8PIN); SET_BIT(PORTC_Register,copy_uint8PIN); break;
			}
		}
		else
		{
			/* Do nothing, Wrong Direction Required */
		}
	}
	
	else
	{
		/* Do nothing, Error in the Pin ID or PORT ID */
	}
}


/*************************************************************************************************
 *
 * FUNCTION    :  MDIO_voidSetPinValue(uint8 copy_uint8PORT , uint8 copy_uint8PIN, uint8 copy_uint8Value)
 *
 * DESCRIBTION :  function which init the register (PORT) and pin of DIO as:
 *                - HIGH
 *				  - LOW
 *				  - TOGGLE	
 * PARAMETER   : number of port , pin and Value ( HIGH , LOW )
 *
 * OUTPUT      : none (void)
 *
 **************************************************************************************************/
void MDIO_voidSetPinValue(uint8 copy_uint8PORT , uint8 copy_uint8PIN, uint8 copy_uint8Value)
{
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((copy_uint8PORT <= PORTD) && (copy_uint8PIN <= PIN7))
	{
		if (copy_uint8Value == HIGH)
		{
			/* Check on the Required PORT Number */
			switch (copy_uint8PORT)
			{
				case PORTA: SET_BIT(PORTA_Register,copy_uint8PIN); break;
				case PORTB: SET_BIT(PORTB_Register,copy_uint8PIN); break;
				case PORTC: SET_BIT(PORTC_Register,copy_uint8PIN); break;
				case PORTD: SET_BIT(PORTD_Register,copy_uint8PIN); break;
			}
		
		}
		
		else if (copy_uint8Value == LOW)
		{
			/* Check on the Required PORT Number */
			switch (copy_uint8PORT)
			{
				case PORTA: CLR_BIT(PORTA_Register,copy_uint8PIN); break;
				case PORTB: CLR_BIT(PORTB_Register,copy_uint8PIN); break;
				case PORTC: CLR_BIT(PORTC_Register,copy_uint8PIN); break;
				case PORTD: CLR_BIT(PORTD_Register,copy_uint8PIN); break;
			}
		}

		else if (copy_uint8Value == TOGGLE)
		{
			/* Check on the Required PORT Number */
			switch (copy_uint8PORT)
			{
				case PORTA: TOG_BIT(PORTA_Register,copy_uint8PIN); break;
				case PORTB: TOG_BIT(PORTB_Register,copy_uint8PIN); break;
				case PORTC: TOG_BIT(PORTC_Register,copy_uint8PIN); break;
				case PORTD: TOG_BIT(PORTD_Register,copy_uint8PIN); break;
			}
		}
	
		else
		{
			/* Do nothing, Wrong value to set */
		}
	}
	
	else
	{
		/* Do nothing, Error in the Pin ID or PORT ID */
	}
}


/*************************************************************************************************
 *
 * FUNCTION    :  MDIO_uint8GetPinValue(uint8 copy_uint8PORT, uint8 copy_uint8PIN)
 *
 * DESCRIBTION :  function which get the value of Specifice pin of DIO and return it as:
 *                - HIGH (1)
 *				  - LOW	 (0)
 * PARAMETER   : number of port and pin 
 *
 * OUTPUT      : the value of pin
 *
 **************************************************************************************************/
uint8 MDIO_uint8GetPinValue(uint8 copy_uint8PORT, uint8 copy_uint8PIN)
{
	/* Define Local Variable to get the BIT Value */
	uint8 Local_uint8Result;
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((copy_uint8PORT <= PORTD) && (copy_uint8PIN <= PIN7))
	{
		/* Check on the Required PORT Number */
		switch (copy_uint8PORT)
		{
			case PORTA: Local_uint8Result= GET_BIT(PINA_Register,copy_uint8PIN); break;
			case PORTB: Local_uint8Result= GET_BIT(PINB_Register,copy_uint8PIN); break;
			case PORTC: Local_uint8Result= GET_BIT(PINC_Register,copy_uint8PIN); break;
			case PORTD: Local_uint8Result= GET_BIT(PIND_Register,copy_uint8PIN); break;
		}
	}
	
	else
	{
		/* return 0xff in case of error in the Pin ID or PORT ID */
		Local_uint8Result = 0xFF;
	}
	
	return Local_uint8Result;
}


/* IO Full Value Of Ports */

/*************************************************************************************************
 *
 * FUNCTION    :  MDIO_voidSetPortDirection (uint8 copy_uint8PortId, uint8 copy_uint8MODE)
 *
 * DESCRIBTION :  function which init the register (DDR) and Number of pin of DIO as:
 *                - Output (1) or INPUT (0)
 *				   
 * PARAMETER   : Number of port and Number of pin 
 *
 * OUTPUT      : None (void)
 *
 **************************************************************************************************/
void MDIO_voidSetPortDirection (uint8 copy_uint8PortId, uint8 copy_uint8MODE)
{
	/* Check on the Required PORT Number */
	switch (copy_uint8PortId)
	{
		case     PORTA: DDRA_Register = copy_uint8MODE; break;
		case     PORTB: DDRB_Register = copy_uint8MODE; break;
		case     PORTC: DDRC_Register = copy_uint8MODE; break;
		case     PORTD: DDRD_Register = copy_uint8MODE; break;
		default: /* Wrong Port ID */       break;
	}
}

/*************************************************************************************************
 *
 * FUNCTION    :  MDIO_voidSetPortValue (uint8 copy_uint8PortId, uint8 copy_uint8PortVal)
 *
 * DESCRIBTION :  function which init the register (PORT) and Number of pin of DIO as:
 *                - HIGH (1) or LOW (0)
 *				   
 * PARAMETER   : Number of port and Number of pin 
 *
 * OUTPUT      : None (void)
 *
 **************************************************************************************************/
void MDIO_voidSetPortValue (uint8 copy_uint8PortId, uint8 copy_uint8PortVal)
{
	/* Check on the Required PORT Number */
	switch (copy_uint8PortId)
	{
		case     PORTA: PORTA_Register = copy_uint8PortVal; break;
		case     PORTB: PORTB_Register = copy_uint8PortVal; break;
		case     PORTC: PORTC_Register = copy_uint8PortVal; break;
		case     PORTD: PORTD_Register = copy_uint8PortVal; break;
		default: /* Wrong Port ID */        break;
	}
}
