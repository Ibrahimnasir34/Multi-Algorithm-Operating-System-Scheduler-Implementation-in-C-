#include<iostream>
#define MAX_PROCESS 10
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;

//Preamptive snj

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int responseTime;
    int waitTime;
};

bool compareArrivalTime(const Process& p1, const Process& p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

bool compareBurstTime(const Process& p1, const Process& p2) {
    return p1.burstTime < p2.burstTime;
}

void sjnPreemptive(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), compareArrivalTime);

    int n = processes.size();
    std::vector<bool> completed(n, false);
    std::vector<int> remainingTime(n);
    std::vector<int> executedTime(n, 0);
    std::vector<int> startTime(n);

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        int shortestJob = -1;
        int minRemainingTime = INT_MAX;

        for (int i = 0; i < n; ++i) {
            if (!completed[i] && processes[i].arrivalTime <= currentTime) {
                if (processes[i].burstTime < minRemainingTime) {
                    shortestJob = i;
                    minRemainingTime = processes[i].burstTime;
                }
            }
        }

        if (shortestJob == -1) {
            ++currentTime;
            continue;
        }

        if (executedTime[shortestJob] == 0) {
            processes[shortestJob].responseTime = currentTime - processes[shortestJob].arrivalTime;
            processes[shortestJob].waitTime += processes[shortestJob].responseTime;
        }

        --processes[shortestJob].burstTime;
        ++executedTime[shortestJob];
        ++currentTime;

        if (processes[shortestJob].burstTime == 0) {
            processes[shortestJob].completionTime = currentTime;
            processes[shortestJob].turnaroundTime = processes[shortestJob].completionTime - processes[shortestJob].arrivalTime;
            completed[shortestJob] = true;
            ++completedProcesses;
        }
    }
}

void printProcesses(const std::vector<Process>& processes) {
    int n = processes.size();
    double totalTurnaroundTime = 0;
    double totalResponseTime = 0;
    double totalWaitTime = 0;

    std::cout << "PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tResponse Time\tWait Time\n";
    for (int i = 0; i < n; ++i) {
        std::cout << processes[i].pid << "\t"
                  << processes[i].arrivalTime << "\t\t"
                  << processes[i].burstTime << "\t\t"
                  << processes[i].completionTime << "\t\t"
                  << processes[i].turnaroundTime << "\t\t"
                  << processes[i].responseTime << "\t\t"
                  << processes[i].waitTime << "\n";

        totalTurnaroundTime += processes[i].turnaroundTime;
        totalResponseTime += processes[i].responseTime;
        totalWaitTime += processes[i].waitTime;
    }

    double averageTurnaroundTime = totalTurnaroundTime / n;
    double averageResponseTime = totalResponseTime / n;
    double averageWaitTime = totalWaitTime / n;

    std::cout << "\nAverage Turnaround Time: " << averageTurnaroundTime << "\n";
    std::cout << "Average Response Time: " << averageResponseTime << "\n";
    std::cout << "Average Wait Time: " << averageWaitTime << "\n";
}
//Banker's Algorithm'
int allocation[10][3],need[10][3],Max[10][3],available[10][3];
int p,current[3];
bool executed[10],come;
void IMP(){
	come=false;
	for (int i = 0; i < 10; ++i)
	{
		executed[i]=false;
	}
}
void Calculate(){
	IMP();
	int i,j;
	for (i = 0; i < p; ++i)
	{	
		for (j = 0; j < p; ++j)
		{
			while(executed[j] && j<p-1){
				j++;
			}
			if (need[j][0]<=current[0]&&need[j][1]<=current[1]&&need[j][2]<=current[2])
			{
				if (!executed[j])
				{
					executed[j]=true;
					current[0]+=allocation[j][0];current[1]+=allocation[j][1];current[2]+=allocation[j][2];
					cout<<"\nProcess P"<<j+1;
					cout<<"\nCurrent: "<<current[0]<<" "<<current[1]<<" "<<current[2]<<"\n";
					cout<<"\nProcess executed without deadlock";
					come=true;
					break;
				}
			}
		}
		if (!come)
		{	
			cout<<"\n			Dead lock\n\n";
			break;
		}else{
			come=false;
		}
	}
}

//FCFS code
class process
{
  public:
  int process_num;
  int burst_time;
  int arrival_time;
  int response_time;
  int waiting_time;
  int turnaround_time;
  void input_process(int);
  int get_at()
  {
    return arrival_time;
  }
};
void process::input_process(int count)
{
  process_num=count+1;
  cout<<"\nENTER BURST TIME FOR PROCESS "<<count+1<<" : ";
  cin>>burst_time;
  cout<<"ENTER ARRIVAL TIME FOR PROCESS "<<count+1<<" : ";
  cin>>arrival_time;
}
void calc_wait_tat(process*,int);
void average(process*,int);
void display(process*,int);
//FCFS ends

//Pariority starts
struct node{
    char pname;
    int btime;
    int atime;
    int priority;
    int restime=0;
    int ctime=0;
    int wtime=0;
}a[50],b[50],c[50];

void insert(int n){
    int i;
    for(i=0;i<n;i++){
        cin>>a[i].pname;
        cin>>a[i].priority;
        cin>>a[i].atime;
        cin>>a[i].btime;
        a[i].wtime=-a[i].atime+1;
    }
}

bool btimeSort(node a,node b){
    return a.btime < b.btime; 
}

bool atimeSort(node a,node b){
    return a.atime < b.atime; 
}
bool prioritySort(node a,node b){
    return a.priority < b.priority; 
}
int k=0,f=0,r=0;
void disp(int nop,int qt){
    int n=nop,q;
    sort(a,a+n,atimeSort);
    int ttime=0,i;
    int j,tArray[n];
    int alltime=0;
    bool moveLast=false;
    for(i=0;i<n;i++){
        alltime+=a[i].btime;
    }
    alltime+=a[0].atime;
    for(i=0;ttime<=alltime;){
        j=i;
        while(a[j].atime<=ttime&&j!=n){
            b[r]=a[j];
            j++;
            r++;
        }
        if(r==f){
            c[k].pname='i';
            c[k].btime=a[j].atime-ttime;
            c[k].atime=ttime;
            ttime+=c[k].btime;
            k++;
            continue;
        }
        i=j;
        if(moveLast==true){
            sort(b+f,b+r,prioritySort);
            // b[r]=b[f];
            // f++;
            // r++;
        }

        j=f;
        if(b[j].btime>qt){
            c[k]=b[j];
            c[k].btime=qt;
            k++;
            b[j].btime=b[j].btime-qt;
            ttime+=qt;  
            moveLast=true;
            for(q=0;q<n;q++){
                if(b[j].pname!=a[q].pname){
                    a[q].wtime+=qt;
                }
            }
        }
        else{
            c[k]=b[j];
            k++;
            f++;
            ttime+=b[j].btime;  
            moveLast=false;
            for(q=0;q<n;q++){
                if(b[j].pname!=a[q].pname){
                    a[q].wtime+=b[j].btime;
                }
            }
        }
        if(f==r&&i>=n)
        break;
    }
    tArray[i]=ttime;
    ttime+=a[i].btime;
    for(i=0;i<k-1;i++){
        if(c[i].pname==c[i+1].pname){
            c[i].btime+=c[i+1].btime;
            for(j=i+1;j<k-1;j++)
                c[j]=c[j+1];
            k--;
            i--;
        }
    }
    
    int rtime=0;
    for(j=0;j<n;j++){
        rtime=0;
        for(i=0;i<k;i++){
            if(c[i].pname==a[j].pname){
                a[j].restime=rtime;
                break;
            }
            rtime+=c[i].btime;
        }
    }

    float averageWaitingTime=0;
    float averageResponseTime=0;
    float averageTAT=0;
    
    cout<<"\nGantt Chart\n";
    rtime=0;
    for (i=0; i<k; i++){
        if(i!=k)
            cout<<"|  "<<'P'<< c[i].pname << "   "; 
        rtime+=c[i].btime;
        for(j=0;j<n;j++){
            if(a[j].pname==c[i].pname)
                a[j].ctime=rtime;
        } 
    }
    cout<<"\n";
    rtime=0;
    for (i=0; i<k+1; i++){
        cout << rtime << "\t";
        tArray[i]=rtime;
        rtime+=c[i].btime; 
    }

    cout<<"\n";
    cout<<"\n";
    cout<<"P.Name Priority AT\tBT\tCT\tTAT\tWT\tRT\n";
    for (i=0; i<nop&&a[i].pname!='i'; i++){
        if(a[i].pname=='\0')
            break;
        cout <<'P'<< a[i].pname << "\t"; 
        cout << a[i].priority << "\t";
        cout << a[i].atime << "\t";
        cout << a[i].btime << "\t";
        cout << a[i].ctime << "\t"; 
        cout << a[i].wtime+a[i].ctime-rtime+a[i].btime << "\t"; 
        averageTAT+=a[i].wtime+a[i].ctime-rtime+a[i].btime;
        cout << a[i].wtime+a[i].ctime-rtime << "\t"; 
        averageWaitingTime+=a[i].wtime+a[i].ctime-rtime;
        cout << a[i].restime-a[i].atime << "\t";  
        averageResponseTime+=a[i].restime-a[i].atime;
        cout <<"\n"; 
    }

    cout<<"Average Response time: "<<(float)averageResponseTime/(float)n<<endl;
    cout<<"Average Waiting time: "<<(float)averageWaitingTime/(float)n<<endl;
    cout<<"Average TA time: "<<(float)averageTAT/(float)n<<endl;

}

//pariority ends

//Round RObbin
void findWaitingTime(int processes[], int n,
int bt[], int wt[], int quantum)
{
// Make a copy of burst times bt[] to store remaining
// burst times.
int rem_bt[n];
for (int i = 0 ; i < n ; i++)
rem_bt[i] = bt[i];
int t = 0; // Current time
// Keep traversing processes in round robin manner
// until all of them are not done.
while (1)
{
bool done = true;
// Traverse all processes one by one repeatedly
for (int i = 0 ; i < n; i++)
{
// If burst time of a process is greater than 0
// then only need to process further
if (rem_bt[i] > 0)
{
done = false; // There is a pending process
if (rem_bt[i] > quantum)
{
// Increase the value of t i.e. shows
// how much time a process has been processed
t += quantum;
// Decrease the burst_time of current process
// by quantum
rem_bt[i] -= quantum;
}
// If burst time is smaller than or equal to
// quantum. Last cycle for this process
else
{
// Increase the value of t i.e. shows
// how much time a process has been processed
t = t + rem_bt[i];
// Waiting time is current time minus time
// used by this process
wt[i] = t - bt[i];
// As the process gets fully executed
// make its remaining burst time = 0
rem_bt[i] = 0;
}
}
}
// If all processes are done
if (done == true)
break;
}
}
// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n,
int bt[], int wt[], int tat[])
{
// calculating turnaround time by adding
// bt[i] + wt[i]
for (int i = 0; i < n ; i++)
tat[i] = bt[i] + wt[i];
}
// Function to calculate average time
void findavgTime(int processes[], int n, int bt[],
int quantum)
{
int wt[n], tat[n], total_wt = 0, total_tat = 0;
// Function to find waiting time of all processes
findWaitingTime(processes, n, bt, wt, quantum);
// Function to find turn around time for all processes
findTurnAroundTime(processes, n, bt, wt, tat);
// Display processes along with all details
cout << "PN\t "<< " \tBT "
<< " WT " << " \tTAT\n";
// Calculate total waiting time and total turn
// around time
for (int i=0; i<n; i++)
{
total_wt = total_wt + wt[i];
total_tat = total_tat + tat[i];
cout << " " << i+1 << "\t\t" << bt[i] <<"\t "
<< wt[i] <<"\t\t " << tat[i] <<endl;
}
cout << "Average waiting time = "
<< (float)total_wt / (float)n;
cout << "\nAverage turn around time = "
<< (float)total_tat / (float)n;
}


int main(){
	
// Lable for goto statement
	menu:  
	cout<<"1) First come first serve \n";
	cout<<"2) Shortest job first (Non-Preamptive) \n";
	cout<<"3) Priority (Preamptive)\n";
	cout<<"4) Priority (Non-Preamptive)\n";
	cout<<"5) Round Robin \n";
	cout<<"6) Banker's Algorithm\n";
	cout<<"7) Shortest job first (Preamptive) \n";
	cout<<"8) Main Menu  \n";
	cout<<"Enter your choice:";
	int s;
	char ch;
	cin>>s;
	switch(s){
	case 1:
	{
		process p[MAX_PROCESS],temp;
  int num,i,j;
  cout<<"ENTER NUMBER OF PROCESSES : ";
  cin>>num;
  for(i=0;i<num;++i)
    p[i].input_process(i);
  for(i=0;i<num;++i)
  {
    for(j=i+1;j<num;++j)
    {
      if(p[i].get_at()>p[j].get_at())
      {
        temp=p[i];
        p[i]=p[j];
        p[j]=temp;
      }
    }
  }
  calc_wait_tat(p,num);
  display(p,num);
  cout<<"\n\n";
  cout<<"Enter 'Y' to again go to main menu..\n";
  cin>>ch;
  if(ch=='y' || ch=='y'){
  	goto menu;
  }
  else
  return 0;
	}
	
	break;
	case 2:
	{
      int n,temp,tt=0,min,d,i,j;
      float atat=0,awt=0,stat=0,swt=0;

      cout<<"enter no of process"<<endl;
      cin>>n;
      int a[n],b[n],e[n],tat[n],wt[n];
  
      for(i=0;i<n;i++)
      {
            cout<<"enter arival time ";       //input
            cin>>a[i];
      }
      for(i=0;i<n;i++)
      {
            cout<<"enter brust time ";      //input
            cin>>b[i];
      }
      for(i=0;i<n;i++)
      {
         for(j=i+1;j<n;j++)
          {
                if(b[i]>b[j])
                {
                      temp=a[i];
                      a[i]=a[j];
                      a[j]=temp;

                      temp=b[i];
                      b[i]=b[j];
                      b[j]=temp;
                }
          }
      }
      min=a[0];
      for(i=0;i<n;i++)
      {
            if(min>a[i])
            {
                  min=a[i];
                  d=i;
            }
      }
      tt=min;
      e[d]=tt+b[d];
      tt=e[d];

      for(i=0;i<n;i++)
      {
            if(a[i]!=min)
            {
                  e[i]=b[i]+tt;
                  tt=e[i];
            }
      }
      for(i=0;i<n;i++)
      {

            tat[i]=e[i]-a[i];
            stat=stat+tat[i];
            wt[i]=tat[i]-b[i];
            swt=swt+wt[i];
      }
      atat=stat/n;
      awt=swt/n;
      cout<<"Process  Arrival-time(s)  Burst-time(s)  Waiting-time(s)  Turnaround-time(s)\n";

    for(i=0;i<n;i++)
    {
    cout<<"P"<<i+1<<"              "<<a[i]<<"                "<<b[i]<<"                  "<<wt[i]<<"               "<<tat[i]<<endl;
    }

    cout<<"awt="<<awt<<" atat="<<atat;  //average waiting time and turn around time
    cout<<"\n\n";
  cout<<"Enter 'Y' to again go to main menu..\n";
  cin>>ch;
  if(ch=='y' || ch=='y'){
  	goto menu;
  }
  else
  return 0;
}
	break;
	case 3:
	{
    int nop,choice,i,qt;
    cout<<"Enter number of processes\n";
    cin>>nop;
    cout<<"Enter process, priority, AT, BT\n";
    insert(nop);
    disp(nop,1);
    cout<<"\n\n";
  cout<<"Enter 'Y' to again go to main menu..\n";
  cin>>ch;
  if(ch=='y' || ch=='y'){
  	goto menu;
  }
  else
  return 0;
}
	break;
	case 5:
	{
	// process id's
int processes[] = { 1, 2, 3};
int n = sizeof processes / sizeof processes[0];
// Burst time of all processes
int burst_time[] = {10, 5, 8};
// Time quantum
int quantum = 2;
findavgTime(processes, n, burst_time, quantum);
return 0;

	cout<<"\n\n";
  cout<<"Enter 'Y' to again go to main menu..\n";
  cin>>ch;
  if(ch=='y' || ch=='y'){
  	goto menu;
  }
  else
  return 0;

}
	break;
	case 4:
		{
			int a[10],b[10],x[10],pr[10]={0};
 int waiting[10],turnaround[10],completion[10];
 int i,j,smallest,count=0,time,n;
 double avg=0,tt=0,end;
 cout<<"\nEnter the number of Processes: ";
 cin>>n;
 for(i=0;i<n;i++)
 {
 cout<<"\nEnter arrival time of process: ";
 cin>>a[i];
 }
 for(i=0;i<n;i++)
 {
 cout<<"\nEnter burst time of process: ";
 cin>>b[i];
 }
 for(i=0;i<n;i++)
 {
 cout<<"\nEnter priority of process: ";
 cin>>pr[i];
 }
 for(i=0;i<n;i++)
 x[i]=b[i];
 pr[9]=-1;
 for(time=0;count!=n;time++)
 {
 smallest=9;
 for(i=0;i<n;i++)
 {
 if(a[i]<=time && pr[i]>pr[smallest] && b[i]>0 )
 smallest=i;
 }
 time+=b[smallest]-1;
 b[smallest]=-1;
 count++;
 end=time+1;
 completion[smallest] = end;
 waiting[smallest] = end - a[smallest] - x[smallest];
 turnaround[smallest] = end - a[smallest];
 }
 cout<<"Process"<<"\t"<< "burst-time"<<"\t"<<"arrival-time" <<"\t"<<"waiting-time"
<<"\t"<<"turnaround-time"<< "\t"<<"completion-time"<<"\t"<<"Priority"<<endl;
 for(i=0;i<n;i++)
 {

cout<<"p"<<i+1<<"\t\t"<<x[i]<<"\t\t"<<a[i]<<"\t\t"<<waiting[i]<<"\t\t"<<turnaround[i]<<"\t\
t"<<completion[i]<<"\t\t"<<pr[i]<<endl;
 avg = avg + waiting[i];
 tt = tt + turnaround[i];
 }
 cout<<"\n\nAverage waiting time ="<<avg/n;
 cout<<" Average Turnaround time ="<<tt/n<<endl;
 cout<<"\n\n";
  cout<<"Enter 'Y' to again go to main menu..\n";
  cin>>ch;
  if(ch=='y' || ch=='y'){
  	goto menu;
  }
  else
  return 0;
 break;
		}
		case 6:{
				int keepon = 1;
	cout<<"Enter No. of processes: ";
	cin>>p;
	cout<<"\n";
	cout<<"Enter the current resources: ";
	cin>>current[0]>>current[1]>>current[2];
	for (int i = 0; i < p; ++i)
	{
		cout<<"\n\n			Process P"<<i+1<<" Details\n";
		cout<<"Enter Allocation : ";
		cin>>allocation[i][0]>>allocation[i][1]>>allocation[i][2];
		cout<<"Enter Max :";
		cin>>Max[i][0]>>Max[i][1]>>Max[i][2];
		need[i][0]=Max[i][0]-allocation[i][0];need[i][1]=Max[i][1]-allocation[i][1];need[i][2]=Max[i][2]-allocation[i][2];
	}
	cout<<"\n\n			Table for Bankers Algo\n\n";
	cout<<"Initial Resources: "<<current[0]<<" "<<current[1]<<" "<<current[2]<<"\n\n";
	cout<<"Process    Max    Allocation    Need\n";
	for (int i = 0; i < p; ++i)
	{
		cout<<"  P"<<i+1<<"    ";
		cout<<"  "<<Max[i][0]<<" "<<Max[i][1]<<" "<<Max[i][2]<<"     ";
		cout<<" "<<allocation[i][0]<<" "<<allocation[i][1]<<" "<<allocation[i][2]<<"     ";
		cout<<" "<<need[i][0]<<" "<<need[i][1]<<" "<<need[i][2];
		cout<<"\n";
	}
	cout<<"\n\n";
	Calculate();
	while(keepon){
		int val,pro;
		cout<<"\n\nSelect Below oprations:\n\n";
		cout<<"1.Change Max of process: \n";
		cout<<"2.Change Allocation of process\n";
		cout<<"3.Change Initial Resources\n";
		cout<<"4.Exit\n\n";
		cin>>val;
		if (val==1)
		{
			cout<<"\n\nEnter Process No: ";
			cin>>pro;
			cout<<"\nEnter New Max: ";
			cin>>Max[pro-1][0]>>Max[pro-1][1]>>Max[pro-1][2];
		}
		else if (val==2)
		{
			cout<<"\n\nEnter Process No: ";
			cin>>pro;
			cout<<"\nEnter New Allocation: ";
			cin>>allocation[pro-1][0]>>allocation[pro-1][1]>>allocation[pro-1][2];
		}
		else if (val==3)
		{
			cout<<"\nEnter Initial Resources: ";
			cin>>current[0]>>current[1]>>current[2];
		}
	
		Calculate();
		cout<<"\n\n";
  cout<<"Enter 'Y' to again go to main menu..\n";
  cin>>ch;
  if(ch=='y' || ch=='y'){
  	goto menu;
  }
  else
  return 0;
	}
			break;
		}
		case 7:{
			int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::vector<Process> processes(n);
    std::cout << "Enter the arrival time and burst time for each process:\n";
    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        std::cout << "Process " << i + 1 << " - Arrival Time: ";
        std::cin >> processes[i].arrivalTime;
        std::cout << "Process " << i + 1 << " - Burst Time: ";
        std::cin >> processes[i].burstTime;
    }

    sjnPreemptive(processes);

    printProcesses(processes);
    cout<<"\n\n";
  cout<<"Enter 'Y' to again go to main menu..\n";
  cin>>ch;
  if(ch=='y' || ch=='y'){
  	goto menu;
  }
  else
  return 0;

			break;
		}
	default:
	cout<<"You entered a worng choice!";	
	}
}

//FCFS
void calc_wait_tat(process *p,int n)
{
  int i;
  p[0].response_time=0;
  for(i=1;i<n;++i)
  {
    p[i].response_time=p[i-1].burst_time+p[i-1].response_time;
    if(p[i].response_time<p[i].arrival_time)
      p[i].response_time=p[i].arrival_time;
  }
  p[0].waiting_time=0;
  for(i=1;i<n;++i)
    p[i].waiting_time=p[i].response_time-p[i].arrival_time;
  for(i=0;i<n;++i)
    p[i].turnaround_time=p[i].waiting_time+p[i].burst_time;
}
void average(process *p,int n)
{
  float avg_wt=0,avg_tat=0;
  for(int i=0;i<n;++i)
  {
    avg_wt+=(float)p[i].waiting_time;
    avg_tat+=(float)p[i].turnaround_time;
  }
  avg_wt/=n;
  avg_tat/=n;
  cout<<"\n\nAVERAGE WAITING TIME : "<<avg_wt;
  cout<<"\nAVERAGE TURN AROUND TIME : "<<avg_tat;
}
void display(process *p,int n)
{
        cout<<"Processes "<<"  Burst time  "<<" Waiting time  "<<" Turn around time\n";
        for (int i=0;i<n;i++)
        {
                cout<<"\n   "<<p[i].process_num<<"\t\t"<<p[i].burst_time<<"\t     "<<p[i].waiting_time<<"\t\t      "<<p[i].turnaround_time;
        }
        average(p,n);
}
//FCFS ends
