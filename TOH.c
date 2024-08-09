#include<stdio.h>

void TOH(int n, char from, char to, char temp) {
    if (n==1) {
        printf("Disc %d moved from %c to %c\n",n, from,to);
        return;
    }
    else {
        TOH(n-1,from,temp,to);
        printf("Disc %d moved from %c to %c\n",n,from,to);
        TOH(n-1,temp,to,from);
    }
}
int main() {
    int n = 3;
    TOH(n, 'A', 'C', 'B');
}