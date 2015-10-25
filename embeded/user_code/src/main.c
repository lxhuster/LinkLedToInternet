/*
 *Abstract:Main Func
 */
#include <sys_init.h>
#include <app.h>

int main()
{
    Sys_Init();
    while(1)
		{
        led_app();
    }
    return 0;
}
