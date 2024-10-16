#include <gtest/gtest.h>
#include "aes.h"
#include <stdio.h>

using namespace aes;
using namespace aes::mathfuncs;

TEST(MathsFunctionTest, GaloisMultiplication) {
    FAIL();
}

// Galois Multiplicative Inverse testing
TEST(MathsFunctionTest, GaloisMultiplicativeInverse) {
    // Check that the 0 case is handled correctly
    EXPECT_EQ(GaloisMultiplicativeInverse(0), 0);
    // Check inversion of every possible byte value
    for (int i = 1; i<256; i++) {
        byte inv = GaloisMultiplicativeInverse(i);
        EXPECT_EQ(GaloisByteMultiplication(i, inv), 1);
    }
}

// Galois Polynomial Multiplication testing
TEST(MathsFunctionTest, GaloisPolynomialMultiplication) {
    // test example multiplication; multiply by one
    byte a[4] = {0x1, 0x0, 0x0, 0x0};
    byte b[4] = {0x5, 0x4, 0x3, 0x2};
    byte result[4];
    GaloisPolynomialMultiplication(a, b, result);
    EXPECT_EQ(result[0], 0x5);
    EXPECT_EQ(result[1], 0x4);
    EXPECT_EQ(result[2], 0x3);
    EXPECT_EQ(result[3], 0x2);

    // test example multiplication; more complicated
    // 16x3 + 243x2 + 137x + 25  *  197x3 + 201x2 + 3x + 100
    byte c[4] = {25, 137, 243, 16};
    byte d[4] = {100, 3, 201, 197};
    byte r0 = GaloisByteMultiplication(25,100) ^ GaloisByteMultiplication(16,3) ^ GaloisByteMultiplication(243,201) ^ GaloisByteMultiplication(137,197);
    byte r1 = GaloisByteMultiplication(137,100) ^ GaloisByteMultiplication(25,3) ^ GaloisByteMultiplication(16,201) ^ GaloisByteMultiplication(243,197);
    byte r2 = GaloisByteMultiplication(243,100) ^ GaloisByteMultiplication(137,3) ^ GaloisByteMultiplication(25,201) ^ GaloisByteMultiplication(16,197);
    byte r3 = GaloisByteMultiplication(16,100) ^ GaloisByteMultiplication(243,3) ^ GaloisByteMultiplication(137,201) ^ GaloisByteMultiplication(25,197);
    GaloisPolynomialMultiplication(c, d, result);
    EXPECT_EQ(result[0], r0);
    EXPECT_EQ(result[1], r1);
    EXPECT_EQ(result[2], r2);
    EXPECT_EQ(result[3], r3);
}

// Affine application testing
TEST(MathsFunctionTest, AffineApplication) {
    FAIL();
}

TEST(MathsFunctionTest, AffineInversion) {
    FAIL();
}

