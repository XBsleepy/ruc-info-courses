# 基础

## hello world

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

* go不用在语句或者声明末尾加分号,出分一行上有多条语句.换行符添加的位置有时会影响正确解析.如func声明中{必须和func在同一行且位于末尾,不能独占一行.而x+y可分为x+\n y而不能x\n +y,因为后者会自动加入分号分隔符.

## 变量

### 声明

```go
package main //文件属于main包的一部分
import (
	"fmt"
) //导入fmt包
func main() { //main函数调用
	var a="abc"//字符串
	var b,c int =1,2//整形
    var d =true//布尔
    var e float64//浮点数
}
```

