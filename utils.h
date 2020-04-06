#ifndef _UTILS_H
#define _UTILS_H


#define LOW(arg)		((arg)& 0xFF)
#define SET_BITS(port, mask)		((port) |= (mask))
#define CLR_BITS(port, mask)	((port) &= ~(mask))
#define FLIP_BITS(port, mask)	((port) ^= (mask))

#define FORCE_BITS(port, mask, value)		(port) = ((port) & ~(mask)) | ((value)&(mask))
#define GPIO_PIN_DRV_TYPE(mask, type)		FORCE_BITS(GPIO->MODER, 3<<((pin)*2), mode<<((pin)*2))

#endif
