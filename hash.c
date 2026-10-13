#include "hash.h"

unsigned char* SSHA(const unsigned char* msg, size_t length) {
    unsigned char A = 56;
    unsigned char B = 99;
    unsigned char C = 102;
    unsigned char D = 67;
    unsigned char E = 76;

    for (int i = 0; i < length; i++) {
        unsigned char g = (B & C) | (C & D);
        unsigned char old_A = A;
        unsigned char old_B = B;
        unsigned char old_E = E;

        A = old_E;
        B = old_A;
        C = (old_B >> 2) + old_E;
        D = (old_B >> 2) ^ (old_B >> 1);
        E = (g + (old_B >> 1) + msg[i]);
    }

    unsigned char* digest = (unsigned char*)malloc(DIGEST_SIZE * sizeof(unsigned char));
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;
    return digest;
}

int digest_equal(struct Digest digest1, struct Digest digest2) {
    return ((digest1.hash0 == digest2.hash0) &&
        (digest1.hash1 == digest2.hash1) &&
        (digest1.hash2 == digest2.hash2) &&
        (digest1.hash3 == digest2.hash3) &&
        (digest1.hash4 == digest2.hash4));

}

void printDigest(struct Digest digest) {
    printf("%d %d %d %d %d\n", digest.hash0, digest.hash1, digest.hash2, digest.hash3, digest.hash4);
}



//SSHA2 algorithm generated with Claude AI
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Returns a heap-allocated 40-character hex string (plus null terminator).
 * The caller must free() it. Returns NULL on allocation failure
 * or if msg is NULL while length > 0. */
char* SSHA2(const unsigned char* msg, size_t length)
{
    if (msg == NULL && length > 0)
        return NULL;

    /* Initial state (SHA-1 style IVs, since the diagram doesn't specify them) */
    uint32_t A = 0x67452301u;
    uint32_t B = 0xEFCDAB89u;
    uint32_t C = 0x98BADCFEu;
    uint32_t D = 0x10325476u;
    uint32_t E = 0xC3D2E1F0u;

    for (size_t i = 0; i < length; i++) {
        uint32_t shr2 = B >> 2;
        uint32_t shr1 = B >> 1;

        uint32_t newA = E;
        uint32_t newB = A;
        uint32_t newC = shr2 + E;
        uint32_t newD = shr2 ^ shr1;
        uint32_t newE = shr1 + ((B & C) | (D & C)) + (uint32_t)msg[i];

        A = newA;
        B = newB;
        C = newC;
        D = newD;
        E = newE;
    }

    char* out = (char*)malloc(41);
    if (out == NULL)
        return NULL;

    snprintf(out, 41, "%08x%08x%08x%08x%08x",
        (unsigned)A, (unsigned)B, (unsigned)C, (unsigned)D, (unsigned)E);

    return out;
}
