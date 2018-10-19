#include <stdio.h>
#include <stdlib.h>

#define Max_points 100010
struct points{
    int x,y;
};
typedef struct points points;

struct points point_array[Max_points];
void mergeSort(struct points arr[], int l, int r);
void merge(struct points arr[], int l, int m, int r);
void merge_Y(struct points arr[], int l, int m, int r);
void mergeSort_Y(struct points arr[], int l, int r);
unsigned long long int sum_area(struct points arr[],int st,int ed);

void main01(struct points point_array[],int N_points){
    /*
    int N_points;
    scanf("%d",&N_points);
    int i;
    for(i=0;i<N_points;i++){
        scanf("%d %d",&point_array[i].x,&point_array[i].y);
    }
    */
    int i,j;
    unsigned long long int sum=0;
    for(i=0;i<N_points;i++){
        for(j=0;j<i;j++){
            sum+=(abs(point_array[i].x-point_array[j].x))*abs((point_array[i].y-point_array[j].y));
        }
    }
    printf("%llu\n",sum);
    return;
}


int main()
{
    int N_points;
    scanf("%d",&N_points);
    int i;
    for(i=0;i<N_points;i++){
        scanf("%d %d",&point_array[i].x,&point_array[i].y);
    }
    //main01(point_array,N_points);
    #ifdef debug_input
    printf("%d\n",N_points);
    for(i=0;i<N_points;i++){
        printf("%d %d\n",point_array[i].x,point_array[i].y);
    }
    #endif // debug_input
    /*照x座標排好*/
    mergeSort(point_array,0,N_points-1);
    #ifdef debug_input
    printf("%d\n",N_points);
    for(i=0;i<N_points;i++){
        printf("%d %d\n",point_array[i].x,point_array[i].y);
    }
    #endif // debug_input
    unsigned long long int ans=sum_area(point_array,0,N_points-1);
    /*int不一定足夠*/
    printf("%llu\n",ans);
    return 0;

}
unsigned long long int sum_area(struct points arr[],int st,int ed){
    #ifdef debug_recur
        printf("here\n");
        printf("st==%d ed==%d\n",st,ed);
    #endif // debug
    if(st==ed){
        return 0;
    }
    int m=st+(ed-st)/2;//奇數左邊多一個
    unsigned long long int left_sum,right_sum;
    left_sum=sum_area(arr,st,m);
    right_sum=sum_area(arr,m+1,ed);

    /*merge*/
    /*試試不加開兩個陣列?*/
    /*
    struct points *left_arr=(struct points*)malloc(Max_points*sizeof(struct points));
    struct points *right_arr=(struct points*)malloc(Max_points*sizeof(struct points));

    int i,j,l,r;
    for(i=0,j=st;j<=m;i++,j++){
        left_arr[i]=arr[j];
    }
    l=m-st+1;
    for(i=0,j=m+1;j<=ed;i++,j++){
        right_arr[i]=arr[j];
    }
    r=ed-(m+1)+1;
    */
    /*依照y座標排序*/
    /*st~m m+1~ed*/
    mergeSort_Y(arr,st,m);//l個
    mergeSort_Y(arr,m+1,ed);//r個
    #ifdef debug
        int a;
        printf("left\n");
        for(a=0;a<l;a++){
            printf("%d %d\n",left_arr[a].x,left_arr[a].y);
        }
        printf("right\n");
        for(a=0;a<r;a++){
            printf("%d %d\n",right_arr[a].x,right_arr[a].y);
        }
    #endif // debug
    unsigned long long int sum_XrYr=0,sum_XrYl=0,sum_XlYr=0,sum_XlYl=0;
    unsigned long long int sum_Xl=0,sum_Yl=0,k=0,sum_YY=0;
    int i,j;
    for(i=st,j=m+1;j<=ed;j++){
        /*右點固定不變,變左點*/
        while(arr[i].y<arr[j].y && i<=m){
            #ifdef debug
                printf("k==%d\n",k);
            #endif // debug
            /*維護四個變數*/
            k++;//右自點乘數
            sum_Xl=sum_Xl+arr[i].x;
            sum_Yl=sum_Yl+arr[i].y;
            sum_YY=sum_YY+arr[i].x*arr[i].y;
            i++;
        }
        sum_XrYr+=k*(arr[j].x*arr[j].y);
        sum_XlYl+=sum_YY;
        sum_XlYr+=arr[j].y*sum_Xl;
        sum_XrYl+=arr[j].x*sum_Yl;
    }
    unsigned long long int cross_sum=sum_XrYr+sum_XlYl-sum_XlYr-sum_XrYl;
    #ifdef debug
        printf("%d %d %d %d\n",sum_XrYr,sum_XlYl,sum_XlYr,sum_XrYl);
    #endif // debug
    sum_XrYr=0,sum_XrYl=0,sum_XlYr=0,sum_XlYl=0;
    k=0;
    unsigned long long int sum_Xr=0,sum_Yr=0,sum_XX=0;
    for(i=st,j=m+1;i<=m;i++){
        /*左點固定不變,變右點*/
        while(arr[i].y>arr[j].y && j<=ed){
            #ifdef debug
                printf("k==%d\n",k);
            #endif // debug
            /*維護四個變數*/
            k++;//左自點乘數
            sum_Xr=sum_Xr+arr[j].x;
            sum_Yr=sum_Yr+arr[j].y;
            sum_XX=sum_XX+arr[j].x*arr[j].y;
            j++;//右點往上爬
        }
        sum_XlYl+=k*(arr[i].x*arr[i].y);
        sum_XrYr+=sum_XX;
        sum_XrYl+=arr[i].y*sum_Xr;
        sum_XlYr+=arr[i].x*sum_Yr;
    }
    cross_sum=cross_sum+sum_XlYr+sum_XrYl-sum_XrYr-sum_XlYl;
    unsigned long long sum=left_sum+right_sum+cross_sum;
    #ifdef debug
        printf("%d %d %d %d\n",sum_XlYl,sum_XrYr,sum_XrYl,sum_XlYr);
        return 0;
    #endif // debug
    return sum;
}
void mergeSort_Y(struct points arr[], int l, int r){
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort_Y(arr, l, m);
        mergeSort_Y(arr, m+1, r);
        merge_Y(arr, l, m, r);
    }
}
void merge_Y(struct points arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    struct points* L=(struct points*)malloc(n1*sizeof(struct points));//L[n1]
    struct points* R=(struct points*)malloc(n2*sizeof(struct points));//R[n2]

    for (i = 0; i < n1; i++){
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++){
        R[j] = arr[m + 1+ j];
    }

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].y <= R[j].y)
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
void merge(struct points arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    struct points* L=(struct points*)malloc(n1*sizeof(struct points));//L[n1]
    struct points* R=(struct points*)malloc(n2*sizeof(struct points));//R[n2]

    for (i = 0; i < n1; i++){
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++){
        R[j] = arr[m + 1+ j];
    }

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].x <= R[j].x)
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
void mergeSort(struct points arr[], int l, int r){
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

