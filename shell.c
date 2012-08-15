//
// shell.c
// written by esxgx 2012
//
#include "sha1.h"


#define SWAP(x)	(((x) >> 24) | (((x)&0x00FF0000) >> 8) | (((x)&0x0000FF00) << 8) | (x << 24))


uint32_t sha1(char *msg, int len)
{
	static uint32_t H[SHA1_HASH_SIZE];
	
	H[0] = 0x67452301;
	H[1] = 0xefcdab89;
	H[2] = 0x98badcfe;
	H[3] = 0x10325476;
	H[4] = 0xc3d2e1f0;
	
	msg[len] = 0x80;
	int pading_len = 64 - ((len + 1) & 63);
	if (pading_len < 8) pading_len += 64;
	int i;
	for(i=1; i<pading_len - 7; ++i)
		msg[len + i] = 0;
	((uint32_t *)&msg[len + i])[1] = SWAP(len << 3);

	sha1_step(H, (uint32_t *)msg, ((len + 1 + pading_len) / sizeof(uint32_t)) / SHA1_STEP_SIZE);
	return SWAP(H[0]);
}