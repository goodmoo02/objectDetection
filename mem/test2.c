#include <stdio.h>

int add(int a){
    return a;
}

int main(){
    int n = 5;
    add(n)++;
    printf("%d", add(n) + 1);
}