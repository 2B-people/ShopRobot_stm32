#ifdef __cplusplus
extern "C" {
#endif

#include "millisecondtimer.h"
#include "delay.h"

volatile uint32_t _counter;

void initialise(void) 
{
	_counter = 0;
	SysTick_Config(SystemCoreClock / 1000000);
}

void delay(uint32_t millis) 
{
	// uint32_t target;

	// target = _counter + millis*1000;
	// while(_counter < target);
	delay_ms(millis);

} 

// void delay_ns(uint32_t millis)
// {
// 	uint32_t target;

// 	target = _counter + millis;
// 	while(_counter < target);	
// }
void SysTick_Handler(void) 
{
	_counter++;
}

uint32_t millis(void) 
{
	return _counter;
}

void reset(void) 
{
	_counter = 0;
}

#ifdef __cplusplus
}
#endif

