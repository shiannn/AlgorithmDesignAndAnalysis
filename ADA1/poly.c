#include <stdio.h>
#include <stdlib.h>

#define max_powers 100010
struct poly{
    int power;
    long long int *coeff;
    /*指標*/
};
typedef struct poly poly;

poly poly_multy(poly A,poly B){
    if(A.power<=10){
        /*base case*/
        /*
        poly ret;
        ret.power=0;
        ret.coeff=(long long int*)calloc(ret.power+1,sizeof(long long int));
        ret.coeff[0]=A.coeff[0]*B.coeff[0];
        */
        poly ret;
        ret.power=A.power+B.power;
        ret.coeff=(long long int*)calloc(ret.power+1,sizeof(long long int));
        int i,j;
        for(i=0;i<=A.power;i++){
            for(j=0;j<=B.power;j++){
                ret.coeff[i+j]+=A.coeff[i]*B.coeff[j];
            }
        }
        return ret;
    }
    int mA=A.power/2;
    poly A0,A1;
    A0.power=mA;
    A0.coeff=(long long int*)calloc((A0.power+1),sizeof(long long int));
    int i;
    for(i=0;i<=A0.power;i++){
        A0.coeff[i]=A.coeff[i];
    }

    A1.power=A.power-(A.power+1)/2;
    A1.coeff=(long long int*)calloc((A1.power+1),sizeof(long long int));
    for(i=A0.power+1;i<=A.power;i++){
        A1.coeff[i-(A.power+1)/2]=A.coeff[i];
    }

    int mB=B.power/2;
    poly B0,B1;
    B0.power=mB;
    B0.coeff=(long long int*)calloc((B0.power+1),sizeof(long long int));
    for(i=0;i<=B0.power;i++){
        B0.coeff[i]=B.coeff[i];
    }

    B1.power=B.power-(B.power+1)/2;
    B1.coeff=(long long int*)calloc((B1.power+1),sizeof(long long int));//0~power
    for(i=B0.power+1;i<=B.power;i++){
        B1.coeff[i-(B.power+1)/2]=B.coeff[i];
    }
    /*-------------------------------*/
    /*(A0+A1)*(B0+B1)*/

    poly A0_plus_A1;
    A0_plus_A1.power=A0.power;
    A0_plus_A1.coeff=(long long int*)calloc((A0.power+1),sizeof(long long int));

    for(i=0;i<=A0_plus_A1.power;i++){
        A0_plus_A1.coeff[i]=A0.coeff[i]+A1.coeff[i];
    }

    poly B0_plus_B1;
    B0_plus_B1.power=B0.power;
    B0_plus_B1.coeff=(long long int*)calloc((B0.power+1),sizeof(long long int));

    for(i=0;i<=B0_plus_B1.power;i++){
        B0_plus_B1.coeff[i]=B0.coeff[i]+B1.coeff[i];
    }
    /*get(A0+A1)(B0+B1)*/
    /*------------------------*/

    poly A0B0=poly_multy(A0,B0);
    poly A1B1=poly_multy(A1,B1);
    poly E=poly_multy(A0_plus_A1,B0_plus_B1);

    /*middle=E-A0B0-A1B1*/
    poly middle;
    middle.power=E.power;
    middle.coeff=(long long int*)calloc(middle.power+1,sizeof(long long int));
    for(i=0;i<=E.power;i++){
        middle.coeff[i]=E.coeff[i]-A0B0.coeff[i]-A1B1.coeff[i];
    }
    /*回填到ret*/
    /*往後挪動(n+1)/2位*/
    poly ret;
    if(A.power%2==1){
        ret.power=A1B1.power+A.power+1;
        //ret.coeff[i+A.power+1]+=A1B1.coeff[i];
    }
    else{
        ret.power=A1B1.power+A.power;
    }
    ret.coeff=(long long int*)calloc(ret.power+1,sizeof(long long int));
    for(i=0;i<=A0B0.power;i++){
        ret.coeff[i]+=A0B0.coeff[i];
    }
    for(i=0;i<=middle.power;i++){
        ret.coeff[i+(A.power+1)/2]+=middle.coeff[i];
    }
    for(i=0;i<=A1B1.power;i++){
        if(A.power%2==1){
            ret.coeff[i+A.power+1]+=A1B1.coeff[i];
        }
        else{
            ret.coeff[i+A.power]+=A1B1.coeff[i];
        }
    }
    /*記得free,long long*/
    free(A0B0.coeff);
    free(A1B1.coeff);
    free(E.coeff);
    free(middle.coeff);
    free(A0.coeff);
    free(A1.coeff);
    free(B0.coeff);
    free(B1.coeff);
    free(A0_plus_A1.coeff);
    free(B0_plus_B1.coeff);

    return ret;
}
poly pile;

int main()
{
    pile.coeff=(long long int*)calloc(max_powers,sizeof(long long int));

    int n_pile;
    scanf("%d",&n_pile);
    int i,each_pile;
    int power=0;
    for(i=0;i<n_pile;i++){
        scanf("%d",&each_pile);
        pile.coeff[each_pile]++;//係數
        if(each_pile>pile.power)pile.power=each_pile;
    }

    poly ans=poly_multy(pile,pile);

    /*得到ans陣列*/
    /*處理*/

    for(i=0;i<=ans.power;i++){
        if(i%2==1){
            ans.coeff[i]/=2;
        }
        else if(i%2==0){
            ans.coeff[i]\
            =(ans.coeff[i]\
              -(pile.coeff[i/2])*(pile.coeff[i/2]))/2\
              +(pile.coeff[i/2]*pile.coeff[i/2]-pile.coeff[i/2])/2;
        }
    }

    int m,magic_num;
    scanf("%d",&m);
    for(i=0;i<m;i++){
        scanf("%d",&magic_num);
        if(magic_num<=ans.power){
            printf("%lld ",ans.coeff[magic_num]);
        }
        else{
            printf("0 ");
        }
    }
    return 0;
}

