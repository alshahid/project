/*
 * timer0.h
 *
 *  Created on: May 25, 2022
 *      Author: george
 */

#ifndef TIMER0_H_
#define TIMER0_H_

void timer0_init_CTC_mode(unsigned char tick);
void TIMER0_setCallBack(void (*a_ptr)(void));
void TIMER0_deInit(void);

#endif /* TIMER0_H_ */
