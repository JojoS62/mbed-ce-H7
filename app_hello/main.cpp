#include "mbed.h"

int main()
{
    printf("mbed-ce hello-world\n");
    printf("Hello from "  MBED_STRINGIFY(TARGET_NAME) "\n");
    printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION); 	while(true) 

	{
		printf("Hello world from Mbed CE!\n");
		ThisThread::sleep_for(1s);
	}

	// main() is expected to loop forever.
	// If main() actually returns the processor will halt
	return 0;
}