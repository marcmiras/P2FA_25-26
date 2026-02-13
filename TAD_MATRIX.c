/*
 * File:   TAD_MATRIX.c
 * Author: Marc Miras Fortuny
 *
 * Created on February 11, 2026, 4:31 PM
 */

#include "TAD_MATRIX.h"
#include "TAD_TIMER.h"
#include "pic18f4321.h"

// Rows
#define R0 TRISDbits.TRISD0
#define R1 TRISDbits.TRISD1
#define R2 TRISDbits.TRISD2
#define R3 TRISDbits.TRISD3

// Columns
#define C0 TRISCbits.TRISC0
#define C1 TRISCbits.TRISC1
#define C2 TRISCbits.TRISC2

// Variables locals
static unsigned char change;
static unsigned char State;
static unsigned char key;
static unsigned char saved_col;
static unsigned char saved_row;

// Loop variables
static unsigned char i = 0;
static unsigned char j = 0; 

// Variable auxiliar de temps
static unsigned long aux_time = 0;

// Temporal, hauria de venir d'algun lloc
static unsigned char tmr_handle;

typedef struct {
    unsigned char debounce;
} Flag;

// Flags per ajudar
static Flag flag;
    
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
    // Rows
    TRISDbits.TRISD0 = 1; TRISDbits.TRISD1 = 1; TRISDbits.TRISD2 = 1; TRISDbits.TRISD3 = 1;
    
    // Columns
    TRISCbits.TRISC0 = 0; TRISCbits.TRISC1 = 0; TRISCbits.TRISC2 = 0;
    
    TI_NewTimer(&tmr_handle);
}

unsigned char KP_loopRows(unsigned char row) {
    LATDbits.LATD0 = 1; LATDbits.LATD1 = 1; LATDbits.LATD2 = 1; LATDbits.LATD3 = 1;
    
    if (row++ == 0) LATDbits.LATD0 = 0;
    if (row++ == 1) LATDbits.LATD1 = 0;
    if (row++ == 2) LATDbits.LATD2 = 0;
    if (row == 3) { 
        LATDbits.LATD3 = 0;   
        row = 0;
    }    
    
    return row;
}

// Complete after getting KP and Bounces done
unsigned char KP_getKey(unsigned char row, unsigned char col, unsigned char i) {
    unsigned char key;
    
    return layout_teclat[][][i];
}

unsigned char KP_getRow() {
    // Completar LLEGIR COLUMNA
}

unsigned char KP_isPressed() {
    return ((!C0 && !C1 && !C2) ? 0 : 1);
}

void KP_Motor() {
   
    switch (State) {
        // Escombratge
        case 0:
            aux_time = 0;
            j = KP_loopRows(j);
            if (KP_isPressed()) {
                state = 1;
                
            }    
       
            break;
            
        // Check Key Pressed / Check Release  
        case 1: 
            TI_ResetTics(tmr_handle);
            
            if ((TI_GetTics(tmr_handle) - aux_time) >= 15) {
                if (!KP_isPressed()) {
                    if (!flag.debounce) state = 0;
                    else {
                        state = 3;
                        flag.debounce = 0;
                    }    
                if (KP_isPressed()) {
                    state = 2;
                    if (!flag.debounce) TI_ResetTics(tmr_handle);
                }    
            }
            break;
            
        // Count Key Pressed    
        case 2:
            if (!KP_isPressed()) {
                aux_time = TI_GetTics(tmr_handle);
                flag.debounce = 1;
                state = 1;
            }    
            break;
        
        // Check how many times is pressed  
        case 3:  
            TI_ResetTics(tmr_handle);
            
            if (aux_time >= 1000) {
               key = getKey();
            }
            else {
                i++
            };     
            
            break;
     
    } 
    
    return void;
}
