/*
	Priority Process Scheduling
	Assumed lesser priority order to be executed first
	Non-Preemptive
*/
#include "stdio.h"
#include "stdlib.h"
struct process
{
	int process_id;
	int arrival_time;
	int burst_time;
	int waiting_time;
	int turn_around_time;
	int priority;
};
int main()
{
	int n,i,j;
	int bt=0,k=1,tat=0,sum=0,min,mini;
	printf("Enter number of processes: ");
	scanf("%d",&n);
	struct process proc[n],temp;
	for(i=0;i<n;i++)
	{
		printf("\n");
		printf("Enter arrival time for process%d: ",i+1);
		scanf("%d",&proc[i].arrival_time);
		printf("Enter burst time for process%d: ",i+1);
		scanf("%d",&proc[i].burst_time);
		printf("Enter priority for process%d: ",i+1);
		scanf("%d",&proc[i].priority);
		proc[i].process_id = i+1;
	}

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(proc[i].arrival_time < proc[j].arrival_time)
			{
				temp = proc[j];
				proc[j] = proc[i];
				proc[i] = temp;
			}
		}
	}

	for(i=0;i<n;i++)
	{
		bt+=proc[i].burst_time;
		min = proc[k].burst_time;
		mini = proc[k].priority;
		for(j=k;j<n;j++)
		{
			if(bt>=proc[j].arrival_time && proc[j].priority<mini)
			{
				temp=proc[k];
				proc[k]=proc[j];
				proc[j]=temp;
			}
		}
		k++;
	}
	proc[0].waiting_time=0;
	int wait_time_total=0;
	int turn_around_time_total=0;
	for(i=1;i<n;i++)
	{
		sum+=proc[i-1].burst_time;
		proc[i].waiting_time = sum-proc[i].arrival_time;
		wait_time_total += proc[i].waiting_time;
	}
	for(i=0;i<n;i++)
	{
		tat+=proc[i].burst_time;
		proc[i].turn_around_time = tat - proc[i].arrival_time;
		turn_around_time_total+=proc[i].turn_around_time;
	}
	printf("Process\t   Burst Time\t  Arrival Time\t   Waiting Time\t  Turn-Around Time\n");

	for(i=0;i<n;i++)
	{

		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",proc[i].process_id,proc[i].burst_time, proc[i].arrival_time, proc[i].waiting_time,proc[i].turn_around_time);
	}
	printf("Average waiting time: %f\n", (float)wait_time_total/n);
	printf("Average turn around time: %f\n",(float)turn_around_time_total/n);

}
