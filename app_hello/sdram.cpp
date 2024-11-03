#include "fmc.h"
#include "sdram.h"
//#include "debug.h"

/* W9825G6 SDRAM */

void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram)
{
    FMC_SDRAM_CommandTypeDef Command;
    __IO uint32_t tmpmrd = 0;

    /* Configure a clock configuration enable command */
    Command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;  // Enable SDRAM clock
    Command.CommandTarget = FMC_COMMAND_TARGET_BANK; // Select area to be controlled
    Command.AutoRefreshNumber = 1;
    Command.ModeRegisterDefinition = 0;

    HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT); //  Send control command
    HAL_Delay(1);                                           //  Wait
	
    /* Configure a PALL (precharge all) command */
    Command.CommandMode = FMC_SDRAM_CMD_PALL;        // Precharge command
    Command.CommandTarget = FMC_COMMAND_TARGET_BANK; // Select area to be controlled
    Command.AutoRefreshNumber = 1;
    Command.ModeRegisterDefinition = 0;

    HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT); //  Send control command

    /* Configure a Auto-Refresh command */
    Command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE; // Using Auto Refresh
    Command.CommandTarget = FMC_COMMAND_TARGET_BANK;      // Select area to be controlled
    Command.AutoRefreshNumber = 8;                        // Number of automatic refreshes
    Command.ModeRegisterDefinition = 0;

    HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT); //Send control command

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

    HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT); // Send control command

    HAL_SDRAM_ProgramRefreshRate(hsdram, 918); // Configuring refresh rate
}

