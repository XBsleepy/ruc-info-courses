## JSON是什么

### 简介

**JSON **指的是 **JavaScript 对象表示法**（**J**ava**S**cript **O**bject **N**otation）,是一种**轻量级**的文本数据交换格式,且其不依赖于语言和平台,很多语言都支持JSON.

JSON有对象和数组两种结构

对象用"{}"表示,数组用"[]"表示,对象与数组可以互相包含.

`{}`中保存的是无序的 `键:值`的集合,而`[]`保存的是有序的值的集合.

string/number/bool/null/object/array都可以做值,但键必须是字符串.

### 访问

在对象中,键与值用`:`分割,键值对用`,`分割,用`./[]`访问对象的值,JSON对象可以嵌套,互相包含,同样可以用`./[]`来进行访问.

``` json
obj = {
    "name":"name","name1":name
}
```

>  obj.name
>
> obj[name]

而如果要访问数组,可以用下标

```json
obj={
"name":[ "Google", "Runoob", "Taobao" ]
}
x=obj.name[0]//Google
```

## GO中的简单JSON操作

对已有结构体/Map,只要保证每个字段的第一个字母大写,就可以用json.Marshal()序列化.序列化,变为byte数组,JSON的格式.

```GO
type userInfo struct {
	Name  string
	Age   int 
	Hobby []string
}
func main() {
	a := userInfo{Name: "wang", Age: 18, Hobby: []string{"Golang", "TypeScript"}}
	buf, err := json.Marshal(a)
	if err != nil {
		panic(err)
	}
	fmt.Println(buf)         // 需要强制类型转换,否则输出[123 34 78 97...]
	fmt.Println(string(buf)) // {"Name":"wang","Age":18,"Hobby":["Golang","TypeScript"]}JSON格式

```



```GO
Age   int `json:"age"`//加上`json:"age"`,能够在序列化时得到age而不是Age
```



序列化后也可以用`json.Unmarshal()`来反序列化到一个空变量中

```GO
var b userInfo
	err = json.Unmarshal(buf, &b)
	if err != nil {
		panic(err)
	}
	fmt.Printf("%#v\n", b) // main.userInfo{Name:"wang", Age:18, Hobby:[]string{"Golang", "TypeScript"}}
```

注意,反序列化后,仍然是Age而不是age.

## 实例

在例子 [在线词典](https://github.com/wangkechun/go-by-example/tree/master/simpledict)中,用代码在golang中构造请求时会比较复杂,可用网址可以直接生成请求https://curlconverter.com/#go

将部分编译错误行删掉就可正确运行,最后能得到一个JSON字符串

返回的数据是一个巨大的json,可以用a[name]取,但不是最佳实践,最好用结构体接受,但比较复杂,可以用网站:[JSON转Golang Struct - 在线工具 - OKTools](https://oktools.net/json2go)直接进行转换.

通过新建一个结构体变量来对其进行反序列化得到结构体,从而更好地处理数据.