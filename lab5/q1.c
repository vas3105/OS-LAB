#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include<sys/wait.h>
int main(void)
{
    int status;
pid_t p1;
p1=fork();
if(p1==0)
{
    printf("child process pid is %d\n",getpid());
     printf("child process ppid is %d\n",getppid());

}
else
{
    wait(&status);
    printf("parent process pid is %d\n",getpid());
    printf("parent process ppid is %d\n",getppid());
}
}

