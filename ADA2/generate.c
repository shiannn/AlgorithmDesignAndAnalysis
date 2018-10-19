#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int n;
    n=(rand()%250)+1;
    printf("%d\n",n);
    int i,a,b;
    for(i=0;i<n;i++){
        a=rand()%10000+1;
        b=rand()%10000+1;
        printf("%d %d\n",a,b);
    }
}

