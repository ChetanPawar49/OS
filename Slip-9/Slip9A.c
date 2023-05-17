#include<stdio.h> //Slip7A
#include<stdlib.h> 
int ind,A[10][10],M[10][10],N[10][10],Av[10],Safe[10],Finish[10],nor,nop,work[10],req[10][10]; 
void AcceptData(int X[][10]) 
{ 
int i,j; 
for(i=0;i<nop;i++) 
{ 
printf("P%d:\n",i); 
for(j=0;j<nor;j++) 
{ 
printf("%c:",65+j); 
scanf("%d",&X[i][j]); 
} 
} 
} 
void AcceptAvailability() 
{ 
int i; 
for(i=0;i<nor;i++) 
{ 
printf("%c",65+i); 
scanf("%d",&Av[i]); 
work[i]=Av[i]; 
} 
} 
void DisplayData() 
{ 
int i,j; 
printf("\n\tAllocation\t\tMax\t\tNeed\n"); 
printf("\t"); 
for(i=0;i<3;i++) 
{ 
for(j=0;j<nor;j++) 
printf("%4c",65+j); 
printf("\t"); 
} 
for(i=0;i<nop;i++) 
{ 
printf("\nP%d\t",i); 
for(j=0;j<nor;j++) 
printf("%4d",A[i][j]); 
printf("\t"); 
for(j=0;j<nor;j++) 
printf("%4d",M[i][j]); 
printf("\t"); 
for(j=0;j<nor;j++) 
printf("%4d",N[i][j]); 
} 
printf("\nAvailable\n"); 
for(j=0;j<nor;j++) 
printf("%4d",work[j]); 
} 
void CalcNeed() 
{ 
int i,j; 
for(i=0;i<nop;i++) 
for(j=0;j<nor;j++) 
N[i][j]=M[i][j]-A[i][j]; 
} 
void Resource_Request(int no) 
{ 
int i,f11=0,f12=0; 
for(i=0;i<nor;i++) 
{ 
if(req[no][i]<=N[no][i]) 
f11=1; 
else 
f11=0; 
} 
if(f11==0) 
{ 
printf("\n Error!Process has exceeded its maximum claim"); 
exit(0); 
} 
if(f11==1) 
{ 
for(i=0;i<nor;i++) 
{ 
if(req[no][i]<=work[i]) 
f12=1; 
else 
f12=0; 
} 
if(f12==0) 
{ 
printf("\n Process has to wait for resources"); 
exit(0); 
} 
} 
if(f11==1 && f12==1) 
{ 
for(i=0;i<nor;i++) 
{ 
work[i]=work[i]-req[no][i]; 
A[no][i]=A[no][i]+req[no][i]; 
N[no][i]=N[no][i]-req[no][i]; 
} 
} 
} 
int checkNeed(int pno) 
{ 
int i; 
for(i=0;i<nor;i++) 
if(N[pno][i]>work[i]) 
return(0); 
return(1); 
} 
void Banker() 
{ 
int i=0,j=0,k=0,flag=0; 
while(flag<2) 
{ 
if(!Finish[i]) 
{ 
printf("\nNeed%d(",i); 
for(j=0;j<nor;j++) 
printf("%d",N[i][j]); 
if(!checkNeed(i)) 
{ 
printf("\b)>Work"); 
for(j=0;j<nor;j++) 
printf("%d",work[j]); 
printf("\b)"); 
printf("\nNeed Cannot be satisfied,consider next process"); 
} 
else 
{ 
printf("b)<=Work("); 
for(j=0;j<nor;j++) 
printf("%d,",work[j]); 
printf("\b)"); 
printf("\nNeed can be satisfied,so allocate required resources"); 
printf("\nWork(%d)=",i); 
for(j=0;j<nor;j++) 
{ 
work[j]+=A[i][j]; 
} 
for(j=0;j<nor;j++) 
printf("%4d",work[j]); 
printf("\nAfter P%d terminates it will release all its resources\n",i); 
Safe[k++]=i; 
Finish[i]=1; 
} 
} 
if((i+1)%nop==0) 
flag++; 
i=(i+1)%nop; 
} 
if(k==nop) 
{ 
printf("\nSystem is in safe state..."); 
printf("\nSafe Sequence:"); 
for(i=0;i<k;i++) 
printf("P%d->",Safe[i]); 
printf("\b\b"); 
} 
else 
{ 
printf("\nSystem is in not safe state..."); 
} 
} 
int main() 
{ 
int i; 
printf("\nEnter no of processes & No of Resources:"); 
scanf("%d%d",&nop,&nor); 
printf("Enter Allocation\n"); 
AcceptData(A); 
printf("Enter Max Requirement\n"); 
AcceptData(M); 
printf("Enter Availability\n"); 
AcceptAvailability(); 
CalcNeed(); 
DisplayData(); 
Banker(); 
printf("\n Enter Process number from which request arrives:"); 
scanf("%d",&ind); 
printf("\nEnter request for process%d\n",ind); 
for(i=0;i<nor;i++) 
{ 
printf("%c",65+i); 
scanf("%d",&req[ind][i]); 
} 
for(i=0;i<nop;i++) 
Finish[i]=0; 
for(i=0;i<nor;i++) 
work[i]=Av[i]; 
Resource_Request(ind); 
Banker(); 
return(0); 
} 