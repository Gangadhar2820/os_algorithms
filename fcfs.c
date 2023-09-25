/*
 * Non-preemptive First Come First Serve (FCFS)
 * Scheduling Algorithm in Operating System
 * @author : Rongala Gangadhar
 */


#include<stdio.h>

int n,process[20][20],time=-1,ready_Q[20],front=-1,rear=-1,running=-1,executed=0;
void checkJobs();

void main(){
    int i;
    float avg_wait=0;
    printf("\nEnter no of process : ");
    scanf("%d",&n);
    /* index 0 : process id
             1 : arrival time 
             2 : burst time
             3 : remaining time
             4 : response time
             5 : completion time
             6 : TAT
             7 : waiting time
             8 - readyQueue status 1 - added 0 - not added*/
    for(i=0;i<n;i++){
        printf("\n\nEnter process P%d Arrival time : ",i);
        scanf("%d",&process[i][1]);
        printf("\nEnter process P%d Burst time : ",i);
        scanf("%d",&process[i][2]);
        process[i][3]=process[i][2];
        process[i][0]=i;
        process[i][8]=0;
    }

    while(executed != n){
        time++;
        checkJobs();

        if(running == -1){
            if(front < rear){
                front++;
                running=ready_Q[front];
            }
        }

        if(running > -1){

            if(process[running][2] == process[running][3] && process[running][2] == 1){
                process[running][4]=time;
                process[running][5]=time+1;
                process[running][3]--;
                executed++;
                process[running][6] = process[running][5] - process[running][1];
                process[running][7] = process[running][6] - process[running][2];
            }

            else if(process[running][2] == process[running][3] && process[running][2] > 1 ){
                process[running][4]=time;
                process[running][3]--;
            }

            else if(process[running][3]==1 && process[running][2] != process[running][3]){
                process[running][5]=time+1;
                process[running][3]--;
                executed++;
                process[running][6] = process[running][5] - process[running][1];
                process[running][7] = process[running][6] - process[running][2];
            }

            else if(process[running][3] < process[running][2] && process[running][3] > 1){
                process[running][3]--;
            }

        }
        //To Enable tracing uncomment below block of code

        // printf("\ntime : %d - %d\tready_Q : [ ",time,time+1);
        // if(rear == -1){
        //     printf("   ");
        // }else{
        //     for(i=front;i<=rear;i++){
        //         printf("P%d ",ready_Q[i]);
        //     }
        // }
        // printf("]\tRunning : P%d\texecuted : %d\n",running,executed);

        if(process[running][3] == 0){
            running = -1;
        }
    }

    printf("\nId\tAT\tBT\tRT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d\n",process[i][0],process[i][1],process[i][2],process[i][4],process[i][5],process[i][6],process[i][7]);
        avg_wait+=process[i][7];
    }
    avg_wait/=n;
    printf("\nAverage Waiting Time is : %.2f",avg_wait);

}

void checkJobs(){
    for(int i=0;i<n;i++){
        if(time == process[i][1] && process[i][8] == 0){
            rear++;
            ready_Q[rear]=process[i][0];
            process[i][8]=1;
        }
    }
}