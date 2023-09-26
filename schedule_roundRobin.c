/*
 * Preemptive Round Robin
 * Scheduling Algorithm in Operating System
 * @author : Rongala Gangadhar
 */

#include<stdio.h>

int n,process[20][20],ready_stack[20],top=-1,current=-1,executed=0,running=-1,time=-1,
timeSlice ;

void checkJobs();

void main(){ 
    int i,j,timeQuantum ;
    float avg_wait = 0;
    printf("\nEnter no of process : ");
    scanf("%d",&n);
    printf("\nEnter Time Quantum : ");
    scanf("%d",&timeQuantum);
    timeSlice=timeQuantum;
    /*Index  0 - id
             1 - arrival time
             2 - burst time
             3 - remaining time
             4 - response time
             5 - completion time
             6 - tat
             7 - waiting time
             8 - readyQueue status 1 - added 0 - not added
                                  */
    for(i=0;i<n;i++){
        process[i][0]=i;
        printf("\n\nEnter process P%d arrival time : ",i);
        scanf("%d",&process[i][1]);
        printf("\nEnter process P%d burst time : ",i);
        scanf("%d",&process[i][2]);
        process[i][3]=process[i][2];
        process[i][8]=0;

    }

    while(executed != n){

        time++;
        checkJobs();
        if(current == -1 && top > -1){
            current = 0;
            running = ready_stack[current];
        }

        if(timeSlice < 1 && current != -1 || process[ready_stack[current]][3] == 0 ){
            timeSlice = timeQuantum;
            for(i=0;i<=top;i++){
                current = (current+1)%(top+1);
                if(process[ready_stack[current]][3]!=0){
                break;
                }
            }
            running=ready_stack[current];
        }   
    
        if(running > -1){
            if(process[running][2] == process[running][3] && process[running][2] == 1 ){
                process[running][4]=time;
                process[running][5]=time+1;
                process[running][3]--;
                executed++;
                timeSlice=0;
                process[running][6] = process[running][5] - process[running][1];
                process[running][7] = process[running][6] - process[running][2];
            }

            else if(process[running][2] == process[running][3] && process[running][3] > 1 ){
                process[running][4]=time;
                process[running][3]--;
                timeSlice--;
            }
            else if(process[running][3]==1 && process[running][2] != process[running][3]){
                process[running][5]=time+1;
                process[running][3]--;
                executed++;
                timeSlice=0;
                process[running][6] = process[running][5] - process[running][1];
                process[running][7] = process[running][6] - process[running][2];
                
            }else if(process[running][3] < process[running][2] && process[running][3] > 1){
                process[running][3]--;
                timeSlice--;  
            }
            
        }
        //for tracing uncomment below line of code
        // printf("\ntime : %d -- %d\trunning : P%d\texecuted : %d\n",time,time+1,running,executed);
        
    }

    printf("\nId\tAT\tBT\tRT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d\n",process[i][0],process[i][1],process[i][2],process[i][4],process[i][5],process[i][6],process[i][7]);
        avg_wait+=process[i][7];
    }
    avg_wait/=n;

    printf("\nAverage waiting time : %.2f",avg_wait);

}

void checkJobs(){
    for(int i=0;i<n;i++){
        if(process[i][1] == time && process[i][8] == 0){
            top++;
            ready_stack[top]=process[i][0];
            process[i][8]=1;  
        }
    }
}