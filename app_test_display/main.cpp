#include "mbed.h"


DigitalOut led(LED1);

int main()
{
    printf("Test FK743 5\" display\n");
    printf("Hello from "  MBED_STRINGIFY(TARGET_NAME) "\n");
    printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    printf("SystemCoreClock : %ld MHz\n\n", SystemCoreClock / 1'000'000);


    printf("starting mainloop, LED should blink\n");
    while(true)
    {
        ThisThread::sleep_for(500ms);
        led = !led;
    }

    return 0;
}
