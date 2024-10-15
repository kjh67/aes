#include <gtest/gtest.h>
#include "aes.h"
#include <stdio.h>

using namespace aes;

// Galois Multiplicative Inverse testing
TEST(GaloisInverseTest, CorrectlyComputesInverse) {
    // Check that the 0 case is accounted for correctly
    ASSERT_EQ(mathfuncs::GaloisMultiplicativeInverse((byte) 0), 0);
    // Check inversion of every possible byte value
    for (int i = 1; i<256; i++) {
        byte inv = mathfuncs::GaloisMultiplicativeInverse(i);
        ASSERT_EQ(mathfuncs::GaloisByteMultiplication(i, inv), 1);
    }
}


// Galois Polynomial Multiplication testing


// Affine application testing
