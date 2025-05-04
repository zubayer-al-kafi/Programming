#include <stdio.h>
void corner();
int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        int n,m;
        scanf("%d %d",&n,&m);
        int x1,y1,x2,y2;
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);

        if(x1==y1 && x2==y2 && x1==x2)
            printf("0\n");
        else if((x1==1&&y1==1)||(x2==1&&y2==1))
        {
            printf("2\n");
        }
        else if ((x1==1&&y1==m)||(x2==1&&y2==m))
        {
            printf("2\n");
        }
        else if((x1==n&&y1==1)||(x2==n&&y2==1))
        {
            printf("2\n");
        }
        else if((x1==n&&y1==m)||(x2==n&&y2==m))
        {
            printf("2\n");
        }

        else if ((x1==1 && y1!=1) ||(x2==1 && y2 !=1))
        {
            printf("3\n");
        }
        else if ((x1==n && y1!=m) ||(x2==n && y2 !=m))
        {
            printf("3\n");
        }
        else if ((x1!=1 && y1==1) ||(x2!=1 && y2 ==1))
        {
            printf("3\n");
        }
        else if ((x1!=n && y1==m) ||(x2!=n && y2 ==m))
        {
            printf("3\n");
        }
        else if(x1==y1 && x2==y2 && x1==x2)
            printf("0\n");
        else
            printf("4\n");
    }
    return 0;
}