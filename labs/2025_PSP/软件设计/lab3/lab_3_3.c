// 22-psp

#include <msp430.h>

void ClockInit() {         // 最终MCLK:16MHZ,SMCLK:8MHZ,ACLK:32KHZ
    UCSCTL6 &= ~XT1OFF;    // 启动XT1
    P5SEL |= BIT2 + BIT3;  // XT2引脚功能选择
    UCSCTL6 &= ~XT2OFF;    // 打开XT2
    __bis_SR_register(SCG0);
    UCSCTL0 = DCO0 + DCO1 + DCO2 + DCO3 + DCO4;
    UCSCTL1 = DCORSEL_4;   // DCO频率范围在28.2MHZ以下
    UCSCTL2 = FLLD_5 + 1;  // D=16，N=1
    // n=8,FLLREFCLK时钟源为XT2CLK；DCOCLK=D*(N+1)*(FLLREFCLK/n);DCOCLKDIV=(N+1)*(FLLREFCLK/n);
    UCSCTL3 = SELREF_5 + FLLREFDIV_3;
    // ACLK的时钟源为DCOCLKDIV,MCLK\SMCLK的时钟源为DCOCLK
    UCSCTL4 = SELA_4 + SELS_3 + SELM_3;
    // ACLK由DCOCLKDIV的32分频得到，SMCLK由DCOCLK的2分频得到
    UCSCTL5 = DIVA_5 + DIVS_1;
}

void IO_Init(void) {
    P8DIR |= BIT1;
    P3DIR |= BIT7;
    P3DIR |= BIT6;
    P1DIR |= BIT0;

    P2DIR |= BIT5;
    P2SEL |= BIT5;

    P1DIR |= BIT5;
    P2DIR |= BIT4;
    P1OUT |= BIT5;
    P2OUT &= ~BIT4;

    P2OUT |= BIT3 + BIT6;
    P2REN |= BIT3 + BIT6;
}

int apInterface_adc(void) {
    if (!(P2IN & BIT3)) {
        __delay_cycles(5);
        if (!(P2IN & BIT3)) {
            return 1;
        }
    }
    if (!(P2IN & BIT6)) {
        __delay_cycles(5);
        if (!(P2IN & BIT6)) {
            return 2;
        }
    }

    return 0;
}
int main(void) {
    unsigned int Period = 512;  // PWM Period  CCR0
    int duty = 0;               // PWM duty cycle (%)
    int iValue = 0;
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
    ClockInit();
    IO_Init();

    TA2CTL = MC_1 + TASSEL_2 + TACLR;  // SMCLK(8M), up mode, clear TAR
    TA2CCR0 = Period;                  // PWM Period
    TA2CCTL2 = OUTMOD_7;               // CCR1 toggle/set
    TA2CCR2 = duty;                    // CCR1 PWM duty cycle  0

    __no_operation();  // For debugger
    while (1) {
        iValue = apInterface_adc();
        switch (iValue) {
            case 1:
                duty += 1;
                if (duty >= Period) {
                    duty = Period;
                }
                break;
            case 2:
                duty -= 1;
                if (duty <= 0) {
                    duty = 0;
                }
                break;
            default:
                break;
        }

        TA2CCR2 = duty;
        __delay_cycles(16000000 * 0.005);
    }
}
