#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int n;
    n=(rand()%1000)+1;
    printf("%d\n",n);
    int i,a,b;
    for(i=0;i<n;i++){
        a=rand()%100000+1;
        //b=rand()%100000+1;
        printf("%d ",a);
    }
    printf("\n");
    int m=(rand()%1000000)+1;
    printf("%d\n",m);
    for(i=0;i<m;i++){
    	a=rand()%1000+1;
	printf("%d ",a);
    }
    printf("\n");
}
