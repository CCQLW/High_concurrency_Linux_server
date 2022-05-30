#include <stdio.h>
#include <unistd.h>

int main()
{

    int second = alarm(5);
    printf(" %d \n", second);
    sleep(2);
    second = alarm(2);
    printf(" %d \n", second);

    while (1)
    {
    }

    return 0;
}