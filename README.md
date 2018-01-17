# VMPC Stream Cipher - Reference C Implementation  
Reference implementation of the VMPC Stream Cipher designed by Bartosz Zoltak

# Usage:  
#include "vmpc.h"  
int keylen = 16;  
int ivlen = 16;  
ksa(key, iv, keylen, ivlen);  
crypt(inbuf, outbuf, buflen);  
