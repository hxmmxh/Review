#include <stdio.h>
#include <sys/wait.h>

void pre_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status= %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s \n", WTERMSIG(status),
#ifdef WCOREDUMP
               WCOREDUMP(status) ? "(core file generated)" : "");
#else
               "");
#endif
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number=%d\n", WSTOPSIG(status));
}

int main()
{
    pid_t pid;
    int status;
    //正常退出
    if ((pid = fork()) < 0)
        printf("fork error");
    else if (pid == 0)
        exit(7);
    if (wait(&status) != pid)
        printf("wait error");
    pre_exit(status);
    //调用abort，产生SIGABRT信号退出
    if ((pid = fork()) < 0)
        printf("fork error");
    else if (pid == 0)
        abort();
    if (wait(&status) != pid)
        printf("wait error");
    pre_exit(status);
    //通过除以0产生SIGFPE错误返回
    if ((pid = fork()) < 0)
        printf("fork error");
    else if (pid == 0)
        status /= 0;
    if (wait(&status) != pid)
        printf("wait error");
    pre_exit(status);
}