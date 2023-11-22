//orphan
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
void main()
{
 int pid;
 pid=getpid();
 printf("current process ID is :%d\n",pid);
 printf("\n forking child process...\n");
 pid=fork();
 if(pid<0)
 {
   printf("\n process can not be created");
 }
 else
 {
   if(pid==0)
   {
    printf("\n child process is sleeping...");
    sleep(5);
    printf("\n orphan childs parent ID:%d",getppid());
   }
   else
   {
    printf("\n parent process completed...");
   }
 }
 return;
}
  
  //====================================================================================
  //====================================================================================
  //optimal

 /*Program for Optimal Page replacement simulation*/
#include<stdio.h>

struct frmnode
{
  int pno,refloc;
}frames[20];
int n;

int page_found(int pno)
{
 int fno;
 for(fno=0;fno<n;fno++)
  if(frames[fno].pno==pno)
   return fno;

 return -1;
}

int get_free_frame()
{ int fno;
 for (fno=0; fno<n; fno++)
  if (frames[fno].pno==-1)//free
   return(fno);

 return(-1);
}

int get_opt_frame()
{
 int optfno=0,fno;
 for (fno=1; fno<n; fno++)
  if(frames[fno].refloc>frames[optfno].refloc)
   optfno=fno;
 return optfno;
}
int main()
{
 int p_request[]={1,2,3,4,2,1,5,6,2,1,2,3,7,6,3,2,1,2,3,6};
 int size=sizeof(p_request)/2;//number of requests
 int page_falts=0,i,j,k,fno;

 
 printf("\nHow many frames:");  scanf("%d",&n);
 //initialize frames
 for (i=0; i<n; i++)
 { frames[i].pno=-1;
 }

 printf("\nPageNo     Page Frames     Page Fault");
 printf("\n---------------------------------------------------");
 for(i=0;i<size;i++)
 {
  j=page_found(p_request[i]);
  if(j==-1)  //page fault occurs
  {
   j=get_free_frame();

   if (j==-1) //no free frame - do page replacement
    j=get_opt_frame();
   page_falts++;
   frames[j].pno=p_request[i];//load page in frame

   for(fno=0;fno<n;fno++)//find loc of page in future
   {
    for(k=i+1;k<size;k++)
     if(frames[fno].pno==p_request[k])
      { frames[fno].refloc=k; break;}
     else
      frames[fno].refloc=size;
   }

   printf("\n%4d\t ",p_request[i]);
   for (fno=0; fno<n; fno++)
    printf("%4d:%2d",frames[fno].pno,frames[fno].refloc);
   printf(" : YES");
  }
  else //page found in frame j
  {
   for(fno=0;fno<n;fno++)//find loc of page in future
   {
    for(k=i+1;k<size;k++)
     if(frames[fno].pno==p_request[k])
      { frames[fno].refloc=k; break;}
     else
      frames[fno].refloc=size;
   }

   printf("\n%4d\t ",p_request[i]);
   for (fno=0; fno<n; fno++)
    printf("%4d:%2d",frames[fno].pno,frames[fno].refloc);
   printf(" : NO");
  }
 }//for
 printf("\n-------------------------------------------------------");
 printf("\n Number of Page_Falts=%d",page_falts);
 }




