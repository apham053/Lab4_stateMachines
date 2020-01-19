/*	Author: apham053
 *  Partner(s) Name: Steven Rodriguez
 *	Lab Section: 021
 *	Assignment: Lab #4  Exercise #2
 * 
 *	Exercise Description: 
 *  
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

unsigned char C = 0x07;        
#define A (PINA & 0x03)  

enum States { Start, Wait, Add, Sub, Reset} State;

void tickButton() {
    switch(State) {
        case Start:         
	    State = Wait; 
	    break;
	case Wait: 
	    if (A == 0x01) {
		State = Add; 
	    }
	    else if (A == 0x02) {
		State = Sub;
	    }
	    else if (A == 0x03) {
		State = Reset;
	    }
	    else {
		State = Wait;
	    }
	    break;
	case Add: 
	    if (A == 0x00) {     //release
		if (C == 0x09) {
		    State = Wait;
		}
		else {
		    ++C;
		    State = Wait;    
	        }
	    }
	    else if (A == 0x03) {
		State = Reset;
	    }
	    break;
	case Sub:
            if (A == 0x00) {     //release 
                if (C == 0x00) {
                    State = Wait;
                }
                else {
                    --C;
		    State = Wait;    
                }
            }
            else if (A == 0x03) {
                State = Reset;
            }
            break;
	case Reset:
	    C = 0x00;
	    State = Wait;
	    break;
        default:
	    State = Start;
	    break;
    }
    
    switch(State) {
	case Start:
	    break;
	case Wait:
	    break;
	case Add:
            break;
	case Sub:
            break;
	case Reset:
            break;
	default:
	    break;	    
    }    
}

int main(void) {
	DDRA = 0x00;
	DDRC = 0xFF;
	PORTA = 0xFF;
	PORTC = 0x00;
	State = Start;   // initial call
	
	while (1) {
	tickButton();	
	PORTC = C;
        C = 0x07;
	}
    
    return 1;
}
    
