#include <stdio.h>
#include <stdlib.h>

//#define debug_input
#define max_days 200010
//#define debug_stack

struct each_day{
    unsigned long long int l,r;
};
typedef struct each_day each_day;

struct stack{
    int top,num,capacity;
    each_day *array;
};
typedef struct stack stack;

each_day pop(stack*s);
each_day top(stack*s);
void push(stack*s,each_day temp);

int main()
{
    int n_days;
    scanf("%d",&n_days);
    int i;
    each_day temp;
    #ifdef debug_input
        printf("%d\n",n_days);
    #endif // debug_input
    stack s;
    s.capacity=max_days;
    s.array=(each_day*)malloc((s.capacity)*sizeof(each_day));
    s.num=0;
    s.top=0;

    unsigned long long int ans=0;

    for(i=0;i<n_days;i++){
        scanf("%llu %llu",&temp.l,&temp.r);
        #ifdef debug_input
        printf("%d %d\n",temp.l,temp.r);
        #endif // debug_input
        /*push到stack中*/
        if(s.num==0){
            push(&s,temp);
            ans=ans+(temp.r-temp.l)*(temp.r-temp.l);
        }
        else{/*stack已經有*/
            while((s.num>0)&&(temp.l<=top(&s).l)){
                ans=ans-(top(&s).r-top(&s).l)*(top(&s).r-top(&s).l);
                pop(&s);
            }
            if(s.num==0){/*temp把所有人都重疊掉*/
                push(&s,temp);
                ans=ans+(temp.r-temp.l)*(temp.r-temp.l);
            }
            else{
                if(temp.l<=top(&s).r){
                    each_day temp2;
                    temp2.l=top(&s).l;
                    temp2.r=temp.r;

                    ans=ans-(top(&s).r-top(&s).l)*(top(&s).r-top(&s).l);
                    pop(&s);

                    push(&s,temp2);
                    ans=ans+(temp2.r-temp2.l)*(temp2.r-temp2.l);
                }
                else{/*沒有overlap*/
                    push(&s,temp);
                    ans=ans+(temp.r-temp.l)*(temp.r-temp.l);
                }
            }
        }
        printf("%llu\n",ans);
    }
    #ifdef debug_stack
        for(i=0;i<s.num;i++){
            printf("%d %d\n",s.array[i].l,s.array[i].r);
        }
    #endif // debug_stack
    //printf("Hello world!\n");
    return 0;
}
each_day pop(stack*s){
    each_day ret=s->array[s->top-1];
    s->top--;
    s->num--;
    return ret;
}
each_day top(stack*s){
    return (s->array[s->top-1]);
}
void push(stack*s,each_day temp){
    s->array[s->top]=temp;
    s->num++;
    s->top++;
}

