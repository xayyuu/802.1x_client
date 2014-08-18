#include "public.h"
#include <stdlib.h>
#include <string.h>

void enc_pass(char *original, char *out)
{
        memset(out, 0, 32);

        int i, len = strlen(original);
        for(i = 0; i < len; i++)
        {
                out[i] = (char)((signed char)original[i] ^ (signed char)(MAGIC + i));
         }
        out[i] = '\0';
}

void print_mac(char *src)
{
        char mac[32] = ""; 
        sprintf(mac, "%02x%02x%02x%02x%02x%02x",
                            (unsigned char)src[0],
                            (unsigned char)src[1],
                            (unsigned char)src[2],
                            (unsigned char)src[3],
                            (unsigned char)src[4],
                            (unsigned char)src[5]);

                printf("%s\n", mac);
}

