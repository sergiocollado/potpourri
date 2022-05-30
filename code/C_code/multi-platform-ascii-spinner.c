// reference: https://codereview.stackexchange.com/questions/144121/multi-platform-ascii-spinner-in-c

#ifdef _WIN32
    #include <windows.h>
    #define sleepThr(x) Sleep(x)
#else
    #include <unistd.h>
    #define sleepThr(x) usleep((x) * 1000)
#endif

#include <stdio.h>

#define INTERVAL 200

int main()
{
    int counter;
    while (1)
    {
        for (counter = 0; counter < 4; counter++)
        {
            printf("\b%c", "|/-\\"[counter]);
            fflush(stdout);
            sleepThr(INTERVAL);
        }
    }

    return 0;
}
