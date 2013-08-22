#include <stdint.h>

/* converts 16bit color to 24bit */
uint16_t true2high(uint32_t tru)
{
	uint32_t r = tru/65536.0;
	uint32_t g = (tru - r*65536)/256.0;
	uint32_t b = tru - r*65536 - g*256;
	r = (r/256.0)*32.0;
	g = (g/256.0)*64.0;
	b = (b/256.0)*32.0;
	return r*32*64 + g*32 + b;
}

/* converts 24bit color to 16bit */
uint32_t high2true(uint16_t high)
{
	uint32_t r = high/2048.0;
	uint32_t g = (high - r*2048.0)/32.0;
	uint32_t b = high - r*2048.0 - g*32.0;
	r = (r/32.0)*256.0;
	g = (g/64.0)*256.0;
	b = (b/32.0)*256.0;
	return r*256*256 + g*256 + b;
}
