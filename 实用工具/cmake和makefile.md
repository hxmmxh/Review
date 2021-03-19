
- [cmake](#cmake)
  - [1. CMAKE简介](#1-cmake简介)
  - [- 如果提示没有找到编译器，可以`apt install build-essential`解决，提供编译程序必须软件包的列表信息，编译程序有了这个软件包才知道 头文件在哪 才知道库函数在哪还会下载依赖的软件包 最后才组成一个开发环境](#--如果提示没有找到编译器可以apt-install-build-essential解决提供编译程序必须软件包的列表信息编译程序有了这个软件包才知道-头文件在哪-才知道库函数在哪还会下载依赖的软件包-最后才组成一个开发环境)
  - [2. 安装CMAKE](#2-安装cmake)
  - [3. CMAKE语法](#3-cmake语法)
    - [3.1 命令](#31-命令)
    - [3.2 变量和字符串](#32-变量和字符串)
    - [3.3 程序流控制结构](#33-程序流控制结构)
    - [CMAKE全局变量](#cmake全局变量)
    - [CMake常见命令](#cmake常见命令)
  - [5. cmake使用案例](#5-cmake使用案例)
    - [1. 单目录一个或多源文件的编译](#1-单目录一个或多源文件的编译)
    - [2. 多目录编译](#2-多目录编译)
    - [3. 自定义编译选项](#3-自定义编译选项)
    - [4. 安装和测试功能](#4-安装和测试功能)


# cmake

https://www.hahack.com/codes/cmake/  
https://www.cnblogs.com/lsgxeva/p/9454443.html


https://blog.codekissyoung.com/常用软件/cmake  
https://blog.csdn.net/luanpeng825485697/article/details/81202136  
https://www.cnblogs.com/coderfenghc/archive/2012/10/20/2712806.html  
 



## 1. CMAKE简介
- CMake是一个跨平台的、开源的构建工具。cmake是makefile的上层工具，它们的目的正是为了产生可移植的makefile，并简化自己动手写makefile时的巨大工作量。
* CMake是一个跨平台的自动化建构系统,它使用一个名为 CMakeLists.txt 的文件来描述构建过程,可以产生标准的构建文件,如 Unix 的 Makefile 或Windows Visual C++ 的 projects/workspaces 。文件 CMakeLists.txt 需要手工编写,也可以通过编写脚本进行半自动的生成
* 允许开发者编写一种平台无关的 CMakeList.txt 文件来定制整个编译流程，然后再根据目标用户的平台进一步生成所需的本地化 Makefile 和工程文件，如 Unix 的 Makefile 或 Windows 的 Visual Studio 工程。从而做到“Write once, run everywhere”
* 在 linux 平台下使用 CMake 生成 Makefile 并编译的流程如下:
    * 编写 CMakeLists.txt。
    * 执行命令`cmake PATH`或者`ccmake PATH`生成 Makefile ( ccmake 和 cmake 的区别在于前者提供了一个交互式的界面,PATH 是 CMakeLists.txt 所在的目录 )。在当前目录可以不加PATH
    * 使用 make 命令进行编译。
* 内部构建生成的Cmake的中间文件与源代码文件混杂在一起，并且cmake没有提供清理这些中间文件的命令。所以cmake推荐使用外部构建，步骤如下:
    * 在CMakeLists.txt的同级目录下，新建一个build文件夹
    * 进入build文件夹，执行cmake ..命令，这样所有的中间文件以及Makefile都在build目录下了
    * 在build目录下执行make就可以得到可执行文件
    ```BASH
    mkdir  build   
    cd  build
    cmake ..
    make 
    ```
- 如果提示没有找到编译器，可以`apt install build-essential`解决，提供编译程序必须软件包的列表信息，编译程序有了这个软件包才知道 头文件在哪 才知道库函数在哪还会下载依赖的软件包 最后才组成一个开发环境
----------------------
## 2. 安装CMAKE
* sudo apt-get install cmake
* 或者cmake官网下载压缩包，解压缩后安装
```BASH
tar -xzvf cmake-2.6.4.tar.gz
cd cmake-2.6.4
./bootstrap
make
make install
```
---------------------
## 3. CMAKE语法
- CMakeLists.txt 的语法比较简单,由命令、注释和空格组成
- 命令是不区分大小写的
- 符号 # 后面的内容被认为是注释

### 3.1 命令
- 命令是不区分大小写的,由命令名称、小括号和参数组成,参数之间使用空格进行间隔。
- 符号"#"后面的内容被认为是注释

```cmake
command(arg1 arg2 ...)          # 运行命令
command(arg1 ${var_name})       # 使用变量
```
- command可以是一个命令名；或者是一个宏；也可以是一个函数名。
- args是以空格分隔的参数例表（如果参数中包含空格，则要加双引号）
- 除了用于分隔参数的空白字符（空格、换行号、tabs）都是被忽略不计的。任何包含在双引号中的字符都做为一个参数。一个反斜杠用于转换码。

### 3.2 变量和字符串
* 可以用一个set命令把一个字符串列表设置为一个变量，然后把这个变量传递给需要传递多参数的函数
* 字符串列表可以由；或空格分隔组成
* 用${VAR} 语法得到变量的引用。
* 如果你想传把一个字符串列表做为一个单独的参数传递给函数，用双引号包含它
```cmake
set(var a;b;c)
set(var a b c)
# 上面两行效果等价

command(${var})
# 等效于 command(a b c)
command("${var}")
等效于 command("a b c")

```
### 3.3 程序流控制结构
* 条件语句
```cmake
IF(expression)
    COMMAND1(ARGS)
ELSE(expression)
    COMMAND2(ARGS)
ENDIF(expression)

IF(var)                       # 不是空, 0, N, NO, OFF, FALSE, NOTFOUND 或 <var>_NOTFOUND时，为真
IF(NOT var)                   # 与上述条件相反。
IF(var1 AND var2)             # 当两个变量都为真是为真。
IF(var1 OR var2)              # 当两个变量其中一个为真时为真。
IF(COMMAND cmd)               # 当给定的cmd确实是命令并可以调用是为真
IF(EXISTS dir)                # 目录名存在
IF(EXISTS file)               # 文件名存在
IF(IS_DIRECTORY dirname)      # 当dirname是目录
IF(file1 IS_NEWER_THAN file2) # 当file1比file2新,为真
IF(variable MATCHES regex)    # 符合正则
```
* 循环控制
```cmake
set(VAR a b c) 
  # loop over a, b,c with the variable f 
foreach(f ${VAR}) 
    message(${f}) 
endforeach(f)
```
* 定义宏和函数
```cmake
# define a macro hello 
macro(hello MESSAGE)
    message(${MESSAGE})
endmacro(hello) 
# call the macro with the string "hello world" 
hello("hello world") 
# define a function hello 
function(hello MESSAGE)
    message(${MESSAGE}) 
endfunction(hello)

```
* 正则表达式
```camke
^ 匹配一行或一字符串开头
$匹配一行或一字符串结尾
.匹配单一字符或一个新行
[ ]匹配括号中的任一字符
[^ ] 匹配不在括号内的任一字符
[-] 匹配指定范围内的字符
* 匹配0次或多次
+ 匹配一次或多次
? 匹配0次或一次
()保存匹配的表达式并用随后的替换它

```

-------------------------

### CMAKE全局变量
* PROJECT_SOURCE_DIR 工程的根目录
* PROJECT_BINARY_DIR 运行cmake命令的目录,通常是${PROJECT_SOURCE_DIR}/build
* CMAKE_INCLUDE_PATH 环境变量,非cmake变量
* CMAKE_LIBRARY_PATH 环境变量
* CMAKE_CURRENT_SOURCE_DIR 当前处理的CMakeLists.txt所在的路径
* CMAKE_CURRENT_BINARY_DIR target编译目录  
    使用ADD_SURDIRECTORY(src bin)可以更改此变量的值  
    SET(EXECUTABLE_OUTPUT_PATH <新路径>)并不会对此变量有影响,只是改变了最终目标文件的存储路径
* CMAKE_CURRENT_LIST_FILE 输出调用这个变量的CMakeLists.txt的完整路径
* CMAKE_CURRENT_LIST_LINE 输出这个变量所在的行
* CMAKE_MODULE_PATH 定义自己的cmake模块所在的路径  
    SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake),然后可以用INCLUDE命令来调用自己的模块
* EXECUTABLE_OUTPUT_PATH 重新定义目标二进制可执行文件的存放位置
* LIBRARY_OUTPUT_PATH 重新定义目标链接库文件的存放位置
* PROJECT_NAME 返回通过PROJECT指令定义的项目名称
* CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS 用来控制IF ELSE语句的书写方式
  
-----------------------------------

### CMake常见命令
```cmake
# cmake最低版本需求，不加入此行会受到警告信息
cmake_minimum_required (<version>) 
# 项目名称
project (<name>)
# 把参数 <dir> 中所有的源文件名称赋值给参数 <variable>
aux_source_directory(<dir> <variable>) 
# 使用给定的源文件生成可执行文件
add_executable(<name> ${SRC_LIST}) 
# 指明可执行文件需要连接的链接库，当多个库存在依赖时,依赖库要写在后面,B文件依赖A文件中的内容，那么B文件应该放在A文件的左边
target_link_libraries(<name> lib1 lib2 lib3) 
# 添加一个名为<name>的库文件,指定STATIC, SHARED, MODULE参数来指定要创建的库的类型, STATIC对应的静态库(.a)，SHARED对应共享动态库(.so)
add_library(<name> [STATIC | SHARED | MODULE] [EXCLUDE_FROM_ALL] source1 source2 ... sourceN)
# 指明本项目包含一个子目录,子目录中也需要包含有CMakeLists.txt
add_subdirectory(sub_dir)
# 添加编译参数
add_definitions()
# 设置头文件位置,指定头文件的搜索路径
include_directories(./include ${MY_INCLUDE})
# 设置动态链接库或静态链接库的搜索路径，参数是目录
link_directories（directory1 directory2 ...）
# 添加需要链接的库文件路径，参数是文件路径
LINK_LIBRARIES()
# 查找库所在目录,在path中查找name1的路径，保存在VAR中，，如果所有目录中都没有，VARB就会被赋为NO_DEFAULT_PATH
find_library (<VAR> name1 [path1 path2 ...])
```

```cmake
# 设置可执行文件的输出路径(EXCUTABLE_OUTPUT_PATH是全局变量)
set(EXECUTABLE_OUTPUT_PATH [output_path])
# 设置库文件的输出路径(LIBRARY_OUTPUT_PATH是全局变量)
set(LIBRARY_OUTPUT_PATH [output_path])
# 设置C++编译参数(CMAKE_CXX_FLAGS是全局变量)
set(CMAKE_CXX_FLAGS "-Wall std=c++11")
# 设置源文件集合(SOURCE_FILES是本地变量即自定义变量)
set(SOURCE_FILES main.cpp test.cpp ...)
```
----------------------
## 5. cmake使用案例
从简单到复杂介绍几个常见的使用场景
### 1. 单目录一个或多源文件的编译

```cmake
# CMake 最低版本号要求
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
# 项目信息
PROJECT(main)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
# 指定生成目标
ADD_EXECUTABLE(main ${DIR_SRCS})
```

### 2. 多目录编译
- 在项目的根目录下编写CMakeLists.txt，然后在每个子目录也编写一个
- 适当时把文件编译成静态库由main函数调用
```cmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(main) 
ADD_SUBDIRECTORY( src )
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
ADD_EXECUTABLE(main ${DIR_SRCS}  )
# 添加链接库
TARGET_LINK_LIBRARIES( main Test )
```

```cmake
AUX_SOURCE_DIRECTORY(. DIR_TEST1_SRCS)
# 设置库文件的输出路径
set(LIBRARY_OUTPUT_PATH [output_path])
# 生成链接库
ADD_LIBRARY (Test ${DIR_TEST1_SRCS})
```

### 3. 自定义编译选项


### 4. 安装和测试功能

---------------------
**参考资料**
[cmake](https://blog.csdn.net/gg_18826075157/article/details/72780431)  
[cmake](https://blog.csdn.net/kai_zone/article/details/82656964)  
[cmake](https://blog.csdn.net/fengzhongluoleidehua/article/details/79809756)  
[cmake常用语法](https://www.jianshu.com/p/8909efe13308)
[cmake手册详解](https://www.cnblogs.com/coderfenghc/tag/cmake/)
[camke命名](https://blog.csdn.net/wzzfeitian/article/details/40963457/)
