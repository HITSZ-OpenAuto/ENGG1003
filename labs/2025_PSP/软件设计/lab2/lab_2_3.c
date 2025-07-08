// 22-psp

#include <msp430.h>
int main(void) {
    // stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    // SMCLK, 清除 TAR，增计数
    TA0CTL = TASSEL_2 + TACLR + MC0;

    TA0CCR0 = 512;  // PWM周期 0.5ms

    TA0CCTL3 = OUTMOD_7;  // 输出模式7
    TA0CCR3 = 400;        // 占空比80%

    TA0CCTL4 = OUTMOD_7;  // 输出模式7;
    TA0CCR4 = 51;         // 占空比10%

    P1DIR |= BIT4;  // P1.4 方向为输出
    P1SEL |= BIT4;  // P1.4端口为外设，定时器TA0.3
    P1DIR |= BIT5;  // P1.5方向为输出
    P1SEL |= BIT5;  // P1.5端口为外设，定时器TA0.4
}
