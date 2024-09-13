相信不止我一个人是先听说的github,再知道的git.作为程序员必备的东西却一直没用过.因为听课的时候发现需要使用,于是不得不开始尝试,记录了新手学习git使用的曲折历程.

首先通过百度,知道了啥是git.

## git是什么?

>  **git**是一个[分布式版本控制](https://zh.wikipedia.org/wiki/分散式版本控制)软件

## 下载Git

找到了多种安装方式:[官方自动安装](https://git-scm.com/download/win)或[Chocolatey Software | Git 2.41.0](https://community.chocolatey.org/packages/git)或[通过Github(https://github.com/git-for-windows).

## 安装Git

理论上通过官方安装程序,进行安装,一路默认设置应该就可以.但当时因为Git下载太慢,在国内找了压缩包进行解压来使用.由于没有经验,所以一点一点的进行了很多尝试,踩了很多坑,下面一一展示.

解压压缩包之后,第一步,添加环境变量,由于之前配置过GO和C++和python,这一步比较轻车熟路.

点击编辑环境变量

![image-20230817222157856](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230817222157856.png)

再加入到环境变量中,这里在系统变量或者用户变量都可以.![屏幕截图(372)](C:\Users\Baijy\Desktop\屏幕截图(372).png)

在powershell中输入`git --version`后能够正常显示版本信息了.

然后据网络上教程说,可以在开始菜单输入git看看能不能找到git bash,那么显然是找不到的.

看起来好像无伤大雅,也就没管了.

但当想创建仓库时,需要用到`右键-git bash here`的操作,问题来了,右键之后没有.于是又上网找教程.

找到了[手动修改注册表添加git bash here 的教程](https://blog.csdn.net/Passerby_Wang/article/details/120881670).

但发现好像弄出来有点不一样??(无所谓,能用就行)

![image-20230817223310744](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230817223310744.png)

然后打开vscode,发现终端里找不到git bash.那咋办?只能再找[教程](https://blog.csdn.net/Passerby_Wang/article/details/120881670)进行手动添加.

![image-20230818202025354](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230818202025354.png)

终于看起来万事具备了,第一次执行了git clone 命令,得到了第一个仓库,感慨万千,总算是成功迈出了第一步,可喜可贺.

![image-20230818202546590](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230818202546590.png)