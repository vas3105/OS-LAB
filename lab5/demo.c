#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include<sys/wait.h>
int main()
{
    int status;
pid_t p1;
p1=fork();
if(p1==0)
{
    printf("child process p1 pid is %d\n",getpid());
     printf("child process p1 ppid is %d\n",getppid());

}

else 
{   p1=fork();
    if(p1==0)
    {
    
    printf("child process p2 pid is %d\n",getpid());
    printf("child process p2 ppid is %d\n",getppid());
    }
    else 
{
    wait(&status);
    printf("parent process pid is %d\n",getpid());
    printf("parent process ppid is %d\n",getppid());
}
    

}

}
