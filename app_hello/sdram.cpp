//#include "fmc.h"
#include "sdram.h"

#define DBG_log printf

/* W9825G6 SDRAM */


void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram)
{
    FMC_SDRAM_CommandTypeDef Command;
    __IO uint32_t tmpmrd = 0;
    [[maybe_unused]] volatile HAL_StatusTypeDef rc = HAL_OK;

    /* Configure a clock configuration enable command */
    Command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;  // Enable SDRAM clock
    Command.CommandTarget = FMC_COMMAND_TARGET_BANK; // Select area to be controlled
    Command.AutoRefreshNumber = 1;
    Command.ModeRegisterDefinition = 0;

    rc = HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT); //  Send control command
    HAL_Delay(1);                                           //  Wait
	
    /* Configure a PALL (precharge all) command */
    Command.CommandMode = FMC_SDRAM_CMD_PALL;        // Precharge command
    Command.CommandTarget = FMC_COMMAND_TARGET_BANK; // Select area to be controlled
    Command.AutoRefreshNumber = 1;
    Command.ModeRegisterDefinition = 0;

    rc = HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT); //  Send control command

    /* Configure a Auto-Refresh command */
    Command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE; // Using Auto Refresh
    Command.CommandTarget = FMC_COMMAND_TARGET_BANK;      // Select area to be controlled
    Command.AutoRefreshNumber = 8;                        // Number of automatic refreshes
    Command.ModeRegisterDefinition = 0;

    rc = HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT); //Send control command

    /* Program the external memory mode register */
    tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2 |
             SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
             SDRAM_MODEREG_CAS_LATENCY_3 |
             SDRAM_MODEREG_OPERATING_MODE_STANDARD |
             SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

    Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;   // Load Mode Register Command
    Command.CommandTarget = FMC_COMMAND_TARGET_BANK; // Select area to be controlled
    Command.AutoRefreshNumber = 1;
    Command.ModeRegisterDefinition = tmpmrd;

    rc = HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT); // Send control command

    rc = HAL_SDRAM_ProgramRefreshRate(hsdram, 918); // Configuring refresh rate
}

HAL_StatusTypeDef SDRAM_Test(void)
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
                return HAL_ERROR; //Returns the failure flag
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
            return HAL_ERROR;
        }
    }
    
    DBG_log("\r\nSDRAM 8-Bit data validation pass!\r\n");


   return HAL_OK; 
}
