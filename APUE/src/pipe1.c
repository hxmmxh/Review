#include <unistd.h>

int main()
{
    int n;
    int fd[2];
    pid_t pid;
    char line[2048];

    pipe(fd);
    pid = fork();
    //创建一个从父进程到子进程的管道
    if(pid>0)//在父进程中关闭读端
    {
        close(fd[0]);
        write(fd[1], "helloworld\n", 12);
    }
    else//在子进程中关闭写端
    {
        close(fd[1]);
        n=read(fd[0], line, 12);
        write(STDOUT_FILENO, line, n);
    }
    exit(0);
}