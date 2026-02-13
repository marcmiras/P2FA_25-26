/*
 * File:   TAD_MATRIX.c
 * Author: Marc Miras Fortuny
 *
 * Created on February 11, 2026, 4:31 PM
 */

#include "TAD_MATRIX.h"
#include "TAD_TIMER.h"
#include "pic18f4321.h"

void KP_Init() {
    unsigned char change;
    unsigned char estat;

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
    
    return void;
    
    // Necessary?
    unsigned char tmr_ok;
}

unsigned char KP_changeKey(unsigned char Tmr_address) {
    if (TI_NewTimer(&Tmr_address) == TI_CERT) change = (TI_GetTics(Tmr_address) > 1) ? "N" : "Y"; 
    return change;
}

void KP_Motor() {
    // Diferència de temps entre Timer calls
    estat = KP_changeKey(&tmr_handle);
    
    switch (estat) {
        case "Y":
            break;
        case "N":
            break;           
    } 
    
    return void;
}
