#include <stdio.h>
#include <stdlib.h>
//#include <limits.h>

#define max_node 100010
#define _I64_MAX 9223372036854775807
//#define debug_input
//#define debug_priority_queue
struct node{
    int num;
    int distance;//和前一個的距離;
    struct node*next;
};
typedef struct node node;

long long int shortest[max_node];
node*head[max_node];
node*ptr[max_node];
int pos[max_node];//紀錄每個node在priority queue的位置

struct minheap{
    int *array;
    int capacity,num;
};
typedef struct minheap minheap;

void decreasekey(int i,minheap*Q_ptr);
void BFS(int start,minheap* Q_ptr);
void addedge(int st,int ed,int w);
int parent(int i);
void insert(int src,minheap* Q_ptr);
int right(int i);
int left(int i);
void swap(int *x, int *y);
void minheapify(int i,minheap *Q_ptr);
int extract(minheap* Q_ptr);

int main()
{
    int n_bears,m_touples;
    scanf("%d %d",&n_bears,&m_touples);
    int i,a,b,c;
    for(i=1;i<=n_bears;i++){
        shortest[i]=_I64_MAX;
    }
    for(i=1;i<=m_touples;i++){
        scanf("%d %d %d",&a,&b,&c);
        /*a和b之間有權重為c的edge*/
        addedge(a,b,c);
        addedge(b,a,c);
    }
    #ifdef debug_input
        for(i=1;i<=n_bears;i++){
            printf("shortest==%lld\n",shortest[i]);
            node*ptr_debug;
            ptr_debug=head[i];
            while(ptr_debug!=NULL){
                printf("st==%d ed==%d distance==%d\n"\
                       ,i,ptr_debug->num,ptr_debug->distance);
                ptr_debug=ptr_debug->next;
            }
        }
    #endif // debug_input
    /*作dijkstra來更新最短距離*/
    /*priority queue*/
    minheap Q;
    Q.capacity=n_bears+1;
    Q.num=0;
    Q.array=(int*)malloc(Q.capacity*sizeof(int));

    for(i=1;i<=n_bears;i++){
        insert(i,&Q);
        pos[i]=i;
    }

    #ifdef debug_priority_queue
        for(i=1;i<=Q.num;i++){
            printf("Q.arr[%d]==%d\n",i,Q.array[i]);
        }
    #endif // debug_priority_queue
    BFS(1,&Q);

    long long int max=0;
    for(i=1;i<=n_bears;i++){
        //printf("%lld\n",shortest[i]);
        if(shortest[i]>max){
            max=shortest[i];
        }
    }
    if(max==_I64_MAX){
        printf("-1\n");
    }
    else{
        printf("%lld\n",max);
    }
    //printf("Hello world!\n");
    return 0;
}
//Q.array內部要存第幾個node
int extract(minheap* Q_ptr){
    if(Q_ptr->num==1){
        Q_ptr->num--;
        return (Q_ptr->array[1]);
    }
    int root=Q_ptr->array[1];
    Q_ptr->array[1]=Q_ptr->array[Q_ptr->num];
    pos[Q_ptr->array[Q_ptr->num]]=1;

    Q_ptr->num--;
    minheapify(1,Q_ptr);
    return root;
}
void minheapify(int i,minheap *Q_ptr){
    int l=left(i);
    int r=right(i);
    int smallest=i;
    if (l<=Q_ptr->num && shortest[Q_ptr->array[l]] < shortest[Q_ptr->array[i]])
        smallest = l;
    if (r <= Q_ptr->num && shortest[Q_ptr->array[r]] < shortest[Q_ptr->array[smallest]])
        smallest = r;
    if (smallest != i)
    {
        /*換priority queue內的值*/
        swap(&Q_ptr->array[i], &Q_ptr->array[smallest]);

        /*換pos*/
        int temp=pos[Q_ptr->array[i]];
        pos[Q_ptr->array[i]]=pos[Q_ptr->array[smallest]];
        pos[Q_ptr->array[smallest]]=temp;

        minheapify(smallest,Q_ptr);
    }
}
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
int left(int i) { return (2*i); }
int right(int i) { return (2*i+1); }
void insert(int src,minheap* Q_ptr){
    Q_ptr->num++;
    int i=Q_ptr->num;
    Q_ptr->array[i]=src;

    while(i!=1&&shortest[Q_ptr->array[parent(i)]]>shortest[Q_ptr->array[i]]){
        swap(&Q_ptr->array[parent(i)],&Q_ptr->array[i]);
        i=parent(i);
    }
}

int parent(int i){
    return (i/2);
}
void BFS(int start,minheap* Q_ptr){
    shortest[start]=0;
    #ifdef debug_priority_queue
        int i;
        for(i=1;i<=Q_ptr->num;i++){
            printf("Q_ptr->arr[%d]==%d\n",i,Q_ptr->array[i]);
        }
    #endif // debug_priority_queue

    /*並非是在priority queue的start位置*/
    /*ptr->num node在priority queue的哪裡?*/
    decreasekey(pos[start],Q_ptr);

    while(Q_ptr->num>0){//queue不為空

        int src=extract(Q_ptr);
        node*ptr;
        for(ptr=head[src];ptr!=NULL;ptr=ptr->next){
            if(shortest[ptr->num]>shortest[src]+ptr->distance){
                shortest[ptr->num]=shortest[src]+ptr->distance;
                /*維護priority queue*/
                decreasekey(pos[ptr->num],Q_ptr);
                /*並非是在priority queue的ptr->num位置*/
                /*ptr->num node在priority queue的哪裡?*/

            }
        }
    }
}
void decreasekey(int i,minheap*Q_ptr){

    while (i != 1 && shortest[Q_ptr->array[parent(i)]] > shortest[Q_ptr->array[i]])
    {

       swap(&Q_ptr->array[i], &Q_ptr->array[parent(i)]);
       /*換pos*/
        int temp=pos[Q_ptr->array[i]];
        pos[Q_ptr->array[i]]=pos[Q_ptr->array[parent(i)]];
        pos[Q_ptr->array[parent(i)]]=temp;

       i = parent(i);
    }
}
void addedge(int st,int ed,int w){
    node*temp=(node*)malloc(sizeof(node));
    temp->num=ed;
    temp->next=NULL;
    temp->distance=w;
    if(head[st]==NULL){
        head[st]=temp;
        ptr[st]=head[st];
    }
    else{
        ptr[st]->next=temp;
        ptr[st]=ptr[st]->next;
    }
}
