# 远程连接Linux服务器

## ssh介绍

SSH之所以能够保证安全，原因在于它采用了非对称加密技术(RSA)加密了所有传输的数据。

传统的网络服务程序，如FTP、Pop和Telnet其本质上都是不安全的；因为它们在网络上用明文传送数据、用户帐号和用户口令，很容易受到中间人（man-in-the-middle）攻击方式的攻击。就是存在另一个人或者一台机器冒充真正的服务器接收用户传给服务器的数据，然后再冒充用户把数据传给真正的服务器。

但并不是说SSH就是绝对安全的，因为它本身提供两种级别的验证方法：

第一种级别（基于口令的安全验证）：只要你知道自己帐号和口令，就可以登录到远程主机。所有传输的数据都会被加密，但是不能保证你正在连接的服务器就是你想连接的服务器。可能会有别的服务器在冒充真正的服务器，也就是受到“中间人攻击”这种方式的攻击。

第二种级别（基于密钥的安全验证）：你必须为自己创建一对密钥，并把公钥放在需要访问的服务器上。如果你要连接到SSH服务器上，客户端软件就会向服务器发出请求，请求用你的密钥进行安全验证。服务器收到请求之后，先在该服务器上你的主目录下寻找你的公钥，然后把它和你发送过来的公钥进行比较。如果两个密钥一致，服务器就用公钥加密“质询”(challenge)并把它发送给客户端软件。客户端软件收到“质询”之后就可以用你的私钥在本地解密再把它发送给服务器完成登录。与第一种级别相比，第二种级别不仅加密所有传输的数据，也不需要在网络上传送口令，因此安全性更高，可以有效防止中间人攻击

## 1. ssh登录介绍


### 启动服务器ssh服务

1. 如果只是想远程登陆别的机器只需要安装客户端（Ubuntu默认安装了客户端），如果要开放本机的SSH服务就需要安装服务器。
```bash
# 检查安装系统时是否已经安装SSH服务端软件包
rpm -qa|grep openssh #centOs
dpkg -l | grep ssh #Ubuntu
```

2. 安装服务器ssh操作
- Ubuntu
```bash
# 确认ssh-server是否已经启动了,出现sshd 表示ssh-server已经启动了
ps -e | grep ssh  
# 安装
sudo apt install openssh-server
sudo apt install openssh-client
# 启动服务
sudo /etc/init.d/ssh start
sudo service sshd start
# 重启服务
sudo service ssh restart
# 自动启动
sudo systemctl enable ssh
# 查看服务状态
sudo service ssh status 
# 关闭服务
sudo service ssh stop
```
- CentOs
```bash
# 安装
yum install -y openssl openssh-server
# 重启sshd服务
systemctl restart sshd.service
# 自动启动
systemctl enable sshd
```

### 远程登录方法
   
1. 口令登录
   - 口令登录非常简单，只需要一条命令，命令格式为： ssh 客户端用户名@服务器ip地址，例如`ssh root@126.123.123.23`,可以在服务器端电脑上利用 ifconfig 命令查看服务器的ip地址
   - 如果客户机的用户名和服务器的用户名相同，登录时可以省略用户名
   - SSH服务的默认端口是22，也就是说，如果你不设置端口的话登录请求会自动送到远程主机的22端口。我们可以使用 -p 选项来修改端口号,例如`ssh -p 1343 root@126.123.123.23`
   - 第一次登录远程主机，会给出提示该远程主机的真实性无法确定，输入yes就行
   - 然后会要求我们输入远程主机的密码，输入的密码正确就可以成功登录了
   - 以通过 Ctrl+D 或者 exit 命令退出远程登录
2. 公钥登录
   - 在本机生成密钥对`ssh-keygen -t rsa` 
   - 执行完毕后会在 /home/当前用户 目录下生成一个 .ssh 文件夹,其中包含私钥文件 id_rsa 和公钥文件 id_rsa.pub。
   - 本地测试，`cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys`,随后`ssh localhost`，如果成功登录并且不用输入密码那么 ssh无密码机制就算建立成功了
   - 使用ssh-copy-id命令将公钥复制到远程主机。ssh-copy-id会将公钥写到远程主机的 ~/.ssh/authorized_keys文件中。或者手动把它追加在authorized_keys文件的末尾就行了
3. 服务器重新安装系统后出错的解决方法
   -  会出现REMOTE HOST IDENTIFICATION HAS CHANGED!错误
   -  出现这个问题的原因是,第一次使用SSH连接时，会生成一个认证，储存在客户端的known_hosts中，服务器重新安装系统了，所以会出现以上错误
   -  解决办法`ssh-keygen -R 服务器端的ip地址`


## 连接操作

https://blog.csdn.net/weixin_42864357/article/details/105658765

1. 搜索Remote Development插件并进行安装
2. 进入设置，搜索ssh，找到并选中拓展中的Remote-SSH中的ShowLoginTerminal选项，因为在连接的时候，终端会让你输入yes或者密码等
3. 点击 远程资源管理器，鼠标移到 SSH TARGETS 点击齿轮图
4. 点击弹出的 config文件
5. 填写自己的服务器配置，Host为在VS Code内显示的名称，可以随意填写，Hostname是远程服务器的公网IP地址，User 是用于登录的用户名称


https://blog.csdn.net/li528405176/article/details/82810342