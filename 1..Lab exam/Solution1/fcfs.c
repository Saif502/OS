#include "stdio.h"
#include "stdlib.h"
struct process
{
	int process_id;
	int arrival_time;
	int burst_time;
	int waiting_time;
	int turn_around_time;
};
int main()
{
    FILE *fp;
    fp = fopen("input.txt", "r");
	int n,i;
	fscanf(fp,"%d",&n);
	struct process proc[n];
	for(i=0;i<n;i++)
	{
		proc[i].arrival_time=0;
		fscanf(fp,"%d",&proc[i].burst_time);
		proc[i].process_id = i+1;
	}
	int service_time[n];
	service_time[0]=0;
	proc[0].waiting_time=0;

	for(i=1;i<n;i++)
	{
		service_time[i]=service_time[i-1]+proc[i-1].burst_time;
		proc[i].waiting_time = service_time[i]-proc[i].arrival_time;

		if(proc[i].waiting_time<0)
			proc[i].waiting_time=0;
	}

	for(i=0;i<n;i++)
	{
		proc[i].turn_around_time = proc[i].burst_time + proc[i].waiting_time;
	}
	printf("\n\n");
	printf("Process\tBurst Time\tWaiting Time\tTurn-Around Time\tCompletion Time\n");
	int total_waiting_time=0,total_turn_around_time=0;
	for(i=0;i<n;i++)
	{
		total_waiting_time+=proc[i].waiting_time;
		total_turn_around_time+=proc[i].turn_around_time;

		int completion_time=proc[i].turn_around_time + proc[i].arrival_time;

		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",proc[i].process_id,proc[i].burst_time, proc[i].waiting_time,proc[i].turn_around_time,completion_time);
	}
	printf("Average waiting time: %f\n", (float)total_waiting_time/n);
	printf("Average turn around time: %f\n",(float)total_turn_around_time/n);
	return 0;
}
