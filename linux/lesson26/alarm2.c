#include <stdio.h>
#include <unistd.h>

int main()
{
    alarm(1);
    int i = 1;
    while (1)
    {
        printf("%d\n", i++);
    }
    return 0;
}