/*
 * Exercise2_CTC_Mode.c
 *
 * Created: 1/21/2014 11:29:49 PM
 * Author: Mohamed Tarek
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer0.h"

#include "common_macros.h"

#define NULL ((void*)0)

static volatile void (*g_callBack)(void)=NULL;


/* Interrupt Service Routine for timer0 compare mode */
ISR(TIMER0_COMP_vect)
{
	if(g_callBack!=NULL)
	{
		(*g_callBack)();
	}
}

/* For clock=1Mhz and prescale F_CPU/1024 every count will take 1ms
 * so we just need 250 counts to get 250ms every overflow. put initial timer counter=0  
 * and output compare register=250 0 --> 250 (250ms per overflow)
 * so we need timer to overflow 2 times to get a 0.5 second 
 */

void timer0_init_CTC_mode(unsigned char tick)
{
	TCNT0 = 0; //timer initial value
	OCR0  = tick; //compare value
	TIMSK |= (1<<OCIE0); //enable compare interrupt
	/* Configure timer0 control register 
	 * 1. Non PWM mode FOC0=1
	 * 2. CTC Mode WGM01=1 & WGM00=0
	 * 3. No need for OC0 in this example so COM00=0 & COM01=0 
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<FOC0) | (1<<WGM01) | (1<<CS02) | (1<<CS00);

	/* global interrupt enable */
	SET_BIT(SREG,7);
}

void TIMER0_setCallBack(void (*a_ptr)(void))
{
	g_callBack=a_ptr;
}

void TIMER0_deInit(void)
{
	TCCR0=0;
	TCNT0=0;
	OCR0=0;
	TIMSK&=~(1<<TOIE0);
	TIMSK&=~(1<<OCIE0);
}

