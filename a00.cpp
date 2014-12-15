#include <stdio.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main()
{
    ///
    // SUBJECT: cpuid
    ///

    int iEAX, iEBX, iECX, iEDX;

    printf("+----\n");
    printf("| SUBJECT: cpuid\n");
    printf("+----\n");
    printf("\n");

    {
        iEAX = 0;

        asm volatile
        (
            "cpuid" "\n"

            : "=a"(iEAX), "=b"(iEBX), "=c"(iECX), "=d"(iEDX)
            : "a"(iEAX)
            :
        );
 
        printf("RESULT:\n");
        printf("  EAX = %d\n", iEAX);
        printf("  EBX-EDX-ECX = %c%c%c%c%c%c%c%c%c%c%c%c\n",
            (char)(iEBX & 0xff), (char)((iEBX >> 8) & 0xff), (char)((iEBX >> 16) & 0xff), (char)((iEBX >> 24) & 0xff),
            (char)(iEDX & 0xff), (char)((iEDX >> 8) & 0xff), (char)((iEDX >> 16) & 0xff), (char)((iEDX >> 24) & 0xff),
            (char)(iECX & 0xff), (char)((iECX >> 8) & 0xff), (char)((iECX >> 16) & 0xff), (char)((iECX >> 24) & 0xff));
        printf("\n");
    }

    {
        iEAX = 1;

        asm volatile
        (
            "cpuid" "\n"

            : "=c"(iECX), "=d"(iEDX)
            : "a"(iEAX)
            :
        );

        printf("RESULT:\n");
        printf("  SSE = %d\n", ((iEDX >> 25) & 0x01));
        printf("  SSE2 = %d\n", ((iEDX >> 26) & 0x01));
        printf("  SSE3 = %d\n", (iECX & 0x01));
        printf("  supp SSE3 = %d\n", ((iECX >> 9) & 0x01));
        printf("  SSE4.1 = %d\n", ((iECX >> 19) & 0x01));
        printf("  SSE4.2 = %d\n", ((iECX >> 20) & 0x01));
        printf("  AVX = %d\n", ((iECX >> 28) & 0x01));
        printf("\n");
    }

    {
        iEAX = 7;

        asm volatile
        (
            "cpuid" "\n"

            : "=b"(iEBX)
            : "a"(iEAX)
            :
        );

        printf("RESULT:\n");
        printf("  AVX2 = %d\n", ((iEBX >> 5) & 0x01));
        printf("\n");
    }
    
    return 0;
}
