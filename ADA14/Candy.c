//本題和周寬討論
//本題參考https://github.com/morris821028/UVa/blob/master/OnlineJudge/JudgeGirl/132.%20Color%20Countries.c
#include <stdio.h>
#include <stdlib.h>

#define max_student 25
#define max_color 5
//#define debug_graph

int n_student;
int count=0;
int RGB[max_color];

int graph[max_student][max_student];
int color[max_student];//每個學生的糖果顏色
int dfs(int u,int index);
int max_3(int a,int b,int c);
int max_2(int a,int b);

int main()
{
    int m_relation;
    scanf("%d %d",&n_student,&m_relation);
    int i,j,a,b;
    for(i=0;i<m_relation;i++){
        scanf("%d %d",&a,&b);
        graph[a][b]=1;
        graph[b][a]=1;
    }
    #ifdef debug_graph
        for(i=1;i<=n_student;i++){
            for(j=1;j<=n_student;j++){
                printf("%d ",graph[i][j]);
            }
            printf("\n");
        }
    #endif // debug_graph
    int ret=dfs(1,1);
    if(ret==0){
        printf("-1\n");
    }
    else{
        printf("%d\n",count);
    }
    //printf("Hello world!\n");
    return 0;
}
int dfs(int u,int index){
    /*準備要塗第index個點*/
    /*已經塗了(index-1)個點 1~(index-1)*/
    if(max_3(RGB[1],RGB[2],RGB[3])+(n_student-(index-1))<=count){
        return 1;
    }
    int i,ret=0,temp;
    if(index==(n_student+1)){
        /*
        count++;
        printf("count %d: ",count);
        for(i=1;i<=num_student;i++){
            printf("%d ",color[i]);
        }
        printf("\n");
        */
        /*計算用最多的color*/
        /*
        for(i=1;i<=n_student;i++){
            if(color[i]==1){
                RED++;
            }
            else if(color[i]==2){
                GREEN++;
            }
            else if(color[i]==3){
                BLUE++;
            }
        }
        */
        //temp=max_3(RED,GREEN,BLUE);
        if(RGB[1]>count){
            count=RGB[1];
        }
        if(RGB[2]>count){
            count=RGB[2];
        }
        if(RGB[3]>count){
            count=RGB[3];
        }

        return 1;
    }
    int unavailable[max_color]={0};
    int adj=-1,next=-1;

    for(i=1;i<=n_student;i++){
        /*遍歷所有人 看能塗甚麼顏色以及找下個人*/
        if(i==u)continue;
        if((graph[u][i]==1)&&(color[i]>0)){
            unavailable[color[i]]=1;//不能塗color[i]
        }
        if((graph[u][i]==1)&&(color[i]==0)){
            adj=i;//i還沒塗顏色,下一個可以去找它
        }
        if(color[i]==0){
            next=i;//i不是u的鄰居但也還沒塗色
        }
    }
    if(index==1){
        /*第1個點不用試三種顏色*/
        color[u]=1;
        RGB[1]++;
        if(adj!=-1){
            if(dfs(adj,index+1)){
                ret=1;
            }
        }
        else{
            if(dfs(next,index+1)){
                ret=1;
            }
        }
        color[u]=0;
        RGB[1]--;
    }
    else{
        for(i=1;i<=3;i++){
            if(unavailable[i]==1)continue;//不能塗這個顏色
            color[u]=i;
            RGB[i]++;
            if(adj!=-1){
                if(dfs(adj,index+1)){
                    ret=1;
                }
            }
            else{
                if(dfs(next,index+1)){
                    ret=1;
                }
            }
            color[u]=0;
            RGB[i]--;
        }
    }

    /*都不能塗,全部continue掉*/
    /*或是往下dfs之後碰壁*/
    return ret;
}
int max_3(int a,int b,int c){
    int temp=max_2(a,b);
    return (max_2(temp,c));
}
int max_2(int a,int b){
    if(a>b)return a;
    return b;
}

