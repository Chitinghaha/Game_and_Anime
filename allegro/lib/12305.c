#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct
{
    int al;
    int ln;
    int ind;
} ST;

int cmp(const void *x,const void *y)
{
    ST *a=(ST *)x;
    ST *b=(ST *)y;
    if(a->al > b->al) return 1;
    else if(a->al<b->al) return -1;
    else
    {
        if(a->ln>b->ln) return 1;
        else if(a->ln<b->ln) return -1;
        else
        {
            if(a->ind>b->ind) return 1;
            else if(a->ind<b->ind) return -1;

        }

    }
}

    int main(void)
    {
        int num;
        scanf("%d",&num);
        ST arr[num];
        ST *b;
        b = (ST *) malloc(sizeof(ST)*num);
        int x,y,z,i;
        for (i=0; i<num; i++)
        {
            scanf("%d%d",&x,&y);
            b[i].al = x ;
            b[i].ln = y ;
            b[i].ind = i+1 ;
        }
        qsort(b, num, sizeof(ST), cmp);
        for (i=0; i<num-1; i++) printf("%d ",b[i].ind);
        printf("%d\n",b[num-1].ind);
        return 0;
    }
