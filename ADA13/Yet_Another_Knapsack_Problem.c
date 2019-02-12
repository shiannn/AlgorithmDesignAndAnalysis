#include <stdio.h>
#include <stdlib.h>

#define max_things 50
//#define debug_input
#define max_choose 1050000
//#define debug_choose
//#define debug_sort
//#define debug_stack

struct choose{
    long long int sumWeight,sumValue;
};
typedef struct choose choose;

choose choose_array[max_choose];
choose choose_array2[max_choose];
choose choose_array3[max_choose];
choose choose_array4[max_choose];
void merge(choose arr[], int l, int m, int r);
void mergeSort(choose arr[], int l, int r);
int main()
{
    int value[max_things];
    int weight[max_things];

    int value2[max_things];
    int weight2[max_things];

    int n_things,W_bags;
    int i;
    scanf("%d %d",&n_things,&W_bags);
    for(i=0;i<n_things;i++){
        scanf("%d %d",&value[i],&weight[i]);
    }
    #ifdef debug_input
        printf("%d %d\n",n_things,W_bags);
        for(i=0;i<n_things;i++){
            printf("%d %d\n",value[i],weight[i]);
        }
    #endif // debug_input

    /*枚舉前一半 0~n2-1 後一半n2~n_thing-1*/
    int j;
    int n2 = n_things/2;
    for (i=0;i<(1<<n2);i++) {
        /*第i種選法*/
		long long int sumw = 0, sumv = 0;
		for (j = 0; j < n2; j++) {
		    /*判斷第j物有沒有被選*/
			if ((i>>j) & 1) {
				sumw += weight[j];
				sumv += value[j];
			}
		}
		choose_array[i].sumValue=sumv;
		choose_array[i].sumWeight=sumw;
	}

    #ifdef debug_choose
        for (i=0;i<(1<<n2);i++) {
            printf("%lld %lld\n",choose_array[i].sumValue,choose_array[i].sumWeight);
        }
    #endif // debug_choose

    int first_half=(1<<n2)-1;
    /*以Weight做排序*/
    mergeSort(choose_array,0,first_half);
    /*0~(1<<n2)-1*/
    #ifdef debug_sort
        for (i=0;i<(1<<n2);i++) {
            printf("%lld %lld\n",choose_array[i].sumValue,choose_array[i].sumWeight);
        }
    #endif // debug_sort
    /*利用stack維持遞增value*/

    for (i=0,j=0;i<(1<<n2);i++) {
        if(i==0){
            choose_array2[j]=choose_array[i];
            j++;
        }
        else{
            if(choose_array[i].sumValue>choose_array2[j-1].sumValue){
                choose_array2[j]=choose_array[i];
                j++;
            }
        }
    }
    int number2=j;
    #ifdef debug_stack
        for (i=0;i<(1<<n2);i++) {
            printf("two %lld %lld\n",choose_array2[i].sumValue,choose_array2[i].sumWeight);
        }
    #endif // debug_stack

    /*得到choose2陣列*/
    /*另外一側*/
    int n3 = n_things-n2;//n2~n_thing-1
    /*n3個東西*/
    /*貼到weight2 value2陣列*/
    for(i=n2,j=0;i<n_things;i++,j++){
        weight2[j]=weight[i];
        value2[j]=value[i];
    }
    for (i=0;i<(1<<n3);i++) {
        /*第i種選法*/
		long long int sumw = 0, sumv = 0;
		for (j = 0; j < n3; j++) {
		    /*判斷第j物有沒有被選*/
			if ((i>>j) & 1) {
				sumw += weight2[j];
				sumv += value2[j];
			}
		}
		choose_array3[i].sumValue=sumv;
		choose_array3[i].sumWeight=sumw;
	}
	#ifdef debug_choose
        for (i=0;i<(1<<n3);i++) {
            printf("%lld %lld\n",choose_array3[i].sumValue,choose_array3[i].sumWeight);
        }
    #endif // debug_choose

    int second_half=(1<<n3)-1;
    /*0~(1<<3)-1*/
    mergeSort(choose_array3,0,second_half);
    for (i=0,j=0;i<(1<<n3);i++) {
        if(i==0){
            choose_array4[j]=choose_array3[i];
            j++;
        }
        else{
            if(choose_array3[i].sumValue>choose_array4[j-1].sumValue){
                choose_array4[j]=choose_array3[i];
                j++;
            }
        }
    }
    int number4=j;
    #ifdef debug_stack
        for (i=0;i<(1<<n3);i++) {
            printf("four %lld %lld\n",choose_array4[i].sumValue,choose_array4[i].sumWeight);
        }
    #endif // debug_stack

    /*取得choose_array4*/
    /*將choose_array2 (0~number2-1)*/
    /*  choose_array4 (0~number4-1) 作binary search*/
    /*choose_array1 0~firsthalf choose_array3 0~secondhalf*/
    /**/
    long long int temp_W;
    int l,mid,r;
    long long int maxvalue=0;
    long long int temp_value;
    for(i=0;i<number2;i++){
        /*前一半的選法就爆?*/
        if(choose_array2[i].sumWeight>W_bags)continue;
        temp_value=choose_array2[i].sumValue;
        for(j=0;j<number4;j++){
            if(choose_array2[i].sumWeight+choose_array4[j].sumWeight<=W_bags){
                temp_value=choose_array2[i].sumValue+choose_array4[j].sumValue;
            }
        }
        if(temp_value>maxvalue){
            maxvalue=temp_value;
        }
        /*
        //在choose_array4裡面binary search
        l=0;
        r=number4-1;
        while( l <= r ){
            int mid = (l + r) >> 1;
            if( choose_array4[mid].sumWeight > temp_W )
                r = mid - 1;
            else l = mid + 1;
        }
        if(choose_array2[i].sumValue+choose_array4[r].sumValue>maxvalue){
            maxvalue=choose_array2[i].sumValue+choose_array4[r].sumValue;
        }
        */
    }
    printf("%lld\n",maxvalue);

    return 0;
}
void mergeSort(choose arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}
void merge(choose arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    choose* L=(choose*)malloc(n1*sizeof(choose));//[n1]
    choose* R=(choose*)malloc(n2*sizeof(choose));//[n2]
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i].sumWeight <= R[j].sumWeight)
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

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

