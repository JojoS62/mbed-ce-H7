#include "mbed.h"
#include "fmc.h"
#include "sdram.h"

#define DBG_log printf

DigitalOut led(LED1);

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
  MPU_InitStruct.BaseAddress = 0xC0000000;   // SDRAM_ADDRESS;
  MPU_InitStruct.Size = MPU_REGION_SIZE_32MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}


ErrorStatus SDRAM_Test(void)
{
    uint32_t i = 0;        
    volatile uint16_t ReadData = 0; 
    volatile uint8_t  ReadData8 = 0;
    uint32_t ExecutionTime_Begin; 
    uint32_t ExecutionTime_End;  
    int  ExecutionTime;       
    float ExecutionSpeed;         

    DBG_log("\r\n -------------------- SDRAM 16 bit access -------------------\r\n"); 
    
    // -------------------- write ----------------------------- 
    ExecutionTime_Begin = HAL_GetTick(); // Start time

    // for (;;) {
        for (i = 0; i < SDRAM_Size / 2; i++) {
            *(__IO uint16_t *)(SDRAM_BANK_ADDR + 2 * i) = (uint16_t)i; // Write data to SDRAM
        }
    // }
    ExecutionTime_End = HAL_GetTick();                                       // End time
    ExecutionTime = ExecutionTime_End - ExecutionTime_Begin;                 // Elapsed time
    ExecutionSpeed = (float)SDRAM_Size / 1024 / 1024 / ExecutionTime * 1000; // Speed MB/S

    DBG_log("\r\nWrite 16-bit data , size: %d MB, elapsed time: %d ms, write speed: %.2f MB/s\r\n", SDRAM_Size / 1024 / 1024, ExecutionTime, ExecutionSpeed);

    // ----------------------------- read -------------------------------
    ExecutionTime_Begin = HAL_GetTick(); // Start time

    for (i = 0; i < SDRAM_Size / 2; i++)
    {
        ReadData = *(__IO uint16_t *)(SDRAM_BANK_ADDR + 2 * i); // Read data from SDRAM
    }

    ExecutionTime_End = HAL_GetTick();                                       // End time
    ExecutionTime = ExecutionTime_End - ExecutionTime_Begin;                 // Elapsed time
    ExecutionSpeed = (float)SDRAM_Size / 1024 / 1024 / ExecutionTime * 1000; // Speed MB/S

    DBG_log("\r\nRead 16-bit data, size: %d MB, elapsed time: %d ms, read speed: %.2f MB/s\r\n", SDRAM_Size / 1024 / 1024, ExecutionTime, ExecutionSpeed);


    DBG_log("\r\n -------------------- 16 Bit data validation  -------------------\r\n"); 
 
    // for (;;) {
        for (i = 0; i < SDRAM_Size / 2; i++) {
            ReadData = *(__IO uint16_t *)(SDRAM_BANK_ADDR + 2 * i); // Read data from SDRAM
            if (ReadData != (uint16_t)i)                            // Detect the data, if not equal, jump out of the function, return to the detection failure results.
            {
                DBG_log("\r\nSDRAM 16 Bit data validation failed! ReadData: %x i: %lx\r\n", ReadData, i);
                return ERROR; //Returns the failure flag
            }
        }
    // }    

    DBG_log("\r\nSDRAM 16-bit data validation pass!\r\n");
    
    DBG_log("\r\n -------------------- SDRAM 8 bit access  -------------------\r\n"); 
    
    // ------------------ write ----------------------------------
    ExecutionTime_Begin = HAL_GetTick(); // Start time

    for (i = 0; i < SDRAM_Size; i++)
    {
           *(__IO uint8_t *)(SDRAM_BANK_ADDR + i) = (uint8_t)i;
    }

    ExecutionTime_End = HAL_GetTick();                                       // End time
    ExecutionTime = ExecutionTime_End - ExecutionTime_Begin;                 // Elapsed time
    ExecutionSpeed = (float)SDRAM_Size / 1024 / 1024 / ExecutionTime * 1000; // Speed MB/S
    DBG_log("\r\nWrite 8-bit data, size: %d MB, elapsed time: %d ms, write speed: %.2f MB/s\r\n", SDRAM_Size / 1024 / 1024, ExecutionTime, ExecutionSpeed);

    // ---------------------- read ---------------------------------------------

    ExecutionTime_Begin = HAL_GetTick(); // Start time
    for (i = 0; i < SDRAM_Size; i++)
    {
        ReadData8 = *(__IO uint8_t *)(SDRAM_BANK_ADDR + i);
    }
  

    ExecutionTime_End = HAL_GetTick();                                       // End time
    ExecutionTime = ExecutionTime_End - ExecutionTime_Begin;                 // Elapsed time
    ExecutionSpeed = (float)SDRAM_Size / 1024 / 1024 / ExecutionTime * 1000; // Speed MB/S
    DBG_log("\r\nRead 8-bit data, size: %d MB, elapsed time: %d ms, read speed: %.2f MB/s\r\n", SDRAM_Size / 1024 / 1024, ExecutionTime, ExecutionSpeed);

   //----------------------- validate data -------------------------------

     for (i = 0; i < SDRAM_Size; i++)
    {
        ReadData8 = *(__IO uint8_t *)(SDRAM_BANK_ADDR + i);
        if (ReadData8 != (uint8_t)i) // Detect the data, if not equal, jump out of the function, return to the detection failure results.
        {
            DBG_log("\r\nSDRAM 8-Bit data validation failed!\r\n");
            return ERROR;
        }
    }
    
    DBG_log("\r\nSDRAM 8-Bit data validation pass!\r\n");


   return SUCCESS; 
}

int main()
{
    // MPU_Config();

    printf("mbed-ce hello-world\n");
    printf("Hello from "  MBED_STRINGIFY(TARGET_NAME) "\n");
    printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION); 	
	
	HAL_EnableCompensationCell(); 

    // HAL_SDRAM_MspInit(&hsdram1);    // calls FMC_MspInit for alternative pin config
	// MX_FMC_Init();

	// SDRAM_Initialization_Sequence(&hsdram1);
	// SDRAM_Test();

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