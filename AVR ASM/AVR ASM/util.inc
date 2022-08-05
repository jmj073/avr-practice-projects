#ifndef __UTIL_INC__
#define __UTIL_INC__

.macro setStack // init_value, reg
	ldi @1, LOW(@0)
	out SPL, @1
	ldi @1, HIGH(@0)
	out SPH, @1
.endmacro

#endif /* __UTIL_INC__ */
