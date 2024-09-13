## Map

哈希表是无序的键值对集合,而map是对哈希表的引用.map中所有的key和value都必须有相同类型

可以用make来创建空的map

```go
m:=make(map[string]int)//string是key的类型,int是value的类型.可以在后面加{}来指定一些最初的key/value,如果只有{}则是一个空map.
```

内置的delete可以用于删除元素

> delete (map,key)

key作索引访问map会得到value,如果不存在则会返回对应的0值,故可以使用:

> a,ok=map[key]

这种方式来判断是否存在该key.

常写作:

>age, ok := ages["bob"]
>if !ok { /* "bob" is not a key in this map; age == 0. */ }
>
>//或:
>
>if age, ok := ages["bob"]; !ok { /* ... */ }

和slice一样,map无法进行相等比较,除非是和nil,如果想判断是否有相同键值对,需要用循环来实现.

## range

用于遍历map和slice.

对于slice,返回下标和对应值(如果不需要索引,可用_来占个位置)

对于map,返回键 值对

## 函数

例子:实现两数相加

``` go
func add(a int,b int)int/*这个int是返回值的类型,可以用(a int, b int)来实现返回a,b*/ {
return a+b
}
```

函数原生支持返回多个值

## 指针

主要用于对参数进行修改

例:

``` go
func add2(n *int){
*n+=2
}//可以实现对传入参数的修改
//但在调用时,需要加一个&,才能通过编译
//在main中:add2(&n)才行
```

## 结构体

语法:

``` go
type struct_name struct{
    //name type
    ID int//类似于这种
}
//在主函数中声明:
var name struct_name
//可通过.操作取值
name.ID
```

一个命名为s的结构体类型无法包含s类型的成员,因为聚合的值不能包含自身(限制同样适用于数组)

结构体与成员顺序相关,不同顺序的话是不同的结构体类型.

结构体也能作为函数参数,也有指针和非指针两种用法.

## 结构体方法

类似于类的成员函数

如:

```go
func(u *struct_name)reset(ID int){//在func后面函数名前面加()来实现,带指针可以实现对结构体修改
    u.ID=ID
}
//在主函数中即可使用:
var u struct_name
u.reset(123)
```

## 错误处理

go通常用一个返回值来传递错误信息

可以通过在函数的返回值类型里面加一个error来实现,表面这个函数可能会有错误

如果有错,可以像这样:

```go
func name(name string)(v *struct_name,err error){//注:需要导入errors包
    if wrong
    return nil,erros.New(/*错误信息*/)else 
    return &v,nil
}
//主函数中调用时需要些两个变量来接收.
```

## 字符串操作

strings包中有很多字符串操作

注意,用len时中文会被当做三个字符

```go
strings.Contains(a, "l")                 //判断l是否在a中
	strings.Count(a, "l")                    //计数
	strings.HasPrefix(a, "h")                //判断开头是否是h
	strings.HasSuffix(a, "o")                //判断末尾是否是o
	strings.Index(a, "ll")                   //找到"ll"开始的下标(return 2)
	strings.Join([]string{"he", "llo"}, "-") //字符串拼接
	strings.Repeat(a, 2)                     //a重复两遍
	strings.Replace(a, "e", "E", 1)          //e->E,最后一个数字是替换几个,如果是-1就全换
	strings.Split("a-b-c", "-")              //去掉-
	strings.ToLower(a)                       //首字母小写
	strings.ToUpper(a)                       //首字母大写
```



## 字符串格式化

```go
fmt.printf()//类似于c中的printf,%v来输出任意类型变量,%+v可以得到更详细的结构,%#v则更详细
//使用%f,%d也是可以的
```

## JSON处理

好复杂,不想看,先跳过吧\*_\*

留个[链接](https://blog.csdn.net/xiazhipeng1000/article/details/112738754?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169114242416800182790896%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=169114242416800182790896&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-112738754-null-null.142^v92^chatgptT3_1&utm_term=go%20json&spm=1018.2226.3001.4187)

## 时间处理

导入"time"包

用time.Now()来获取时间,也可以用time.Date来构造时间(带时区)

输出时可以用"."输出具体的内容

``` go
t:=time.Date(2023,8,4,17,58,0,time.UTC)
diff:=t2.Sub(t)//两时间做差
t.Year()//年
t.Munite()//时间里的分
diff.Minutes()//把做差的时间转换为分
diff.Seconds()//把做差时间转换为秒
time.Uix()//获取一个时间戳
```

## 数字解析

要导入"strconv"包

```go
f,_:=strconv.ParseFloat("1.234",64)//f=1.234, 64为转化为64位浮点数
f,_:=strconv.ParseInt("111",10,64)//f=111, 10为十进制表示,64为64位
f,_:=strconv.Atoi("123")//f=123,快速转换
//输入不合法会返回错误,即"_"对应的位置
```

