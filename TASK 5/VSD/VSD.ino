#include <ch32v00x.h>
#include <debug.h>

void GPIO_Config(void) {

    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // Enable GPIOD clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    // Configure GPIO Pin 0 and Pin 4 (Echo pin and Trigger pin) as Input Pull-Up
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // Configure GPIO Pin 2 and Pin 3 (Trigger and Buzzer control) as Output Push-Pull
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

int main(void) {

    uint8_t echo_status = 0;

    // Configure the NVIC for interrupt priority
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // Update system clock
    SystemCoreClockUpdate();

    // Initialize delay function
    Delay_Init();

    // Configure GPIO pins
    GPIO_Config();

    while(1) {

        // Generate a trigger pulse (10 ms width)
        GPIO_WriteBit(GPIOD, GPIO_Pin_2, SET);
        Delay_Ms(10); // Trigger pulse width
        GPIO_WriteBit(GPIOD, GPIO_Pin_2, RESET);

        // Read the echo pin (Pin 4) for signal indicating an object
        echo_status = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4);

        // If echo pin reads high, object detected near the sensor
        if (echo_status == 1) {

            // Activate the buzzer (Pin 3) when someone is near
            GPIO_WriteBit(GPIOD, GPIO_Pin_3, SET);  // Turn on buzzer

            // Keep the buzzer on for 2 seconds
            Delay_Ms(2000); 

            // Deactivate the buzzer
            GPIO_WriteBit(GPIOD, GPIO_Pin_3, RESET);  

            // Wait for 2 seconds before checking again
            Delay_Ms(2000); 
        }
    }
}
