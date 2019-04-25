/*******************************************************
用RFC1321源码移植到C51
变量使用自定义类型，U8,U16,U32,S8,S16,S32
使用大模式编译，否则需要将部分变量转移定义到xdata中才可以
2008-12-15 keil C51验证通过
祝庆
*******************************************************/
/* MD5C.C - RSA Data Security, Inc., MD5 message-digest algorithm */
//#include <stdio.h>

#include <Head.h>

#define U32 unsigned long
#define U16 unsigned int
#define U8 unsigned char
#define S32 long
#define S16 int
#define S8  char

typedef struct {
	U32 state[4];                                   // state (ABCD) 
	U32 count[2];        // number of bits, modulo 2^64 (lsb first) 
	U8 buffer[64];                         // input buffer 
} MD5_CTX;

void MD5Init (MD5_CTX *context);
void MD5Update (MD5_CTX *context, U8 *input, U16 inputlen);
void MD5Final (U8 digest[16], MD5_CTX *context);

void MD5Transform (U32 state[4], U8 block[64]);
void Encode (U8 *output,U32 *input, U16 len);
void Decode (U32 *output, U8 *input,U16 len);
void MD5_memcpy (U8 * output, U8 * input,U16 len);
void MD5_memset (U8 * output,int value,U16 len);


/* Constants for MD5Transform routine. */
#define SS11 7
#define SS12 12
#define SS13 17
#define SS14 22
#define SS21 5
#define SS22 9
#define SS23 14
#define SS24 20
#define SS31 4
#define SS32 11
#define SS33 16
#define SS34 23
#define SS41 6
#define SS42 10
#define SS43 15
#define SS44 21

//static unsigned char PADDING[64] = {
//U8 code PADDING[64] = {//可以使用只读数组，主要是考虑速度因素
U8 PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* F, G, H and I are basic MD5 functions.
 */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits.
 */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation.
 */
#define FF(a, b, c, d, x, s, ac) { \
 (a) += F ((b), (c), (d)) + (x) + (U32)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define GG(a, b, c, d, x, s, ac) { \
 (a) += G ((b), (c), (d)) + (x) + (U32)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) { \
 (a) += H ((b), (c), (d)) + (x) + (U32)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) { \
 (a) += I ((b), (c), (d)) + (x) + (U32)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }

/***********************************************************
MD5 initialization. Begins an MD5 operation, writing a new context.
***********************************************************/
void MD5Init (MD5_CTX *context)  /* context */
{
	context->count[0] = context->count[1] = 0;
	/* Load magic initialization constants.*/
	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
}

/***********************************************************
MD5 block update operation. Continues an MD5 message-digest
  operation, processing another message block, and updating the
  context.
***********************************************************/
void MD5Update (MD5_CTX * context, U8 *input, U16 inputLen)
{
	U16 i, index, partLen;

	/* Compute number of bytes mod 64 */
	index = (U16)((context->count[0] >> 3) & 0x3F);

	/* Update number of bits */
	if ((context->count[0] += ((U32)inputLen << 3))< ((U32)inputLen << 3))
		context->count[1]++;
	context->count[1] += ((U32)inputLen >> 29);

	partLen = 64 - index;

	/* Transform as many times as possible.*/
	if (inputLen >= partLen)
	{
		MD5_memcpy((U8 *)&context->buffer[index], (U8 *)input, partLen);
		MD5Transform (context->state, context->buffer);

		for (i = partLen; i + 63 < inputLen; i += 64)
			MD5Transform (context->state, &input[i]);

		index = 0;
	}
	else
		i = 0;
	/* Buffer remaining input */
	MD5_memcpy((U8 *)&context->buffer[index], (U8 *)&input[i],inputLen-i);
}

/*************************************************************
MD5 finalization. Ends an MD5 message-digest operation, writing the
  the message digest and zeroizing the context. 
**************************************************************/
void MD5Final (U8 digest[16],MD5_CTX * context)
{
	U8 bits[8];
	U16 index, padLen;

	/* Save number of bits */
	Encode (bits, context->count, 8);

	/* Pad out to 56 mod 64.*/
	index = (U16)((context->count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	MD5Update (context, PADDING, padLen);

	/* Append length (before padding) */
	MD5Update (context, bits, 8);
	/* Store state in digest */
	Encode (digest, context->state, 16);

	/* Zeroize sensitive information.*/
	MD5_memset ((U8 *)context, 0, sizeof (*context));
}

/************************************************************* 
MD5 basic transformation. Transforms state based on block. 
*************************************************************/
void MD5Transform (U32 state[4], U8 block[64])
{
	U32 a = state[0], b = state[1], c = state[2], d = state[3], x[16];

	Decode (x, block, 64);

	/* Round 1 */
	FF (a, b, c, d, x[ 0], SS11, 0xd76aa478); /* 1 */
	FF (d, a, b, c, x[ 1], SS12, 0xe8c7b756); /* 2 */
	FF (c, d, a, b, x[ 2], SS13, 0x242070db); /* 3 */
	FF (b, c, d, a, x[ 3], SS14, 0xc1bdceee); /* 4 */
	FF (a, b, c, d, x[ 4], SS11, 0xf57c0faf); /* 5 */
	FF (d, a, b, c, x[ 5], SS12, 0x4787c62a); /* 6 */
	FF (c, d, a, b, x[ 6], SS13, 0xa8304613); /* 7 */
	FF (b, c, d, a, x[ 7], SS14, 0xfd469501); /* 8 */
	FF (a, b, c, d, x[ 8], SS11, 0x698098d8); /* 9 */
	FF (d, a, b, c, x[ 9], SS12, 0x8b44f7af); /* 10 */
	FF (c, d, a, b, x[10], SS13, 0xffff5bb1); /* 11 */
	FF (b, c, d, a, x[11], SS14, 0x895cd7be); /* 12 */
	FF (a, b, c, d, x[12], SS11, 0x6b901122); /* 13 */
	FF (d, a, b, c, x[13], SS12, 0xfd987193); /* 14 */
	FF (c, d, a, b, x[14], SS13, 0xa679438e); /* 15 */
	FF (b, c, d, a, x[15], SS14, 0x49b40821); /* 16 */
 /* Round 2 */
	GG (a, b, c, d, x[ 1], SS21, 0xf61e2562); /* 17 */
	GG (d, a, b, c, x[ 6], SS22, 0xc040b340); /* 18 */
	GG (c, d, a, b, x[11], SS23, 0x265e5a51); /* 19 */
	GG (b, c, d, a, x[ 0], SS24, 0xe9b6c7aa); /* 20 */
	GG (a, b, c, d, x[ 5], SS21, 0xd62f105d); /* 21 */
	GG (d, a, b, c, x[10], SS22,  0x2441453); /* 22 */
	GG (c, d, a, b, x[15], SS23, 0xd8a1e681); /* 23 */
	GG (b, c, d, a, x[ 4], SS24, 0xe7d3fbc8); /* 24 */
	GG (a, b, c, d, x[ 9], SS21, 0x21e1cde6); /* 25 */
	GG (d, a, b, c, x[14], SS22, 0xc33707d6); /* 26 */
	GG (c, d, a, b, x[ 3], SS23, 0xf4d50d87); /* 27 */
	GG (b, c, d, a, x[ 8], SS24, 0x455a14ed); /* 28 */
	GG (a, b, c, d, x[13], SS21, 0xa9e3e905); /* 29 */
	GG (d, a, b, c, x[ 2], SS22, 0xfcefa3f8); /* 30 */
	GG (c, d, a, b, x[ 7], SS23, 0x676f02d9); /* 31 */
	GG (b, c, d, a, x[12], SS24, 0x8d2a4c8a); /* 32 */
	/* Round 3 */
	HH (a, b, c, d, x[ 5], SS31, 0xfffa3942); /* 33 */
	HH (d, a, b, c, x[ 8], SS32, 0x8771f681); /* 34 */
	HH (c, d, a, b, x[11], SS33, 0x6d9d6122); /* 35 */
	HH (b, c, d, a, x[14], SS34, 0xfde5380c); /* 36 */
	HH (a, b, c, d, x[ 1], SS31, 0xa4beea44); /* 37 */
	HH (d, a, b, c, x[ 4], SS32, 0x4bdecfa9); /* 38 */
	HH (c, d, a, b, x[ 7], SS33, 0xf6bb4b60); /* 39 */
	HH (b, c, d, a, x[10], SS34, 0xbebfbc70); /* 40 */
	HH (a, b, c, d, x[13], SS31, 0x289b7ec6); /* 41 */
	HH (d, a, b, c, x[ 0], SS32, 0xeaa127fa); /* 42 */
	HH (c, d, a, b, x[ 3], SS33, 0xd4ef3085); /* 43 */
	HH (b, c, d, a, x[ 6], SS34,  0x4881d05); /* 44 */
	HH (a, b, c, d, x[ 9], SS31, 0xd9d4d039); /* 45 */
	HH (d, a, b, c, x[12], SS32, 0xe6db99e5); /* 46 */
	HH (c, d, a, b, x[15], SS33, 0x1fa27cf8); /* 47 */
	HH (b, c, d, a, x[ 2], SS34, 0xc4ac5665); /* 48 */
	/* Round 4 */
	II (a, b, c, d, x[ 0], SS41, 0xf4292244); /* 49 */
	II (d, a, b, c, x[ 7], SS42, 0x432aff97); /* 50 */
	II (c, d, a, b, x[14], SS43, 0xab9423a7); /* 51 */
	II (b, c, d, a, x[ 5], SS44, 0xfc93a039); /* 52 */
	II (a, b, c, d, x[12], SS41, 0x655b59c3); /* 53 */
	II (d, a, b, c, x[ 3], SS42, 0x8f0ccc92); /* 54 */
	II (c, d, a, b, x[10], SS43, 0xffeff47d); /* 55 */
	II (b, c, d, a, x[ 1], SS44, 0x85845dd1); /* 56 */
	II (a, b, c, d, x[ 8], SS41, 0x6fa87e4f); /* 57 */
	II (d, a, b, c, x[15], SS42, 0xfe2ce6e0); /* 58 */
	II (c, d, a, b, x[ 6], SS43, 0xa3014314); /* 59 */
	II (b, c, d, a, x[13], SS44, 0x4e0811a1); /* 60 */
	II (a, b, c, d, x[ 4], SS41, 0xf7537e82); /* 61 */
	II (d, a, b, c, x[11], SS42, 0xbd3af235); /* 62 */
	II (c, d, a, b, x[ 2], SS43, 0x2ad7d2bb); /* 63 */
	II (b, c, d, a, x[ 9], SS44, 0xeb86d391); /* 64 */

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;

	/* Zeroize sensitive information.*/
	MD5_memset ((U8 *)x, 0, sizeof (x));
}

/************************************************************
Encodes input (U32) into output (unsigned char). Assumes 
len is a multiple of 4. 
************************************************************/
void Encode (U8 *output,U32 *input, U16 len)
{
	U16 i, j;

	for (i = 0, j = 0; j < len; i++, j += 4) 
	{
		output[j] = (U8)(input[i] & 0xff);
		output[j+1] = (U8)((input[i] >> 8) & 0xff);
		output[j+2] = (U8)((input[i] >> 16) & 0xff);
		output[j+3] = (U8)((input[i] >> 24) & 0xff);
	}
}

/************************************************************
Decodes input (unsigned char) into output (U32). Assumes 
  len is a multiple of 4.
*************************************************************/ 
void Decode (U32 *output, U8 *input,U16 len)
{
	U16 i, j;

	for (i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((U32)input[j]) | (((U32)input[j+1]) << 8) |
			(((U32)input[j+2]) << 16) | (((U32)input[j+3]) << 24);
}

/*************************************************************
Note: Replace "for loop" with standard memcpy if possible.
*************************************************************/
void MD5_memcpy (U8 * output, U8 * input,U16 len)
{
	U16 i;

	for (i = 0; i < len; i++)
		output[i] = input[i];
}

/*************************************************************
Note: Replace "for loop" with standard memset if possible. 
*************************************************************/
void MD5_memset (U8 * output,S16 value,U16 len)
{
	U16 i;

	for (i = 0; i < len; i++)
		((S8 *)output)[i] = (S8)value;
}
/************************************************************/
void MD5test(void)
{
	MD5_CTX contest;
//	U8 buffer[16];
	U8 digest[16];
//	U16 len;
	U8 i;
//	U8 *str;

	MD5Init(&contest);	//初始化结构体
	MD5Update(&contest,"852951",6);//填入被加密数据
	MD5Final(digest,&contest);//计算加密结果

  UART4Send_Data(digest,	16);   //测试用

	
//	for(i=0;i<16;i++)
		//;//printf("%02x",digest[i]);
}
/************************************************************/



























