## hello world

从hello world 开始：

```go
package main //文件属于main包的一部分
import (//声明必须跟在package后
	"fmt"
) //导入fmt包
func main() { //main函数调用
	fmt.Println("Hello,World!")
}
```

main 包定义了一个独立可执行的程序而不是一个库.main函数作用类似于c

一些区别:

* go不用在语句或者声明末尾加分号,除非一行上有多条语句.
* 换行符添加的位置有时会影响正确解析.如func声明中”{“必须和func在同一行且位于末尾,不能独占一行.（而x+y可分为x+\n y而不能x\n +y,因为后者会自动加入分号分隔符.)
* 变量类型要放在变量名后面
* 定义变量却不使用会报错（而不是警告）
* a++/++a是语句无法赋值，如b=a++，会报错
* 如果变量不给初值，默认会给0值
* 如果省略每个变量的类型，可以声明多个类型不同的变量
* 可以通过：=来自动得到类型
* gofmt工具会把代码格式化为标准格式。

## 变量

声明变量

var 变量名字 类型 = 表达式

举例：

```go
package main //文件属于main包的一部分
import (
	"fmt"
) //导入fmt包
func main() { //main函数调用
	var a="abc"//字符串
	var b,c int =1,2//整型变量
    var d =true//布尔
    var e float64//浮点数
    var b, f, s = true, 2.3, "four" // bool, float64, string，同时声明多个类型变量
    f :=float32(e)//自动获得类型
    g:=a+"foo"//内置的字符串拼接
    //如果是常量命名，把var改为const即可
}
```

## 条件语句

不打括号,其余和C差不多

```go
if num:=9;num<0{
    fmt.Println(num+1)
}else if num==9{
    fmt.Println(num)
}else{
    fmt.Println(num-1)
}
```

## 循环

```go 
for{
    fmt.Println("1")
}//死循环，类似于while(1),可以加break跳出，此外，continue差不多
for j:=7;j<9;j++{//类似于c
    fmt.Println(j)
}
//也可以类似于while的写法：
for i<=3{
    fmt.Println(i)
    i=i+1
}
```

## switch

类似于C，但是不加break也不会跑完剩下所有case分支。也有default默认操作

## 数组

下标同样从0开始，可以通过其来访问

``` go
var a [3]int//声明数组
//也可以写为[...]，根据给出的初始值来自动确定个数
b := [...]int{1, 2, 3}
for i, v := range a {//类似python
    fmt.Printf("%d %d\n", i, v)//i是下标，v是值
}
```

## 切片（slice）

可变长度数组，要求元素类型要相同，用make创建，用append添加元素，可以像python数组一样取值

但与数组不同的是，slice之间不能够直接比较，用==无法判断是否含有全部相等元素

``` go
s:=make([]string,3)//make(类型，长度，容量)
var x, y []int
s=append(s,"d")//s.append()不行
```

## map

