/*
 * File:   TAD_MATRIX.c
 * Author: Marc Miras Fortuny
 *
 * Created on February 11, 2026, 4:31 PM
 */

#include "TAD_MATRIX.h"
#include "TAD_TIMER.h"
#include "pic18f4321.h"

#define MULTITAP_TIMEOUT  1000 // 1 segon per acceptar la lletra
#define BOUNCE_TIME  15 // 1 segon per acceptar la lletra

typedef enum {
    ESTAT_REPOS,
    ESTAT_REBOTS,     
    ESTAT_ESPERA,
    ESTAT_TECLA
} KP_estat;

// Variables locals
static unsigned char state;
static unsigned char key;

static unsigned char last_c;
static unsigned char last_r;

static unsigned char c;
static unsigned char r;

// Loop variables
static unsigned char i = 0;
static unsigned char j = 0; 

// Variable auxiliar de temps
static unsigned long aux_time = 0;
static unsigned long last_press_time;

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
    // TRIS: Files Output, Cols Input
    TRISDbits.TRISD0 = 0; TRISDbits.TRISD1 = 0; TRISDbits.TRISD2 = 0; TRISDbits.TRISD3 = 0;
    TRISBbits.TRISB0 = 1; TRISBbits.TRISB1 = 1; TRISBbits.TRISB2 = 1;
    
    INTCON2bits.RBPU = 0; // Pull-ups actives
    
    // Files a 1 (Repòs)
    LATDbits.LATD0 = 1; LATDbits.LATD1 = 1; LATDbits.LATD2 = 1; LATDbits.LATD3 = 1;
    
    TI_NewTimer(&tmr_handle);
}

unsigned char KP_loopRows(unsigned char row) {
    LATDbits.LATD0 = 1; LATDbits.LATD1 = 1; LATDbits.LATD2 = 1; LATDbits.LATD3 = 1;
    
    switch (row) {
        case 0: LATDbits.LATD0 = 0; break;
        case 1: LATDbits.LATD1 = 0; break;
        case 2: LATDbits.LATD2 = 0; break;
        case 3: LATDbits.LATD3 = 0; row = 0; break;
    }

    return row;
}

void KP_getCol(unsigned char *c) {
    if (!PORTBbits.RB0) *c = 0;
    if (!PORTBbits.RB1) *c = 1;
    if (!PORTBbits.RB2) *c = 2;
}

void KP_setRow(unsigned char row, unsigned char val) {
    // Val = 0 (Activa), Val = 1 (Desactiva)
    switch(row) {
        case 0: LATDbits.LATD0 = val; break;
        case 1: LATDbits.LATD1 = val; break;
        case 2: LATDbits.LATD2 = val; break;
        case 3: LATDbits.LATD3 = val; break;
    }
}

unsigned char KP_pressed() {
    return ((!PORTBbits.RB0 & !PORTBbits.RB1 & !PORTBbits.RB2) ? 0 : 1);
}

void KP_Motor() {
    unsigned long now = TI_GetTics(tmr_handle);
    
    switch (state) {
        // --- ESTAT 0: REPOS ---
        case ESTAT_REPOS:
            aux_time = 0;
            j = KP_loopRows(j);
            
            if (KP_pressed()) {
                r = j;
                
                KP_getCol(&c);
                state = ESTAT_REBOTS;
                TI_ResetTics(tmr_handle);
            }    
            break;
            
        // --- ESTAT 1: REBOTS ---
        case ESTAT_REBOTS: 
            if ((TI_GetTics(tmr_handle) - aux_time) >= BOUNCE_TIME) {
                if (!KP_pressed()) {
                    if (!flag.debounce) state = ESTAT_REPOS;
                    else {
                        state = ESTAT_TECLA;
                        flag.debounce = 0;
                    }
                }    
                if (KP_pressed()) {
                    state = ESTAT_ESPERA;
                    if (!flag.debounce) TI_ResetTics(tmr_handle);
                }    
            }
            break;
            
        // --- ESTAT 2: ESPERA (HOLD) ---  
        case ESTAT_ESPERA:
            if (!KP_pressed()) {
                aux_time = TI_GetTics(tmr_handle);
                flag.debounce = 1;
                state = ESTAT_REBOTS;
                TI_ResetTics(tmr_handle);
            }    
            break;
        
        // --- ESTAT 3: LOGICA MULTITAP ---
        case ESTAT_TECLA:  
            if ((aux_time >= MULTITAP_TIMEOUT) && (c == last_c) && (r == last_r)) {
                i++; // Següent lletra
                
                if (layout_teclat[r][c][i] == '\0') i = 0; // Reset si és buit (final)
            }
            else i = 0; // Lletra nova o > 1 segon
            
            last_c = c;
            last_r = r;
            
            key = layout_teclat[r][c][i];
            
            state = ESTAT_REPOS;
            TI_ResetTics(tmr_handle);
            
            break;
    } 
    return;
}
