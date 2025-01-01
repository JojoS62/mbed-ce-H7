#include "mbed.h"
#include "sdram.h"
#include "display_ltdc.h"
#include "storage.h"
#include "lvgl_interface.h"

static void MPU_Config(void);

DigitalOut led(LED1);

int main()
{
    // SCB_CleanDCache();
    // SCB_DisableDCache();

    MPU_Config();
    HAL_EnableCompensationCell();

    printf("Test FK743 lvgl\n");
    printf("Hello from "  MBED_STRINGIFY(TARGET_NAME) "\n");
    printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    printf("SystemCoreClock : %ld MHz\n\n", SystemCoreClock / 1'000'000);
    fflush(stdout);

    // mbed_stats_heap_t heap_info;
    // mbed_stats_heap_get( &heap_info );
    // printf("heap max: %ld current: %ld reserved: %ld alloc_cnt: %ld \n", heap_info.max_size, heap_info.current_size, heap_info.reserved_size, heap_info.alloc_cnt);

    // uint8_t *p = new uint8_t[1024];
    // for (int i = 0; i < 1024; i++) {
    //     p[i] = i;
    // }

    // mbed_stats_heap_get( &heap_info );
    // printf("heap max: %ld current: %ld reserved: %ld alloc_cnt: %ld \n", heap_info.max_size, heap_info.current_size, heap_info.reserved_size, heap_info.alloc_cnt);

    // uint8_t *p1 = new uint8_t[1024];
    // for (int i = 0; i < 1024; i++) {
    //     p1[i] = i;
    // }

    // mbed_stats_heap_get( &heap_info );
    // printf("heap max: %ld current: %ld reserved: %ld alloc_cnt: %ld \n", heap_info.max_size, heap_info.current_size, heap_info.reserved_size, heap_info.alloc_cnt);


    printf("init SDRAM...\n");
    fflush(stdout);

    MX_FMC_Init();

    SDRAM_Initialization_Sequence(&hsdram1);

    printf("starting mainloop, LED should blink\n\n");
    
    lvgl_interface_init();
    
    while(true)
    {
        ThisThread::sleep_for(200ms);
        led = !led;
    }

    return 0;
}

void MPU_Config(void)
{
    MPU_Region_InitTypeDef MPU_InitStruct = {0};
    /* Disables the MPU */
    HAL_MPU_Disable();
    /** Initializes and configures the Region and the memory to be protected
    */
    MPU_InitStruct.Enable = MPU_REGION_ENABLE;
    MPU_InitStruct.Number = MPU_REGION_NUMBER0;
    MPU_InitStruct.BaseAddress = 0x08000000;
    MPU_InitStruct.Size = MPU_REGION_SIZE_2MB;
    MPU_InitStruct.SubRegionDisable = 0x0;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
    MPU_InitStruct.AccessPermission = MPU_REGION_PRIV_RO;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
    MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
    HAL_MPU_ConfigRegion(&MPU_InitStruct);


    /* Configure the MPU attributes as WB for SDRAM */
    MPU_InitStruct.Enable = MPU_REGION_ENABLE;
    MPU_InitStruct.Number = MPU_REGION_NUMBER1;
    MPU_InitStruct.BaseAddress = SDRAM_BANK_ADDR;   // SDRAM_ADDRESS;
    MPU_InitStruct.Size = MPU_REGION_SIZE_32MB;
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
    MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
    MPU_InitStruct.SubRegionDisable = 0x00;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);

    /* Enables the MPU */
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

