#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/resource.h>

void demonize()
{
    //0.屏蔽一些有关控制终端操作的信号，防止在守护进程没有正常运转起来前控制终端受到干扰退出或挂起
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    //1. 设置文件模式创建屏蔽字
    umask(0);
    //2. 调用fork然后使父进程exit
    if (fork() != 0)
        exit(0);
    //3. 调用setsid创建一个新会话
    if (setsid() == -1)
        exit(0);
    signal(SIGHUP, SIG_IGN);
    if (fork() != 0)
        exit(0);
    //4. 更改工作目录到根目录
    if(chdir("/")!=0)
        exit(0);
    //5. 关闭文件描述符
    struct rlimit rl;
    int i=0;
    getrlimit(RLIMIT_NOFILE, &rl);
    if(rl.rlim_max==RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (; i < rl.rlim_max; ++i)
        close(i);
    //6. 重定向标准输入输出和错误输出
    int fd0, fd1, fd2;
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);
}

int main()
{
    demonize();
    sleep(10000);
}