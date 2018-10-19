#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mod 1000000007

#define max_index 1010
#define max_tight 2
#define max_bit3 3
#define max_bit6 3
#define max_bit9 3
#define max_mod33 33
//#define debug_input
//#define debug_backtrace
long int dfs(int index,char array[],int tight,int length,\
        int bit3,int bit6,int bit9,int mod33);
int char2int(char c);
char l[1010];
char r[1010];

long int dp[max_index][max_tight][max_bit3][max_bit6][max_bit9][max_mod33];
long int check[max_index][max_tight][max_bit3][max_bit6][max_bit9][max_mod33];

void initial(long int array[max_index][max_tight][max_bit3][max_bit6][max_bit9][max_mod33]){
    int i1,i2,i3,i4,i5,i6;
    for(i1=0;i1<=max_index-1;i1++){
        for(i2=0;i2<=max_tight-1;i2++){
            for(i3=0;i3<=max_bit3-1;i3++){
                for(i4=0;i4<=max_bit6-1;i4++){
                    for(i5=0;i5<=max_bit9-1;i5++){
                        for(i6=0;i6<=max_mod33-1;i6++){
                            array[i1][i2][i3][i4][i5][i6]=0;
                        }
                    }
                }
            }
        }
    }
}
int main()
{

    scanf("%s %s",l+1,r+1);
    l[0]='!';
    r[0]='!';
    #ifdef debug_input
    printf("%s\n%s\n",l+1,r+1);
    #endif // debug_input
    int lenr=strlen(r+1);
    int lenl=strlen(l+1);
    long int ansr=dfs(1,r,1,lenr,0,0,0,0);
    //printf("r==%d\n",ansr);

    /*
    memset(dp, 0, sizeof(dp));
    memset(check, 0, sizeof(dp));
    */
    initial(dp);
    initial(check);

    long int ansl=dfs(1,l,1,lenl,0,0,0,0);
    //printf("ansr==%ld\nansl==%ld\n",ansr,ansl);
    if(ansr<ansl){
        ansr+=mod;
    }
    long int ans=(ansr-ansl)%mod;
    printf("%ld\n",ans);

    return 0;
}
int main01(){
    char a1[200]="!1243567";
    int len=strlen(a1+1);
    printf("len==%d\n",len);
    int ans=dfs(1,a1,1,len,0,0,0,0);
    printf("%d\n",ans);
}
//字元轉成數字
long int dfs(int index,char array[],int tight,int length,\
        int bit3,int bit6,int bit9,int mod33){
    long int ret=0;
    if(index>length){
        if ((bit3%3==0)&&(bit6%3==0)&&(bit9%3==0)&&(mod33==0)){
            return 1;
        }
        return 0;
    }
    int i;
    if(tight==0){
        for(i=0;i<=9;i++){
            if(i==3){
                if(check[index+1][0][(bit3+1)%3][bit6][bit9][(mod33*10+i)%33]==0){
                    check[index+1][0][(bit3+1)%3][bit6][bit9][(mod33*10+i)%33]=1;
                    dp[index+1][0][(bit3+1)%3][bit6][bit9][(mod33*10+i)%33]=\
                        (dfs(index+1,array,0,length,\
                            (bit3+1)%3,bit6,bit9,(mod33*10+i)%33))%mod;

                }
                ret+=dp[index+1][0][(bit3+1)%3][bit6][bit9][(mod33*10+i)%33];
                ret=ret%mod;
            }
            else if(i==6){
                if(check[index+1][0][bit3][(bit6+1)%3][bit9][(mod33*10+i)%33]==0){
                    check[index+1][0][bit3][(bit6+1)%3][bit9][(mod33*10+i)%33]=1;
                    dp[index+1][0][bit3][(bit6+1)%3][bit9][(mod33*10+i)%33]=\
                      (dfs(index+1,array,0,length,\
                         bit3,(bit6+1)%3,bit9,(mod33*10+i)%33))%mod;

                }
                ret+=dp[index+1][0][bit3][(bit6+1)%3][bit9][(mod33*10+i)%33];
                ret=ret%mod;
            }
            else if(i==9){
                if(check[index+1][0][bit3][bit6][(bit9+1)%3][(mod33*10+i)%33]==0){
                    check[index+1][0][bit3][bit6][(bit9+1)%3][(mod33*10+i)%33]=1;
                    dp[index+1][0][bit3][bit6][(bit9+1)%3][(mod33*10+i)%33]=\
                        (dfs(index+1,array,0,length,\
                         bit3,bit6,(bit9+1)%3,(mod33*10+i)%33))%mod;
                }
                ret+=dp[index+1][0][bit3][bit6][(bit9+1)%3][(mod33*10+i)%33];
                ret=ret%mod;
            }
            else{
                if(check[index+1][0][bit3][bit6][bit9][(mod33*10+i)%33]==0){
                    check[index+1][0][bit3][bit6][bit9][(mod33*10+i)%33]=1;
                    dp[index+1][0][bit3][bit6][bit9][(mod33*10+i)%33]=\
                        (dfs(index+1,array,0,length,\
                         bit3,bit6,bit9,(mod33*10+i)%33))%mod;
                }
                ret+=dp[index+1][0][bit3][bit6][bit9][(mod33*10+i)%33];
                ret=ret%mod;
            }
        }
    }
    else if(tight==1){
        for(i=0;i<=char2int(array[index]);i++){
            if(i==char2int(array[index])){
                if(i==3){
                    if(check[index+1][1][(bit3+1)%3][bit6][bit9][(mod33*10+i)%33]==0){
                        check[index+1][1][(bit3+1)%3][bit6][bit9][(mod33*10+i)%33]=1;
                        dp[index+1][1][(bit3+1)%3][bit6][bit9][(mod33*10+i)%33]=\
                            (dfs(index+1,array,1,length,\
                               (bit3+1)%3,bit6,bit9,(mod33*10+i)%33))%mod;
                    }
                    ret+=dp[index+1][1][(bit3+1)%3][bit6][bit9][(mod33*10+i)%33];
                    ret=ret%mod;
                }
                else if(i==6){
                    if(check[index+1][1][bit3][(bit6+1)%3][bit9][(mod33*10+i)%33]==0){
                        check[index+1][1][bit3][(bit6+1)%3][bit9][(mod33*10+i)%33]=1;
                        dp[index+1][1][bit3][(bit6+1)%3][bit9][(mod33*10+i)%33]=\
                            (dfs(index+1,array,1,length,\
                                bit3,(bit6+1)%3,bit9,(mod33*10+i)%33))%mod;
                    }
                    ret+=dp[index+1][1][bit3][(bit6+1)%3][bit9][(mod33*10+i)%33];
                    ret=ret%mod;
                }
                else if(i==9){
                    if(check[index+1][1][bit3][bit6][(bit9+1)%3][(mod33*10+i)%33]==0){
                        check[index+1][1][bit3][bit6][(bit9+1)%3][(mod33*10+i)%33]=1;
                        dp[index+1][1][bit3][bit6][(bit9+1)%3][(mod33*10+i)%33]=\
                            (dfs(index+1,array,1,length,\
                                bit3,bit6,(bit9+1)%3,(mod33*10+i)%33))%mod;
                    }
                    ret+=dp[index+1][1][bit3][bit6][(bit9+1)%3][(mod33*10+i)%33];
                    ret=ret%mod;
                }
                else{
                    if(check[index+1][1][bit3][bit6][bit9][(mod33*10+i)%33]==0){
                        check[index+1][1][bit3][bit6][bit9][(mod33*10+i)%33]=1;
                        dp[index+1][1][bit3][bit6][bit9][(mod33*10+i)%33]=\
                            (dfs(index+1,array,1,length,\
                                bit3,bit6,bit9,(mod33*10+i)%33))%mod;
                    }
                    ret+=dp[index+1][1][bit3][bit6][bit9][(mod33*10+i)%33];
                    ret=ret%mod;
                }
            }
            else{//無限制
                if(i==3){
                    if(check[index+1][0][(bit3+1)%3][bit6][bit9][(mod33*10+i)%33]==0){
                        check[index+1][0][(bit3+1)%3][bit6][bit9][(mod33*10+i)%33]=1;
                        dp[index+1][0][(bit3+1)%3][bit6][bit9][(mod33*10+i)%33]=\
                            (dfs(index+1,array,0,length,\
                                (bit3+1)%3,bit6,bit9,(mod33*10+i)%33))%mod;
                    }
                    ret+=dp[index+1][0][(bit3+1)%3][bit6][bit9][(mod33*10+i)%33];
                    ret=ret%mod;
                }
                else if(i==6){
                    if(check[index+1][0][bit3][(bit6+1)%3][bit9][(mod33*10+i)%33]==0){
                        check[index+1][0][bit3][(bit6+1)%3][bit9][(mod33*10+i)%33]=1;
                        dp[index+1][0][bit3][(bit6+1)%3][bit9][(mod33*10+i)%33]=\
                            (dfs(index+1,array,0,length,\
                                bit3,(bit6+1)%3,bit9,(mod33*10+i)%33))%mod;
                    }
                    ret+=dp[index+1][0][bit3][(bit6+1)%3][bit9][(mod33*10+i)%33];
                    ret=ret%mod;
                }
                else if(i==9){
                    if(check[index+1][0][bit3][bit6][(bit9+1)%3][(mod33*10+i)%33]==0){
                        check[index+1][0][bit3][bit6][(bit9+1)%3][(mod33*10+i)%33]=1;
                        dp[index+1][0][bit3][bit6][(bit9+1)%3][(mod33*10+i)%33]=\
                            (dfs(index+1,array,0,length,\
                                bit3,bit6,(bit9+1)%3,(mod33*10+i)%33))%mod;
                    }
                    ret+=dp[index+1][0][bit3][bit6][(bit9+1)%3][(mod33*10+i)%33];
                    ret=ret%mod;
                }
                else{
                    if(check[index+1][0][bit3][bit6][bit9][(mod33*10+i)%33]==0){
                        check[index+1][0][bit3][bit6][bit9][(mod33*10+i)%33]=1;
                        dp[index+1][0][bit3][bit6][bit9][(mod33*10+i)%33]=\
                            (dfs(index+1,array,0,length,\
                                bit3,bit6,bit9,(mod33*10+i)%33))%mod;
                    }
                    ret+=dp[index+1][0][bit3][bit6][bit9][(mod33*10+i)%33];
                    ret=ret%mod;
                }
            }
        }
    }
    ret=ret%mod;
    return ret;
}
int char2int(char c){
    return (c-'0');
}
