#include <stdio.h>
#include <stdlib.h>

#define max_string 200010
#define max_rank 200010
//#define debug_input
//#define debug_mergesort

struct rank_t{
    int j,rank;
};
typedef struct rank_t rank_t;

int string_index[max_string];
rank_t rank_arr[max_rank];

void mergesort(rank_t array[],int l,int r);
void merge(rank_t array[],int l,int mid,int r);

int main()
{
    int Testcase;
    scanf("%d",&Testcase);
    #ifdef debug_input
        printf("%d\n",Testcase);
    #endif // debug_input
    int i,j,k,n_string_index,k_output;
    for(i=0;i<Testcase;i++){
        scanf("%d %d",&n_string_index,&k_output);
        #ifdef debug_input
            printf("%d %d\n",n_string_index,k_output);
        #endif // debug_input
        for(j=0;j<n_string_index;j++){
            scanf("%d",&string_index[j]);
        }
        for(j=0;j<n_string_index;j++){
            rank_arr[j].j=j;
            scanf("%d",&rank_arr[j].rank);
        }
        #ifdef debug_input
            for(j=0;j<n_string_index;j++){
                printf("%d ",string_index[j]);
            }
            printf("\n");
            for(j=0;j<n_string_index;j++){
                printf("%d ",rank_arr[j].rank);
            }
            printf("\n");
        #endif // debug_input

        /*依據rank_arr的rank來排序*/
        mergesort(rank_arr,0,n_string_index-1);
        #ifdef debug_mergesort
            for(k=0;k<n_string_index;k++){
                printf("%d %d\n",rank_arr[k].j,rank_arr[k].rank);
            }
            printf("\n");
        #endif // debug_mergesort
        /*rank_arr完成排序*/
        /*利用rank_arr的j來作為檢查string的index*/

        int temp[200010]={0};
        int count=0;
        printf("%d ",string_index[rank_arr[0].j]);
        count++;
        temp[string_index[rank_arr[0].j]]=1;

        for(k=1;k<n_string_index;k++){
            if(string_index[rank_arr[k].j]!=string_index[rank_arr[k-1].j]){
                printf("%d ",string_index[rank_arr[k].j]);
                count++;
                temp[string_index[rank_arr[k].j]]=1;
            }
        }
        k=1;
        while(count<k_output){
            if(temp[k]==0){/*尚未用過*/
                printf("%d ",k);
                count++;
            }
            k++;
        }
        printf("\n");
    }

    //printf("Hello world!\n");
    return 0;
}

void mergesort(rank_t array[],int l,int r){
    if(l<r){
        int mid=l+(r-l)/2;
        mergesort(array,l,mid);
        mergesort(array,mid+1,r);

        merge(array,l,mid,r);
    }
}
void merge(rank_t array[],int l,int mid,int r){
    int i,j,k;
    int n1=mid-l+1;
    int n2=r-mid;

    rank_t*L=(rank_t*)malloc(n1*sizeof(rank_t));
    rank_t*R=(rank_t*)malloc(n2*sizeof(rank_t));

    for (i=0;i<n1;i++)
        L[i]=array[l+i];
    for (j=0;j<n2;j++)
        R[j]=array[mid+1+j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].rank <= R[j].rank)
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        array[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        array[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

