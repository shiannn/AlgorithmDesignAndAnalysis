#include <stdio.h>
#include <stdlib.h>

//int bits[30]={0};//存二進位
int main()
{
    int T_testcase;
    scanf("%d",&T_testcase);
    int i,j,N_cakes,sum;
    //int ptr;
    for(i=0;i<T_testcase;i++){
        scanf("%d",&N_cakes);
        sum=0;
        //ptr=0;
        while(N_cakes>0){
            if(N_cakes%2==1){
                //bits[ptr]=1;
                sum+=1;
                N_cakes/=2;
            }
            else if(N_cakes%2==0){
                //bits[ptr]=2;
                sum+=2;
                N_cakes-=2;
                N_cakes/=2;
            }
            //ptr+=1;
        }
        /*
        for(j=0;j<ptr;j++){
            sum+=bits[j];
        }
        */
        printf("%d\n",sum);
    }

    //printf("Hello world!\n");
    return 0;
}
