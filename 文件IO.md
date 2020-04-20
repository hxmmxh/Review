# 文件IO

* [open函数](#open函数介绍)
* [create函数](#create函数介绍)
* [close函数](#close函数介绍)

## 打开文件

### open函数介绍

```c
包含的头文件：
#include<fcntl.h> //在centos6.0中只要此头文件就可以
#include<sys/types.h>
#incldue<sys/stat.h>
功能：打开和创建文件（建立一个文件描述符，其他的函数可以通过文件描述符对指定文件进行读取与写入的操作。）
```

文件描述符(file descriptor)，简称fd，也叫句柄。每个文件都属于自己的句柄，例如标准输入是0，标准输出是1，标准出错是2。  
每用open打开一个文件就会返回句柄来操作这个文件。可用close（fd）将句柄返回给系统。

```c
函数原型
int open(const char*pathname,int flags);
int open(const char*pathname,int flags,mode_t mode);


返回值
成功：新打开的文件描述符,返回的文件描述符一定是最小的而且没有被使用的
失败：-1

参数说明
1.pathname
  要打开或创建的文件的路径
2.flags
  打开文件时，可以传入多个参数选项，用下面的一个或者多个常量进行“或”运算
  主要参数，必须且只能指定一个：
  O_RDONLY:   只读打开
  O_WRONLY:   只写打开
  O_RDWR:     读，写打开
  次要参数：可以和主要参数配合使用
  O_CREAT:    若文件不存在，则创建它，需要使用mode选项来指明新文件的访问权限。如果没有指定这个选项，并且文件不存在，会返回错误消息
  O_EXCL:     如果使用O_CREAT选项且文件存在，则返回错误消息。可用于测试一个文件是否存在，如果不存在则创建此文件成为一个原子操作。
  O_APPEND:   追加写，如果文件已经有内容，这次打开文件所写的数据附加到文件的末尾而不覆盖原来的内容
  O_TRUNC:    如果文件已经存在则删除文件中原有数据
  O_NOCTTY:   如果文件为终端，那么终端不可以调用open系统调用的那个进程的控制终端
  O_CLOEXEC:  在打开文件的时候，就为文件描述符设置FD_CLOEXEC标志。这是一个新的选项，用于解决在多线程下fork与用fcntl设置FD_CLOEXEC的竞争问题。某些应用使用fork来执行第三方的业务，为了避免泄露已打开文件的内容，那些文件会设置FD_CLOEXEC标志。但是fork与fcntl是两次调用，在多线程下，可能会在fcntl调用前，就已经fork出子进程了，从而导致该文件句柄暴露给子进程.
  O_NONBLOCK、O_NDELAY：将该文件描述符设置为非阻塞的（默认都是阻塞的）
  O_SYNC：设置为I/O同步模式，每次进行写操作时都会将数据同步到磁盘，然后write才能返回。
  O_LARGEFILE：表明文件为大文件。
  O_NOATIME：读取文件时，不更新文件最后的访问时间。
  O_DIRECT：对该文件进行直接I/O，不使用VFS Cache。
  O_DIRECTORY：要求打开的路径必须是目录
3. mode
  用八进制数指定文件访问权限，要注意真正建文件时的权限会受到umask值所影响，因此该文件权限应该为（mode-umaks）。
  1 可执行权限
  2 可写权限
  4 可读权限
  同时指定文件所有者、文件所在用户组、其他用户的权限
  例如：指定0777说明想让三者都具有所有的权限，但是由于umask一开始是002，所以创建出来的权限不是777，而是775
```

打开文件时，内核主要消耗了两种资源：文件描述符与内核管理文件结构file。

[参考文献1](https://blog.csdn.net/dangzhangjing97/article/details/79631173)  
[参考文献2](https://blog.csdn.net/weixin_39296438/article/details/79422068?depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-3&utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-3)

### create函数介绍

```c
#include <sys/stat.h>
#include <fcntl.h>
int creat(const char *pathname ,mode_t mode)
是open的一种封装实现, 等价于 open（pathname，O_WRONLY|O_CREAT|O_TRUNC，mode)
```

## 关闭文件

### close函数介绍

```c
头文件
#include<unistd.h>
功能：关闭一个已经打开的文件

函数原型
int close(int fd)
参数说明：fd是需要关闭的文件描述符
成功：返回0；
失败：返回-1，并设置errno

```
