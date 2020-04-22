# 文件IO

* [文件描述符](#文件描述符)
* [open和openat函数](#open函数介绍)
* [create函数](#create函数介绍)
* [close函数](#close函数介绍)
* [lseek函数](#lseek函数介绍)
* [read函数](#read函数介绍)
* [write函数](#write函数介绍)
* [内核中文件的表示方法](#内核中文件的表示方法)

## 基础函数

### 文件描述符

文件描述符(file descriptor)，简称fd，也叫句柄。
每个文件都属于自己的句柄，例如标准输入是0，标准输出是1，标准出错是2。可用符号常量替换：
STDIN_FILENO,STDOUT_FILENO,STDERR_FILENO，在头文件<unistd.h>中定义  
每用open打开一个文件就会返回句柄来操作这个文件。可用close（fd）将句柄返回给系统。

### open函数介绍

```c
包含的头文件：
#include<fcntl.h> //在centos6.0中只要此头文件就可以
#include<sys/types.h>
#incldue<sys/stat.h>
功能：打开和创建文件（建立一个文件描述符，其他的函数可以通过文件描述符对指定文件进行读取与写入的操作。）
```

```c
函数原型
int open(const char *pathname,int flags);
int open(const char *pathname,int flags,mode_t mode);
int openat(int fd, const char *pathname, int flags);
int openat(int fd, const char *pathname, int flags, mode_t mode);

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
  O_NOCTTY:   如果文件为终端设备，那么不将该设备分配作为此进程的控制终端
  O_CLOEXEC:  在打开文件的时候，就为文件描述符设置FD_CLOEXEC标志。这是一个新的选项，用于解决在多线程下fork与用fcntl设置FD_CLOEXEC的竞争问题。某些应用使用fork来执行第三方的业务，为了避免泄露已打开文件的内容，那些文件会设置FD_CLOEXEC标志。但是fork与fcntl是两次调用，在多线程下，可能会在fcntl调用前，就已经fork出子进程了，从而导致该文件句柄暴露给子进程.
  O_NONBLOCK：将该文件描述符设置为非阻塞的（默认都是阻塞的）
  O_SYNC：设置为I/O同步模式，每次进行写操作时都会将数据同步到磁盘，然后write才能返回。
  O_LARGEFILE：表明文件为大文件。
  O_NOATIME：读取文件时，不更新文件最后的访问时间。
  O_DIRECT：对该文件进行直接I/O，不使用VFS Cache。
  O_DIRECTORY：要求打开的路径必须是目录
  O_NOFOLLOW: 如果引用的是符号链接，则出错
3. mode
  用八进制数指定文件访问权限，要注意真正建文件时的权限会受到umask值所影响，因此该文件权限应该为（mode-umaks）。
  1 可执行权限
  2 可写权限
  4 可读权限
  同时指定文件所有者、文件所在用户组、其他用户的权限
  例如：指定0777说明想让三者都具有所有的权限，但是由于umask一开始是002，所以创建出来的权限不是777，而是775
4. openat
  如果path参数指定的是绝对路径名，fd参数被忽略，openat函数相当于opan函数
  如果path参数指定的是相对路径名，fd参数指出相对路径名在文件系统中的开始地址，可以通过打开相对路径名所在的目录来获取。
  如果path参数是相对路径名，fd参数是常量AT_FDCWD,表明相对路径名从当前目录开始
5. TOCTTOU错误
  time of check to time of use, openat函数可以避免这一错误
  如果有两个基于文件的函数调用，其中第二个调用依赖于第一个调用的结果，那么程序就容易出错。因为这两个调用不是原子操作，在两个函数调用之间文件可能改变了，导致第一个调用的结果不再有效。

```

打开文件时，内核主要消耗了两种资源：文件描述符与内核管理文件结构file。

### create函数介绍

```c
#include <sys/stat.h>
#include <fcntl.h>
int creat(const char *pathname ,mode_t mode)
是open的一种封装实现, 等价于 open（pathname，O_WRONLY|O_CREAT|O_TRUNC，mode)
```

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

当一个进程终止时，内核会自动关闭它所有的打开文件

```

### lseek函数

当前文件偏移量：度量从文件开始处计算的字节数，通常是非负整数，文件的读写操作都是从当前文件偏移量处开始，并使偏移量增加所读写的字节。系统默认除非指定O_APPEND选项，否则打开文件时偏移量设置为0

```c
头文件
#include <unistd.h>
功能：显示地为一个打开文件设置偏移量

off_t lseek(int fd, off_t offset, int whence);
成功返回新的文件偏移量，出错返回-1，并设置errno
只修改文件表项中的当前文件偏移量，不进行任何的IO操作

参数说明：
若whence是SEEK_SET(值为0)， 则将该文件的偏移量设置为据文件开始处offset个字节
若whence是SSEEK_CUR(值为1)， 则将该文件的偏移量设置为当前值加offset个字节，offset参数可正可负
若whence是SSEEK_END(值为2) ，则将该文件的偏移量设置为文件长度加offset个字节，offset参数可正可负
如果打开的文件(例如管道，FIFO,网络套接字)不可以设置偏移量，则返回-1，并将errno设置为ESPIPE
```

文件偏移量可以大于文件的当前长度，对该文件的下一次写将加长该文件，并在文件中构成空洞，空洞中的字节都默认为0.空洞部分并不要求在磁盘上占用存储区。

### read函数介绍

```c
头文件
#include <unistd.h>
ssize_t read (int fd, void *buf, size_t nbytes);
功能:从打开文件中读数据
成功返回读到的字节数，如果已到文件尾部，返回0，出错则返回-1
```

实际读的字节数少于要求读的字节数的情况：
普通文件，在读到要求字节数之前到达了文件尾端
从终端设备读时，通常一次最多读一行
从网络读时，网络中的缓冲机制造成返回值小于所要求读的字节数
从管道或FIFO中读时，管道包含的字节数小于所需的量

### write函数介绍

```c
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t nbytes);
成功返回已写的字节数，失败返回-1
返回值通常等于给定的字节数，否则表示出错
对于普通文件，写操作从文件的当前偏移量处开始，如果指定了O_APPEND则在写操作之前将文件偏移量设置在文件的当前结尾处
```

### 内核中文件的表示方法

内核中共有3种数据结构表示打开的文件  
![图例](pic/打开文件的内核数据结构.png)  
![图例](pic/两个独立进程打开同一个文件.png)

1.进程表项：每个进程在进程表中包含一个记录项，包含一张打开文件描述符表，记录了打开的文件的文件描述符标志和指向文件表项的指针
2.文件表项：所有的打开文件都有一张文件表，包含着文件状态标志、当前文件的偏移量、指向该文件v节点表项的指针
3.v节点表项：每个打开问年间都有一个v节点结构。包含了文件类型和对此文件进行各种操作函数的指针。对于大多数文件，v节点还包含了该结点的i节点，这些信息在打开文件时从磁盘中读入内存。

注意事项：
可能有多个文件描述符项指向同一文件表项，最常见的情况时fork后父进程和子进程各自的每一个打开文件描述符共享同一个文件表项，dup函数也会导致这一现象的发生

文件描述符标志和文件状态标志的作用范围存在区别，前者只用于一个进程的一个描述符，后者则应用于指向该给的那个文件表项的任何进程中的所有描述符


### dup和dup2

```c
#include <unistd.h>
int dup(int fd);
int dup2(int fd, int fd2);
功能：用于复制一个现有的文件描述符
若成功返回新的文件描述符，失败则返回-1
dup中返回的新的文件描述符一定是当前可用文件描述符中的最小值
dup2中用fd2指定了新描述符的值，如果fd2已经打开，则先将其关闭，如果fd2等于fd，则直接返回fd2
返回的新文件描述符与参数fd共享同一个文件表项
```

### 缓冲区相关操作函数

UNIX系统在内核中设有缓冲区高速缓存或页缓存，大多数磁盘IO通过缓冲区进行。向文件写入数据时，内核会先将数据复制到缓冲区中，然后排入队列，晚些时候再写入磁盘。称为延迟写。

```c
#include <unistd.h>
int fsync(int fd);
int fdatasync(int fd);
成功返回0出错返回-1
void sync(void);
```

sync




### fcntl函数

```c
#include <unistd.h>
#include <fcntl.h>
int fcntl(int fdm, int cmd, int arg)
功能：用于改变已打开文件的属性
```

fcntl函数有5种功能：
　1.复制一个现有的描述符（cmd=F_DUPFD）.
　2.获得／设置文件描述符标记(cmd=F_GETFD或F_SETFD)，进程表项中.
  3.获得／设置文件状态标记(cmd=F_GETFL或F_SETFL)，文件表项中.  
  4.获得／设置异步I/O所有权(cmd=F_GETOWN或F_SETOWN).  
  5.获得／设置记录锁(cmd=F_GETLK,F_SETLK或F_SETLKW).  

cmd共有11个选项：
