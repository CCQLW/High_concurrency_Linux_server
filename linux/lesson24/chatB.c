#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int ret = access("chat1", F_OK);
    if (ret == -1)
    {
        printf("管道不存在，正在创建有名管道 chat1 \n");
        ret = mkfifo("chat1", 0664);
        if (ret == -1)
        {
            perror("mkfifo");
            exit(0);
        }
    }

    ret = access("chat2", F_OK);
    if (ret == -1)
    {
        printf("管道不存在，正在创建有名管道 chat2 \n");
        ret = mkfifo("chat2", 0664);
        if (ret == -1)
        {
            perror("mkfifo");
            exit(0);
        }
    }

    int fdw = open("chat1", O_WRONLY);
    if (fdw == -1)
    {
        perror("open");
        exit(0);
    }
    printf("打开chat1成功，等待写入\n");

    int fdr = open("chat2", O_RDONLY);
    if (fdr == -1)
    {
        perror("open");
        exit(0);
    }
    printf("打开chat2成功，等待读取\n");

    char buf[128];

    while (1)
    {
        memset(buf, 0, 128);
        fgets(buf, 128, stdin);
        ret = write(fdw, buf, strlen(buf));
        if (ret == -1)
        {
            perror("write");
            exit(0);
        }

        memset(buf, 0, 128);
        ret = read(fdr, buf, 128);
        if (ret <= 0)
        {
            perror("read");
            exit(0);
        }
        printf("buf: %s", buf);
    }
    close(fdw);
    close(fdr);
}