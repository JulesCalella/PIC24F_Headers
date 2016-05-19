#ifndef PINSETUP_H
#define	PINSETUP_H

void pinInit()
{
    TRISA = 0x0000; // Output
    TRISB = 0x0002;
    LATA = 0x0000;  // Off
    LATB = 0x0000;
    ANSA = 0x0000;  // Digital
    ANSB = 0x0000;
    
    // Unlock Sequence
    //__builtin_write_OSCCONL(0x46);
    //__builtin_write_OSCCONL(0x57);
    //OSCCONbits.IOLOCK = 0;          // Unlock the PPS
    
    asm volatile (  "MOV #OSCCON, w1 \n"
                    "MOV #0x46, w2 \n"
                    "MOV #0x57, w3 \n"
                    "MOV.b w2, [w1] \n"
                    "MOV.b w3, [w1] \n"
                    "BCLR OSCCON, #6") ;
    
    
        // Assign U1RX to pin 
        RPINR18bits.U1RXR = 1;           // RX pin (U1RXR) to PR1
        RPOR0bits.RP0R = 3;             // TX pin (3) to RP0
    
    //__builtin_write_OSCCONL(0x46);
    //__builtin_write_OSCCONL(0x57);
    //OSCCONbits.IOLOCK = 1;          // Unlock the PPS
    
    asm volatile (  "MOV #OSCCON, w1 \n"
                    "MOV #0x46, w2 \n"
                    "MOV #0x57, w3 \n"
                    "MOV.b w2, [w1] \n"
                    "MOV.b w3, [w1] \n"
                    "BCLR OSCCON, #6") ;
    
}

#endif	/* PINSETUP_H */

