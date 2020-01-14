/*	Author: apham053
 *  Partner(s) Name: Steven Rodriguez
 *	Lab Section: 021
 *	Assignment: Lab #4  Exercise #1
 * 
 *	Exercise Description: PB0 and PB1 each connect to an LED, and PB0's LED 
 *  is initially on. Pressing a button connected to PA0 turns off PB0's LED 
 *  and turns on PB1's LED, staying that way after button release. 
 *  Pressing the button again turns off PB1's LED and turns on PB0's LED. 
 * 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
   return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
              //   Set bit to 1           Set bit to 0
}

unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}

int main(void) {
	DDRA = 0x00;
	DDRB = 0xFF;
	PORTA = 0xFF;
	PORTB = 0x00;

	unsigned char B = 0x01; //B0 is initially on
	
    while(1) {
		unsigned char A = PINA & 0x01; //Read PA0
			
			if (GetBit(A, 0)) {        // if button pressed
				B = SetBit(B, 0, 0);   // turn off B0
				B = SetBit(B, 1, 1);   // turn on B1
				
				if (GetBit(A, 0)) {        // if button pressed
					B = SetBit(B, 1, 0);   // turn off B1
					B = SetBit(B, 0, 1);   // turn on B0
				}	
				
			}
			
			PORTB = B;
			B = 0x01;   //reset
			
		
	}
    
    return 1;
}
