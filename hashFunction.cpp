#include "header.h"

template< typename T >
std::string int_to_hex( T i )
{
  std::stringstream stream;
  stream << std::setfill ('0') << std::setw(sizeof(T)*2)
         << std::hex << i;
  return stream.str();
}

//stringa convertina i unsgined int'a
unsigned int StringToInt(string input)
{
	return (unsigned int)input[0] | (unsigned int)(input[1] << 8) | (unsigned int)(input[2] << 16) | (unsigned int)(input[3] << 24);
}

//parotatina bitus
unsigned int leftRotate(unsigned int x, int n) {
  return (x << n) | (x >> (32-n));
}

unsigned int F(unsigned int x, unsigned int y, unsigned int z) {
  return x&y | ~x&z;
}

unsigned int G(unsigned int x, unsigned int y, unsigned int z) {
  return x&z | y&~z;
}

unsigned int H(unsigned int x, unsigned int y, unsigned int z) {
  return x^y^z;
}

unsigned int I(unsigned int x,unsigned int y, unsigned int z) {
  return y ^ (x | ~z);
}


void FF(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {
  a = leftRotate(a+ F(b,c,d) + x + ac, s) + b;
}

void GG(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {
  a = leftRotate(a + G(b,c,d) + x + ac, s) + b;
}

void HH(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {
  a = leftRotate(a + H(b,c,d) + x + ac, s) + b;
}

void II(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {
  a = leftRotate(a + I(b,c,d) + x + ac, s) + b;
}

string hashFunction(string input)
{
	string inputL = std::to_string((int)input.length());
	input.append(64 - input.length() % 64, '\0');
	input.append(64 - inputL.length(), '\0');
	input.append(inputL);

	unsigned int buf[4] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476}; //random reiksmes
	for (int i = 0; i < input.length() / 64; i++)
	{

		unsigned int block[16];
		for (int j = 0; j < 16; j++)
		{
			block[j] = StringToInt(input.substr(64 * i + 4 * j, 4));
		}
		unsigned int a = buf[0];
		unsigned int b = buf[1];
		unsigned int c = buf[2];
		unsigned int d = buf[3];

        //1 round
        FF (a, b, c, d, block[ 0], S11, 0xd76aa478);
        FF (d, a, b, c, block[ 1], S12, 0xe8c7b756);
        FF (c, d, a, b, block[ 2], S13, 0x242070db);
        FF (b, c, d, a, block[ 3], S14, 0xc1bdceee);
        FF (a, b, c, d, block[ 4], S11, 0xf57c0faf);
        FF (d, a, b, c, block[ 5], S12, 0x4787c62a);
        FF (c, d, a, b, block[ 6], S13, 0xa8304613);
        FF (b, c, d, a, block[ 7], S14, 0xfd469501);
        FF (a, b, c, d, block[ 8], S11, 0x698098d8);
        FF (d, a, b, c, block[ 9], S12, 0x8b44f7af);
        FF (c, d, a, b, block[10], S13, 0xffff5bb1);
        FF (b, c, d, a, block[11], S14, 0x895cd7be);
        FF (a, b, c, d, block[12], S11, 0x6b901122);
        FF (d, a, b, c, block[13], S12, 0xfd987193);
        FF (c, d, a, b, block[14], S13, 0xa679438e);
        FF (b, c, d, a, block[15], S14, 0x49b40821);

        //2 round
        GG (a, b, c, d, block[ 1], S21, 0xf61e2562);
        GG (d, a, b, c, block[ 6], S22, 0xc040b340);
        GG (c, d, a, b, block[11], S23, 0x265e5a51);
        GG (b, c, d, a, block[ 0], S24, 0xe9b6c7aa);
        GG (a, b, c, d, block[ 5], S21, 0xd62f105d);
        GG (d, a, b, c, block[10], S22,  0x2441453);
        GG (c, d, a, b, block[15], S23, 0xd8a1e681);
        GG (b, c, d, a, block[ 4], S24, 0xe7d3fbc8);
        GG (a, b, c, d, block[ 9], S21, 0x21e1cde6);
        GG (d, a, b, c, block[14], S22, 0xc33707d6);
        GG (c, d, a, b, block[ 3], S23, 0xf4d50d87);
        GG (b, c, d, a, block[ 8], S24, 0x455a14ed);
        GG (a, b, c, d, block[13], S21, 0xa9e3e905);
        GG (d, a, b, c, block[ 2], S22, 0xfcefa3f8);
        GG (c, d, a, b, block[ 7], S23, 0x676f02d9);
        GG (b, c, d, a, block[12], S24, 0x8d2a4c8a);

        //3 round
        HH (a, b, c, d, block[ 5], S31, 0xfffa3942);
        HH (d, a, b, c, block[ 8], S32, 0x8771f681);
        HH (c, d, a, b, block[11], S33, 0x6d9d6122);
        HH (b, c, d, a, block[14], S34, 0xfde5380c);
        HH (a, b, c, d, block[ 1], S31, 0xa4beea44);
        HH (d, a, b, c, block[ 4], S32, 0x4bdecfa9);
        HH (c, d, a, b, block[ 7], S33, 0xf6bb4b60);
        HH (b, c, d, a, block[10], S34, 0xbebfbc70);
        HH (a, b, c, d, block[13], S31, 0x289b7ec6);
        HH (d, a, b, c, block[ 0], S32, 0xeaa127fa);
        HH (c, d, a, b, block[ 3], S33, 0xd4ef3085);
        HH (b, c, d, a, block[ 6], S34,  0x4881d05);
        HH (a, b, c, d, block[ 9], S31, 0xd9d4d039);
        HH (d, a, b, c, block[12], S32, 0xe6db99e5);
        HH (c, d, a, b, block[15], S33, 0x1fa27cf8);
        HH (b, c, d, a, block[ 2], S34, 0xc4ac5665);

        //4 round
        II (a, b, c, d, block[ 0], S41, 0xf4292244);
        II (d, a, b, c, block[ 7], S42, 0x432aff97);
        II (c, d, a, b, block[14], S43, 0xab9423a7);
        II (b, c, d, a, block[ 5], S44, 0xfc93a039);
        II (a, b, c, d, block[12], S41, 0x655b59c3);
        II (d, a, b, c, block[ 3], S42, 0x8f0ccc92);
        II (c, d, a, b, block[10], S43, 0xffeff47d);
        II (b, c, d, a, block[ 1], S44, 0x85845dd1);
        II (a, b, c, d, block[ 8], S41, 0x6fa87e4f);
        II (d, a, b, c, block[15], S42, 0xfe2ce6e0);
        II (c, d, a, b, block[ 6], S43, 0xa3014314);
        II (b, c, d, a, block[13], S44, 0x4e0811a1);
        II (a, b, c, d, block[ 4], S41, 0xf7537e82);
        II (d, a, b, c, block[11], S42, 0xbd3af235);
        II (c, d, a, b, block[ 2], S43, 0x2ad7d2bb);
        II (b, c, d, a, block[ 9], S44, 0xeb86d391);

		buf[0] += a;
		buf[1] += b;
		buf[2] += c;
		buf[3] += d;
	}

	string returnas = int_to_hex(buf[0]) + int_to_hex(buf[1]) + int_to_hex(buf[2]) + int_to_hex(buf[3]);
	return returnas;
}
