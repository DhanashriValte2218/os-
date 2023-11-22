//LRU
#include<stdio.h>

struct frmnode
{
 int pno,counter;//new
}
frames[20];

int n;

int page_found(int pno)
{
 int fno;
 for(fno=0;fno<n;fno++)
 {if(frames[fno].pno==pno)
    return fno;
  }
 return -1;
}

int get_free_frame()
{int fno;
 for (fno=0; fno<n; fno++)
 {
  if (frames[fno].pno==-1)
   return(fno);
  }
 return(-1);
}

int get_lru_Frame()//new
{
 int lrufno=0,fno;
 for (fno=1; fno<n; fno++)
 {
  if(frames[fno].counter<frames[lrufno].counter)
   lrufno=fno;
 }
 return lrufno;
}
void main()
{
 int p_request[]={5,8,10,14,10,9,5,10,8,5,1,10,9,12,10};
 int size=15,currtime;
 int page_falts=0,i,j,fno;
 
 printf("\nHow many frames:");  scanf("%d",&n);
 //initialize frames
 for (i=0; i<n; i++)
 { frames[i].pno=-1;
 }

 printf("\nPageNo     Page Frames     Page Fault");
 printf("\n---------------------------------------------------");
 currtime=0;//new
 for(i=0;i<size;i++)
 {
  j=page_found(p_request[i]);
  if(j==-1)  //page fault occurs
  {
   j=get_free_frame();
   if (j==-1) //no free frame - do replacement
    j=get_lru_Frame();
   page_falts++;
   frames[j].pno=p_request[i];
   frames[j].counter=currtime;//new
   printf("\n%4d\t ",p_request[i]);
   for (fno=0; fno<n; fno++)
    printf("%4d:%2d",frames[fno].pno,frames[fno].counter);
   printf(" : YES");
  }
  else//page found
  {frames[j].counter=currtime; //new
   printf("\n%4d\t ",p_request[i]);
   for (fno=0; fno<n; fno++)
    printf("%4d:%2d",frames[fno].pno,frames[fno].counter);
   printf(" : NO");

  }//else
  currtime++;//new
 }//for
 printf("\n------------------------------------------");
 printf("\n Number of Page_Falts=%d\n",page_falts);
 
}
//===================================================================================================
//==================================================================================================
//count

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
char comm[100],*ptr;
char *args[10];
int tot;
int count(char *option,char *fname);
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
	char *token;
	i=j=tot=0;
	token=strtok(comm," ");
	while(token!=NULL)
	{
	args[tot]=(char *)malloc(20);
	strcpy(args[tot++],token);
	token=strtok(NULL," ");
	}
	return 0;
}
int take_action()
{
	char str[100];
	pid_t pid;
	int status;
	ptr=comm;
	if(ptr==NULL)
	 return 0;
	if(strlen(comm)<=1)
	 return 0;
	if(strcmp(args[0],"count")==0)
	 count(args[1],args[2]);
	else
		if((pid=fork())<0)
		{
		printf("\n unable to create process");
		return 0;
		}
		else
		if(pid==0)
		{
		execvp(args[0],args);
		strcpy(str,"./");
		strcat(str,args[0]);
		execvp(str,args);
		printf("\n %s:command not found",comm);
		return 0;
		}
		else
		waitpid(pid,&status,0);
		return 0;
}
int count(char *option,char *fname)
{
	int ccnt,wcnt,lcnt,wflag;
	int ch;
	FILE *fp;
	int i;
	fp=fopen(fname,"r");
	if(fp==NULL)
	{
	printf("\n unable to open file");
	exit(0);
	}
	ccnt=wcnt=lcnt=0;
	wflag=0;
	ch=fgetc(fp);
	while(ch!=EOF)
	{
		ccnt++;
		if(ch==' '||ch=='\t')
		{
		 	if(wflag==0)
		 	{	
		 		wcnt++;
		 		wflag=1;
		 	}
		 }
		 else
		 if(ch=='\n')
		 {
		 	lcnt++;
		 	if(wflag==0)
		 	{
		 		wcnt++;
		 		wflag=1;
		 	}
		 }
		 else
			wflag=0;
	 	ch=fgetc(fp);
	 	}
	 	if(wflag==0)
	 	{
	 		wcnt++;
	 		lcnt++;
	 	}
	 	fclose(fp);
	 	if(strcmp(option,"c")==0)
	 	{
	 		printf("\n total characters=%d\n",ccnt);
	 	}
	 	else if(strcmp(option,"w")==0)
	 	{
	 		printf("\n total words=%d\n",wcnt);
	 	}
	 	else if(strcmp(option,"l")==0)
	 	{
	 		printf("\n total lines=%d\n",lcnt);
	 	}
	 	else
	 		printf("invalid option");
	 	return 0;
}
