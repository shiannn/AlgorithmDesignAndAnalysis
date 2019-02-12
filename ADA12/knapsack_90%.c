#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define max_things 1010
#define max_total 20010
#define inf 100000000000000

//#define debug_input
//#define debug_greedy
//#define debug_fixarray
//#define debug_dp
//#define debug_K
//#define debug_TLE

struct thing{
    int value,weight;
};
typedef struct thing thing;

thing thing_array[max_things];
struct ratio{
        int index;
        double ratio;
};
typedef struct ratio ratio;
ratio ratio_array[max_things];

struct fix{
    long long int value,weight;
};
typedef struct fix fix;
fix fix_array[max_things];

long long int dp[max_things][max_total];

//long long int trytrysee=0;
int max_choice=0;

void merge(ratio arr[], int l, int m, int r);
void mergeSort(ratio arr[], int l, int r);
void find(int total,int n_thing,int W_bags,long long int*ret_i,long long int*ret_j);
int main()
{
    int n_things,W_bags;
    scanf("%d %d",&n_things,&W_bags);
    int i;
    for(i=1;i<=n_things;i++){
        scanf("%d %d",&thing_array[i].value,&thing_array[i].weight);

        //trytrysee+=thing_array[i].value;
        if(thing_array[i].value>max_choice){
            max_choice=thing_array[i].value;
        }

        ratio_array[i].ratio=((double)thing_array[i].value)/((double)thing_array[i].weight);
        ratio_array[i].index=i;
    }

    mergeSort(ratio_array,1,n_things);

    long long int Vg=0,temp_W=0;
    /*greedy出來的V*/
    for(i=n_things;i>=1;i--){
        if(temp_W+thing_array[ratio_array[i].index].weight<=W_bags){
            Vg+=thing_array[ratio_array[i].index].value;
            temp_W+=thing_array[ratio_array[i].index].weight;
        }
        else{
            /*裝不下了*/
            if(max_choice>Vg){
                Vg=max_choice;
            }
            break;
        }
    }

    double K=((double)(Vg*0.1))/((double)n_things);


    /*將所有東西的價值除以K*/
    long long int total=0;
    for(i=1;i<=n_things;i++){
        //printf("before==%d\n",thing_array[i].value);
        fix_array[i].value=(thing_array[i].value/K);
        /*除以K可能會變大*/
        //printf("after==%d\n",fix_array[i].value);
        //total+=fix_array[i].value;
        fix_array[i].weight=thing_array[i].weight;
    }

    total=20*n_things;
    assert(total<20010);

    /*dp對fix_array*/
    /*dp[i][j]表示前i項物品要湊出j價值所需最少背包重量*/

    /*-----------------------------------*/
    /*填表*/
    dp[0][0]=0;
    long long int j;
    for(j=1;j<=total;j++){
        dp[0][j]=inf;
    }
    for(j=1;j<=total;j++){
        if(j==fix_array[1].value){
            dp[1][j]=fix_array[1].weight;
        }
        else{
            dp[1][j]=inf;
        }
    }
    for(i=1;i<=n_things;i++){
        dp[i][0]=0;
        /*湊出0價值都不需要負重*/
    }
    for(i=2;i<=n_things;i++){
        for(j=1;j<=total;j++){
            dp[i][j]=dp[i-1][j];//不選
            if((j-fix_array[i].value)>=0){//選
                if(dp[i-1][(j-fix_array[i].value)]+fix_array[i].weight<dp[i][j]){
                    dp[i][j]=dp[i-1][(j-fix_array[i].value)]+fix_array[i].weight;
                }
            }
        }
    }

    /*找出不超過負重的那格*/
    long long int ans_i,ans_j;
    find(total,n_things,W_bags,&ans_i,&ans_j);

    int ans[max_things]={0};
    int ans_count=0;
    long long int ptr=ans_j;
    for(i=ans_i;i>=1;i--){
        if(dp[i][ptr]<dp[i-1][ptr]){
            /*i物有在背包中*/
            ans[i]=1;
            ans_count++;
            ptr=ptr-fix_array[i].value;
        }
    }
    printf("%d\n",ans_count);
    for(i=1;i<=n_things;i++){
        if(ans[i]==1){
            printf("%d ",i);
        }
    }

    return 0;
}
void find(int total,int n_thing,int W_bags,long long int*ret_i,long long int*ret_j){
    int i,j;
    for(j=total;j>=0;j--){
        for(i=n_thing;i>=1;i--){
            if(dp[i][j]<=W_bags){
                //printf("i==%d j==%d %d\n",i,j,dp[i][j]);
                *ret_i=i;
                *ret_j=j;
                return;
            }
        }
    }
}
void mergeSort(ratio arr[], int l, int r)
{
    if (l < r)
    {

        int m = l+(r-l)/2;

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}
void merge(ratio arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    ratio* L=(ratio*)malloc(n1*sizeof(ratio));//[n1]
    ratio* R=(ratio*)malloc(n2*sizeof(ratio));//[n2]

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].ratio <= R[j].ratio)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
/*
5 7
1 3
4 1
6 5
7 3
8 3
*/
/*
4 6
3 20
4 50
6 70
2 90
230
*/

