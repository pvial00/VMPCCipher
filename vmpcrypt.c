#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vmpc.h"

int main(int argc, char *argv[]) {
    FILE *infile, *outfile, *randfile;
    char *in, *out, *mode;
    unsigned char *data = NULL;
    unsigned char *buf = NULL;
    int x = 0;
    int ch;
    unsigned char *K;
    int key_length = 16;
    int iv_length = 16;
    unsigned char iv[iv_length];
    int i;
    mode = argv[1];
    in = argv[2];
    out = argv[3];
    K = argv[4];
    infile = fopen(in, "rb");
    fseek(infile, 0, SEEK_END);
    long fsize = ftell(infile);
    fseek(infile, 0, SEEK_SET);
    data = malloc(fsize);
    fread(data, 1, fsize, infile);
    fclose(infile);
    outfile = fopen(out, "wb");
    if (strcmp(mode, "encrypt") == 0) {
        buf = malloc(fsize);
        randfile = fopen("/dev/urandom", "rb");
        fread(&iv, iv_length, 1, randfile);
        fclose(randfile);
        ksa(K, iv, key_length, iv_length);
        crypt(data, buf, fsize);
        fwrite(iv, 1, iv_length, outfile);
        fwrite(buf, 1, fsize, outfile);
        free(data);
        free(buf);
    }
    else if (strcmp(mode, "decrypt") == 0) {
        for (i = 0; i < iv_length; i++) {
            iv[i] = data[i];
        }
        unsigned char *msg = NULL;
        msg = malloc((fsize - iv_length));
        for (i = iv_length; i < fsize; i++) {
            msg[x] = data[i];
            x++;
        }
        free(data);
        ksa(K, iv, key_length, iv_length);
        crypt(msg, msg, x);
        fwrite(msg, 1, x, outfile);
        free(msg);
    }
    fclose(outfile);
    return 0;
}
