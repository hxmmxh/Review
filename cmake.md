


## CMAKE简介
* CMake是一个跨平台的、开源的构建工具。cmake是makefile的上层工具，它们的目的正是为了产生可移植的makefile，并简化自己动手写makefile时的巨大工作量。
* CMake是一个跨平台的自动化建构系统,它使用一个名为 CMakeLists.txt 的文件来描述构建过程,可以产生标准的构建文件,如 Unix 的 Makefile 或Windows Visual C++ 的 projects/workspaces 。文件 CMakeLists.txt 需要手工编写,也可以通过编写脚本进行半自动的生成
* 在 linux 平台下使用 CMake 生成 Makefile 并编译的流程如下:
    * 编写 CMakeLists.txt。
    * 执行命令“cmake PATH”或者“ccmake PATH”生成 Makefile ( PATH 是 CMakeLists.txt 所在的目录 )。
    * 使用 make 命令进行编译。

----------------------
## 安装CMAKE
* sudo apt-get install cmake
* 或者cmake官网下载压缩包，解压缩后安装
```BASH
tar -xzvf cmake-2.6.4.tar.gz
cd cmake-2.6.4
./bootstrap
make
make install
```
----------------------------
## CMAKE使用
CMakeLists.txt 的语法比较简单,由命令、注释和空格组成,其中命令是不区分大小写的,符号"#"后面的内容被认为是注释。命令由命令名称、小括号和参数组成,参数之间使用空格进行间隔。

```cmake
cmake_minimum_required (<version>) //cmake最低版本需求，不加入此行会受到警告信息
project (<name>) //项目名称
add_executable(<name> ${SRC_LIST}) //使用给定的源文件生成可执行文件
target_link_libraries(<name> lib1 lib2 lib3)//指明可执行文件需要连接的链接库
aux_source_directory(<dir> <variable>) //参数 <dir> 中所有的源文件名称赋值给参数 <variable>
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
``





---------------------
**参考资料**
[cmake](https://blog.csdn.net/gg_18826075157/article/details/72780431)  
[cmake](https://blog.csdn.net/kai_zone/article/details/82656964)  
[cmake](https://blog.csdn.net/fengzhongluoleidehua/article/details/79809756)  
[cmake常用语法](https://www.jianshu.com/p/8909efe13308)
