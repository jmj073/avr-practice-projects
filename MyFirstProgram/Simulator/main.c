/*
 * Simulator
 *
 * Created: 2022-04-30 21:39:22
 * Author : user
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	// DDRB |= (1 << DDB5);
	
	printf("%d\n\r", sizeof(char));
	printf("%d\n\r", sizeof(int));
	printf("%d\n\r", sizeof(short));
	printf("%d\n\r", sizeof(long));
	printf("%d\n\r", sizeof(float));
	printf("%d\n\r", sizeof(double));
	
	while(1);
	return 0;
}

