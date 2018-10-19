#include <stdio.h>
#include <stdlib.h>

#define max_days 200010
//#define debug_input
//#define debug
#define NINF -2147483648
int reward_max(int everyday[],int days,int st,int ed);
int max2(int a,int b);
int max3(int a,int b,int c);

int main()
{
    int up_down_everyday[max_days]={0};
    int n_days;
    scanf("%d",&n_days);
    int i;
    for(i=0;i<n_days;i++){
        scanf("%d",&up_down_everyday[i]);
    }
    #ifdef debug_input
    printf("%d\n",n_days);
    for(i=0;i<n_days;i++){
        printf("%d ",up_down_everyday[i]);
    }
    printf("\n");
    #endif // debug_input
    int ans=reward_max(up_down_everyday,n_days,0,n_days-1);
    printf("%d\n",ans);
    //printf("Hello world!\n");
    return 0;
}
int reward_max(int everyday[],int days,int st,int ed){
    if(st==ed)return everyday[st];
    int m=(st+ed)/2;
    /*st~m m+1~ed*/
    /*左邊多1*/
    int left_max=reward_max(everyday,days,st,m);
    #ifdef debug
        printf("st==%d ed==%d\n",st,ed);
        printf("left_max==%d\n",left_max);
    #endif // debug
    int right_max=reward_max(everyday,days,m+1,ed);
    #ifdef debug
        printf("st==%d ed==%d\n",st,ed);
        printf("right_max==%d\n",right_max);
    #endif // debug
    int cross_max=0,sum=0,max=NINF;
    int i;
    for(i=m;i>=st;i--){
        sum=sum+everyday[i];
        if(sum>max){
            max=sum;
        }
        #ifdef debug
            printf("i==%d\n",i);
            printf("sum==%d lmax==%d\n",lsum,lmax);
        #endif // debug
    }
    sum=max;
    for(i=m+1;i<=ed;i++){
        sum=sum+everyday[i];
        if(sum>max){
            max=sum;
        }
        #ifdef debug
            printf("i==%d\n",i);
            printf("rsum==%d rmax==%d\n",rsum,rmax);
        #endif // debug
    }
    cross_max=max;
    #ifdef debug
        printf("st==%d ed==%d\n",st,ed);
        printf("cross_max==%d\n",cross_max);
    #endif // debug
    return max3(left_max,right_max,cross_max);
}
int max2(int a,int b){
    if(a>b)return a;
    return b;
}
int max3(int a,int b,int c){
    int temp=max2(a,b);
    return max2(temp,c);
}

