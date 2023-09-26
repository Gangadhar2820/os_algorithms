/*
 * Bankers Algorithm in Operating System
 * to avoid DEADLOCK
 * @author : Rongala Gangadhar
 */

#include<stdio.h>

void main(){

    int np,nr,ALLOC[10][10],AVAIL[10],MAX[10][10],NEED[10][10];
    int i,j,k,completed=0;
    printf("\nEnter no of Process : ");
    scanf("%d",&np);
    printf("\nEnter no of resources type : ");
    scanf("%d",&nr);

    printf("\nMAXIMUM RESOURCES :\n");
    for(i=0;i<np;i++){
        printf("FOR P%d : ",i);
        for(j=0;j<nr;j++){
            scanf("%d",&MAX[i][j]);
        }
    }

    printf("\nALLOCATED RESOURCES :\n");
    for(i=0;i<np;i++){
        printf("FOR P%d : ",i);
        for(j=0;j<nr;j++){
            scanf("%d",&ALLOC[i][j]);
        }
    }

    printf("\nAVAILABLE RESOURCES :\n");
    for(j=0;j<nr;j++){
        printf("Type-%d : ",j+1);        
        scanf("%d",&AVAIL[j]);
    }
    printf("\n\nThe Need Matrix is : \n");
    for(i=0;i<np;i++){
        printf("\n\t\tP%d",i);
        for(j=0;j<nr;j++){
            NEED[i][j]=MAX[i][j]-ALLOC[i][j];
            printf("\t%d",NEED[i][j]);
        }   
    }

    while(completed != np){

        for(i=0;i<np;i++){
            for(j=0;j<nr;j++){   
                if(NEED[i][j] > AVAIL[j] || NEED[i][j] == -1){
                    break;
                }
            }
            if(j == nr){
                printf("\n\n* FOR P%d , NEED resources <= AVAILABLE resources\n",i);
                for(j=0;j<nr;j++){
                    AVAIL[j]+=ALLOC[i][j];
                    NEED[i][j]=-1;
                } 
                completed++;
                printf("\n\tNEW AVAILABLE RESOURCES: ");
                for(j=0;j<nr;j++){
                    printf(" %d ",AVAIL[j]);
                }
            }
        }
    }

    printf("\n\nTOTAL RESOURCES : ");
    for(i=0;i<nr;i++){
        printf(" %d ",AVAIL[i]);
    }
    
}