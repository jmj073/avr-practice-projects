/*
 * uart0.h
 *
 * Created: 2021-04-06 오후 2:48:30
 *  Author: kccistc
 */ 


#ifndef UART0_H_
#define UART0_H_

 #include <avr/io.h>
 
 extern char rxBuff[100];
 extern uint8_t rxFlag;
 //exturn
 
void UART0_Init(void);
void UART0_Transmit(unsigned int data);
unsigned char UART0_Receive(void);
void UART0_print_string(char *str);
void UART0_ISR_Process(void);



#endif /* UART0_H_ */