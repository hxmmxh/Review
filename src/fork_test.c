#include <unistd.h>
#include <stdio.h>

int globvar = 6;
char buf[] = "a write to stdout\n";

int main()
{
    int var;
    pid_t pid;

    var = 88;
    if(write(STDOUT_FILENO,buf,sizeof(buf)-1)!=sizeof(buf)-1)
        printf("write error");
    printf("before fork\n");//输出是到行缓冲的设备时，这里只输出一次，输出到全缓冲的文件时，子进程和父进程各输出一次
    //但如果删除末尾的\n，输出到行缓冲和全缓冲时都会输出两次
    //主要没被冲洗，就会复制到子进程中，造成重复输出

    if((pid=fork())<0)
        printf("fork error");
    else if (pid==0)
    {
        globvar++;
        var++;
    }
    else
        sleep(2);
    printf("pid=%ld, glob=%d, var=%d\n", (long)getpid(), globvar, var);
    exit(0);
}