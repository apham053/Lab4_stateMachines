/*	Author: apham053
 *  Partner(s) Name: Steven Rodriguez
 *	Lab Section: 021
 *	Assignment: Lab #4  Exercise #3
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

unsigned char B = 0x00;        
#define A (PINA & 0x87)  

enum States { Start, Init, poundPress, Release, yPress, Lock } State;

void tickButton() {
    switch(State) {
        case Start:
	    B = 0x00;
	    State = Init;
	    break;
	case Init:
	    if (A == 0x04) {
		State = poundPress; 
	    }
	    else if(A == 0x80) {
		State = Lock;
	    }
	    else {
		State = Init;
	    }
	    break;
	case poundPress:
	    if (A == 0x04) {
		State = poundPress;
	    }
	    else if(A == 0x80) {
                State = Lock;
            }
	    else if (A == 0x00) {
		State = Release;
	    }
	    else {
	        State = Init;
	    }
	    break;
	case Release:
	    if (A == 0x00) {
		State = Release;
	    }
	    else if(A == 0x80) {
                State = Lock;
            }
            else if (A == 0x02) {
                State = yPress;
            }
	    else {
		State = Init;
	    }
	    break;
	case yPress:
	    State = Lock;
	    break;
	case Lock:
	    State = Lock;
	    break;
        default:
	    State = Start;
	    break;
    }
    
    switch(State) {
	case Start:
	    break;
	case Init:
	    break;
	case poundPress:
            break;
	case Release:
            break;
	case yPress:
	    break;
	case Lock:
	    if (A == 0x02) {
		B = 0x01;
	    }
	    else if (A == 0x80) {
		B = 0x00;
	    }
	    break;
	default:
	    break;	    
    }    
}

int main(void) {
	DDRA = 0x00;
	DDRB = 0xFF;
	PORTA = 0xFF;
	PORTB = 0x00;
	State = Start;  
	
	while (1) {
	tickButton();	
	PORTB = B;
	}
    
    return 1;
}
