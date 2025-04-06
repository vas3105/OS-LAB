#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<string.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
    char **temp_array=argv;
    int status;
   pid_t p1=fork();
    if(p1==0)
    {
        for(int i=0;i<argc;i++)
        {
            for(int j=0;j<argc-i-1;j++)
            {
                if(*argv[j]> *argv[j+1])
                {
                    char *temp;
                    temp=argv[j];
                    argv[j]=argv[j+1];
                    argv[j+1]=temp;
                }
            }
        }
        printf("sorted strings are\n");
        for(int i=0;i<argc;i++)
        {
            printf("%s\t",argv[i]);
        }
        
    }
   

   
        wait(&status); 
        printf("\n unsorted strings are \n");
        for(int i=0;i<argc;i++)
        {
            printf("%s\t",temp_array[i]);
        }
    
   
    

}
