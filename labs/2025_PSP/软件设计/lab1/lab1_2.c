// 22-psp

#include <msp430.h>

/**
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer
    P8DIR |= BIT1;
    P8OUT &= ~BIT1;
    P3DIR |= BIT7;
    P3OUT &= ~BIT7;
    P7DIR |= BIT4;
    P7OUT &= ~BIT4;
    P6DIR |= BIT3;
    P6OUT &= ~BIT3;
    P1DIR |= BIT5;
    P1OUT &= ~BIT5;
    P2DIR |= BIT4;
    P2OUT |= BIT4;
    P2DIR |= BIT5;
    P2OUT &= ~BIT5;

    P1DIR &= ~BIT2;
    P1REN |= BIT2;
    P1OUT |= BIT2;
    P1IE |= BIT2;
    P1IES |= ~BIT2;
    P1IFG &= ~BIT2;

    P1DIR &= ~BIT3;
    P1REN |= BIT3;
    P1OUT |= BIT3;
    P1IE |= BIT3;
    P1IES |= ~BIT3;
    P1IFG &= ~BIT3;

    P2DIR &= ~BIT3;
    P2REN |= BIT3;
    P2OUT |= BIT3;
    P2IE |= BIT3;
    P2IES |= ~BIT3;
    P2IFG &= ~BIT3;

    P2DIR &= ~BIT6;
    P2REN |= BIT6;
    P2OUT |= BIT6;
    P2IE |= BIT6;
    P2IES |= ~BIT6;
    P2IFG &= ~BIT6;

    _enable_interrupt();

    return 0;
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1() {
    if (P1IFG & BIT2) {
        P8OUT ^= BIT1;
        P1OUT ^= BIT5;
        P2OUT ^= BIT4;
        P2OUT ^= BIT5;
        P1IFG &= ~BIT2;
    }
    if (P1IFG & BIT3) {
        P3OUT ^= BIT7;
        P1IFG &= ~BIT3;
    }
}

#pragma vector = PORT2_VECTOR
__interrupt void Port_2() {
    if (P2IFG & BIT3) {
        P7OUT ^= BIT4;
        P2IFG &= ~BIT3;
    }
    if (P2IFG & BIT6) {
        P6OUT ^= BIT3;
        P2IFG &= ~BIT6;
    }
}
