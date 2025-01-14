#include "mbed.h"
#include "mbed_boot.h"
#include "sdram.h"
#include "display_ltdc.h"
#include "storage.h"

static void MPU_Config(void);

DigitalOut led(LED1);
DisplayLTDC display;

uint8_t imageBuf[800*480];

// load bitmap image from file
void load_bitmap(const char *filename) {
    led = !led;     // toggle LED

    Timer t;
    t.start();

    File bmpFile;

    int rc = bmpFile.open(&fs, filename, O_RDONLY);
    if (rc != 0) {
        printf("File not found\n");
        return;
    }

    // read header
    uint8_t header[54];
    bmpFile.read(header, sizeof(header));

    // check if it is a bitmap file
    if (header[0] != 'B' || header[1] != 'M') {
        printf("Not a bitmap file\n");
        return;
    }

    // read image size
    // uint32_t imageSize = header[0x22] | header[0x23] << 8 | header[0x24] << 16 | header[0x25] << 24;    
    uint32_t imageOffset = header[0x0A] | header[0x0B] << 8 | header[0x0C] << 16 | header[0x0D] << 24;
    // uint32_t width = header[0x12] | header[0x13] << 8 | header[0x14] << 16 | header[0x15] << 24;
    // uint32_t height = header[0x16] | header[0x17] << 8 | header[0x18] << 16 | header[0x19] << 24;
    // [[maybe_unused]] volatile uint16_t bitsPerPixel = header[0x1C] | header[0x1D] << 8;

    // read image data by using buffer in SRAM
    bmpFile.seek(imageOffset);

    #if 1
    uint8_t *imageData = (uint8_t*)(SDRAM_BANK_ADDR);

    uint32_t bufSize = sizeof(imageBuf);

    bmpFile.read(imageBuf, bufSize);
    memcpy(imageData, imageBuf, bufSize);

    bmpFile.read(imageBuf, bufSize);
    memcpy(imageData+bufSize, imageBuf, bufSize);
    #else
    uint8_t *imageData = (uint8_t*)(SDRAM_BANK_ADDR);
    uint8_t *imageBuf = imageData + (2UL << 20);

    uint32_t bufSize = 800*480*2;

    bmpFile.read(imageBuf, bufSize);
    memcpy(imageData, imageBuf, bufSize);
    #endif

    bmpFile.close();

    t.stop();

    printf("load_bitmap %s took %.3f ms\n", filename, t.elapsed_time().count() / 1000.0);
    
    // ThisThread::sleep_for(5s);
}

int main()
{
    MPU_Config();
    HAL_EnableCompensationCell();

    printf("Test FK743 5\" display\n");
    printf("Hello from "  MBED_STRINGIFY(TARGET_NAME) "\n");
    printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    printf("SystemCoreClock : %ld MHz  heap size: %ld\n\n", SystemCoreClock / 1'000'000, mbed_heap_size_total);

    mbed_stats_heap_t heap_info;
    mbed_stats_heap_get( &heap_info );
    printf("heap max: %ld current: %ld reserved: %ld alloc_cnt: %ld \n", heap_info.max_size, heap_info.current_size, heap_info.reserved_size, heap_info.alloc_cnt);

    printf("init SDRAM...\n");
    MX_FMC_Init();

    SDRAM_Initialization_Sequence(&hsdram1);
    SDRAM_Test();

    printf("init display...\n");
    display.LCD_Init();
    display.LCD_SetColor(LCD_YELLOW);
    display.LCD_DisplayString(0, 0, "Hello from Mbed");


    printf("starting mainloop, LED should blink\n\n");

    while(true)
    {
        // display.LCD_SetColor(LCD_RED);
        // display.LCD_FillRect(100, 100, 300, 200);

        load_bitmap("test.bmp");
        ThisThread::sleep_for(2000ms);

        load_bitmap("test1.bmp");
        ThisThread::sleep_for(2000ms);

        load_bitmap("test2.bmp");
        ThisThread::sleep_for(2000ms);

        load_bitmap("test3.bmp");
        ThisThread::sleep_for(2000ms);

        // // display.LCD_SetColor(LCD_GREEN);
        // // display.LCD_FillRect(100, 100, 300, 200);

        // ThisThread::sleep_for(500ms);

        // display.LCD_SetColor(LCD_BLUE);
        // display.LCD_FillRect(100, 100, 300, 200);


        // led = !led;     // toggle LED
        // ThisThread::sleep_for(500ms);
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

