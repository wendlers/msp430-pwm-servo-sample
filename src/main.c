/*
 * This file is part of the MSP430 PWM example. It controls two servos on P1.6 and P2.2.
 *
 * Copyright (C) 2012 Stefan Wendler <sw@kaltpost.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include  <msp430.h>

void delay() 
{
	P1OUT ^= BIT0; 

	volatile unsigned long i;
	i = 49999; 
	do (i--);
	while (i != 0);
}

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;              

	P1DIR |= BIT0; 							// Internal LEDs P1.0 of Launchpad is output

    P1DIR |= BIT6;							// P1.6/TA0.1 is used for PWM, thus also an output -> servo 1
    P2DIR |= BIT2;							// P2.2/TA1.1 is used for PWM, thus also an output -> servo 2

	P1OUT = 0; 								// Clear all outputs P1
	P2OUT = 0; 								// Clear all outputs P2

  	P1SEL |= BIT6;                          // P1.6 select TA0.1 option
  	P2SEL |= BIT2;                          // P2.2 select TA1.1 option

	// if SMCLK is about 1MHz (or 1000000Hz), 
	// and 1000ms are the equivalent of 1 Hz,
	// then, by setting CCR0 to 20000 (1000000 / 1000 * 20)
	// we get a period of 20ms
  	TA0CCR0 = 20000-1;                           // PWM Period TA0.1
  	TA1CCR0 = 20000-1;                           // PWM Period TA1.1

	// setting 1500 is 1.5ms is 0deg. servo pos 
	TA0CCR1 = 1500;                            // CCR1 PWM duty cycle
	TA1CCR1 = 1500;                            // CCR1 PWM duty cycle

	TA0CCTL1 = OUTMOD_7;                       // CCR1 reset/set
	TA0CTL   = TASSEL_2 + MC_1;                // SMCLK, up mode
	TA1CCTL1 = OUTMOD_7;                       // CCR1 reset/set
	TA1CTL   = TASSEL_2 + MC_1;                // SMCLK, up mode

	// loop just blinks build in LEDs to show activity
	for (;;)
	{
		delay();
		TA0CCR1 = 1000;
		TA1CCR1 = 2000;

		delay();
		TA0CCR1 = 1500;
		TA1CCR1 = 1500;

		delay();
		TA0CCR1 = 2000;
		TA1CCR1 = 1000;

		delay();
		TA0CCR1 = 1500;
		TA1CCR1 = 1500;
	}
}
