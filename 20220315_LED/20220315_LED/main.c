/*
 * 20220315_LED.c
 *
 * Created: 2022-03-15 11:31:25
 * Author : user
 */ 

typedef uint8_t u8;

int main() {
	DDRB 0xFF;
	DDRA = 0x00;
	
	while (1) {
		u8 in = ~PINA;
		
		if (in & 0x8)
		PORTB = 0xFF;
		else if (in & 0x4)
		PORTB = 0x3F;
		else if (in & 0x2)
		PORTB = 0x0F;
		else if (in & 0x1)
		PORTB = 0x3;
		else
		PORTB = 0x00;
	}
}

//int main() {
//	DDRB = 0xFF;
//	
//	uint8_t LEDs = 0x55;
//	
//	while (1) {
//		PORTB = LEDs;
//		_delay_ms(1000);
//		LEDs <<= 1;
//		
//		PORTB = LEDs;
//		_delay_ms(1000);
//		LEDs >>= 1;
//	}
//}

// ¿Õº¹
//int main(void)
//{
////    DDRB = 1 << 2;
//	DDRB = 0xFF;
//
//	uint8_t LEDs;
//
//	while (1) {
//		LEDs = 1;
//
//		while (LEDs)
//		{
//			PORTB = LEDs;
//			LEDs <<= 1;
//
//			_delay_ms(100);
//		}
//
//		LEDs = 1 << 7;
//
//		while (LEDs)
//		{
//			PORTB = LEDs;
//			LEDs >>= 1;
//
//			_delay_ms(100);
//		}
//	}
//
//	return 0;
//}

