/*------------------------------------------------------------------------------*
 * File Name: OperatorsEx.c	 													*
 * Creation: GJL 1/27/05														*
 * Purpose: OriginC Source C file containing Operators examples.				*
 * Copyright (c) OriginLab Corp.	2005, 2006, 2007, 2008						*
 * All Rights Reserved															*
 *------------------------------------------------------------------------------*/

#include <Origin.h>

// Sample function to show arithmetic operators
void ArithmeticOperatorsEx()
{
	double a = 5, b = 2, c;
	int i;

	c = +a;
	printf("+a = +%g = %g\n", a, c); // Unary plus

	c = -a;
	printf("-a = -1 * %g = %g\n", a, c); // Unary minus

	c = a ^ b;
	printf("a ^ b = %g ^ %g = %g\n", a, b, c); // Exponentiation

	c = a * b;
	printf("a * b = %g * %g = %g\n", a, b, c); // Multiplication

	c = a / b;
	printf("a / b = %g / %g = %g\n", a, b, c); // Division

	c = a + b;
	printf("a + b = %g + %g = %g\n", a, b, c); // Addition

	c = a - b;
	printf("a - b = %g - %g = %g\n", a, b, c); // Subtraction

	c = a > b ? a - b : b - a; // if a > b then c = a - b else c = b - a
	printf("The positive difference between a and b is %g\n", c); // Arithmatic if

	i = 0;
	printf("i++ = %d++ = %d\n", i, i++); // Increment after (print)
	printf("i         = %d\n", i);       // Just print
	printf("++i = ++%d = %d\n", i, ++i); // Increment before (print)

	printf("i-- = %d-- = %d\n", i, i--); // Decrement after (print)
	printf("i         = %d\n", i);       // Just print
	printf("--i = --%d = %d\n", i, --i); // Decrement before (print)	
}

// Sample function to show relational operators
void RelationalOperatorsEx()
{
	double a = 5, b = 2;
	printf("a = %g and b = %g\n\n", a, b);

	if( b < a )
		printf("b is less than a\n");

	if( b <= a )
		printf("b is less than or equal to a\n");

	if( 5 <= a )
		printf("5 is less than or equal to a\n");

	if( 5 == a )
		printf("5 is equal to a\n");

	if( b != a )
		printf("b is not equal to a\n");

	if( a >= b )
		printf("a is greater than or equal to b\n");

	if( 5 >= a )
		printf("5 is greater than or equal to a\n");

	if( a > b )
		printf("a is greater than b\n");
}

// Sample function to show logical operators
void LogicalOperatorsEx()
{
	bool a = true, b = false;
	printf("a is true and b is false\n\n");

	if( !b )
		printf("!b (NOT b or opposite of b) evaluates to true\n");

	if( a && 1 )
		printf("a && 1 (a AND 1) evaluates to true because both a and 1 are true\n");

	if( a || b )
		printf("a || b (a OR b) evaluates to true because at least one operand (a) is true\n");
}


// Sample function to show bitwise operators
void BitwiseOperatorsEx()
{
	byte i = 5, j;
	printf("i = %d\n\n", i);

	j = ~i;
	printf("j = %d\n", j); // Bitwise NOT (NOT of 5 = 00000101 is 11111010=250)

	j = i << 2;
	printf("j = %d\n", j); // Shift left 2 bits (5 = 00000101 shifted left 2 bits is 00010100 = 20)

	j = j >> 1;
	printf("j = %d\n", j); // Shift right 1 bit (20 = 00010100 shifted right 1 bit is 00001010 = 10) 

	j = j >> 1;
	printf("j = %d\n", j); // Shift right 1 bit (10 = 00001010 shifted right 1 bit is 00000101 = 5) 

	j = i & 1;
	printf("j = %d\n", j); // Bitwise AND (5 = 00000101 AND 00000001 is 00000001 = 1)

	j = i | 2;
	printf("j = %d\n", j); // Bitwise OR (5 = 00000101 OR 00000010 is 00000111 = 7)

#pragma xor(push, FALSE) // Set ^ to Bitwise XOR
	j = i ^ 3;
	printf("j = %d\n", j); // Bitwise XOR (5 = 00000101 XOR 00000011 is 00000110 = 6)
#pragma xor(push, TRUE) // Set ^ back to default exponentiation
}

// Sample function to show assignment operators
void AssignmentOperatorsEx()
{
	double a = 5, b = 2, c;
	printf("a = %g and b = %g\n\n", a, b);

	c = b;
	printf("c = b means the value of b is assigned to c so that c = %g\n", c);

	c += a;
	printf("c += a means the value of c + a is assigned to c so that c = %g\n", c);

	c -= b;
	printf("c -= b means the value of c - b is assigned to c so that c = %g\n", c);

	c *= a;
	printf("c *= a means the value of c * a is assigned to c so that c = %g\n", c);

	c /= b;
	printf("c /= b means the value of c / b is assigned to c so that c = %g\n\n", c);

	c = 3;
	printf("c = %g and b = %g\n\n", c, b);

	c ^= b;
	printf("c ^= b means the value of c ^ b is assigned to c so that c = %g\n\n", c);

	int i = 5;
	printf("i = %d\n\n", i);

	i <<= 2;
	printf("i <<= 2 means shift the bits of i =  5 = 00101 left 2 positions to 10100 so that i = %d\n", i);

	i >>= 1;
	printf("i >>= 1 means shift the bits of i = 20 = 10100 right 1 position to 01010 so that i = %d\n", i);

	i >>= 1;
	printf("i >>= 1 means shift the bits of i = 10 = 01010 right 1 position to 00101 so that i = %d\n", i);
	
	i &= 1;
	printf("i &= 1 means the value of i & 1 (bitwise AND of i = 5 = 00101 and 1 = 00001) is assigned to i so that i = %d\n", i);

	i |= 2;
	printf("i |= 2 means the value of i | 2 (bitwise OR of i = 1 = 00001 and 2 = 00010) is assigned to i so that i = %d\n", i);
}
