/*
 * File:   main.c
 * Author: Marc Miras Fortuny
 *
 * Created on February 11, 2026, 4:26 PM
 */


#include <xc.h>
#include "pic18f4321.h"
#include "TAD_MATRIX.h"
#include "TAD_SPEAKER.h"
#include "TAD_TIMER.h"

void main(void) {
    
    TI_Init();
    KP_Init();
    INT_Init();
    LED_Init();
    //SP_Init();
    
    while(1) {
        
    }
    
    return void;
}
