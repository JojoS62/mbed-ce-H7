#include "mbed.h"
#include "fmc.h"
#include "sdram.h"

#define DBG_log printf

DigitalOut led(LED1);

ErrorStatus SDRAM_Test(void)
{
    uint32_t i = 0;        
    uint16_t ReadData = 0; 
    uint8_t  ReadData8 = 0;
    uint32_t ExecutionTime_Begin; 
    uint32_t ExecutionTime_End;  
    int  ExecutionTime;       
    float ExecutionSpeed;         

    DBG_log("\r\n -------------------- SDRAM 16 bit access -------------------\r\n"); 
    
    // -------------------- write ----------------------------- 
    ExecutionTime_Begin = HAL_GetTick(); // Start time

    for (i = 0; i < SDRAM_Size / 2; i++)
    {
        *(__IO uint16_t *)(SDRAM_BANK_ADDR + 2 * i) = (uint16_t)i; // Write data to SDRAM
    }
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
 
    for (i = 0; i < SDRAM_Size / 2; i++)
    {
        ReadData = *(__IO uint16_t *)(SDRAM_BANK_ADDR + 2 * i); // Read data from SDRAM
        if (ReadData != (uint16_t)i)                            // Detect the data, if not equal, jump out of the function, return to the detection failure results.
        {
            DBG_log("\r\nSDRAM 16 Bit data validation failed!\r\n");
            return ERROR; //Returns the failure flag
        }
    }

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
    printf("mbed-ce hello-world\n");
    printf("Hello from "  MBED_STRINGIFY(TARGET_NAME) "\n");
    printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION); 	
	
	HAL_EnableCompensationCell(); 
	MX_FMC_Init();

	SDRAM_Initialization_Sequence(&hsdram1);
	SDRAM_Test();

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