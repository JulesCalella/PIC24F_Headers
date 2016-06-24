#ifndef UART_H
#define	UART_H

/*
 * The main file should constantly check if U1STAbits.URXDA == 1 (FIFO full) 
 * to deteremine if multiple reads need to need done.  
 * 
 *
 * Baud Rate = FCY / (mult * (U1BRG + 1))  mult=4 for BRGH=1, mult=16 for BRGH=0
*/
void UARTInit()
{
    U1MODEbits.UARTEN = 0;      // Disable UART module
    U1MODEbits.UEN = 0;
    U1STAbits.UTXEN = 0;
    U1STAbits.URXEN = 0;
    U1MODEbits.USIDL = 0;
    U1MODEbits.IREN = 0;
    U1MODEbits.ABAUD = 0;
    U1MODEbits.BRGH = 1;        // High Speed Baud Rate (needed for 115200)
    U1MODEbits.WAKE = 1;
    U1MODEbits.LPBACK = 0;      // Loop back enabled for error checking
    
    U1STAbits.UTXBRK = 0;
    U1STAbits.ADDEN = 0;
    U1STAbits.RIDLE = 0;
    U1STAbits.OERR = 0;
    
    
    U1BRG  = 34;               // Set Baud Rate to 9600 with 416, 115200 with 34
    
    U1MODEbits.PDSEL = 0x00;    // 8 bit, no parity
    U1MODEbits.STSEL = 0x00;    // 1 stop bit
    
    // Interrupts
    IEC0bits.U1TXIE = 0;    // DIsable Interrupt
    IEC0bits.U1RXIE = 0;
    IFS0bits.U1TXIF = 0;    // Erase interrupt flags
    IFS0bits.U1RXIF = 0;
    IPC3bits.U1TXIP = 0;    // Interrupt priorities (0 = disabled)
    IPC2bits.U1RXIP = 0;
    
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;        // Enable TX
    U1STAbits.URXEN = 1;        // Enable RX
}

/*******************************************************************************
 * UARTTxNum will take the data passed to it and will transmit it.  The function 
 * returns '1' if the data is sent, or '0' if it is not sent.
 ******************************************************************************/
void UARTTxNum(int data)
{
    U1TXREG = data;  
}

/*******************************************************************************
 * UARTTxChar is similar to the num version, but sends a character instead.  
 * Having this function saves having to cast an int to a char before 
 * transmitting.
 ******************************************************************************/
void UARTTxChar(char data)
{
    U1TXREG = data;
}

/*******************************************************************************
 * UARTRx receives data and returns it as an int.
 ******************************************************************************/
int UARTRx()
{
    int dataReceived = U1RXREG;
    return dataReceived;
}

#endif	

