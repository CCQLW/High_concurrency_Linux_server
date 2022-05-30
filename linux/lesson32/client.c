// #include <stdio.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <string.h>
// #include <stdlib.h>

// int main()
// {
//     int fd = socket(AF_INET, SOCK_STREAM, 0);

//     if (fd == -1)
//     {
//         perror("socket");
//         exit(-1);
//     }

//     struct sockaddr_in serveraddr;
//     serveraddr.sin_family = AF_INET;
//     inet_pton(AF_INET, "43.138.33.159", &serveraddr.sin_addr.s_addr);
//     serveraddr.sin_port = htons(5001);
//     int ret = connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

//     if (ret == -1)
//     {
//         perror("connect");
//         exit(-1);
//     }

//     char *data = "sever";
//     write(fd, data, strlen(data));

//     char recvBuf[1024];
//     int len = read(fd, recvBuf, sizeof(recvBuf));
//     if (len == -1)
//     {
//         perror("read");
//         exit(-1);
//     }
//     else if (len > 0)
//     {
//         printf("recv data:%s\n", recvBuf);
//     }
//     else if (len == 0)
//     {
//         printf("sever closed..\n");
//     }

//     close(fd);
// }
// TCP通信的客户端

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{

    // 1.创建套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket");
        exit(-1);
    }

    // 2.连接服务器端
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, "81.71.120.235", &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(5001);
    int ret = connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    if (ret == -1)
    {
        perror("connect");
        exit(-1);
    }

    // 3. 通信
    char recvBuf[1024] = {0};
    while (1)
    {

        char *data = "hello,i am client";
        // 给客户端发送数据
        write(fd, data, strlen(data));

        // sleep(1);

        int len = read(fd, recvBuf, sizeof(recvBuf));
        if (len == -1)
        {
            perror("read");
            exit(-1);
        }
        else if (len > 0)
        {
            printf("recv server data : %s\n", recvBuf);
        }
        else if (len == 0)
        {
            // 表示服务器端断开连接
            printf("server closed...");
            break;
        }
    }

    // 关闭连接
    close(fd);

    return 0;
}