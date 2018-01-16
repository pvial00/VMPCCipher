#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vmpc.h"

int main(int argc, char *argv[]) {
    FILE *infile, *outfile, *randfile;
    char *in, *out, *mode;
    unsigned char *data = NULL;
    /* unsigned char *buf = NULL; */
    int x = 0;
    int ch;
    unsigned char *K;
    int iv_length = 16;
    unsigned char iv[iv_length];
    int i;
    randfile = fopen("/dev/urandom", "r");
    ssize_t result = fread(&iv, 1, iv_length, randfile);
    fclose(randfile);
    mode = argv[1];
    in = argv[2];
    out = argv[3];
    K = argv[4];
    infile = fopen(in, "rb");
    fseek(infile, 0, SEEK_END);
    long fsize = ftell(infile);
    fseek(infile, 0, SEEK_SET);
    data = malloc(fsize);
    /* buf = malloc(sizeof(buf) * (fsize)); */
    fread(data, 1, fsize, infile);
    printf("%lu\n", strlen(data));
    printf("%li\n", fsize);
        
    fclose(infile);
    outfile = fopen(out, "wb");
    if (strcmp(mode, "encrypt") == 0) {
        randfile = fopen("/dev/urandom", "r");
        ssize_t result = fread(&iv, 1, iv_length, randfile);
        fclose(randfile);
        ksa(K, iv);
        crypt(data, data);
        fwrite(iv, 1, strlen(iv), outfile);
        printf("%lu\n", strlen(data));
        fwrite(data, 1, fsize, outfile);
        free(data);
    }
    else if (strcmp(mode, "decrypt") == 0) {
        memcpy(iv, &data[0], iv_length);
        unsigned char msg[(fsize - iv_length)];
        for (i = iv_length; i < (fsize - iv_length); i++) {
            msg[x] = data[i];
            x++;
        }
        free(data);
        /* memcpy(msg, &data[iv_length], (fsize  - iv_length)); */
        /* memcpy(msg, &data[iv_length], (fsize - iv_length)); */
        ksa(K, iv);
        crypt(msg, msg);
        fwrite(msg, 1, (fsize - iv_length), outfile);
    }
    /* printf("%lu\n", strlen(buf));
    fwrite(buf, 1, strlen(buf), outfile); */
    fclose(outfile);
    return 0;
}
