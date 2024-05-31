#include<bits/stdc++.h>
using namespace std;

struct data {
       string p_id;
       int arrival_time;
       int burst_time;
       int completionTime;
       int turn_around_time;
       int waiting_time;
       int reponse_time;

};
int main(){

        int n;
        freopen("input.txt","r",stdin);
        cin >> n; vector<data>p(n);
        for(int i = 0;i<n;i++){
            cin >> p[i].p_id >> p[i].arrival_time >> p[i].burst_time;
        }
        //sort according to Arrival time;
        for(int i = 0;i<n;i++){
            for ( int j = i + 1; j<n; j++ ){
                    if (p [ i ].arrival_time > p[ j ].arrival_time)
                         swap(p[i],p[j]);
            }
        }

        int sum = p[0].arrival_time,wt = 0,rt = 0 , tt = 0,ct = 0;

        for(int i = 0;i<n;i++){

            p[i].waiting_time = sum; // sum of (i - 1) burst time
            p[i].completionTime = p[i].waiting_time + p[i].burst_time;
            p[i].turn_around_time = p[i].completionTime - p[i].arrival_time;


           if(i == 0)
              p[i].reponse_time = 0;

           else
              p[i].reponse_time  = p[i-1].completionTime;

              sum +=p[i].burst_time;


              ct += p[i].completionTime;
              rt += p[i].reponse_time;
              wt += p[i].waiting_time;
              tt += p[i].turn_around_time;


        }

        // Display:


cout <<"process_id  " << "Arrival_Time " <<"Burst_time  "<<"completion_time  "<<"Turn_around_time  "<<"Waiting_time  "<<"Response_time\n";

for(int i = 0;i<n;i++){
    cout <<p[i].p_id <<"\t\t" <<  p[i].arrival_time<<"\t\t" << p[i].burst_time <<"\t\t" << p[i].completionTime <<"\t\t" << p[i].turn_around_time <<"\t\t" <<p[i].waiting_time<<"\t\t" << p[i].reponse_time << endl;

}
cout <<"\n\n";

cout << "Average CompletionTime: "<<(ct/((float)n))<<endl;
cout << "Average ResponseTime: "<<(rt/((float)n))<<endl;
cout << "Average WaitingTime: "<<(wt/((float)n))<<endl;
cout << "Average turnAroundTime: "<<(tt/((float)n))<<endl;



return 0;
}
