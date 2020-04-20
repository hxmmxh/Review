# 文件IO

* [open函数](#open函数介绍)

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



[参考文献1](https://blog.csdn.net/dangzhangjing97/article/details/79631173)  
[参考文献2](https://blog.csdn.net/weixin_39296438/article/details/79422068?depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-3&utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-3)