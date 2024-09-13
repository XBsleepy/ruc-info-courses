### 并发与并行

并发:多线程在一个核cpu上运行

并行:直接利用多核实现多线程同时运行.

广义的并发可以认为是系统对外的一种特征,实际中可以认为并行是实现并发的手段

GO可以充分利用多核计算机的优势

### 协程与线程

协程:用户态,轻量级线程,栈KB级别(调度由GO语言本身完成,可以一次创建上万的协程)

线程:内核态,线程跑多个协程,栈MB级别.比较消耗资源

#### 如何开启协程?

在调用函数前加go关键字即可

GO推荐通过协程间通信来共享内存,而不是共享内存实现通信

**通道**:让goroutine之间通信的东西

通过共享内存通信的话,需要加锁

```GO
func CalSquare() {
	src := make(chan int)
	dest := make(chan int, 3)
	go func() {
		defer close(src)
		for i := 0; i < 10; i++ {
			src <- i //将i发送到src的channel
		}
	}()
	go func() {
		defer close(dest)
		for i := range src { //遍历src的数据,实现A,B协程的通信
			dest <- i * i
		}
	}()
	for i := range dest {
		println(i)
	}
}
```



### channel的创建

语法:
make(chan 元素类型,[缓冲大小])

>make(chan int)//无缓冲
>
>make (chan int,2)//容量为2的有缓冲通道

无缓冲会让发送和接收同步化,通道容量代表可以存放的数量

#### lock

上锁能更安全,通过对临界区的控制来实现并发安全,防止出现未定义的情况

Sync中有WaitGroup和Mutex

Mutex可用于上锁

```GO
var(
    x int64
	lock sync.Mutex
)
func addWithLock(){//保证并发安全
    for i:=0;i<2000;i++{
        lock.Lock()
        x+=1
        lock.Unlock()
    }
}
```

#### WaitGroup

WaitGroup的使用,来实现阻塞

Add(delta int) 计数器+delta

Done()计数器减一

Wait()阻塞直到计数器为0

**defer**关键字,用于实现函数调用的延迟执行,让该函数在所执行的函数结束前被调用

```
func ManyGo() {
	var wg sync.WaitGroup
	for i := 0; i < 5; i++ {
		wg.Add(1)
		go func(j int) {
			defer wg.Done()
			hello(j)
		}(i)
	}
	wg.Wait()
}
```



## 依赖管理

**依赖**:go的开发包

GOPATH环境变量:
bin:编译的二进制文件

pkg:加速编译的中间产物

src:项目源码

弊端无法实现package的多版本控制

解决方法:项目目录下增加vendor文件夹

通过每个项目引入一份依赖副本的方式解决多个项目需要同一个package依赖的冲突问题

寻址依赖:vendor=>GOPATH

但通过vender,无法控制以来的版本

Go Module

通过go.mod 文件管理依赖包

通过go get/go mod 指令工具管理依赖包

依赖管理三要素:

> go.mod //配置文件,描述依赖
>
> Proxy //中心仓库管理依赖仓库
>
> go get/mod //本地工具

go.mod两种配置规则

语义化版本

${major}.${minor}.${patch}

不同major间可以不兼容

minor要在major规则上前后兼容

patch一般是做一些代码化的修复

例子:

V1.3.0

V2.3.0

基于commit的伪版本

vX.0.0-yyyymmddhhmmss-abcdefgh1234

版本号-提交时间戳-提交commit的十二位哈希码

每次提交commit都回默认生成一个伪版本号

indirect

若a依赖b,b依赖c,则a对c是非直接依赖,会用//indirect标识出来

在go.mod版本规则中,对于2+的major版本都应加上后缀

主版本2+模块会在模块路径增加/vN后缀
对于没有go.mod文件并且主版本2+的依赖,会在版本号上+incompatible//标识出可能存在不兼容的代码逻辑

依赖分发-回源

Github->SVn->...

问题:无法保证构建稳定性/增加/删除/修改软件版本

无法保证依赖可用性

增加代码托管平台的负载压力

Proxy

通过Proxy来实现稳定可靠的依赖分发,通过proxy来拉取依赖

配置GOPROXY

go.mod通过GOPROXY的环境变量来控制

以此在环境变量下的URL中查找,如果都查找不到就回到原本的第三方平台

go get 工具:

![image-20230805193648957](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230805193648957.png)

go mod:

![image-20230805193659290](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230805193659290.png)