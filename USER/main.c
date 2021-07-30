#include "driverlib.h"
#include "sys.h"
#include "delay.h"
//![Simple GPIO Config]
int main(void)
{	
		delay_init();
		NVIC_group_init();
    /* Halting the Watchdog */
    MAP_WDT_A_holdTimer();

    /* Configuring P1.0 as output */
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    while (1)
    {
        MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
				delay_ms(10000);
		}
}