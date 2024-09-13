# 类

## 继承

### 基类与派生类

派生类：

> class 派生类名：继承方式[^继承方式]  基类名1，继承方式 基类名2，继承方式。。。
>
> {
>
> 派生类成员声明；
> }

多继承：

> 一个派生类有多个基类

### 访问控制

基类成员可以有**public,protected,private**三种形式。

#### 公有继承

基类的公有和保护成员访问属性不变，而基类的**私有成员**不可直接访问。

#### 私有继承

基类的公有和保护成员都以私有成员身份出现，私有成员不可直接访问。

派生类的成员函数及对象无法访问基类的私有成员。可以在类的内部进行访问，但不可在类外访问。

```c++
#include<iostream>
using namespace std;
class Father{
	public:
		void father(int x,int y){
			this-> x=x;
			this->y=y;
		}
		float dis();
		float getx()const {return x;}
		float gety()const {return y;}
		void show();
	private:
		int x;
		int y;
};
float Father::dis(){
	return x+y;
}
void Father::show(){
	cout<<dis()<<endl;
}
class Son:public Father{
	public:
		void rct(int a,int b,int c, int d){
			father(a,b);//无论public还是private，类内部都可以访问之。
			this->c=c;
			this->d=d;
			show();
		}
    	// int getx()const {return Father::getx()};private状态下需要重新声明才可保证接口可用。
	private:
		int c;
		int d;
};
int main(){
	Father a;
	a.father(1,0);
	cout<<a.getx()<<","<<a.gety()<<endl;
	a.show();
	Son b;
	b.rct(1,2,3,4);
	b.getx();//改为private时，b无法getx（）。
	return 0;
}
```

#### 保护继承

基类的公有和保护成员都以保护成员[^保护成员]身份出现，私有成员不可直接访问。

```c++
class Base {
protected:
    int protectedMember;
};

class Derived : public Base {
public:
    void setProtectedMember(int value) {
        protectedMember = value;  // 在派生类中可以访问基类的 protected 成员
    }
};

int main() {
    Derived derivedObj;
    derivedObj.setProtectedMember(10);  // 通过派生类访问基类的 protected 成员
    // derivedObj.protectedMember = 10;  // 错误，无法直接访问 protected 成员
    return 0;
}
```

### 类型兼容规则 

在需要基类对象的任何地方，都可以使用公有派生类的对象来代替。



公有继承能让派生类得到除了构造和析构以外的所有成员。

类型兼容规则包括三种情况：

- 派生类对象可以隐含转换为基类对象
- 派生类对象可以初始化基类引用
- 派生类的指针可以隐含转换为基类指针

代替后，派生类对象可以做作为基类对象使用，但只能使用从基类继承的成员。

```c++
class B{}
class D:public B{}
B b1,*pb1;
D d1;
b1=d1;//用派生类对象的成员逐个赋值给基类对象。
B &rb=d1;//初始化基类引用。
pb1=&d1;
```





[^保护成员]: 可以被派生类访问，但无法被类的外部访问。> `    Derived derivedObj;    derivedObj.setProtectedMember(10);  // 通过派生类访问基类的 protected 成员    // derivedObj.protectedMember = 10;  // 错误，无法直接访问 protected 成员    return 0;`
[^继承方式]: 规定了如何访问从基类中继承的成员，只限定紧随其后的类，private protected public.

### 构造和析构函数

#### 构造函数

初始化：

> 派生类名：：派生类名（参数表）：基类名1（基类1初始化参数表），积累名2（基类2初始化参数表）。。。{
> 派生类构造函数其他操作
>
> }//参数表要把所有用到的参数塞进去

如果对基类初始化时，需要调用基类的带有形参表的构造函数时，派生类就必须声明构造函数。

执行一般顺序：

1. 调用基类构造函数：按照被继承时声明的顺序从左向右
2. 对派生类新增的成员初始化，顺序按照在类中被声明的顺序
3. 执行派生类中构造函数的内容

例子：

```C++
#include<iostream>
using namespace std;

// 基类 Base1
class Base1 {
	public:
		Base1(int i) {
			cout << "Constructing Base1" << i << endl;
		}
};

// 基类 Base2
class Base2 {
	public:
		Base2(int j) {
			cout << "Constructing Base2" << j << endl;
		}
};

// 基类 Base3
class Base3 {
	public:
		Base3() {
			cout << "Constructing Base3*" << endl;
		}
};

// 派生类 Derived，继承自 Base2、Base1 和 Base3,注意其顺序。
class Derived: public Base2, public Base1, public Base3 {
	public://公有成员
		// Derived 类的构造函数，使用成员初始化列表初始化基类和成员对象
		Derived(int a, int b, int c, int d): Base1(a), member2(d), member1(c), Base2(b)
            //Base3只有默认构造函数，不用传递参数，故base3和member3就不用列出。
		{}//注意基类名的个数与顺序，注意成员对象名的个数与顺序。
	private://派生类的私有成员对象
		Base1 member1; // 成员对象 member1，属于类 Base1
		Base2 member2; // 成员对象 member2，属于类 Base2
		Base3 member3; // 成员对象 member3，属于类 Base3
};

int main() {
	Derived obj(1, 2, 3, 4); // 创建 Derived 类的对象 obj，传入参数 (1, 2, 3, 4)
	return 0;
}
/*结果：
Constructing Base22
Constructing Base11
Constructing Base3*
Constructing Base13
Constructing Base24
Constructing Base3* */
```

#### 复制构造函数

#### 析构函数

析构函数无类型，无参数。

派生过程中不继承析构，若要析构需要重新声明。

派生类析构函数会隐式调用基类析构函数，但执行次序和构造函数相反。

#### 删除delete构造函数

通过delete来禁止默认构造函数或删除复制构造函数以阻止复制的做法，在基类中删除掉的构造函数在派生类中也对应是删除状态。

~~~ c++
#include<iostream>
using namespace std;

// 基类 Base
class Base {
	public:
		// 默认构造函数
		Base() = default;

		// 带参数的构造函数，使用传入的字符串初始化成员变量info
		Base(string _info) : info(std::move(_info)) {}

		// 禁用拷贝构造函数
		Base(Base&) = delete;

		// 禁用移动构造函数
		Base(Base&&) = delete;

	private:
		string info; // 成员变量 info，存储基类信息
};

// 派生类 Derived，继承自 Base
class Derived : public Base {
	
};

int main() {
	Derived d1; // 创建派生类对象 d1

	Derived d2(d1); // 非法，禁用了拷贝构造函数，不能通过拷贝初始化

	Derived d3(std::move(d1)); // 非法，禁用了移动构造函数，不能通过移动初始化

	return 0;
}
~~~

1. `Base` 是一个基类，没有定义任何虚函数。它包含一个默认构造函数和带参数的构造函数，用于初始化成员变量 `info`。
2. `Base` 中禁用了拷贝构造函数和移动构造函数，意味着不允许进行拷贝或者移动初始化，防止对象被不正确地复制或移动。
3. `Derived` 是一个派生类，从 `Base` 继承而来。在 `Derived` 中未定义任何成员变量或者函数。
4. `main()` 函数中，首先创建了一个派生类对象 `d1`，其会调用基类和派生类的构造函数进行初始化。
5. 接下来尝试通过 `d1` 进行拷贝初始化以及移动初始化的操作。由于基类禁用了拷贝构造函数和移动构造函数，因此这两种操作都是非法的。

### 派生类成员标识与访问

分类：

* **不可访问**（从基类私有成员继承而来，派生类或是建立派生类对象的模块都无法访问）
* **私有**
* **保护**
* **共友**

#### 作用域分辨符

“：：”

一般形式：

> 类名：：成员名
>
> 类名：：成员名（参数表）

**可见性原则**：两个或多个包含的具有包含关系的作用域中，外层声明存在，若内层没声明则在内层仍可用，若内层有声明则会屏蔽外层。“隐藏规则”

在类的派生结构中，基类成员与派生类新增成员属于两个层，派生类在内。如果派生类声明了与基类成员函数同名的新函数，则基类会被屏蔽，需要使用作用域分辨符和基类名来限定。（哪怕函数参数表不同也如此）

若继承的多个基类都有同名函数，且子类也有，则子类中的会屏蔽别的。如果子类没有，则使用时需要进行限制，通过作用域，基类名来标识。

**重载必须是针对于相同作用域的函数**，子类和父类相同时，是屏蔽而不是重载。

```C++
#include<iostream>
using namespace std;

class Base1{
    public:
        int var;
        void fun(){cout<<"member of Base1"<<endl;}
};

class Base2{
    public:
        int var;
        void fun(){cout<<"member of Base2"<<endl;}
};

class Derived:public Base1, public Base2{
    public:
        int var;
        void fun(){cout<<"member of Derived"<<endl;}
};

int main(){
    Derived d; // 创建Derived类的对象d

    Derived *p=&d; // 创建Derived类的指针p，并将d的地址赋给p

    d.var=1; // 在Derived类对象中设置var为1
    d.fun(); // 调用Derived类的fun函数，输出 "member of Derived"

    d.Base1::var=2; // 在Base1中设置var为2（使用作用域解析运算符::指定）如果不指定，会报错
    d.Base1::fun(); // 调用Base1的fun函数，输出 "member of Base1"

    p->Base2::var=3; // 通过指针p，在Base2中设置var为3（使用作用域解析运算符::指定）
    p->Base2::fun(); // 通过指针p调用Base2的fun函数，输出 "member of Base2"
	//也可以修改为在Derived类里面指定，如：
    //public：
    //using Base1::var
    return 0;
}
```

using还有另一用法，用于基类中的函数名，是派生类中定义同名不同参数的函数时实现重载：

``` c++
class Derived2:public Base1{
    public:
    	using Base1::fun;
    	void fun(int i){。。。}
}
```

还有一种情况,部分或全部直接基类是由另一基类派生而来：

```C++
#include<iostream>
using namespace std;

class Base0{
    public:
        int var0;
        void fun0(){  // Base0类的成员函数
            cout<<"member of Base0"<<endl;
        }
};

class Base1:public Base0{
    public:
        int var1;    // Base1类的成员变量
};

class Base2:public Base0{
    public:
        int var2;    // Base2类的成员变量
};

class Derived:public Base1,public Base2{
    public:
        int var;      // Derived类的成员变量
        void fun(){   // Derived类的成员函数
            cout<<"Member of Derived"<<endl;
        }
};

int main(){
    Derived d;       // 创建Derived类对象d

    d.Base1::var0=2;    // 通过对象d访问Base1类继承自Base0类的成员变量var0
    d.Base1::fun0();    // 通过对象d调用Base0类的成员函数fun0

    d.Base2::var0=3;    // 通过对象d访问Base2类继承自Base0类的成员变量var0
    d.Base2::fun0();    // 通过对象d调用Base0类的成员函数fun0

    return 0;       // 返回0表示程序正常结束
}
```

#### 虚基类

针对上面例子的情况，可以通过虚基类，来减少不必要的副本从而减少内存开销。

作用：将共同基类设置为虚基类，从不同路径继承过来的同名数据成员在内存中就只有一个，同一个函数名也就只有一个映射。

语法形式：

> class 派生类名：virtual 继承方式 基类名//只对紧随其后的基类起作用

```c++
#include<iostream>
using namespace std;

class Base0{
    public:
        int var0;
        void fun0(){    // Base0类的成员函数
            cout<<"member of Base0"<<endl;
        }
};

class Base1: virtual public Base0{    // 使用虚继承
    public:
        int var1;     // Base1类的成员变量
};

class Base2: virtual public Base0{    // 使用虚继承
    public:
        int var2;     // Base2类的成员变量
};

class Derived:public Base1,public Base2{
    public:
        int var;       // Derived类的成员变量
        void fun(){    // Derived类的成员函数
            cout<<"Member of Derived"<<endl;
        }
};

int main(){
    Derived d;       // 创建Derived类对象d

    d.var0=2;        // 直接通过对象d访问var0变量，省略了Base1和Base2的作用域

    d.fun0();        // 通过对象d调用Base0类的成员函数fun0，省略了Base1和Base2的作用域

    return 0;       // 返回0表示程序正常结束
}
```

这段代码在之前的基础上，将Base1和Base2类对Base0类的继承改为虚继承（使用`virtual public Base0`），即将Base0设置为虚基类。

虚基类的特点是当派生类通过多个路径继承同一个虚基类时，只生成一个虚基类子对象。这样可以避免由于多次继承而导致虚基类子对象重复出现的问题。

##### 虚基类及其派生类构造函数

如果虚基类声明中有非默认形式的构造函数，且没有声明默认构造函数。直接或间接继承虚基类的所有派生类都必须在构造函数的成员初始化表中列出对虚基类的初始化。

上例则应改为：

```C++
#include<iostream>
using namespace std;

class Base0{
    public:
        Base0(int var) : var0(var){}  // Base0类的构造函数，接受一个整型参数var，用于初始化var0成员变量
        int var0;    // Base0类的成员变量
        void fun0(){cout<<"member of Base0"<<endl;}  // Base0类的成员函数
};

class Base1: virtual public Base0{
    public:
        Base1(int var) : Base0(var){}  // Base1类的构造函数，接受一个整型参数var，通过初始化列表调用Base0的构造函数进行初始化
        int var1;    // Base1类的成员变量
};

class Base2: virtual public Base0{
    public:
        Base2(int var) : Base0(var){}  // Base2类的构造函数，接受一个整型参数var，通过初始化列表调用Base0的构造函数进行初始化
        int var2;    // Base2类的成员变量
};

class Derived: public Base1, public Base2{
    public:
        Derived(int var) : Base0(var), Base1(var), Base2(var){}  // Derived类的构造函数，接受一个整型参数var，通过初始化列表调用Base0、Base1和Base2的构造函数进行初始化
        int var;      // Derived类的成员变量
        void fun(){cout<<"Member of Derived"<<endl;}     // Derived类的成员函数
};

int main(){
    Derived d(1);     // 创建Derived类对象d，并调用构造函数进行初始化，传入参数1

    d.var0=2;        // **通过对象d直接访问var0变量**，省略了Base1和Base2的作用域

    d.fun0();        // **通过对象d调用Base0类的成员函数fun0**，省略了Base1和Base2的作用域

    return 0;       // 返回0表示程序正常结束
}
```

在构造一个类的对象时，如果存在虚基类，其构造顺序是特殊的。具体指出虚基类的构造顺序如下：

1. 首先，会按照从最顶层的虚基类开始，逐级调用虚基类的构造函数。虚基类的构造函数先于任何其他类的构造函数执行。
2. 在调用虚基类的构造函数时，会先调用虚基类自身的构造函数，然后再按照继承关系调用其直接基类的构造函数。这样可以确保虚基类只被构造一次。
3. 虚基类的构造函数执行完毕后，再按照从最顶层到最底层的顺序，依次调用每个派生类的构造函数。
4. 最后，执行对象所属类的构造函数体内的语句，完成对象的初始化。

#### 深度探索

##### 组合与继承

组合：“有一个”（has-a）

继承：“是一个”（is-a）

##### 派生类对象的内存布局

一个基类指针，无论其指向基类对象，还是派生类对象，通过它来访问一个基类中定义的数据成员都可以使用相同的步骤。

* 单继承
* 多继承
* 虚拟继承

#### 基类向派生类的转换及安全性问题

派生类指针可以隐含转换为基类指针，因为是安全的，而反过来则需要显式的进行。

> Base *pb=new Derived(); //隐式Derived到Base
>
> Derived *pd=static_cast<Derived *>(pd)//显示转换

对于引用也是如此

> Derived d;
>
> Base &rb=d;
>
> Derived &rb=static_cast<Derived &>(rb);

* 基类对象一般无法被显示转换为派生类对象，除非Derived类有接受Base类型的参数的构造函数比如： Base b; Derived d=static_case<Derived>(b)；非法
* 执行基类向派生类的转换时，一定要确保被转换的指针和引用所指向或引用的对象符合转换的目的类型。如：Derived *pd=static_cast<Derived *>(pd);，必须保证pd指向对象有Derived类型，或是Derived的派生类。
* 多重继承时，执行基类指针到派生类的显式转换时，有时需要将指针所存储的地址进行调整后才能得到新的指针的值。
* 如果涉及void指针，即使最初的指针类型和最后的指针类型是兼容的，但只要不完全相同，结果就有可能错误

## 多态

### 概述

类型：

* 重载多态
* 强制多态
* 包含多态
* 参数多态

实现：

编译时的多态和运行时的多态，分别对应动态绑定和静态绑定

### 运算符重载

#### 规则

1. 除少数几个（“.”,".*","::","?:"）外，都可重载，且只可重载C++中已存在的。
2. 优先级和结合性不变。

两种重载形式：

重载类为成员函数：

> 返回类型 类名：：operator 运算符（形参表）
>
> {
>
> 函数体
> }

参数个数比原来操作数少一个。

非成员函数：

> 返回类型 operator 运算符（形参表）
>
> {
> 函数体
>
> }

operator：关键字。 运算符：c++中可重载的运算符。返回类型：指定了返回值的类型。

操作个数与原来相同。

#### 运算符重载为成员函数

oprd++与oprd--，应当将运算符重载为oprd所属类的成员函数，此时后面应该加一（int）形参，来与前置加加区别。//并且注意，这里形参不带名字。

~~~C++
#include <iostream>

using namespace std;

class Complex {
private:
    double real;        // 存储实部
    double imaginary;   // 存储虚部

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imaginary(i) {}

    // 重载加法运算符
    Complex operator+(const Complex& other) const {
        Complex result;
        result.real = real + other.real;                // 实部相加
        result.imaginary = imaginary + other.imaginary; // 虚部相加
        return result;
    }

    // 重载减法运算符
    Complex operator-(const Complex& other) const {
        Complex result;
        result.real = real - other.real;                // 实部相减
        result.imaginary = imaginary - other.imaginary; // 虚部相减
        return result;
    }

    // 打印复数的实部和虚部
    void print() const {
        cout << real << " + " << imaginary << "i" << endl;
    }
};

int main() {
    Complex c1(2.0, 3.0);   // 创建复数1，实部为2.0，虚部为3.0
    Complex c2(1.0, 2.0);   // 创建复数2，实部为1.0，虚部为2.0

    Complex sum = c1 + c2;      // 两个复数相加
    Complex diff = c1 - c2;     // 两个复数相减

    cout << "Sum: ";
    sum.print();               // 打印相加结果

    cout << "Difference: ";
    diff.print();              // 打印相减结果

    return 0;
}
~~~

运算符重载为非成员函数

```C++
#include<iostream>
using namespace std;
class Complex {
	public:
		Complex(double r = 0.0, double i = 0.0 )	: real(r), imag(i) {}
		friend Complex operator+(const Complex &c1, const Complex &c2);
		friend Complex operator -(const Complex &c1, const Complex &c2);
		friend ostream & operator <<(ostream &out, const Complex &c);
	private:
		double real;
		double imag;
};
Complex operator+(const Complex &c1, const Complex &c2) {
	return Complex(c1.real + c2.real, c1.imag + c2.imag);
}
Complex operator-(const Complex &c1, const Complex &c2) {
	return Complex(c1.real - c2.real, c1.imag - c2.imag);
}
ostream & operator<<(ostream &out, const Complex &c) {
cout<<"("<<c.real<<","<<c.imag<<")"<<endl;
return out;
}
int main(){
	Complex c1(5,4), c2(2,10),c3;
	cout<<c1-c2<<endl<<c1+c2;
	return 0;
}
```

三种使用非成员函数的重载情形：

1. 重载操作符的第一个对象不可变，比如上例中的ostream
2. 支持更加灵活的参数类型转换
3. =、[]、()、->只能够被重载为成员函数

### 虚函数

​	虚函数是动态绑定的基础，虚函数必须是非静态的成员函数，经过派生后在类族中实现运行多态的过程

#### 一般虚函数成员

virtual 函数类型 函数名（形参）；

虚函数声明只能出现在类定义中的函数原型声明中，而不能在成员函数实现的时候。

运行中多态需满足三个条件：

* 赋值兼容规则 

* 声明虚函数
* 由成员函数来调用或者是通过指针、引用来访问虚函数

一般不将虚函数声明为内联函数，因为要保证是动态绑定。

如果不给出显式的虚函数声明，系统就会遵循以下规则来判断：

* 是否与基类的虚函数有相同的名称
* 是否有相同的参数个数及相同的对应参数类型
* 是否有相同的返回值或者满足赋值兼容规则的指针、引用型的返回值

如果均满足，则会自动判定为虚函数，派生类中的虚函数会隐藏基类中同名函数的所有其他重载形式。

基类构造函数调用虚函数时，不会调用派生类的虚函数。

**虚函数好求难**

![image-20230727192832993](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230727192832993.png)

final和override

![image-20230728194823468](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230728194823468.png)

#### 虚析构函数

语法： virtual ~类名

#### 纯虚函数与抽象类

抽象类是特殊的类，为一个类族提供统一操作界面。

##### 纯虚函数

声明格式：

virtual 函数类型 函数名（参数表）=0；

声明为纯虚函数后，基类中就可以不再给出函数的实现部分。

纯虚函数的函数体由派生类给出。

##### 抽象类

带有纯虚函数的类是一个抽象类，作用为为一个类族建立统一的公共接口，使得更好的实现多态性。

抽象类不可以实例化，但可以定义一个抽象类的指针和引用，以此访问派生类对象，进而访问成员。

#### 深度探索

##### 多态类型与非多态类型

多态类型：有虚函数的类类型

非多态类型：其他所有

对于多态类型，基类指针指向派生类的对象并以之调用虚函数时，实际执行的操作由派生类决定。

**设计多态类型的一个重要原则是把多态类型的析构函数都设定为虚函数**

对非多态类的公有继承应当慎重，且一般无太大必要。

##### 运行时类型识别

1. 用dynamic_cast执行基类转向派生类

   可以将基类指针或引用显示转换为派生类指针或引用.

   但会进行检查,如果与所指对象的实际类型与目的类型不兼容,则:

   如果执行的是指针类型转换,会得到空指针

   如果是引用类型的转换,会报错.

   另外,转换之前必须是多态类型的指针或引用.


```c++
#include<iostream>
using namespace std;

class Base{
    public:
    virtual void fun1(){cout<<"Base::fun1()"<<endl;}
    virtual ~Base(){}
};
class Derived1: public Base{
    public:
    virtual void fun1(){cout<<"Derived1::fun1()"<<endl;}
    virtual void fun2(){cout<<"Derived2::fun2()"<<endl;}
    
};
class Derived2: public Derived1{
    public:
    virtual void fun1(){cout<<"Derived2::fun1()"<<endl;}
    virtual void fun2(){cout<<"Derived2::fun2()"<<endl;}

};
void fun(Base *b){
    b->fun1();
    Derived1 *d=dynamic_cast<Derived1 *>(b);//尝试将b转换为Derived
    if(d!=0) d->fun2();//判断转换是否成功
}
int main(){
    Base b;
    fun( &b);
    Derived1 d1;
    fun( &d1);
    Derived2 d2;
    fun(&d2);
    return 0;
}
```

由于 funl 函数是基类 Base 中定义的函数,通过 Base 类的指针 b 可以直接调用 funl()函数。fun2 函数是派生类 Derived1 中引人的新函数，只能对 Derived1 和 Derived2 类的对象调用,因此在 fun 函数中,需要用 dynamic cast将 Base 指针 b 转换为 Derived 指针 d,并根据转换结果是否为空指针来判断转换是否成功,只有转换成功了,才调用 fun2 函数。d1是 Derived1 类型的对象.对指向 d1 的指针执行转换,自然能够成功得到 Derived1 类型的指针;d2 是 Derived2 类型的对象,由于 Derived2 是 Derived1 的派生类,对指向 d2 的指针执行转换，也能够成功得到 Derived1 类型的指针。

2. typeid获取运行时类型信息

typeid可以获得一个类型的相关信息,两种语法形式:

typeid(表达式)

typeid(类型说明符)

可以作用于表达式或者类型说明符

如果表达式有多态类型,那么会对其进行求值,得到的是用于描述表达式求值结果的运行时类型的type_info对象的常引用.

##### 虚函数动态绑定的实现原理

动态绑定的关键是在运行时决定被调用的函数.

好难,先跳过把

# 模板与群体数据

群体可分为线性群体和非线性群体

* 线性群体中的元素按照位置排列有序
* 非线性群体不用位置顺序还标识元素

## 函数模板与类模板

模板时C++参数化程序设计的工具,通过它可以实现参数化多态性.即将程序所处理的对象的类型参数化,使得一段程序可以用于处理多种不同类型的对象.

### 函数模板

定义形式:

> template<模板参数表>
>
> 类型名 函数名 (参数表)
>
> {
>
> 函数体定义}

所有模板函数都用template定义开始.

模板参数表:包括class/typename标识符,类型说明符 标识符,template<参数表>class 标识符

如求绝对值的模板函数:

```C++
#include<iostream>
using namespace std;
template<typename T>
T abs(T x)
{
    return x<0?-x :x;
}
int main(){
    int n=-5;
    double d=-5.5;
    cout<<abs(n)<<endl;
    cout<<abs(d)<<endl;
    return 0;
}
```

上例中编译器从实参类型推导出模板函数的类型参数.

当类型参数的含义确定后编译器将以函数模板为样板生成一个函数,这一过程称为实例化.

函数模板与函数区别:

* 函数模板编译时不产生目标代码,只有模板生成的实例会生成目标代码
* 被多个源文件引用的函数模板,应当**连同函数体**一同放在头文件中,而不能只将**声明**放在头文件中
* 函数指针也只能指向模板的实例而无法指向模板本身

### 类模板

类模板使用户可以为类定义一种模式,使得类中的某些数据成员/成员函数的参数,返回值或局部变量取到不同类型(包括系统预定义的和用户自定义的)

声明形式:

> template<模板参数表>
>
> class 类名
>
> {
>
> 类成员声明
>
> }

其中类成员声明方式与普通类几乎相同,但各个成员(数据成员和函数成员)中通常要用到模板的类型参数T.

在类模板外定义成员函数:

> template<模板参数名>
>
> 类型名 类名<模板参数标识符列表>::函数名(参数名)

使用模板来建立对象时,要按照如下形式:

模板名<模板参数表> 对象名...

## 线性群体

### 概念

元素次序与位置关系对应

* 可直接访问:可以直接访问任何一个元素而不用访问之前的元素,如**数组下标**访问
* 顺序访问:只能按照排列顺序依次访问

以及特殊的:栈和队列

栈:"后进先出",只能从一端进行访问,可访问的为栈顶,另外一端为栈底.

队列:"先进先出"从一端加入元素,另一端删除元素.可添加处为队尾,另一端为队头.

### 直接访问群体--数组类

1. 深复制和潜复制
2. 与众不同的运算符

​	运算符返回值是对象的引用."[]"运算的结果被放在左边,是左值.如果返回值是对象的值,则不应该作为左值,对+-,直接返回变量或对象的值是应该的,因为对其结果赋值没有意义.而[]不同,故需要将其返回值指定为引用,通过引用改变对象的值.

3. 指针转换运算符作用

### 链表类

链表是一种动态数据结构,可以用来表示顺序访问的线性群体.

**单链表**:链表的每个结点中只有一个指向后继结点的指针.

**双向链表**:如果每个结点中有两个用于连接其他结点的指针,一个指向前趋结点,一个指向后继结点,则构成双向链表.

1. 结点类

​	数据成员包括数据域和指针域.数据域存放群体中元素的内容,既可以是若干个基本类型的数据,也可以是自定义类型的数据,甚至是内嵌对象.

2. 链表类

   1. 数据成员

   链表数据成员中需要保存**表头指针,表尾指针,元素个数,当前的遍历位置**等信息.

   2. 成员函数

   包括**生成新结点,插入结点,删除结点,访问/修改结点数据,遍历链表**等.此外,还应该重载"=".

   

3. 栈类

基本状态:栈空,栈满,一般状态.

基本操作:初始化,入栈,出栈,栈清空,访问栈顶元素,检测栈的状态(满/空)

4. 队列类

基本状态:一般状态,队空,队满

数据成员:队列元素,队头指针和队尾指针

基本操作:初始化,入队,出队,清空u低劣,访问队首元素,检测队列状态.

## 群体数据结构的组织

插入排序/选择排序/交换排序

顺序查找/二分查找

## 深度探索

### 模板的实例化机制

好难,不想看了

# 标准库!

## 泛型程序设计及STL的结构

### 泛型程序设计基本概念

指编写不依赖于具体数据类型的程序，而模板是其主要工具。

**概念（concept）**的内涵是这些功能，外延式具备这些功能的所有数据类型。

**模型（model）**是具备一个概念所需要的功能的数据类型

此外，概念之间有包含关系。如果A所需求的**所有功能**也是B所需求的功能，那么就说B是A的子概念。

### STL库

STL定义了一套概念体系，为泛型程序设计提供了逻辑基础。

```C++
#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<functional>
using namespace std;
int main(){
    const int N=5;
    vector<int>s(N);
    for(auto& si:s)
        cin>>si;
    transform(s.begin(),s.end(),ostream_iterator<int>(cout," "),negate<int>()/*negate是一个类模板，重载了（），接受一个参数*/);
    cout<<endl;
    return 0;
}
```

STL的四个基本组件：**容器、迭代器、函数对象、算法**

**容器**是容纳，包含一组元素的对象，库中有13种基本容器。分为顺序容器和关联容器。使用不同容器需要包含不同头文件。

**迭代器（iterator）**提供了顺序访问每个元素的方法。可以用++来获得指向下一个元素的迭代器，用*访问迭代器指向的元素，结构体或类还可->访问元素成员。（指针是特殊迭代器，迭代器是泛化的指针）

**函数对象**是一个行为类似函数的对象，可以像函数一样调用。普通函数和重载了（）的都可以。使用STL函数对象要包含头文件<functional>

**算法**使用STL的算法需要包含头文件<algorithm>

![image-20230804100145472](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230804100145472.png)

### 迭代器

1.输入流迭代器

实例：cin

用于从一个输入流中连续输入某中类型的数据，如：

>  template<class T>istream_iterator<T>;

T应该满足有默认构造函数和可以用>>从输入流输入两个条件。

2.输出流迭代器

实例：cout

用于从一个输出流中连续输出某种类型的数据，如：

> template<class T>ostream_iterator<T>;

T表示输出流中输出数据的类型，要求可以用<<向输出流输出，一般可用下面的构造函数来构造：

> ostream_iterator(ostream& out);
>
> ostream_iterator(ostream& out,const char* delimiter);

其中，delimiter可选，表示输出数据之间的分隔符。对于迭代器iter，*iter只能做赋值运算符的左值。

```C++
#include<iterator>
#include<iostream>
#include<algorithm>
using namespace std;
double square(double x){
    return x*x;
}
int main(){
    transform(istream_iterator<double>(cin),istream_iterator<double>(),ostream_iterator<double>(cout,"\t"),square);
    cout<<endl;
    return 0;
}
```

在迭代器帮助下输入输出流可以直接参与STL算法，这是引入这两种迭代器的意义。

**适配器（adapter）**是指用于为已有对象提供新的接口的对象，适配器本身一般不提供心得功能，只为了改变对象的接口而存在。

#### 迭代器的分类

一句迭代器的功能分为五类：

![image-20230804104129357](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230804104129357.png)

1. 输入迭代器

   用来从序列中读取数据，但是不一定能够向其中写入。支持对序列不可重复的单向遍历。

   此外：

   p1==p1，判断是否相同

   p1!=p2，判断是否不同

   *p1 获取输入迭代器所指向元素的指，该表达式返回值可以转换到T类型

   p->m 等价于（*P1).m

   *p++ 值为{T t=*p1;++p1;return t;}

   注意：==成立不保证++p1==++p2

2. 输出迭代器

   允许写入数据，但不保证可读取。也支持单向遍历

   *p1=t 向迭代器所指向的位置写入一个元素，返回类型不确定

   *p1++=t 等价于{ *p1=t；++p1;}，返回类型不确定

   另外，写入元素的操作和++操作必须交替机型，否则会导致不确定行为.

3. 前向迭代器

​	支持数据读取和写入，支持对序列进行可重复单向遍历。

​	如果p1==p2，那么++p1==++p2一定成立。此外不需要++和写入交替进行的限制。

​	\*p1 对前向迭代器使用*运算符的结果保证具有T&类型

​	p1++对前向迭代器实例可以使用前置++使之指向下一个元素。

4. 双向迭代器

   是单向迭代器的子概念，在单向基础上支持迭代器向反向移动。

   --p1指向上一个元素，返回值为自身的引用

   p1--可以使用前置--使得指向上一个元素

5. 随机访问迭代器

​	在双向迭代器的基础上，它可以直接向前或向后移动n个元素，几乎和指针一样。

​	p1+=n迭代器迁移n个元素

​	p1-=n后移n个元素

​	p1+n/n+p1获得指向p1前第n个元素的迭代器

​	p1-n获得指向p1后第n个元素的迭代器

​	p1-p2返回一个满足p1==p2+n的n

​	p1 op p2 （op是<,<=等，用于比较指向的前后关系）

​	pl[n]	等价于*（pl+n）

#### 迭代器区间

当且仅当执行n次++运算后p1==p2，[p1,p2)才是一个合法区间

```C++
#include<algorithm>
#include<iterator>
#include<vector>
#include<iostream>
using namespace std;
template<class T,class InputIt, class OutputIt>
void mysort(InputIt first, InputIt last, OutputIt result)
{
    vector<T>s;
    for (;first!=last;++first)
    {
        s.push_back(*first);
        sort(s.begin(),s.end());
        copy(s.begin(),s.end(),result);
    }
}
int main(){
    double a[5]={1.2,2.4,0.8,3.3,3.2};
    mysort<double>(a,a+5,ostream_iterator<double>(cout," "));
    cout<<endl;
    cout<<endl;
    mysort<int>(istream_iterator<int>(cin),istream_iterator<int>(),ostream_iterator<int>(cout," "));
    cout<<endl;
    return 0;
    }
```

在设计算法时要尽量用内涵尽可能小，外延尽可能大的迭代器概念以互活得最广的适用范围。

#### 迭代器辅助函数

模板——advance和distance

为所有迭代器提供了前进或后退多个元素以及计算两个迭代器距离的能力。

advance:

template <class InputIt, class Distance>

void advance(InputIt& iter, Distance n);

执行advance(iter,n)就相当于执行iter+=n，可取负值。

distance：

template<class IputIt>

unsigned distance(InputIt first,InputIt last);

用来计算first多少次之后可以到达last，调用前必须有last>=first成立。

### 容器基本功能与分类

设S为一种类型，s1，s2为实例，则容器基本功能：

> S s1 构造一个没有任何元素的空容器
>
> s1 op s2 op可以是==，！=等，会对两个容器之间的元素按照字典序比较
>
> s1.begin（）返回指向s1第一个元素的迭代器
>
> s2.end()返回指向s2最后一个元素的**下一个位置**的迭代器
>
> s1.clear() 清空容器
>
> s1.empty()返回一个bool判断是否为空
>
> s1.size()返回元素个数
>
> s1.swap(s2)交换s1和s2的内容

![image-20230804162142101](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230804162142101.png)

### 顺序容器

#### 基本功能

顺序容器包括:**向量,双端队列,列表,单向链表.数组**,除数组固定大小外,别的都不变

1. 构造函数

   > S s(n,t) 构造一个有n个t元素构成的容器实例s
   >
   > S s(n); 构造一个有n个元素的容器实例s,每个元素都是T()
   >
   > S s(q1,q2);使用将[q1,q2)区间内的数据作为s的元素构造s.

2. 赋值函数

   > s.assign(n,t);赋值后的容器由n个t构成
   >
   > s.assign(n);每个元素都是T()
   >
   > s.assign(q1,q2)容器的元素为[q1,q2)的数据

3. 插入元素

   > s.insert(p1,t)在s容器中p1后插入一个元素t,返回迭代器指向新插入元素
   >
   > s.insert(p1,n,t)p1后插入n个新元素t,无返回值
   >
   > s.insert(p1,q1,q2)将[q1,q2)内的元素顺序插入p1后
   >
   > s.emplace(p1,args)将args传递给T的构造函数构造新元素t,在s中p1处插入新元素,返回一个指向新元素的迭代器

4. 元素删除

   > s1.erase(p1);删除p1指向的元素,返回被删除的下一个元素的迭代器
   >
   > s.erase(p1,p2),删除[p1,p2)内的元素返回p2所指向元素的迭代器

5. 改变容器大小

   > s1.resize(n) 将大小改为n,原有元素大于n则删除多余的,小于则补充T()

6. 首尾元素直接访问

   > s.front()
   >
   > s.back()

7. 在尾部插入/删除元素

   > s.push_back(t)
   >
   > s.emplace_back(args);将args传递给T的构造函数构造新元素t,向容器尾部插入之.
   >
   > s.pop_back()

8. 在容器头部插入/删除元素

   > s.push_front(t)
   >
   > s.emplace_front(t)
   >
   > s.pop_front()

9. 容器的列表初始化

   > list<int>numberSeq={1,4,5,7,}
   >
   > vector<string>strs={"hello"," world"}

例子:

```C++
#include<iostream>
#include<list>
#include<iterator>//教材漏了一个头文件
#include<deque>
using namespace std;
template<class T>//输出指定的整型顺序容器元素.
void printContainer(const char* msg, const T& s)
{
    cout<<msg<<":";
    copy(s.begin(),s.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
}
int main(){
    deque<int>s;
    for (int i=0;i<10;i++)
    {
        int x;
        cin>>x;
        s.push_front(x);//读入10个元素,从头上加入
    }
    printContainer("deque at first",s);
    list<int>l(s.rbegin(),s.rend());//用s容器的逆序来构造列表容器
    printContainer("list at first",l);
    //将l的每相邻两个容器顺序颠倒
    list<int>::iterator iter=l.begin();
    while(iter!=l.end()){
        int v=*iter;//取元素
        iter=l.erase(iter);//删除元素得到指向下一位置的迭代器
        l.insert(++iter,v);//得到指向下一个元素的迭代器
        printContainer("list at last",l);//将刚删除的元素插入下一位置
        //用l的内容给s赋值,然后输出
        s.assign(l.begin(),l.end());
        printContainer("deque at last ",s);
        return 0;
    }
}
/*0 9 8 6 4 3 2 1 5 4 
deque at first:4 5 1 2 3 4 6 8 9 0
list at first:0 9 8 6 4 3 2 1 5 4
list at last:9 0 8 6 4 3 2 1 5 4
deque at last :9 0 8 6 4 3 2 1 5 4 */
```

#### 5种顺序容器的特性

1. 向量(vector)

   支持高效随机访问和高效向尾部加入新元素的容器

   区分容量和大小,s.capacity()返回容量,

   s.reserve(n)若当前容量大于等于n,什么也不做,否则扩容使容量大于等于n

   当容器扩展时,之前的指针与迭代器会失效

2. 双端队列

   支持向两端高效插入数据,支持随机访问.

   随机访问效率低于向量容器.

   执行两端删除时效率高

   如果插入到内部,则效率较低,越靠近中间效率越低,且会让迭代器,指针,引用失效.

```C++
#include<vector>
#include<deque>
#include<algorithm>
#include<iterator>
#include<iostream>
using namespace std;
int main(){
    istream_iterator<int>i1(cin),i2;
    vector<int>s1(i1,i2);
    sort(s1.begin(),s1.end());
    deque<int>s2;
    for(vector<int>::iterator iter=s1.begin();iter!=s1.end();++iter)
    {
        if(*iter%2==0)
        s2.push_back(* iter);
        else
        s2.push_front(* iter);
    }
    copy(s2.begin(),s2.end(),ostream_iterator<int>(cout," "));
    return 0;
}
```



3. 列表

   不能随机访问,但可以高效插入和删除元素.并且插入元素不会使原有的指针迭代器引用失效

   列表还有一特殊操作,接合(splice),就是将一个列表容器的一部分连续元素从列表中删除后插入到另一个列表容器中.效率很高

   > s1.splice(p,p2) 将s2列表所有元素插入s1列表中p-1和p之间,清空s2.
   >
   > s1.splice(p,s2,q1)将s2列表中q1所指向的元素插入到s1中p-1和p之间.,将q1所指向的元素从s2列表删除
   >
   > s1.splice(p,s2,q1,q2)将s2列表中[q1,q2)区间内的所有元素插入到s1列表中p-1和p之间,将[q1,q2)区间内的元素从s2列表中删除.

   ```c++
   #include<list>
   #include<iterator>
   #include<string>
   #include<iostream>
   using namespace std;
   int main(){
       string names1[]={"alice","helen","lucy","susan"};
       string names2[]={"bob","david","levin","mike"};
       list<string>s1(names1,names1+4);
       list<string>s2(names2,names2+4);
       s2.splice(s2.end(),s1,s1.begin());
       list<string>::iterator iter1=s1.begin();
       advance(iter1,2);
       list<string>::iterator iter2=s2.begin();
       ++iter2;
       list<string>::iterator iter3=iter2;
       advance(iter3,2);
       s1.splice(iter1,s2,iter2,iter3);
       copy(s1.begin(),s1.end(),ostream_iterator<string>(cout," "));
       cout<<endl;
       copy(s2.begin(),s2.end(),ostream_iterator<string>(cout," "));
       cout<<endl;
       return 0;
       }
   ```

   

4. 单向链表和数组

​	forward_list和array.

​	forward_list不支持size操作

​	array是对内置数组的封装,更安全,更方便.

> array<int,10>arr;//arr为保存了10个int类型的数组

array类型可以进行复制或对象赋值操作.

5. 顺序容器比较



![image-20230805134454032](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230805134454032.png)

![image-20230805134519235](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230805134519235.png)

#### 顺序容器的插入迭代器

插入迭代器是一种配十七,可以向指定元素的指定位置插入元素.有三种:

> template<class Container>class front_insert_iterator;
>
> template<class Container>class back_insert_iterator;
>
> template<class Container>class insert_iterator;

可以用辅助函数构造:

> template<class Container> 
>
> **front_insert_iterator**<Container>front_inserter(Container& s);

#### 适配器

通过对顺序容器的封装实现栈/队列.

> template<class T,class Container=deque<T>>class stack;
>
> template<class T,class Container=deque<T>class queue;

### 关联容器

#### 分类及基本功能

关联容器访问到的序列总是升序的,s.begin()总是指向最小元素,s.end()-1总是指向最大元素.

最大优势是可以根据键来查找容器中的一个元素

关联容器的键之间必须能够用"<"来比较大小.如果键的类型是类类型,则需要重载运算符

注意:<必须满足以下性质:

1. 自反性,x<x必须返回false
2. 传递性,x<y和y<z均为true,则x<z返回true
3. ==传递性,如果x==y定义为!(x<y)&&!(y<x),则如果x==y和y==z都true,那么x==z必须true

#### 集合

集合有序,但无重复元素,可以排序

#### 映射 map

和集合一样是单重关联容器,区别在于,集合元素是键本身,而映射的元素是由键和附加数据构成的二元组.映射很像(字典)

#### 多重结合和映射

多重集合允许重复元素,多重映射允许一个键对应多个附加数据.

可通过equal_range成员函数获取一个键对应的所有值

#### 无序容器

对应四个容器,加入前缀unordered_

通过哈希函数和键类型的==运算符来组织元素

### 函数对象

#### 概念

一个行为类似函数的对象,可以有或无参数,功能是获得一个值活着改变操作的状态.任何普通函数/函数指针/lambda表达式/重载了调用运算符operator的类的对象都满足函数对象的特征.

分为五大类:

![image-20230806165430318](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230806165430318.png)

一般地,具有0/1/2个传入参数的函数对象,称为产生器/一元函数/二元函数

![image-20230806170139365](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230806170139365.png)

#### lambda

形式:

[捕获列表](参数列表)->返回类型{函数体}

如:

> auto lmda=[]{return "hello"};
>
> cout<<lmda()<<endl;

#### 对象参数绑定

将一种函数对象转换为另一种符合要求的函数对象

没看懂

### 算法

算法本身是一种函数模板

算法不直接用容器做参数,而是使用迭代器类型.

STL中几乎所有算法头文件都是`<algorithm>`

#### 算法基础

四个大类:不可变序列算法/可变序列算法/排序和搜索算法/数值算法.

#### 不可变序列算法

不直接修改所操作容器内容的算法.

包括:查找元素,检查相等,计数元素

![image-20230807085745589](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230807085745589.png)

```C++
#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
using namespace std;
int main(){
    int iarray[]={0,1,2,3,4,5,6,6,6,7,8};
    vector<int>ivector(iarray,iarray+sizeof(iarray)/sizeof(int));
    int iarray1[]={6,6};
    vector<int>ivector1(iarray1,iarray1+sizeof(iarray1)/sizeof(int));
    int iarray2[]={5,6};
    vector<int>ivector2(iarray2,iarray2+sizeof(iarray2)/sizeof(int));
    int iarray3[]={0,1,2,3,4,5,7,7,7,9,7};
    vector<int>ivector3(iarray3,iarray3+sizeof(iarray3)/sizeof(int));
 //找出ivector之中相邻元素相等的第一个元素:
    cout<<*adjacent_find(ivector.begin(),ivector.end())<<endl;
    //找出小于7的元素个数
    cout<<count_if(ivector.begin(),ivector.end(),bind2nd(less<int>(),7))<<endl;
 //找出大于2的第一个元素所在位置  
    cout<<*find_if(ivector.begin(),ivector.end(),bind2nd(greater<int>(),2))<<endl;
    //子序列ivector2再ivector中出现的起点元素位置
    cout<<*search(ivector.begin(),ivector.end(),ivector2.begin(),ivector2.end())<<endl;
    //查找连续出现3个6的起点位置
    cout<<*search_n(ivector.begin(),ivector.end(),3,6,equal_to<int>())<<endl;
    //判断ivector和ivector3是否相等
    cout<<equal(ivector.begin(),ivector.end(),ivector3.begin())<<endl;
    //查找ivector3在ivector中不匹配点的位置.
    auto result=mismatch(ivector.begin(),ivector.end(),ivector3.begin());
    cout<<result.first-ivector.begin()<<endl;
    return 0;
}   
```

#### 可变序列算法

可以修改他们所操作容器的元素

包括:复制,生成,删除.替换,倒序,旋转,交换,变换,分割,去重,填充,洗牌(shuffle).

![image-20230807092759327](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230807092759327.png)

![image-20230807092813694](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230807092813694.png)

可变序列算法通常对操作区间有要求,因为有可能会发生对不可用位置元素的修改.

#### 排序和搜索算法

包括对序列进行排序,合并的算法,搜索算法,有序序列的集合操作,堆操作相关算法.

#### 数值算法

需要包含头文件`<numeric>`

![image-20230807093934367](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20230807093934367.png)
