/* 
 * File:   TAD_MATRIX.h
 * Author: Marc Miras Fortuny
 *
 * Created on February 11, 2026, 4:43 PM
 */

#ifndef TAD_MATRIX_H
#define	TAD_MATRIX_H

// VARIABLES
unsigned char change;

const static unsigned char layout_teclat[4][3][6];

// FUNCIONS
void KP_Init();
unsigned char KP_changeKey(unsigned char tmr_handle);
void KP_motor();
unsigned char KP_getKey();

#endif	/* TAD_MATRIX_H */

