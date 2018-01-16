#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int P[256];
int s;
int temp;

void ksa( unsigned char *K, unsigned char *iv ) {
    int i, n, m, c, z;
    c = strlen(K);
    z = sizeof(iv);
    for (i = 0; i < 256; i++) {
        P[i] = i;
    }
    for (m = 0; m < 768; m++) {
        n = m % 256;
	s = P[(s + P[n] + K[m % c]) % 256];
        temp = P[n];
        P[n] = P[s];
        P[s] = temp;
    }

    for (m = 0; m < 768; m++) {
        n = m % 256;
        s = P[(s + P[n] + iv[m % z]) % 256];
        temp = P[n];
        P[n] = P[s];
        P[s] = temp;
    }
}

unsigned char * crypt(unsigned char *inbuf, unsigned char *outbuf) {
    int n = 0;
    int i;
    int dlen = strlen(inbuf);
    printf("dlen%d\n", dlen);
    for (i = 0; i < dlen; i++) {
        s = P[((s + P[n]) % 256)];
        outbuf[i] = inbuf[i] ^ P[(P[P[s]]+1) % 256];
        temp = P[n];
        P[n] = P[s];
        P[s] = temp;
        n = (n + 1) % 256;
    }
}
