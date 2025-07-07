#include<msp430.h>
//ADC 初始化
void ADInit(char channel)
{
    ADC12CTL0 |= ADC12MSC;                                      //自动循环采样转换
    ADC12CTL0 |= ADC12ON;                                       //启动ADC12模块
    ADC12CTL1 |= ADC12CONSEQ1 ;                                 //选择单通道循环采样转换
    ADC12CTL1 |= ADC12SHP;                                      //采样保持模式
    switch (channel)
    {
            case 0:ADC12MCTL0 |= ADC12INCH_0;   break;          //选择通道0，P6.0
            case 1:ADC12MCTL0 |= ADC12INCH_1;   break;          //选择通道1，P6.1
            case 2:ADC12MCTL0 |= ADC12INCH_2;   break;          //选择通道2，P6.2
            case 3:ADC12MCTL0 |= ADC12INCH_3;   break;          //选择通道3，P6.3
            case 4:ADC12MCTL0 |= ADC12INCH_4;   break;          //选择通道4，P6.4
            case 5:ADC12MCTL0 |= ADC12INCH_5;   break;          //选择通道5，P6.5  连接拨码电位器
            case 6:ADC12MCTL0 |= ADC12INCH_6;   break;          //选择通道6，P6.6
            case 12:ADC12MCTL0 |= ADC12INCH_12; break;          //选择通道12，P7.0
            default: ;break;
    }

    ADC12CTL0 |= ADC12ENC;
}
void InitAD()
{
    ADC12CTL0 |= ADC12MSC; //自动循环采样转换
    ADC12CTL0 |= ADC12ON; //启动ADC12模块
    ADC12CTL1 |= ADC12CONSEQ_3 ;//选择序列通道多次循环采样转换
    ADC12CTL1 |= ADC12SHP; //采样保持模式
    ADC12CTL1 |= ADC12CSTARTADD_0;
    ADC12MCTL0 |=ADC12INCH_1; //通道选择
    ADC12MCTL1 |=ADC12INCH_2+ADC12EOS;
    ADC12CTL0 |= ADC12ENC;
}
#define N_POINT 13
unsigned int  GetAD()
{
    unsigned int temp = 0;          //设置变量

    ADC12CTL0 |= ADC12SC;           //开始采样转换
    temp = ADC12MEM0;                //把结果赋给变量

    return temp;

}
unsigned int  GetADled()
{
    unsigned int led = 0;          //设置变量

    ADC12CTL0 |= ADC12SC;           //开始采样转换

    led = ADC12MEM1;                //把结果赋给变量

    return led;

}

unsigned int Filter( )
{
     char count,i,j;
     unsigned int value_buf[N_POINT];
     unsigned int temp=0;
     int sum=0;
      for (count=0;count<N_POINT;count++)
      {
            value_buf[count] = GetAD();
      }
      for (j=0;j<N_POINT-1;j++)
      {
            for (i=0;i<N_POINT-j-1;i++)
           {
                if ( value_buf[i]>value_buf[i+1] )
              {
                   temp = value_buf[i];
                   value_buf[i] = value_buf[i+1];
                   value_buf[i+1] = temp;
               }
           }
    }
    for(count=1;count<N_POINT-1;count++)
    sum += value_buf[count];
    //如果为2的n次方等分，则可以用>>n的减少计算量  a=a*8;  可以为 a=a<<3;
    //b=b/8; 可以为b=b>>3;
    return (unsigned int)(sum/(N_POINT-2));
}
unsigned int Filterled( )
{
     char count,i,j;
     unsigned int value_buf[N_POINT];
     unsigned int led=0;
     int sum=0;
      for (count=0;count<N_POINT;count++)
      {
            value_buf[count] = GetADled();
      }
      for (j=0;j<N_POINT-1;j++)
      {
            for (i=0;i<N_POINT-j-1;i++)
           {
                if ( value_buf[i]>value_buf[i+1] )
              {
                   led = value_buf[i];
                   value_buf[i] = value_buf[i+1];
                   value_buf[i+1] = led;
               }
           }
    }
    for(count=1;count<N_POINT-1;count++)
    sum += value_buf[count];
    //如果为2的n次方等分，则可以用>>n的减少计算量  a=a*8;  可以为 a=a<<3;
    //b=b/8; 可以为b=b>>3;
    return (unsigned int)(sum/(N_POINT-2));
}
unsigned int icnt;
void IO_Init(void)
{
    P3DIR |= BIT7;                            // 设置P3.7口为输出模式  控制LED灯
    P3OUT &= ~BIT7;                      // 选中P3.78.1为输出方式
    P1DIR |= BIT4;                            // 设置P1.4口为输出模式  控制LED灯
    P1OUT &= ~BIT4;                      // 选中P1.4口为输出方式
    P7DIR |= BIT4;                           // 设置P3.7口为输出模式  控制LED灯
    P7OUT &= ~BIT4;                     // 选中P7.4为输出方式
    P3DIR |= BIT6;                           // 设置P3.6口为输出模式  控制蜂鸣器
    P3OUT |= BIT6;                          // 选中P3.6为输出方式

    P2DIR &= ~(BIT3+BIT6);
    P2REN |= BIT3+BIT6;
    P2OUT |= BIT3+BIT6;

    P1DIR &=~( BIT3+BIT2);
    P1REN = BIT3+BIT2;
    P1OUT |= BIT3+BIT2;
    P6DIR |= BIT3;                          // 设置6.3口为输出模式  控制LED灯
    P6OUT &= ~BIT3;                          // 选中P6.3为输出方式
    P6DIR |= BIT4;                          // 设置P6.4口为输出模式  控制LED灯
    P6OUT &= ~BIT4;                          // 选中P6.4为输出方式
    P3DIR |= BIT5;                          // 设置P3.5口为输出模式  控制LED灯
    P3OUT &= ~BIT5;                          // 选中P3.5为输出方式
}

int apInterface_Key( void )
{
   return 0;
}

unsigned int ivalue = 0;                                             //设置判断变量
unsigned int a = 0;                                             //设置判断变量
/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    IO_Init();

    InitAD();
    TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //时钟为SMCLK,比较模式，开始时清零计数器
    TA0CCTL0 = CCIE;                        //比较器中断使能
    TA0CCR0  = 50000;                       //比较值设为50000，相当于50ms的时间间隔
    __enable_interrupt();


    while(1)
    {
        //ivalue = GetAD();   //没有软件滤波
        a = GetADled(); //没有软件滤波
        ivalue = Filter( );                                              //软件滤波
        if(ivalue>=900)
        {

            P1OUT |= BIT4;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //时钟为SMCLK,比较模式，开始时清零计数器
            icnt=0;

        }
        if(a>1950&a<2000)
        {
             P3OUT|=BIT7;
             P7OUT|=BIT4;
             P6OUT|=BIT3;
             P6OUT|=BIT4;
             P3OUT|=BIT5;
        }
        if(a>2000&a<2050);
        {
             P7OUT|=BIT4;
             P6OUT|=BIT3;
             P6OUT|=BIT4;
             P3OUT|=BIT5;
             P3OUT&=~BIT7;
        }
        if(a>2050&a<2100)
        {
            P6OUT|=BIT3;
            P6OUT|=BIT4;
            P3OUT|=BIT5;
            P3OUT&=~BIT7;
            P7OUT&=~BIT4;
        }
        if(a>2100&a<2150)
        {
            P6OUT|=BIT4;
            P3OUT|=BIT5;
            P3OUT&=~BIT7;
            P7OUT&=~BIT4;
            P6OUT&=~BIT3;
         }
        if(a>2150)
        {
            P3OUT|=BIT5;
            P3OUT&=~BIT7;
            P7OUT&=~BIT4;
            P6OUT&=~BIT3;
            P6OUT&=~BIT4;
        }

    }

}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    icnt++;
    if(icnt==40)
    {//2s关灯

       P1OUT &= ~BIT4;
       icnt=0;
    }
}
