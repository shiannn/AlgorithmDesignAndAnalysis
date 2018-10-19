#include <stdio.h>
#include <stdlib.h>

#define max_edge 1010
#define mod 1000000007
//#define debug_input
unsigned long long int matrix[max_edge][max_edge];
unsigned long long int dp[max_edge][max_edge];

int illuminate(unsigned long long int input){
    unsigned long long int a=input;
    int num3=0,num6=0,num9=0;
    int digit=0;
    while(a>0){
        digit=a%10;
        if(digit==3){
            num3++;
        }
        else if(digit==6){
            num6++;
        }
        else if(digit==9){
            num9++;
        }
        a/=10;
    }
    if(input%33==0&&num3%3==0&&num6%3==0&&num9%3==0){
        return 1;
    }
    else{
        return 0;
    }
}
int main01(){
    unsigned long long int input;
    while(scanf("%llu",&input)!=EOF){
        printf("%d\n",illuminate(input));
    }
    return 0;
}
int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    unsigned long long input;
    int i,j,check;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            //scanf("%llu",&matrix[i][j]);
            scanf("%llu",&input);
            check=illuminate(input);
            if(check==1){
                matrix[i][j]=0;//不可走
            }
            else if(check==0){
                matrix[i][j]=1;//可走
            }
        }
    }
    /*先確認最左上角*/
    if(illuminate(matrix[0][0])==1){
        dp[0][0]=0;
    }
    else{
        dp[0][0]=1;//可走
    }
    for(j=1;j<m;j++){
        if(illuminate(matrix[0][j])==1){
            //不能走
            dp[0][j]=0;
        }
        else{
            dp[0][j]=dp[0][j-1];
        }
    }
    for(i=1;i<n;i++){
        if(illuminate(matrix[i][0])==1){
            //不能走
            dp[i][0]=0;
        }
        else{
            dp[i][0]=dp[i-1][0];
        }
    }
    for(i=1;i<n;i++){
        for(j=1;j<m;j++){
            if(illuminate(matrix[i][j])==1){
                dp[i][j]=0;//不能走
            }
            else{//可以走
                dp[i][j]=(dp[i-1][j]+dp[i][j-1])%mod;
            }
        }
    }
    printf("%llu\n",dp[n-1][m-1]);
    #ifdef debug_input
    printf("n==%d m==%d\n",n,m);
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            printf("%llu ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("dp\n");
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            printf("%llu ",dp[i][j]);
        }
        printf("\n");
    }
    #endif // debug_input

    //printf("Hello world!\n");
    return 0;
}

