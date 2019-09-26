

[参考资料](https://www.liaoxuefeng.com/wiki/896043488029600)




### 版本回退
* HEAD指向的版本就是当前版本，因此，Git允许我们在版本的历史之间穿梭，使用命令git reset --hard commit_id。
* 穿梭前，用git log可以查看提交历史，以便确定要回退到哪个版本。
* 要重返未来，用git reflog查看命令历史，以便确定要回到未来的哪个版本。



###  暂存区
* 第一步是用git add把文件添加进去，实际上就是把文件修改添加到暂存区；
* 第二步是用git commit提交更改，实际上就是把暂存区的所有内容提交到当前分支。


### 撤销修改
* 命令git checkout -- readme.txt意思就是，把readme.txt文件在工作区的修改全部撤销，这里有两种情况：
    * 一种是readme.txt自修改后还没有被放到暂存区，现在，撤销修改就回到和版本库一模一样的状态；
    * 一种是readme.txt已经添加到暂存区后，又作了修改，现在，撤销修改就回到添加到暂存区后的状态。
    * 总之，就是让这个文件回到最近一次git commit或git add时的状态。
* git reset命令既可以回退版本，也可以把暂存区的修改回退到工作区
    * 场景1：当你改乱了工作区某个文件的内容，想直接丢弃工作区的修改时，用命令git checkout -- file。
    * 场景2：当你不但改乱了工作区某个文件的内容，还添加到了暂存区时，想丢弃修改，分两步，第一步用命令git reset HEAD <file>，就回到了场景1，第二步按场景1操作。
    * 场景3：已经提交了不合适的修改到版本库时，想要撤销本次提交，参考版本回退一节，不过前提是没有推送到远程库。






## 分支管理

* 查看分支：git branch
* 创建分支：git branch <name>
* 切换分支：git checkout <name>或者git switch <name>
* 创建+切换分支：git checkout -b <name>或者git switch -c <name>
* 合并某分支到当前分支：git merge <name>
* 删除分支：git branch -d <name>
* 如果要丢弃一个没有被合并过的分支，可以通过git branch -D <name>强行删除。
* Fast-forward信息，Git告诉我们，这次合并是“快进模式”，也就是直接把master指向dev的当前提交，所以合并速度非常快。
* 解决冲突就是把Git合并失败的文件手动编辑为我们希望的内容，再提交。
* 合并分支时，加上--no-ff参数就可以用普通模式合并，合并后的历史有分支，能看出来曾经做过合并，而fast forward合并就看不出来曾经做过合并。

* git stash功能，可以把当前工作现场“储藏”起来，等以后恢复现场后继续工作
* 是用git stash apply恢复，但是恢复后，stash内容并不删除，你需要用git stash drop来删除；
* 另一种方式是用git stash pop，恢复的同时把stash内容也删了：
* 在master分支上修复的bug，想要合并到当前dev分支，可以用git cherry-pick <commit>命令，把bug提交的修改“复制”到当前分支，避免重复劳动



## 多人合作远程库管理
* 查看远程库信息，使用git remote -v；
* 本地新建的分支如果不推送到远程，对其他人就是不可见的；
* 从本地推送分支，使用git push origin branch-name，如果推送失败，先用git pull抓取远程的新提交；
* 在本地创建和远程分支对应的分支，使用git checkout -b branch-name origin/branch-name，本地和远程分支的名称最好一致；
* 建立本地分支和远程分支的关联，使用git branch --set-upstream branch-name origin/branch-name；
* 从远程抓取分支，使用git pull，如果有冲突，要先处理冲突。



### git merge和git rebase
[参考资料](https://blog.csdn.net/wh_19910525/article/details/7554489)
[参考资料](https://www.cnblogs.com/shuimuzhushui/p/9000253.html)

git merge：将两个分支，合并提交为一个新提交，并且新提交有2个parent。
git rebase：会取消分支中的每个提交，并把他们临时存放，然后把当前分支更新到最新的origin分支，最后再吧所有提交应用到分支上。

rebase会把你当前分支的 commit 放到公共分支的最后面,所以叫变基。就好像你从公共分支又重新拉出来这个分支一样。
merge 会把公共分支和你当前的commit 合并在一起，形成一个新的 commit 提交

不要在公共分支使用rebase

### git fetch和git pull
[参考资料](https://www.cnblogs.com/runnerjack/p/9342362.html)
* git fetch是将远程主机的最新内容拉到本地，用户在检查了以后决定是否合并到工作本机分支中。
* git pull 则是将远程主机的最新内容拉下来后直接合并，即：git pull = git fetch + git merge，这样可能会产生冲突，需要手动解决。
