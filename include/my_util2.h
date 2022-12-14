/*
 * my_util.h
 *
 * Created: 2022-06-11 22:51:23
 * Author : JMJ
 */ 

#ifndef MY_UTIL_H
#define MY_UTIL_H

#include <stdint.h>

// bit================================================

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

// PIN================================================

struct GPIO
{
	volatile uint8_t pin;
	volatile uint8_t ddr;
	volatile uint8_t port;	
};

// etc================================================

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