#include <stdio.h>
#include "sysfs_gpio.h"

int main()
{
	gpioOutput(4);
	gpioInput(17);
	gpioWrite(4,1);

	while(gpioRead(17) != 1)
	{
		printf("Does not == 1");
	}

	gpioWrite(4,0);

	return 0;
}