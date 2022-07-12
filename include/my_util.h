/*
 * my_util.h
 *
 * Created: 2022-06-11 22:51:23
 * Author : JMJ
 */ 

#ifndef MY_UTIL_H
#define MY_UTIL_H

// bit================================================

#define nth(n) (1 << (n))

/* right rotate shift */
// WARNING: 'a' must be unsigned
#ifndef __GNUC__
#define rrs(a, n) ((((a) << (sizeof(a) * 8 - (n))) | ((a) >> (n))))
#else
#define rrs(dd, n) \
({ \
	_Static_assert((typeof(dd))-1 >= 0, \
	"argument 'dd' to 'rrs(dd, n) macro' must be unsigned"); \
	typeof(dd) d = (dd); \
	typeof(n) m = (n); \
	( (d << (sizeof(d) * 8 - m)) | (d >> m) ); \
})
#endif

/* left rotate shift */
#ifndef __GNUC__
#define lrs(a, n) ((((a) >> (sizeof(a) * 8 - (n))) | ((a) << (n))))
#else
#define lrs(dd, n) \
({ \
	typeof(dd) d = (dd); \
	typeof(n) m = (n); \
	( (d >> (sizeof(d) * 8 - m)) | (d << m) ); \
})
#endif

// control statement==================================

#define loop for(;;)
#define check_ret(bool, ...) if (bool) return __VA_ARGS__

// PIN================================================

/*
+ NOTE: The argument 'pin' must be &PINX(pointer).
+ WARNING: pin cannot be PINF(at least in one ATmega128A)
+ example: DDR(&PINA) => DDRA
*/
#define PIN(pin)	((pin)[0])
#define DDR(pin)	((pin)[1])
#define PORT(pin)	((pin)[2])

// etc================================================

/* 
**for software debouncing**

	+ arguments:
		source, flag, delay

	+ example:
		double_check(PINB, 0x01, 20)

*/
#define double_check(s, f, delay) ( \
	((s) & (f)) && \
	( _delay_ms(delay), ((s) & (f)) )\
)

#define min(a, b) \
({ \
	typeof(a) _a = (a); \
	typeof(b) _b = (b); \
	(_a < _b ? _a : _b); \
})

#define round_align(dst, divisor) \
({ \
	typeof(dst) a = (dst); \
	typeof(divisor) b = (divisor); \
	((a + b - 1) / b) * b; \
})

/* right rotate */
#define RR(d, n) (((d) + 1) % (n))
/* left rotate */
#ifndef __GNUC__
#define LR(d, n) (((d) + (n) - 1) % (n))
#else
#define LR(d, n)\
({\
	typeof(n) _n = (n);\
	((d) + _n - 1) % _n;\
})
#endif


#endif // MY_UTIL_H