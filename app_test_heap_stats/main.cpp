#include "mbed.h"
#include "mbed_boot.h"
#include "malloc.h"

DigitalOut led(LED1);

void print_heap_info()
{
    mbed_stats_heap_t heap_info;
    mbed_stats_heap_get( &heap_info );
    printf("heap max: %ld current: %ld reserved: %ld overhead: %ld alloc_cnt: %ld \n\n", heap_info.max_size, heap_info.current_size, heap_info.reserved_size, heap_info.overhead_size, heap_info.alloc_cnt);
    fflush(stdout);
}

int main()
{
    print_heap_info();

    printf("\nmbed-ce test heap statistics\n");
    printf("Hello from "  MBED_STRINGIFY(TARGET_NAME) "\n");
    printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    printf("SystemCoreClock : %ld MHz  heap size: %ld\n\n", SystemCoreClock / 1'000'000, mbed_heap_size_total);

    print_heap_info();

    uint8_t *p1 = new uint8_t[10*1024];
    printf("p1: %p alloc 10240 bytes\n", p1);

    print_heap_info();

    uint8_t *p2 = new uint8_t[10*1024];
    printf("p2: %p alloc 10240 bytes\n", p2);
    print_heap_info();

    printf("delete p2\n");
    delete[] p2;
    print_heap_info();

    printf("delete p1\n");
    delete[] p1;
    print_heap_info();

    // test memalign
    size_t alloc_size = 2*1024 - 6;
    uint8_t *p3 = (uint8_t*)memalign(32, alloc_size);
    printf("p3: %p alloc %zu bytes\n", p3, alloc_size);
    print_heap_info();

    printf("free p3\n");
    free(p3);
    print_heap_info();

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

