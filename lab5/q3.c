#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<string.h>
#include <stdlib.h>
#define MAX_LEN 150
int main()
{
    int status;
    int n;
    char strings[n][50];
    printf("enter the value of n\t");
    scanf("%d",&n);
    printf("entre the strings:\n");
    for(int i=0;i<n;i++)
    {
       scanf("%s",strings[i]);
    }
    pid_t p1,p2;
    p1=fork();
    if(p1==0)
    {
        for(int i=0;i<n-1;i++)
        {
            for(int j=0;j<n-i-1;j++)
            {
                 if (strcmp(strings[j], strings[j + 1]) > 0)
                {
                    char temp[MAX_LEN];
                    strcpy(temp, strings[j]);
                    strcpy(strings[j], strings[j + 1]);
                    strcpy(strings[j + 1], temp);
                }
                
            }
        }
        printf("1st child sorted strings:\n");
        for(int i=0;i<n;i++)
        {
            printf("%s\t",strings[i]);
        }
        printf("\n");
        exit(0);
    }
    else 
    {       p2=fork();
            if(p2==0)
        {
         //child 2 process
           for (int i = 0; i < n - 1; i++) {
        int minIndex = i;  
        for (int j = i + 1; j < n; j++) {
            if (strcmp(strings[j], strings[minIndex]) < 0) {
                minIndex = j;  
            }
        }
        
        if (minIndex != i) {
            char temp[MAX_LEN];
            strcpy(temp, strings[i]);
            strcpy(strings[i], strings[minIndex]);
            strcpy(strings[minIndex], temp);
        }
        } 
        printf("2nd child sorted strings:\n");
        for(int i=0;i<n;i++)
        {
            printf("%s\t",strings[i]);
        }
        printf("\n");
        //exit(0);
        }
    else 
        {
             wait(&status);  // Wait for the first child to finish
             //wait(&status);
            //parent process
            printf("this is the parent process\n");
        }


}
}
