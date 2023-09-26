/*
 * First Come First Serve ( FCFS )
 * Page replacement Algorithm in Operating System
 * @author : Rongala Gangadhar
 */



#include<stdio.h>
#include<stdbool.h>

void main(){

    int n,pages[20],frames[10],FRAME_SIZE,pointer=-1,pageFault=0,pageHit=0;
    int i,j;
    bool present;

    printf("\nEnter no of pages : ");
    scanf("%d",&n);
    printf("\nEnter %d references of %d pages : ",n,n);
    for(i=0;i<n;i++){
        scanf("%d",&pages[i]);
    }
    printf("\nEnter size of frames : ");
    scanf("%d",&FRAME_SIZE);
    for(i=0;i<FRAME_SIZE;i++){
        frames[i]=-1;
    }

    printf("\n\nThe reference string is : ");
    for(i=0;i<n;i++){
        printf("%d ",pages[i]);
    }
    printf("\n\n");

    for(i=0;i<n;i++){
        present=false;
        for(j=0;j<FRAME_SIZE;j++){
            if(pages[i] == frames[j]){
                present=true;
            }
        }
        if(present){
            pageHit++;
        }else{
            pointer = (pointer+1)%FRAME_SIZE;
            frames[pointer]=pages[i];
            pageFault++;
        }

        printf("\npage : %d\tframes : [ ",pages[i]);
        for(j=0;j<FRAME_SIZE;j++){

            if(pointer == j){
                printf(" `%d` ",frames[j]);
            }else{
                printf(" %d ",frames[j]);
            }
          
        }
        printf("]");
        if(present){
            printf("\t\tPage Hit\n");
        }else{
            printf("\t\tPage Fault\n");
        }
    }

    printf("\nThe Total Page Fault Count : %d\n",pageFault);
    printf("\nThe Total Page Hit Count : %d\n\n",pageHit);

}