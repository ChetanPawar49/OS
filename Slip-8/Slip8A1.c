#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 50

int dirlen = 0;

typedef struct directory
{
	char fileName[20];
	int startBlock;
	int length;
}dir;

void showBitVector(int *a,int size)
{
	int i;
	for(i=0;i<size;++i)
		printf("%d",a[i]);
}

void showDirectory(dir d[10])
{
	int i;
	printf("\nFileName\tStarting Block\tNo.of blocks\n");
	for(i=0;i<dirlen;i++)
		printf("%s\t%d\t%d\n",d[i].fileName,d[i].startBlock,d[i].length);
	printf("Total files = %d\n",i);
	
}

void changeDirectory(dir d[20],char fn[20],int blocks,int start)
{
	strcpy(d[dirlen].fileName,fn);
	d[dirlen].startBlock=start;
	d[dirlen++].length=blocks;
}

void freeDirectory(dir d[20],int index)
{
	int i=index+1;
	for(;i<dirlen;i++)
		d[i-1]=d[i];
	dirlen--;
}

int searchInDir(char fn[20],dir d[10])

{
	int i;
	for(i=0;i<=dirlen;++i)
	{
		printf("\n%s-%s\n",fn,d[i].fileName);
		if(strcmp(fn,d[i].fileName)==0)
			return i;
	}
	return -1;
}

int createFile(int bitVector[50],int size,int blocks)
{
	int i=0,count=0;
	for(;i<size;++i)
	{
		if(bitVector[i]==0)
			count++;
		if(count==blocks)
			return (i-blocks+1);
		if(bitVector[i]==1)
		{
			count=0;
			continue;
		}
	}
	return 0;
}
				
void changeBitVector(int bitVector[N],int size,int start,int len)
{
	int i;
	for(i=start;i<start+len+1;i++)
		bitVector[i]=1;
}
				
void freeBitVector(int bitVector[N],int size,int start,int len)
{
	int i;
	printf("\nstart=%d\tblocks=%d\n",start,len);
	for(i=start;i<start+len;i++)
		bitVector[i]=0;
}

int main()
{
	dir dirent[10];
	char fn[20];
	int bitVector[N];
	int i,ch,blocks,status,found;
	for(i=0;i<N;i++)
		bitVector[i]=rand()%2;
	do
	{
		printf("\n0.Exit\n1.Show Bit Vector\n2.Create New file\n");
		printf("3.Show Directory\n4.Delete File\nEnter your choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:	showBitVector(bitVector,N);
					break;
			case 2:	printf("\nEnter name of file:");
					scanf("%s",fn);
					fn[strlen(fn)]='\0';
					found=searchInDir(fn,dirent);
					if(found==1)
					{
						printf("\nFile %s already exists in directory",fn);
						printf("\nPlease enter other name\n");
						break;
					}
					printf("\nEnter number of blocks to allocate to file:");
					scanf("%d",&blocks);
					status=createFile(bitVector, N,blocks);
					printf("\nstart block=%d",status);
					if(status==0)
						printf("\nFile cant be allocated %d sequential blocks",blocks);
					else
					{
						changeBitVector(bitVector,N,status,blocks);
						changeDirectory(dirent,fn,blocks,status);
					}
					break;
			case 3:	showDirectory(dirent);
					break;
			case 4:	if(dirlen==0)
						printf("No file exists in directory to delete\n");
					else
					{
						printf("\nEnter name of file:");
						scanf("%s",fn);
						fn[strlen(fn)]='\0';
						found=searchInDir(fn,dirent);
						if(found==-1)
						{
							printf("\nFile %s doesnt exist \n",fn);
							break;
						}						
						else
						{
							freeBitVector(bitVector,N,dirent[found].startBlock,dirent[found].length);
							freeDirectory(dirent,found);
						}
					}
		}
	}while(ch!=0);
	return 0;
}
