#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vmpc.h"

int main(int argc, char *argv[]) {
    FILE *infile, *outfile, *randfile;
    char *in, *out, *mode;
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
    printf("%ld\n", fsize);
    fseek(infile, 0, SEEK_SET);
    data = malloc(sizeof(data) * (fsize));
    buf = malloc(sizeof(buf) * (fsize));
    fread(data, 1, fsize, infile);
    printf("%lu\n", strlen(data));
        
    fclose(infile);
    outfile = fopen(out, "wb");
    if (strcmp(mode, "encrypt") == 0) {
       randfile = fopen("/dev/urandom", "r");
       ssize_t result = fread(&iv, 1, iv_length, randfile);
       fclose(randfile);
       printf("%lu\n", strlen(iv));
       ksa(K, iv);
       printf("%s\n", iv);
       crypt(data);
       fputs(iv, outfile);
    }
    else if (strcmp(mode, "decrypt") == 0) {
        memcpy(iv, &data[0], iv_length);
        unsigned char msg[(strlen(data) - iv_length)];
        memcpy(msg, &data[iv_length], (strlen(data) - iv_length));
        printf("%s\n", iv);
        ksa(K, iv);
        crypt(msg);
    }
    fputs(buf, outfile);
    fclose(outfile);
    free(data);
    free(buf);
    return 0;
}
