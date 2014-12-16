#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <iostream>
using namespace std;

int main()
{
    ///
    // SUBJECT: cpuid
    ///

    uint32_t uiEAX, uiEBX, uiECX, uiEDX;

    printf("+----\n");
    printf("| SUBJECT: cpuid\n");
    printf("+----\n");
    printf("\n");

    {
        uiEAX = 0;

        asm volatile
        (
            "cpuid" "\n"

            : "=a"(uiEAX), "=b"(uiEBX), "=c"(uiECX), "=d"(uiEDX)
            : "a"(uiEAX)
            :
        );
 
        printf("RESULT: (EAX=0h)\n");
        printf("  MAX INFO = %u\n", uiEAX);
        printf("  CPU = %c%c%c%c%c%c%c%c%c%c%c%c\n",
            (char)(uiEBX & 0xff), (char)((uiEBX >> 8) & 0xff), (char)((uiEBX >> 16) & 0xff), (char)((uiEBX >> 24) & 0xff),
            (char)(uiEDX & 0xff), (char)((uiEDX >> 8) & 0xff), (char)((uiEDX >> 16) & 0xff), (char)((uiEDX >> 24) & 0xff),
            (char)(uiECX & 0xff), (char)((uiECX >> 8) & 0xff), (char)((uiECX >> 16) & 0xff), (char)((uiECX >> 24) & 0xff));
        printf("\n");
    }

    {
        uiEAX = 1;

        asm volatile
        (
            "cpuid" "\n"

            : "=c"(uiECX), "=d"(uiEDX)
            : "a"(uiEAX)
            :
        );

        printf("RESULT: (EAX=1h)\n");
        printf("  SSE = %u\n", ((uiEDX >> 25) & 0x01));
        printf("  SSE2 = %u\n", ((uiEDX >> 26) & 0x01));
        printf("  SSE3 = %u\n", (uiECX & 0x01));
        printf("  supp SSE3 = %u\n", ((uiECX >> 9) & 0x01));
        printf("  SSE4.1 = %u\n", ((uiECX >> 19) & 0x01));
        printf("  SSE4.2 = %u\n", ((uiECX >> 20) & 0x01));
        printf("  OSXSAVE(AVX) = %u\n", ((uiECX >> 27) & 0x01));
        printf("  AVX = %u\n", ((uiECX >> 28) & 0x01));
        printf("\n");
    }

    {
        uiEAX = 7;
        uiECX = 0;

        asm volatile
        (
            "cpuid" "\n"

            : "=a"(uiEAX), "=b"(uiEBX)
            : "a"(uiEAX), "c"(uiECX)
            :
        );

        printf("RESULT: (EAX=7h, ECX=0h)\n");
        printf("  MAX LEAF = %u\n", uiEAX);
        printf("  AVX2 = %u\n", ((uiEBX >> 5) & 0x01));
        printf("\n");
    }
    
    return 0;
}
