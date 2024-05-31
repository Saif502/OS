#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int need[100][100],allot[100][100],max[100][100],available[100];
bool isFinished[100];
int sequence[100];
void isSafe(int N,int M)
{
        int i,j,work[100],count=0;
        for(i=0;i<M;i++)
            work[i]=available[i];
        for(i=0;i<100;i++)
            isFinished[i]=false;
        while(count<N)
        {
                bool canAllot=false;
                for(i=0;i<N;i++)
                {
                   if(isFinished[i]==false)
                   {

                        for(j=0;j<M;j++)
                        {
                            if(work[j]<need[i][j])
                            {
                                break;
                            }
                        }
                        if(j==M)
                        {
                            for(j=0;j<M;j++)
                            {
                                work[j]+=allot[i][j];
                            }

                            sequence[count++]=i;
                            isFinished[i]=true;
                            canAllot=true;
                        }
                   }
                }
                if(canAllot==false)
                {
                    printf("System Is  not safe\n");
                    return ;
                }
        }
        printf("System is in safe state\n");
        printf("Safe sequence :");
        for(i=0;i<N;i++)
            printf("%d ",sequence[i]);
        printf("\n");
}

int main()
{
   FILE *fp;
    fp = fopen("input.txt", "r");
        int i,j,N,M;
        printf("Enter the number of process and resources :");
        fscanf(fp,"%d %d",&N,&M);

        printf("Available resources :\n");

        for(i=0;i<M;i++)
            fscanf(fp,"%d",&available[i]);

        printf("Allocation Matrix :\n");

        for(i=0;i<N;i++)
            for(j=0;j<M;j++)
                fscanf(fp,"%d",&allot[i][j]);

        printf("Max  :\n");

        for(i=0;i<N;i++)
            for(j=0;j<M;j++)
                fscanf(fp,"%d",&max[i][j]);
        for(i=0;i<N;i++)
            for(j=0;j<M;j++)
                need[i][j]=max[i][j]-allot[i][j];
       
        isSafe(N,M);
         printf("\nNeed matrix: \n");
            for(i=0;i<N;i++)
                {for(j=0;j<M;j++)
                   { printf("%d ",need[i][j]);}
                   printf("\n");
                   }
                
        printf("\n");
    return 0;
}