// 22-psp

#include <msp430.h>

/**
 * blink.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer
    P3DIR |= BIT7;             // configure P1.0 as output
    P3OUT &= ~BIT7;
    P1REN |= BIT3;
    P1OUT |= BIT3;

    while (1) {
        if (!(P1IN & BIT3))
            P3OUT |= BIT7;
        else
            P3OUT &= ~BIT7;
    }
    return 0;
}
