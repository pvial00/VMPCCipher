#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int P[256], temp;
int s = 0;

void ksa( unsigned char *K, unsigned char *iv, int keylen, int ivlen ) {
    int i, n, m;
    for (i = 0; i < 256; i++) {
        P[i] = i;
    }
    for (m = 0; m < 768; m++) {
        n = m % 256;
	s = P[(s + P[n] + K[m % keylen]) % 256];
        temp = P[n];
        P[n] = P[s];
        P[s] = temp;
    }
    for (m = 0; m < 768; m++) {
        n = m % 256;
        s = P[(s + P[n] + iv[m % ivlen]) % 256];
        temp = P[n];
        P[n] = P[s];
        P[s] = temp;
    }
}

unsigned char * crypt(unsigned char *inbuf, unsigned char *outbuf, int buflen) {
    int n = 0;
    int i;
    for (i = 0; i < buflen; i++) {
        s = P[(s + P[n]) % 256];
        outbuf[i] = inbuf[i] ^ P[(P[P[s]]+1) % 256];
        temp = P[n];
        P[n] = P[s];
        P[s] = temp;
        n = (n + 1) % 256;
    }
}
