#include <stdio.h>
#include <unistd.h>

int main(){
    alarm(10);
    int i =0;
    while(1){
        printf("%d\n",i);
    }
}