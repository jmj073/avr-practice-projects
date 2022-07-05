/*
 * UART
 *
 * Created: 2022-04-27 22:38:02
 * Author : user
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>



#define forever while (1)


FILE OUTPUT = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);

// \r\n====================================
int main()
{
	UART1_init();
	stdout = &OUTPUT;
	
	while (1) {
		UART1_transmit(UART1_receive());
	}
	
	forever;
}

// �� ���(�Ҽ���)==========================
//int main(void)
//{
	//UART0_init(); // UART0 �ʱ�ȭ
	//stdout = &OUTPUT; // printf ��� ����
//
	//printf("** Data Types...\r\n");
	//printf("Integer: %d\r\n", 128);
	//printf("Float: %f\n\r", 3.14);
	//printf("String: %s\r\n", "hello, world!");
//
	//forever;
	//
	//return 0;
//}

// ���� ī��Ʈ==============================
//int main(void)
//{
     //UART0_init();
 	//stdout = &OUTPUT;
//
 	//unsigned int cnt = 0;
 	//while (1) {
 		//printf("%d\n\r", cnt++);
 		//_delay_ms(1000);
 	//}
//
 	//return 0;
//}

// ������ Ÿ�� ũ�� ���=====================
//int main(void)
//{
//	UART0_init();
//	stdout = &OUTPUT;
//
//	printf("** Size of Data Types\n\r");
//	printf("%d\n\r", sizeof(char));
//	printf("%d\n\r", sizeof(int));
//	printf("%d\n\r", sizeof(short));
//	printf("%d\n\r", sizeof(long));
//	printf("%d\n\r", sizeof(float));
//	printf("%d\n\r", sizeof(double));
//
//	while (1){}
//
//	return 0;
//}