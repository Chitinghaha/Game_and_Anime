#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cmp(const void* a, const void* b)
{

    char *ab = (char*) a;
    char *ba = (char*) b;
    return strlen(a)-strlen(b);
}

int main(void)
{

    int n;
    scanf("%d", &n);

    char array[n][1005];

    int i,flag=1;

    for(i=0; i < n; i++)
    {
        scanf("%s", array[i]);
    }
    if(n==1)
    {
        printf("YES\n");
        printf("%s\n",array[0]);
        return 0;
    }
    qsort(array, n, sizeof(array[0]), cmp);
    for (i=1; i < n; i++)
    {
        if(strstr(array[i],array[i-1])== NULL)
        {
            flag=0;
            break;
        }
    }

    if(flag==0)
        printf("NO\n");
    else
    {
        printf("YES\n");
    for(i=0; i< n; i++) printf("%s\n",array[i]);
    }
    return 0;
}
