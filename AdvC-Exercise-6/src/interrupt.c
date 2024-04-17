#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void SignalHandler(int sig)
{
    switch (sig)
    {
    case SIGINT:
        printf("SIGINT detected\n");
        break;

    case SIGTSTP:
        printf("SIGTSTP detected\n");
        break;

    case SIGQUIT:
        printf("SIGQUIT detected\n");
        break;

    case 19:
        printf("SIGSTOP detected\n");
        break;

    case SIGCONT:
        printf("SIGCONT detected\n");
        break;

    case SIGTERM:
        printf("SIGTERM detected\n");
        break;

    case SIGUSR1:
        printf("SIGUSR1 detected\n");
        break;

    case SIGUSR2:
        printf("SIGUSR2 detected\n");
        exit(0);
        break;

    default:
        break;
    }
}

int main()
{
    int num;
    int pid = getpid();
    signal(SIGINT, SignalHandler);
    signal(SIGTSTP, SignalHandler);
    signal(SIGQUIT, SignalHandler);
    signal(SIGSTOP, SignalHandler);
    signal(SIGCONT, SignalHandler);
    signal(SIGTERM, SignalHandler);
    signal(SIGUSR1, SignalHandler);
    signal(SIGUSR2, SignalHandler);

    printf("User Defind ISRs: \n");
    printf("1. SIGINT\n2. SIGTSTP\n3. SIGQUIT\n4. SIGSTOP\n5. SIGCONT\n6. SIGTERM\n7. SIGUSR1\n8. SIGUSR2(for EXIT)\n");
    while (1)
    {
        printf("Enter ISR no.: ");
        scanf(" %d", &num);
        switch (num)
        {
        case 1:
            kill(pid, SIGINT);
            break;
        case 2:
            kill(pid, SIGTSTP);
            break;
        case 3:
            kill(pid, SIGQUIT);
            break;
        case 4:
            printf("SIGSTOP signal is a special signal that cannot be handled by user-defined signal handler functions.\n");
            // kill(pid, SIGSTOP);
            break;
        case 5:
            kill(pid, SIGCONT);
            break;
        case 6:
            kill(pid, SIGTERM);
            break;
        case 7:
            kill(pid, SIGUSR1);
            break;
        case 8:
            kill(pid, SIGUSR2);
            break;

        default:
            printf("Enter valid ISR no. !");
            break;
        }
    }
    return 0;
}