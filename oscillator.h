#ifndef OSCILLATOR_H
#define	OSCILLATOR_H

/* 
 * In order to run the oscillator with the PLL, PLLDIV must be set to PLLNX.
 * Clock Switching must also be enabled otherwise NOSC does not work. The 
 * switch must be written in assembly as it is very time sensitive.
 * 
 */

void oscInit()
{
    TRISB = 0x00;
    LATB = 0x00;
    
    CLKDIVbits.RCDIV = 0; // 4MHz
    
    // Read COSC bits 
        
    // Unlock sequence high Byte of OSCCON 78h and 9Ah
    __builtin_write_OSCCONH(0x78);
    __builtin_write_OSCCONH(0x9A);
    
    // Write values to NOSC
    __builtin_write_OSCCONH(0x01);
    
    // Unlock sequence low Byte OSCCON 46h and 57h
    __builtin_write_OSCCONL(0x46);
    __builtin_write_OSCCONL(0x57);
    
    // Set OSWEN bits to switch
    __builtin_write_OSCCONL(0x01);
    
    // LOCK and CF automatically cleared
    // Hardware waits till PLL lock is detected
    // OSWEN bit is cleared automatically
    while(OSCCONbits.OSWEN != 0) continue;       
}

#endif	/* XC_HEADER_TEMPLATE_H */

