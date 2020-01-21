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
           
}

unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}

unsigned char C = 0x07;        
#define A (PINA & 0x03)  
int count = 0;

enum States { Start, Wait, Add, Sub, Reset, Release} State;

void tickButton() {
    switch(State) {
        case Start:
	    C = 0x07;        
	    State = Wait; 	
	    break;
	case Wait: 
	    if (A == 0x01) {
		count = count + 1;
		State = Add; 
	    }
	    else if (A == 0x02) {
		count = count + 2;
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
	    State = Release;
	    break;
	case Sub:
	    State = Release;
            break;
	case Reset:
	    State = Release;
	    break;
	case Release:
	    if (A == 0x01) {
		count = count + 1;
		if (count == 3) {
		    State = Reset;
		}
		else {
                    State = Release;
		}
            }
            else if (A == 0x02) {
		count = count + 2;
                if (count == 3) {
                    State = Reset;
                }
		else {
		    State = Release;
		}
            }
	    else if (A == 0x03) {
		State = Release;
	    }
	    else if (A == 0x00) {
                State = Wait;  
	    }
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
	    if (C < 0x09) {
                C = C + 1;
            }
	    else {
                C = 0x09;
            }
            break;
	case Sub:
	    if (C > 0x00) {
		C = C - 1;
	    }
	    else {
		C = 0x00;
	    }
            break;
	case Reset:
	    C = 0x00;
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
	State = Start;  
	
	while (1) {
	tickButton();	
	PORTC = C;
	}
    
    return 1;
}
