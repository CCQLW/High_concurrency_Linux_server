#include <stdio.h>
int main()
{
    union
    {
        short value;
        char bytes[sizeof(short)];
    } test;
    test.value = 0x0102;
    printf("%d %d\n", test.bytes[0], test.bytes[1]);
    // if(test.bytes[0]==1){
    //     printf("大端\n");
    // }else{
    //     printf("小端\n");
    // }
}