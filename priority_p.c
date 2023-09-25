/*
 * Preemptive Priority
 * Scheduling Algorithm in Operating System
 * @author : Rongala Gangadhar
 */

#include<stdio.h>

int n,process[20][20],ready_stack[20],top = -1,executed = 0,time = -1,running = -1;

void sortJobs();
void checkJobs();

void main(){
    
    int i,j;
    float avg_wait = 0;
    printf("\nEnter no of process : ");
    scanf("%d",&n);
    
    /*Index : 
          0 - process id
          1 - priority
          2 - arrival time
          3 - burst time
          4 - remaining burst time
          5 - response time
          6 - completion time
          7 - tat
          8 - waiting time
          9 - readyStack status 1 - added 0 - not added
                            */

    for(i=0;i<n;i++){
        process[i][0] = i;
        printf("\n\nEnter process P%d priority : ",i);
        scanf("%d",&process[i][1]);
        printf("\nEnter process P%d arrival time : ",i);
        scanf("%d", &process[i][2]);
        printf("\nEnter process P%d burst time : ",i);
        scanf("%d",&process[i][3]);
        process[i][4]=process[i][3];
        process[i][9]=0;
    }

    while(executed != n){
        time++;
        checkJobs();
        sortJobs();

    
        if(top > -1){
            running=ready_stack[top];
        }
        

        if(running > -1){

            if(process[running][3] == process[running][4] && process[running][3] == 1){
                process[running][5]=time;
                process[running][6]=time+1;
                process[running][4]--;
                executed++;
                process[running][7] = process[running][6] - process[running][2];
                process[running][8] = process[running][7] - process[running][3];
            }

            else if(process[running][3] == process[running][4] && process[running][3] > 1 ){
                process[running][5]=time;
                process[running][4]--;
            }

            else if(process[running][4]==1 && process[running][3] != process[running][4]){
                process[running][6]=time+1;
                process[running][4]--;
                executed++;
                process[running][7] = process[running][6] - process[running][2];
                process[running][8] = process[running][7] - process[running][3];
             }

            else if(process[running][4] < process[running][3] && process[running][4] > 1){
                process[running][4]--;
            }

        }

        //To Enable tracing uncomment below block of code
        printf("\ntime: %d - %d\tready_stack : [ ",time,time+1);
        if(top == -1 ){
            printf(" ");
        }else{
            for(i=top;i>=0;i--){
                printf("P%d ",ready_stack[i]);
            }
        }
        printf("]\tRunning: P%d\texecuted: %d\n",running,executed);
        

        if(process[running][4] == 0){
            top--;
        }

      

    }

    printf("\nId\tPRT\tAT\tBT\tRT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",process[i][0],process[i][1],process[i][2],process[i][3],process[i][5],process[i][6],process[i][7],process[i][8]);
        avg_wait+=process[i][8];
    }
    avg_wait/=n;
    printf("\nAverage Waiting Time is : %.2f",avg_wait);
    
}


void checkJobs(){
    for(int i=0;i<n;i++){
        if(process[i][2] == time && process[i][9] == 0){
            top++;
            ready_stack[top]=process[i][0];
            process[i][9]=1;
        }
    }
}

void sortJobs(){
    int i,j,temp;
    for(i=0;i<top;i++){
        for(j=i+1;j<=top;j++){
            if(process[ready_stack[i]][1] < process[ready_stack[j]][1]){
                temp = ready_stack[i];
                ready_stack[i] = ready_stack[j];
                ready_stack[j] = temp;
            }
        }
    }
}