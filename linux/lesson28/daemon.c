/*
    写一个守护进程，每隔2s获取一下系统时间，将这个时间写入到磁盘文件中。
*/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void work(int mun)
{

    time_t tm = time(NULL);
    struct tm *loc = localtime(&tm);
    char buf[1024];
    sprintf(buf, "%d-%d-%d %d:%d:%d\n", loc->tm_year + 1900, loc->tm_mon + 1,
            loc->tm_mday, loc->tm_hour, loc->tm_min, loc->tm_sec);

    int fd = open("time.txt", O_RDWR | O_CREAT | O_APPEND, 0664);
    write(fd, buf, strlen(buf));
    close(fd);
    // char * str = asctime(loc);
    // int fd = open("time.txt", O_RDWR | O_CREAT | O_APPEND, 0664);
    // write(fd ,str, strlen(str));
    // close(fd);
}
int main()
{

    pid_t pid = fork();

    if (pid > 0)
        exit(0);

    setsid();

    umask(022);

    chdir("/home/beijing");
    int fd = open("dev/null", O_RDWR);
    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);

    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = work;
    sigemptyset(&act.sa_mask);

    sigaction(SIGALRM, &act, NULL);

    struct itimerval val;
    val.it_value.tv_sec = 2;
    val.it_value.tv_usec = 0;
    val.it_interval.tv_sec = 2;
    val.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &val, NULL);

    while (1)
    {
        sleep(80);
    }

    return 0;
}