#include "mbed.h"
#include "mbed_boot.h"


DigitalOut led(LED1);

int main()
{
    printf("mbed-ce test heap statistics\n");
    printf("Hello from "  MBED_STRINGIFY(TARGET_NAME) "\n");
    printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    printf("SystemCoreClock : %ld MHz  heap size: %ld\n\n", SystemCoreClock / 1'000'000, mbed_heap_size_total);

    mbed_stats_heap_t heap_info;
    mbed_stats_heap_get( &heap_info );
    printf("heap max: %ld current: %ld reserved: %ld alloc_cnt: %ld \n", heap_info.max_size, heap_info.current_size, heap_info.reserved_size, heap_info.alloc_cnt);

    uint8_t *p = new uint8_t[10*1024];
    for (int i = 0; i < 1024; i++) {
        p[i] = i;
    }

    mbed_stats_heap_get( &heap_info );
    printf("heap max: %ld current: %ld reserved: %ld alloc_cnt: %ld \n", heap_info.max_size, heap_info.current_size, heap_info.reserved_size, heap_info.alloc_cnt);

    uint8_t *p1 = new uint8_t[10*1024];
    for (int i = 0; i < 1024; i++) {
        p1[i] = i;
    }

    mbed_stats_heap_get( &heap_info );
    printf("heap max: %ld current: %ld reserved: %ld alloc_cnt: %ld \n", heap_info.max_size, heap_info.current_size, heap_info.reserved_size, heap_info.alloc_cnt);

    delete[] p1;
    mbed_stats_heap_get( &heap_info );
    printf("heap max: %ld current: %ld reserved: %ld alloc_cnt: %ld \n", heap_info.max_size, heap_info.current_size, heap_info.reserved_size, heap_info.alloc_cnt);

    delete[] p;
    mbed_stats_heap_get( &heap_info );
    printf("heap max: %ld current: %ld reserved: %ld alloc_cnt: %ld \n", heap_info.max_size, heap_info.current_size, heap_info.reserved_size, heap_info.alloc_cnt);


    printf("starting mainloop, LED should blink\n");
    while(true)
    {
        ThisThread::sleep_for(500ms);
        led = !led;
    }

    // main() is expected to loop forever.
    // If main() actually returns the processor will halt
    return 0;
}

