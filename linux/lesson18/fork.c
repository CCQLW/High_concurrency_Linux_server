#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid > 0)
    {
        printf("pid :%d", pid);
        printf("parent, pid: %d,ppid: %d\n", getpid(), getppid());
    }
    else if (pid == 0)
    {
        printf("child, pid = %d  ppid =  %d\n", getpid(), getppid());
    }
    for (int i = 0; i < 100; i++)
    {
        printf("i: %d  pid = %d\n", i, getpid());
        // sleep(1);
    }
}
