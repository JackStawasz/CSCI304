/* 
 * CS:APP Data Lab 
 * 
 * Jack Stawasz 931109548
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  // De Morgan's Law for "not" sign distribution
  return ~(~x | ~y);
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
	return	(x << 31) >> 31;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  n = n << 3; // Convert n bytes to n bits

  return	(x >> n) & 0xFF; // Extract the n-th byte via mask
}
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  return !(x ^ y);
}
/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
  unsigned int ones = ~0; // Start with unsigned 1s so shifting pads with 0s
  int lowMask = ones << lowbit; // Exclude bits lower than lownbit via 0 padding
  int highbit_from_end = (~highbit + 1) + 31; // Mimic subtraction (31 - highbit) via 2s complement conversion
  int highMask = ones >> highbit_from_end; // Exclude bits higher than highbit via 0 padding

  return lowMask & highMask; // Apply both masks
}
/* 
 * reverseBytes - reverse the bytes of x
 *   Example: reverseBytes(0x01020304) = 0x04030201
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int reverseBytes(int x) {
  int byte1 = (x << 24); // No mask needed, left shift pads with 0s
  int byte2 = (x << 8) & 0x00FF0000;
  int byte3 = (x >> 8) & 0x0000FF00;
  int byte4 = (x >> 24) & 0x000000FF; // Mask in case negative padding
  return byte1 | byte2 | byte3 | byte4;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  int negX = ~x + 1; // 2s complement of x
  int sign = (x | negX) >> 31; // C implementation returns -1 for neg and 0 for 0
  return sign + 1; // Convert sign to 0 or 1
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
  int negX = ~x + 1; // 2s complement of x
  return x & negX; // Only the lowest 1 is shared between x and -x
}
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
  return ~0;
}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  int maxNegative = 1 << 31; // 0x80000000, right-pads with 0s
  return ~maxNegative; // Negate the max negative int to get max positive int
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	int negN = ~n + 1;
	int shiftVal = 32 + negN;
	int shiftLeft = x << shiftVal;
	int shiftRight = shiftLeft >> shiftVal;
	int same = shiftRight ^ x;
	return !same;
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  // Get sign bits of x, y, and sum
  int sum = x + y;
  int signX = (x >> 31) & 1;
  int signY = (y >> 31) & 1;
  int signSum = (sum >> 31) & 1;

  // Overflow when x & y have same sign but sum is different
  int overflow = (!(signX ^ signY)) & (signX ^ signSum);
  return !overflow; // Return opposite of overflow
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) { // TODO -- EXPLAIN WITH COMMENTS OR SIMPLIFY!!!!
    int signX = (x >> 31) & 1;
    int signY = (y >> 31) & 1;
    int signDiff = signX ^ signY;

    int diff = x + (~y + 1);
    int isLess = (diff >> 31) & 1;
    int isEqual = !(x ^ y);

    return (signDiff & (!signX)) | ((!signDiff) & (!isLess) & (!isEqual));
}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
  int signBit = x >> 31; // Extract sign bit (32nd bit)
  return signBit & 1; // Remove implementation-dependent padding
}
/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x) {
  int fiveX = (x << 2) + x;
  int roundFix = (fiveX >> 31) & 7; // Negative numbers must round to 0, not clip toward -inf
  return (fiveX + roundFix) >> 3;
}
/* 
 * sm2tc - Convert from sign-magnitude to two's complement
 *   where the MSB is the sign bit
 *   Example: sm2tc(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int sm2tc(int x) {
	int signBit = x >> 31; //extend the sign bit to all bits. If x is negative, signBit is all 1s; otherwise, signBit is all 0s
	int maskSignBit = ~(1 << 31); //a mask to remove sign bit
	int reverse = ~(x & maskSignBit) + 1; //get 2's complement for negative cases
	return ((~signBit) & x) | (signBit & reverse); //if positive or 0, return x; else, return reverse.
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  // Edge cases
  if (x==0) {
    return 0; // Sign, exponent, data are all 0
  }

  // Extract sign
  int signBit = (x >> 31) & 1;
  if(signBit) {
    x = ~x + 1; // Convert negative to positive
  }
  signBit = signBit << 31; // Shift sign bit into IEEE 754 position

  // Extract exponent
  int msb = 31; // Start counting from the left
  while(!(x & (1 << msb)) && msb > 0) { // Decrement msb until the highest 1 bit is found
    msb--;
  }
  int exponent = msb + 127; // IEEE 754 bias=127
  exponent = exponent << 23; // Shift exponent into IEEE 754 position

  // Extract data component (mantissa)
  int mantissa = 0;
  if (msb <= 23) { // Exponent within precission range (all bits fit)
    mantissa = x << (23 - msb); // Fill mantissa with x's bits from left to right
  } else { // Exponent outside of precission range (needs to round)
    mantissa = 0;
  }

  // Merge x info into xFloat
  int xFloat = signBit | exponent | mantissa;
  return xFloat;
}
