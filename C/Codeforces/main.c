#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{

    FILE *fp;

    int t,flag=1;
    scanf("%d",&t);
    getchar();
    fp = fopen("info.txt","w");
    char input[33];
    gets(input);
    fprintf(fp,"%s",input);
    printf("OK\n");
    fclose(fp);
    t--;
    while(t--)
    {
    fp = fopen("info.txt","a");
    gets(input);
    fprintf(fp,"%s",input);
    fclose(fp);
    fp=fopen("info.txt","r");
    char fin[33];
    while(fscanf(fp,"%s",fin) != EOF)
    {
        if(strcmp(input,fin)==0)
        {
            flag=0;
            break;
        }
    }

    if(flag==0)
        printf("NOT OK\n");
    else
        printf("OK\n");
    }
}
