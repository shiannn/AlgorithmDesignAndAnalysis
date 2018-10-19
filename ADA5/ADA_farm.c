#include <stdio.h>
#include <stdlib.h>
#define max_horse 1010

//#define debug_input
struct horse_coordinate{
    int x,y;
};
typedef struct horse_coordinate horse_coordinate;

horse_coordinate horse_array[max_horse];

long long int time(int a,int b,horse_coordinate array[]);
int main()
{
    int N_NumHorse;
    scanf("%d",&N_NumHorse);
    int i;
    for(i=0;i<N_NumHorse;i++){
        scanf("%d %d",&horse_array[i].x,&horse_array[i].y);
    }
    #ifdef debug_input
    printf("%d\n",N_NumHorse);
    for(i=0;i<N_NumHorse;i++){
        printf("%d %d\n",horse_array[i].x,horse_array[i].y);
    }
    #endif // debug_input

    /*70*/
    int j;
    long long int sum;
    for(i=0;i<N_NumHorse;i++){
        sum=0;
        for(j=0;j<N_NumHorse;j++){
            if(i==j)continue;
            sum+=time(i,j,horse_array);
        }
        printf("%lld\n",sum);
    }
    return 0;
}
long long int time(int a,int b,horse_coordinate array[]){
    long long int ret=0;
    int delta_x=abs(array[a].x-array[b].x);
    int delta_y=abs(array[a].y-array[b].y);
    if(delta_y>2*delta_x){
        //使用delta_x次正日字
        delta_y-=2*delta_x;
        ret+=2*delta_x;//馬步時間
        ret+=delta_y;//兵步時間
    }
    else if(delta_y==2*delta_x){
        //使用delta_x次正日字
        delta_y-=2*delta_x;
        ret+=2*delta_x;//馬步時間
        ret+=delta_y;//兵步時間 (0)
    }
    else if(delta_x>2*delta_y){
        //使用delta_y次躺日字
        delta_x-=2*delta_y;
        ret+=2*delta_y;//馬步時間
        ret+=delta_x;//兵步時間
    }
    else if(delta_x==2*delta_y){
        //使用delta_y次躺日字
        delta_x-=2*delta_y;
        ret+=2*delta_y;//馬步時間
        ret+=delta_x;//兵步時間(0)
    }
    else if(delta_y<2*delta_x&&delta_y>delta_x){
        //用正日字走到y=x
        //每用一次delta_y和delta_x就拉近一點
        //delta_y-delta_x次正日字
        ret+=2*(delta_y-delta_x);
        delta_y-=2*(delta_y-delta_x);//(delta_y,delta_y)
        ret+=4*(delta_y/3);
        if(delta_y%3==1){
            ret+=2;
        }
        else if(delta_y%3==2){
            ret+=3;
        }
    }
    else if(delta_y==delta_x){
        ret+=4*(delta_x/3);
        if(delta_x%3==1){
            ret+=2;
        }
        else if(delta_x%3==2){
            ret+=3;
        }
    }
    else if(delta_x<2*delta_y&&delta_x>delta_y){
        //用躺日字走到y=x
        //每用一次delta_x和delta_y就拉近一點
        //delta_x-delta_y次躺日字
        ret+=2*(delta_x-delta_y);
        delta_x-=2*(delta_x-delta_y);//(delta_x,delta_x)
        ret+=4*(delta_x/3);
        if(delta_x%3==1){
            ret+=2;
        }
        else if(delta_x%3==2){
            ret+=3;
        }
    }
    return ret;
}

