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
//==============================================================================================
//================================================================================================
//non-premitive
#include <stdio.h>
struct input
{
char pname[10];
int bt, at, tbt, ft, p;
} tab[10];
struct gantt
{
char pname[10];
int start, end;
} g[30], g1[30];
int n, i, time, prev, k;
void getinput()
{
printf("\nEnter No of Process: ");
scanf("%d", &n);
for (i = 0; i < n; i++)
{
printf("\nEnter Process Name: ");
scanf("%s", tab[i].pname);
printf("Arrival Time:");
scanf("%d", &tab[i].at);
printf("Burst Time: ");
scanf("%d", &tab[i].bt);
tab[i].tbt = tab[i].bt;
printf("\nEnter the Priority:");
scanf("%d", &tab[i].p);
}
}
void printinput()
{
// int TWT=0,TTAT=0;
printf("\nPname\tAT\tBT");
for (i = 0; i < n; i++)
printf("\n%s\t%d\t%d", tab[i].pname, tab[i].at, tab[i].bt);
}
void printoutput()
{
int TWT = 0, TTAT = 0;
float ATAT, AWT;
printf("\nPname\tAT\tBT\tFT\tWT\tTAT");
for (i = 0; i < n; i++)
{
printf("\n%s\t%d\t%d\t%d\t%d\t%d", tab[i].pname, tab[i].at, tab[i].bt,
tab[i].ft, tab[i].ft-tab[i].at - tab[i].bt, tab[i].ft - tab[i].at);
TWT = TWT + (tab[i].ft - tab[i].at - tab[i].bt);
TTAT = TTAT + (tab[i].ft - tab[i].at);
}
printf("\nTotal WT: %d", TWT);
printf("\nTotal TAT:%d", TTAT);
AWT = (float)TWT / n;
ATAT = (float)TTAT / n;
printf("\nAverage WT: %f", AWT);
printf("\nAverage TAT:%f", ATAT);
}
void sort()
{
int pass;
struct input temp;
for (pass = 1; pass < n; pass++)
{
for (i = 0; i < n - pass; i++)
{
if (tab[i].at > tab[i + 1].at)
{
temp = tab[i];
tab[i] = tab[i + 1];
tab[i + 1] = temp;
}
}
}
}
int arrived(int time)
{
for (i = 0; i < n; i++)
{
if (tab[i].at <= time && tab[i].tbt != 0)
return 1;
}
return 0;
}
int gethighpriority(int time)
{
int processpos, min = 99;
for (i = 0; i < n; i++) // i=0,1
{
// p1,p3 min=2
if (tab[i].at <= time && tab[i].tbt != 0 && tab[i].p < min)
{
min = tab[i].p;
processpos = i;
}
}
return processpos;
}
void processinput()
{
int finish = 0, j;
k = 0;
while (finish != n)
{
if (arrived(time))
{
i = gethighpriority(time);
for (j = 0; j < tab[i].bt; j++)
{
time++;
tab[i].tbt--;
g[k].start = prev;
g[k].end = time;
prev = time;
strcpy(g[k++].pname, tab[i].pname);
tab[i].ft = time;
if (tab[i].tbt == 0)
{
finish++;
break;
}
}
}
else
{
time++;
g[k].start = prev;
g[k].end = time;
strcpy(g[k++].pname, "idle");
prev = time;
}
// i++;
}
}
void ganttchart()
{
int i, j = 0;
printf("\n******Each Unit Gantt chart******");
printf("\nStart\tpname\tEnd");
for (i = 0; i < k; i++)
{
printf("\n%d\t%s\t%d", g[i].start, g[i].pname, g[i].end);
}
printf("\n********Final Gantt Chart*******");
g1[0] = g[0];
for (i = 1; i < k; i++)
{
if (strcmp(g[i].pname, g1[j].pname) == 0)
g1[j].end = g[i].end;
else
{
j++;
g1[j] = g[i];
}
}
printf("\nStart\tpname\tEnd");
for (i = 0; i <= j; i++)
{
printf("\n%d\t%s\t%d", g1[i].start, g1[i].pname, g1[i].end);
}
}
int main()
{
getinput();
printinput();
sort();
printf("\nData After Sorting: ");
printinput();
processinput();
printoutput();
ganttchart();
for (i = 0; i < n; i++)
{
tab[i].tbt = tab[i].bt = rand() % 10 + 1;
tab[i].at = tab[i].ft + 2;
}
printinput();
processinput();
printoutput();
ganttchart();
}
