//MFU
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

int get_mfu_frame()
{
  int fno;
  int selfno=0;
  for (fno=1; fno<n; fno++)
  {
    if(frames[fno].freq>frames[selfno].freq)
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
	   if (j==-1) //no free fram`e - do page replacement
		 j=get_mfu_frame();
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
   }
  printf("\n-------------------------------------------------------");
  printf("\n Number of Page_Falts=%d\n",page_falts);
  
}
//======================================================================================
//=======================================================================================

//search



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
char comm[100],*ptr;
char *args[10];
int tot_arg;
int search(char option,char *pattern,char *fname);
int sep_args();
int getcomm();
int take_action();
int main()
{
	do
	{
	printf("myshell$");
	getcomm();
	sep_args();
	take_action();
	}while(1);
	return 0;
}
int getcomm()
{
	int len;
	ptr=fgets(comm,80,stdin);
	len=strlen(comm);
	comm[len-1]='\0';
	return 0;
}

int sep_args()
{
	int i,j;
	i=j=tot_arg=0;
	args[tot_arg]=(char *)malloc(sizeof(char)*20);
	for(i=0;comm[i]!='\0';i++)
	{
		if(comm[i]==' ')
		{
			args[tot_arg][j]='\0';
			tot_arg++;
			args[tot_arg]=(char *)malloc(sizeof(char) * 20);
			j=0;
		}
		else
		{
			args[tot_arg][j]=comm[i];
			j++;
		}
	}
	args[tot_arg][j]='\0';
	return 0;
}
int take_action()
{
	char str[100];
	pid_t pid;
	int status;
	ptr=comm;
	if(ptr==NULL)
		exit(0);
	if(strlen(comm)<=1)
		return 0;
	if(strcmp(args[0],"search")==0)
		search(*args[1],args[2],args[3]);
	else if((pid=fork())<0)
		printf("\nUnable to create process.");
	else if(pid==0)
	{
		
		execvp(args[0],args);
		strcpy(str,"./");
		strcat(str,args[0]);
		execvp(str,args);
		printf("\n %s:command not found",comm);
		exit(0);
	}
	else
	waitpid(pid,&status,0);
	return 0;
}
 int search(char option,char *pattern,char *fname)
 {
 	char buff[100],*ptr;
 	int cnt,i;
 	FILE *fp;
 	fp=fopen(fname,"r");
 	if(fp==NULL)
 	{
 		printf("\nUnable to open file");
 		exit(0);
 	}
 	switch(option)
 	{
 	case 'a':while(!feof(fp))
 		{
 			buff[0]='\0';
 			fgets(buff,80,fp);
 			ptr=strstr(buff,pattern);
 			if(ptr!=NULL)
 				printf("%s",buff);
 		}
 		fclose(fp);
 		break;
 	case 'c':cnt=0;
 		while(!feof(fp))
 		{
 			buff[0]='\0';
 			fgets(buff,80,fp);
 			ptr=strstr(buff,pattern);
 			while(ptr!=NULL)
 			{
 				cnt++;
 				ptr=ptr+strlen(pattern);
 				ptr=strstr(ptr,pattern);
 			}
 		}
 		fclose(fp);
 		printf("\n The search string %s occurs %dtimes\n",pattern,cnt);
 		break;
 	case 'f':while(!feof(fp))
 		{
 			buff[0]='\0';
 			fgets(buff,80,fp);
 			ptr=strstr(buff,pattern);
 			if(ptr!=NULL)
 			{
 				printf("%s",buff);
 				break;
 			}
 		}
 		fclose(fp);
 		break;
 }
 return 0;
}		
