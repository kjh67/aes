#include "aes.h"
#include <stdio.h>

namespace aes::mathfuncs {

byte GaloisByteMultiplication(byte p, byte q) {
    // Left-to-right multiplication algorithm, from Markus Kuhn's Cryptography
    // course notes (https://www.cl.cam.ac.uk/teaching/2324/Crypto/crypto-slides-4up.pdf)
    int modulus = 0x11B;
    int c;
    int a = q, b=p;
    if (a%2 == 1) {c=b;} else {c=0;}
    for (int i=1; i<8; i++) {
        if ((b>>7) % 2 == 1) {
            b = (b << 1) ^ modulus;
        }
        else {
            b = b << 1;
        }
        if ((a>>i) % 2 == 1) {
            c = c^b;
        }
    }
    return (byte) c;
}

byte GaloisMultiplicativeInverse(byte p) {
    // Adapted version of Euclid's Algorithm
    int u1 = 0, u3 = 0x11B, v1 = 1, v3 = p;
    while (v3 != 0) {
        int t1 = u1, t3 = u3;
        // Calculate difference in bit lengths; u3 will be at least v3
        int v3_copy = v3, u3_copy=u3;
        while (v3_copy != 0) {
            v3_copy = v3_copy>>1;
            u3_copy = u3_copy>>1;
        }
        int q = 0;
        while (u3_copy != 0) {
            u3_copy = u3_copy>>1;
            q++;
        }
        // Shift temps by the bit length difference
        if (q>=0) {
            t1 ^= v1<<q;
            t3 ^= v3<<q;
        }
        u1 = v1; u3 = v3;
        v1 = t1; v3 = t3;
    }
    // Final modulus if inverse is over 256
    if (u1 >= 0x100) u1 ^= 0x11B;
    return (byte) u1;
}

// In-place multiplication
void GaloisPolynomialMultiplication(byte* p, byte* q, byte* result) {
    // Performed by matrix multiplication, as earlier described
    byte a3 = p[3], a2 = p[2], a1 = p[1], a0 = p[0];
    byte b3 = q[3], b2 = q[2], b1 = q[1], b0 = q[0];
    for (int i=0; i<4; i++) {
        result[i] = GaloisByteMultiplication(a0, b0)
                    ^ GaloisByteMultiplication(a3,b1)
                    ^ GaloisByteMultiplication(a2,b2)
                    ^ GaloisByteMultiplication(a1,b3);
        // Rotate matrix row
        byte t = a0; a0 = a1;  a1 = a2; a2 = a3; a3 = t;
    }
}

byte AffineApplication(byte p, byte* affine_mat, byte affine_vec) {
    // matmul: XOR together all the bitwise ANDs
    // addition; XOR in the vector?
    return p;
}

}
