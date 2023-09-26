/*
 * Optimal
 * Page replacement Algorithm in Operating System
 * @author : Rongala Gangadhar
 */


#include<stdio.h>
#include<stdbool.h>

void main(){

    int n,pages[20],frames[10],FRAME_SIZE,pointer=0,pageFault=0,pageHit=0,index[10];
    int i,j,k;
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
        index[i]=100;
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
        }
        else{
           if(pointer < FRAME_SIZE){
            frames[pointer] = pages[i];
             pointer++;
           }
           else{
            for(j=0;j<FRAME_SIZE;j++){
                index[j]=100;
                for(k=i+1;k<n;k++){
                    if(frames[j]==pages[k]){
                        index[j]=k;
                        break;
                    }
                }
            }
            k=index[0];
            for(j=1;j<FRAME_SIZE;j++){
                if(index[j]>k){
                    k=index[j];
                }
            }
            for(j=0;j<FRAME_SIZE;j++){
                if(k == index[j]){
                    frames[j]=pages[i];
                    break;
                }
            }
           }
            pageFault++;
        }

        printf("\npage : %d\tframes : [ ",pages[i]);
        for(j=0;j<FRAME_SIZE;j++){
                printf(" %d ",frames[j]);  
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