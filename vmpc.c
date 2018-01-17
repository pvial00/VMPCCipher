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
    fread(data, 1, fsize, infile);
    printf("%lu\n", strlen(data));
    printf("%li\n", fsize);
    fclose(infile);
    outfile = fopen(out, "w");
    if (strcmp(mode, "encrypt") == 0) {
        buf = malloc(fsize);
        randfile = fopen("/dev/urandom", "rb");
        ssize_t result = fread(&iv, 1, iv_length, randfile);
        fclose(randfile);
        printf("%s\n", iv);
        printf("%lu\n", strlen(iv));
        ksa(K, iv);
        crypt(data, buf, fsize);
        fwrite(iv, 1, iv_length, outfile);
        printf("%lu\n", strlen(data));
        fwrite(buf, 1, fsize, outfile);
        free(data);
        free(buf);
    }
    else if (strcmp(mode, "decrypt") == 0) {
        /*memcpy(iv, &data[0], iv_length); */
        for (i = 0; i < iv_length; i++) {
            iv[i] = data[i];
        }
        printf("%s\n", iv);
        printf("%lu\n", strlen(iv));
        unsigned char *msg = NULL;
        msg = malloc((fsize - iv_length));
        for (i = iv_length; i < (fsize - iv_length); i++) {
            msg[x] = data[i];
            x++;
        }
        free(data);
        /* memcpy(msg, &data[iv_length], (fsize  - iv_length)); */
        /* memcpy(msg, &data[iv_length], (fsize - iv_length)); */
        ksa(K, iv);
        printf("%lu\n", strlen(msg));
        crypt(msg, msg, (fsize - iv_length));
        fwrite(msg, 1, (fsize - iv_length), outfile);
        free(msg);
    }
    fclose(outfile);
    return 0;
}
