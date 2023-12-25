#include <stdio.h>
#include "sysfs_gpio.h"

int main()
{
	gpioOutput(4);
	gpioInput(17);
	gpioWrite(4,1);
	gpioWrite(4,0);

	int count = 0;

	while(gpioRead(17) != 1)
	{
		
	}

	while(gpioRead(17) != 0)
	{
		count++;
	}

	float cm = (30.48 * .08);
	float convert = count * cm;

	printf("%d revolution \n",count);
	printf("%.2f cm\n",convert);

	return 0;

}