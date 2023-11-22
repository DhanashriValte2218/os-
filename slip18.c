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
//========================================================================================================
//========================================================================================================

//FCFS CPU-scheduling

#include<stdio.h>

	typedef struct PCB
	{
		int pid,arrival,burst,finish,start;
		int avg,avg1;
	}NODE;
	
	void pline(int x);
	void display(int num,NODE *p);
	
	void main()
	{
		int i,j,num;
		float avg=0.0,sum=0.0;
		NODE p[10],temp;
		printf("\n enter the total number of processes:");
		scanf("%d",&num);
		printf("PID\tAT\tBT\n");
		for(i=0;i<num;i++)
		{
			printf("p[%d]",i+1);
			scanf("%d%d",&p[i].arrival,&p[i].burst);
			p[i].pid=i+1;
		}

		for(i=0;i<num-1;i++)
		{
			for(j=0;j<num-i-1;j++)
			{
				if(p[j].arrival>p[j+1].arrival)
				{
					temp=p[j];
					p[j]=p[j+1];
					p[j+1]=temp;
				}
			}
		}
		
		for(i=0;i<num;i++)
		{
			sum=sum+p[i].burst;
			p[i].finish=sum;
		}
		sum=0;
		pline(50);
		printf("PID\tAT\tBT\tFT\tST\tWT\tTAT\n");
		pline(50);
		for(i=0;i<num;i++)
		{
			if(i==0)
			{
				p[i].start=p[i].arrival;
			}
			else
			{
				p[i].start=p[i-1].finish;
			}
			printf("p[%d]\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].arrival,p[i].burst,p[i].finish,p[i].start,p[i].start-	p[i].arrival,p[i].finish-p[i].arrival);
 			sum+=p[i].finish;
		}
		pline(50);
		
		float sum1=0;
		int sum2=0;
		
		for(i=0;i<num;i++)
		{
			p[i].avg=p[i].finish-p[i].arrival;
			p[i].avg1=p[i].start-p[i].arrival;
			sum1+=p[i].avg;
			sum2+=p[i].avg1;
		}
		
		printf("\n");
		printf("your gantt chart is:\n");
		display(num,p);
		printf("\n");
		printf("average turnaround time is: %.2f\n",sum1/num);
		printf("average waiting time is: %.2f\n",sum2/num);
	}
	

	void pline(int x)
	{
		int i;
		for(i=0;i<x;i++)
		{
			printf("-");
		}
		printf("\n");
	}

	void display(int num,NODE *p)
	{
		pline(16*num);
		for(int i=0;i<num;i++)
		{
			if(i==0)
				printf("|\tp[%d]\t",p[i].pid);
			else
				printf("|\tp[%d]\t",p[i].pid);
		}
		
		printf("|");
		printf("\n");
		pline(16*num);
		for(int i=0;i<num+1;i++)
		{
			if(i==0)
				printf("%d\t\t",i);
			else
				printf("%d\t\t",p[i-1].finish);
		}
	}









