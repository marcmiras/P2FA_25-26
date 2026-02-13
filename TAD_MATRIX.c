/*
 * File:   matrix.c
 * Author: marcm
 *
 * Created on February 11, 2026, 4:31 PM
 */

#include "TAD_MATRIX.h"
#include "TAD_TIMER.h"
#include "pic18f4321.h"

unsigned char estat;

// Temporal
unsigned char tmr_address;

// [FILES][COLUMNES][CARACTERS_POSSIBLES]
const unsigned char layout_teclat[4][3][6] = {
    // Fila 0
    { "1",      "ABC2",   "DEF3"  }, 
    // Fila 1
    { "GHI4",   "JKL5",   "MNO6"  }, 
    // Fila 2
    { "PQRS7",  "TUV8",   "WXYZ9" }, 
    // Fila 3
    { "*",      "0",      "#"     }
};

unsigned char changeKey(unsigned char Tmr_address) {
    di(); TI_Init(); ei(); 
            
    unsigned char change = (TI_GetTics(Tmr_address) > 1) ? "N" : "Y"; 
    
    return change;
}

void KP_Motor() {
    // Diferència de temps entre Timer calls
    estat = changeKey(&tmr_address);
    
    switch (estat) {
        case "Y":
            break;
        case "N":
            break;           
    } 
    
    return void;
}
