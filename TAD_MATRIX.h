/* 
 * File:   TAD_MATRIX.h
 * Author: Marc Miras Fortuny
 *
 * Created on February 11, 2026, 4:43 PM
 */

#ifndef TAD_MATRIX_H
#define	TAD_MATRIX_H

// VARIABLES
unsigned char estat;
unsigned char change;
unsigned char tmr_ok;
unsigned char tmr_handle;

const static unsigned char layout_teclat[4][3][6];

// FUNCIONS
void KP_Init();
unsigned char KP_changeKey(unsigned char Tmr_address);
void KP_motor();

#endif	/* TAD_MATRIX_H */

