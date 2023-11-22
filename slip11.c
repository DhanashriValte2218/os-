//LFU
#include<stdio.h>

struct node
{
  int pno, freq;
}frames[20];
int n;

int page_found(int pno)
{
  int fno;
  for(fno=0;fno<n;fno++)
  {
    if(frames[fno].pno==pno)
	   return fno;
  }
  return -1;
}

int get_free_frame()
{  int fno;
  for (fno=0; fno<=n; fno++)
  {
    if (frames[fno].pno==-1)
      return(fno);
  }
   return(-1);
}

int get_lfu_frame()
{
  int fno;
  int selfno=0;
  for (fno=1; fno<n; fno++)
  {
    if(frames[fno].freq<frames[selfno].freq)
	selfno=fno;
  }
  return selfno;
}
void main()
{

   int p_request[]={5,8,10,14,10,9,5,10,8,5,1,10,9,12,10};
   int size=15;
   int page_falts=0,i,j,fno;
   
   printf("\nHow many frames:");  scanf("%d",&n);
   //initialize frames
   for (i=0; i<n; i++)
   { frames[i].pno=-1;
     frames[i].freq=0;
   }

   printf("\nPageNo     Page Frames          	Page Fault");
   printf("\n---------------------------------------------------");
   for(i=0;i<size;i++)
   {
	 j=page_found(p_request[i]);
	 if(j==-1)  //page fault occurs
	 {
	   j=get_free_frame();
	   if (j==-1) //no free frame - do page replacement
		 j=get_lfu_frame();
	   page_falts++;
	   frames[j].pno=p_request[i];
	   frames[j].freq=1;
	   printf("\n%4d\t ",p_request[i]);
	   for (fno=0; fno<n; fno++)
		 printf("%4d:%2d",frames[fno].pno,frames[fno].freq);
	   printf(" : YES");
	 }
	else //page found in frame j
	{
	   frames[j].freq++;
	   printf("\n%4d\t ",p_request[i]);
	   for (fno=0; fno<n; fno++)
		 printf("%4d:%2d",frames[fno].pno,frames[fno].freq);
	   printf(" : NO");
	}
   }//for
  printf("\n-------------------------------------------------------");
  printf("\n Number of Page_Falts=%d\n",page_falts);
  
}
//==========================================================================================
//========================================================================================
//list
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<dirent.h>
void make_toks(char *s,char *tok[])
{
	int i=0;
	char *p;
	p=strtok(s," ");
	while(p!=NULL)
	{
		tok[i++]=p;
		p=strtok(NULL," ");
	}
	tok[i]=NULL;
}
void list(char *dn,char op)
{
	DIR *dp;
	struct dirent *entry;
	int dc=0,fc=0;
	dp=opendir(dn);
	if(dp==NULL)
	{
		printf("dir %s not found\n",dn);
		return;
	}
	switch(op)
	{
		case 'f':while(entry=readdir(dp))
			{
				if(entry->d_type==DT_REG)
					printf("%s\n",entry->d_name);
			}
			break;
		case 'n':while(entry=readdir(dp))
			{
				if(entry->d_type==DT_DIR)dc++;
				if(entry->d_type==DT_REG)fc++;	
			}
			printf("%d Dir(s)\t%d File(s)\n",dc,fc);
			break;
		case 'i':while(entry=readdir(dp))
			{
				if(entry->d_type==DT_REG)
					printf("%s\t%d\n",entry->d_name,entry->d_fileno);
			}
	}
	closedir(dp);
}
int main()
{
	char buff[80],*args[10];
	int pid;
	while(1)
	{
	printf("myshell$");
	fflush(stdin);
	fgets(buff,80,stdin);
	buff[strlen(buff)-1]='\0';
	make_toks(buff,args);
	if(strcmp(args[0],"list")==0)
		list(args[2],args[1][0]);
	else
	{
		pid=fork();
		if(pid>0)
			wait();
		else
		{
			if(execvp(args[0],args)==-1)
			printf("Bad Command");
		}
	}
	}
	return 0;
}