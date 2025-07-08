// 22-psp

#include <msp430.h>

unsigned int icnt;
void IO_Init(void) {
    P8DIR |= BIT1;   // 设置P8.1口为输出模式  控制LED灯
    P8OUT &= ~BIT1;  // 选中P8.1为输出方式
    P3DIR |= BIT7;   // 设置P8.1口为输出模式  控制LED灯
    P3OUT &= ~BIT7;  // 选中P8.1为输出方式

    P2DIR &= ~(BIT3 + BIT6);
    P2REN |= BIT3 + BIT6;
    P2OUT |= BIT3 + BIT6;

    P1DIR &= ~(BIT3 + BIT2);
    P1REN = BIT3 + BIT2;
    P1OUT |= BIT3 + BIT2;
}

int apInterface_Key(void) {
    if (!(P1IN & BIT2)) {
        __delay_cycles(5);
        if (!(P1IN & BIT2)) {
            return 1;
        }
    }

    if (!(P1IN & BIT3)) {
        __delay_cycles(5);
        if (!(P1IN & BIT3)) {
            return 2;
        }
    }

    if (!(P2IN & BIT3)) {
        __delay_cycles(5);
        if (!(P2IN & BIT3)) {
            return 3;
        }
    }

    if (!(P2IN & BIT6)) {
        __delay_cycles(5);
        if (!(P2IN & BIT6)) {
            return 4;
        }
    }
    return 0;
}

/**
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer
    IO_Init();
    TA0CTL |= MC_1 + TASSEL_2 + TACLR;  // 时钟为SMCLK,比较模式，开始时清零计数器
    TA0CCTL0 = CCIE;                    // 比较器中断使能
    TA0CCR0 = 50000;                    // 比较值设为50000，相当于50ms的时间间隔
    __enable_interrupt();

    while (1) {
        if (apInterface_Key() == 1) {
            P8OUT |= BIT1;
            P3OUT |= BIT7;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;  // 时钟为SMCLK,比较模式，开始时清零计数器
            icnt = 0;
        }
    }
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void) {
    icnt++;
    if (icnt == 100) {  // 5s关灯
        P8OUT &= ~BIT1;
        P3OUT &= ~BIT7;
        icnt = 0;
    }
}
