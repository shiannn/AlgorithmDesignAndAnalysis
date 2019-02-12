#include <stdio.h>
#include <stdlib.h>

#define max_node 1030
//#define debug_input
//#define debug_mergesort
//#define debug_set

int graph[max_node][max_node];

struct edge{
    int src,dest,prize,time,divide;
};
typedef struct edge edge;

struct set{
    int rank,parent;
};
typedef struct set set;

set disjoint_set[max_node];
void Union(set disjoint_set[], int x, int y);
int find(set disjoint_set[], int i);

edge edge_array[max_node*max_node];

void mergesort(edge array[],int l,int r);
void merge(edge array[],int l,int mid,int r);

int gcd(int a,int b);

int check[max_node];
int main()
{
    int N_bits;
    scanf("%d",&N_bits);
    int i,j,temp,count_edge=0;
    for(i=1;i<=N_bits;i++){
        for(j=i;j<=N_bits;j++){
            scanf("%d",&temp);
            /*存到i,j和排序陣列*/
            graph[i][j+1]=temp;

            edge_array[count_edge].src=i;
            edge_array[count_edge].dest=j+1;
            edge_array[count_edge].prize=temp;

            count_edge++;
        }
    }
    count_edge=0;
    for(i=1;i<=N_bits;i++){
        for(j=i;j<=N_bits;j++){
            scanf("%d",&temp);
            /*存time到排序陣列*/
            edge_array[count_edge].time=temp;
            count_edge++;
        }
    }
    /*共有count_edge個邊*/

    #ifdef debug_input
        for(i=0;i<count_edge;i++){
            printf("src==%d dest==%d\n",edge_array[i].src,edge_array[i].dest);
            printf("prize==%d time==%d\n",edge_array[i].prize,edge_array[i].time);
        }
        printf("\n");
    #endif // debug_input

    /*sort edge_array*/
    mergesort(edge_array,0,count_edge-1);

    #ifdef debug_mergesort
        for(i=0;i<count_edge;i++){
            printf("src==%d dest==%d prize==%d time==%d\n"\
                   ,edge_array[i].src,edge_array[i].dest\
                   ,edge_array[i].prize,edge_array[i].time);
        }
    #endif // debug_mergesort

    for(i=1;i<=N_bits+1;i++){
        /*1~(N+1)的node*/
        disjoint_set[i].parent=i;
        disjoint_set[i].rank=0;
    }
    /*------------------------*/
    int ans=0;
    i=0;
    edge to_add;
    int already_add=0;
    while(already_add<N_bits){
        /*從sorted edge array中加入*/
        to_add=edge_array[i++];
        /*能幫助解密碼再選*/

        #ifdef debug_set
            printf("time==%d\n",to_add.time);
        #endif // debug_set
        /*判斷是否成環 不合樹*/

        int x = find(disjoint_set, to_add.src);
        int y = find(disjoint_set, to_add.dest);

        if (x != y)
        {
            ans+=to_add.time;
            already_add++;
            Union(disjoint_set, x, y);
            #ifdef debug_set
                printf("get");
            #endif // debug_set
        }
    }
    /*約分N_bits ans*/
    int prime=gcd(N_bits,ans);

    printf("%d %d\n",(N_bits/prime),(ans/prime));
    //printf("Hello world!\n");
    return 0;
}

int gcd(int a,int b)
{
    if (!b) return (a);
    return gcd(b, a % b);
}

void Union(set disjoint_set[], int x, int y)
{
    int xroot = find(disjoint_set, x);
    int yroot = find(disjoint_set, y);

    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if (disjoint_set[xroot].rank < disjoint_set[yroot].rank)
        disjoint_set[xroot].parent = yroot;
    else if (disjoint_set[xroot].rank > disjoint_set[yroot].rank)
        disjoint_set[yroot].parent = xroot;

    // If ranks are same, then make one as root and
    // increment its rank by one
    else
    {
        disjoint_set[yroot].parent = xroot;
        disjoint_set[xroot].rank++;
    }
}
int find(set disjoint_set[], int i)
{
    if (disjoint_set[i].parent != i)
        disjoint_set[i].parent = find(disjoint_set, disjoint_set[i].parent);

    return disjoint_set[i].parent;
}
void mergesort(edge array[],int l,int r){
    if(l<r){
        int mid=l+(r-l)/2;
        mergesort(array,l,mid);
        mergesort(array,mid+1,r);

        merge(array,l,mid,r);
    }
}
void merge(edge array[],int l,int mid,int r){
    int i,j,k;
    int n1=mid-l+1;
    int n2=r-mid;

    edge*L=(edge*)malloc(n1*sizeof(edge));
    edge*R=(edge*)malloc(n2*sizeof(edge));

    for (i=0;i<n1;i++)
        L[i]=array[l+i];
    for (j=0;j<n2;j++)
        R[j]=array[mid+1+j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].time <= R[j].time)
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
