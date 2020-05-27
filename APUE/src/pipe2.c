#include <unistd.h>
#include <stdio.h>

#define DEF_PAGER "/bin/more" //默认的分页程序

int main(int argc, char *argv[])
{
    int n;
    int fd[2];
    pid_t pid;
    char *pager, *argv0;
    char line[2048];
    FILE *fp;

    if (argc != 2)
    {
        printf("usage: a.out <pathname>");
        abort();
    }

    fp = fopen(argv[1], "r");

    pipe(fd);

    pid = fork();

    if (pid > 0)
    {
        close(fd[0]);
        while(fgets(line,2048,fp)!=NULL)
        {
            n = strlen(line);
            write(fd[1], line, n);
        }
    close(fd[1]);
    waitpid(pid, NULL, 0);
    return;
    }
    else
    {
        close(fd[1]);
        if(fd[0]!=STDIN_FILENO)
        {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
        }

        
    }
    
}