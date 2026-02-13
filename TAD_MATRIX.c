/*
 * File:   TAD_MATRIX.c
 * Author: Marc Miras Fortuny
 *
 * Created on February 11, 2026, 4:31 PM
 */

#include "TAD_MATRIX.h"
#include "TAD_TIMER.h"
#include "pic18f4321.h"

static unsigned char change;
static unsigned char State;

// Temporal, hauria de venir d'algun lloc
unsigned char tmr_handle;

    
// [FILES][COLUMNES][CARACTERS_POSSIBLES]
// Flash
const static unsigned char layout_teclat[4][3][6] = {
    // Fila 0
    { "1",      "ABC2",   "DEF3"  }, 
    // Fila 1
    { "GHI4",   "JKL5",   "MNO6"  }, 
    // Fila 2
    { "PQRS7",  "TUV8",   "WXYZ9" }, 
    // Fila 3
    { "*",      "0",      "#"     }
};

void KP_Init() {    
    TI_NewTimer(&tmr_handle);
}

unsigned char KP_changeKey(unsigned char Tmr_address) {
    return ((TI_GetTics(Tmr_address) > 1) ? "N" : "Y") ;
}

unsigned char KP_getKey() {
    unsigned char key;
    
    
    
    return key;
}

void KP_Motor() {
    // Diferència de temps entre Timer calls
    //estat = KP_changeKey(&tmr_handle);
    
    switch (State) {
        // Hi ha tecla
        case 0:
            
            break;
            
        // Comptar bounce (key pressed)
        case 1:
            break;
         
        // S'està prement encara tecla?    
        case 2:
            break;
            
        // Quant temps es pren (comptatge)    
        case 3:    
            break;           
    } 
    
    return void;
}
