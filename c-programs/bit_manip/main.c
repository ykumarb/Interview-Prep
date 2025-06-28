/*
 * File: main.c
 *
 * Description: Bit manipulation - Generate xor from 1 to given n
 *
 * Author: Yupindra Kumar Balaji
 */

#include "main.h"

/* Entry point of program */
int main(void)
{
	int n = 0;
	int res = 0;
	BMP_INFO("Input n: ");
	BMP_SCANF("%d", &n);

	res = bmp_generate_xor_1ton(n);

	BMP_DEBUG("Res: %d\n", res);

	return 0;
}

int bmp_generate_xor_1ton(int n)
{
	int res = 0;

	/* Logic pattern:
	 * n = 5
	 * 1 ^ 2 = 3
	 * 1 ^ 2 ^ 3 = 3 ^ 3 = 0
	 * 1 ^ 2 ^ 3 ^ 4 = 0 ^ 4 = 4
	 * 1 ^ 2 ^ 3 ^ 4 ^ 5 = 4 ^ 5 = 1
	 * 1 ^ 2 ^ 3 ^ 4 ^ 5 ^ 6 = 1 ^ 6 = 7
	 * 1 ^ 2 ^ 3 ^ 4 ^ 5 ^ 6 ^ 7 = 7 ^ 7 = 0
	 *
	 * Intuition:
	 * From the above we can observe foll. The pattern repeats itself
	 * 1. n % 4 == 0 xor val: 4
	 * 2. n % 4 == 1 xor val: 1
	 * 3. n % 4 == 3 xor val: 0
	 * 4. n % 4 == 2 xor val: n + 1
	 */
	
	 /* Solution */
	 if (n % 4 == 0) return n;
	 else if (n % 4 == 1) return 1; 
	 else if (n % 4 == 2) return n + 1;
	 else if (n % 4 == 3) return 0; 

	return res;
}
