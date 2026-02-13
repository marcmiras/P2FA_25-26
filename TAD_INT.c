/*
 * File:   TAD_INT.c
 * Author: Marc Miras Fortuny
 *
 * Created on February 13, 2026, 10:56 AM
 */

#include <xc.h>
#include "pic18f4321.h"
#include "TAD_INT.h"
#include "TAD_TIMER.h"

// Declaració de variables
static unsigned char State = 0;
static unsigned char MyTimer;

void INT_Init(void) {
    
    return void;
}

void INT_raise_int() {
    // Cada segon, incrementar intensitat. Jugar amb interrupció timer 1s
    return void;
}

void INT_Motor() {
    
    switch (State) {
        case 0:
            break;
        case 1:
            break;
    } 
    
    return void;
    
}