/*
 * UART.h
 *
 * Created: 2022-05-05 21:29:45
 *  Author: JMJ
 */ 


#ifndef UART_H_
#define UART_H_

void UART0_init();
void UART0_transmit(char data);
unsigned char UART0_receive();

void UART1_init();
void UART1_transmit(char data);
unsigned char UART1_receive();

#endif /* UART_H_ */