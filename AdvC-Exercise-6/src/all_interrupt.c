#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void SignalHandler(int sig)
{
    printf("\nReceived signal: %d (%s)\n", sig, strsignal(sig));
    if (sig == SIGQUIT)
    {
        exit(0);
    }
}

int main()
{
    int sig;

    for (sig = 1; sig < _NSIG; sig++)
    {
        signal(sig, SignalHandler);
    }

    while (1)
    {
        printf("Hello World\n");
        sleep(1);
    }

    return 0;
}