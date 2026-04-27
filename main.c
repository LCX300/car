#include "stm32f10x.h"
#include "Delay.h"
#include "CAN.h"
#include "Motor.h"

CanRxMsg RxMessage;

int main(void)
{
    uint8_t cmd;
    Motor_Init();
    CAN1_Init();

    while(1)
    {
        if(CAN_MessagePending(CAN1, CAN_FIFO0))
        {
            CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);

            if(RxMessage.StdId == 0x11 && RxMessage.DLC == 1)
            {
                cmd = RxMessage.Data[0];

                // 7号 = 倒车灯 + 电机转动
                if(cmd == 7)
                {
                    Motor_Forward();
                    Delay_ms(600);
                    Motor_Stop();
                }
            }
        }
    }
}

