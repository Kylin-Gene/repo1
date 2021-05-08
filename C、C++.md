# C、C++

## 关键字

### C语言宏中的“#”和“##”

#### **1、(#)字符串操作**

作用：

```c
#define example1(instr) printf("the input string is : %s\n",#instr);
#define example2(instr) #instr
//可以用 #*  来代替一个字符串

int main()
{
	example1(nihao);
	cout << example2(mingtianjian);
	return 0;
}
```

```c
the input string is : nihao
mingtianjian
```



**2、(##)符号连接操作符**





**3、实现sizeof**

```C
#define sizeof_v(x)  ((char*)(&x-1) - (char*)(&x))
```



## const

#### 修饰变量

作用：定义（全局、局部）变量为常量，且在定义的时候初始化



#### 修饰指针

**1、常指针 **: *const pointer to #type*

​	1）不能修改指针所指向的变量。

​	2）要在定义的时候初始化。

​	3）形式有两种

```C
char* const p
char const* p
//const都是修饰后面的p，即指针
```

```C
char* const p = &a;	//不能修改p的值
//p = &b;  			//错误
//int* const p;		//错误：未初始化
```

**2、指向常量的指针**

​	1）不能通过该指针修改所指向变量的值

```C
const int* p;
p =&a;
//*p = 20;			//错误

const A *p
```

**3、指向常量的常指针**

​	1)不能通过指针修改

​	2）不能修改指针的值

```C
const char* const p = &str;
```



#### **常引用-修饰引用**

作用：不能用常引用修改所引用变量的值

```c
const int& p = a;
//p = 10;			//错误:不能修改值
```



#### 修饰类对象

```C
const A tmp；				//常对象，只能调用常成员函数
A a;			
const A* p = &a;	//指向常量的指针，只能调用常成员函数，不能修改数据成员，可以指向其他A
const A &p = a;		//常引用，不能修改数据成员，只能调用常成员函数
A* const p = &a; 	//常指针
```



#### **常对象成员**

作用：即该成员变量的值在初始化之后就不能修改。初始化的方式 **<u>在定义的时候初始化</u>**  <u>**在初始化列表中初始化**</u>

```C
class A
{
    const int a;
    const int b = 10;	//在定义的时候初始化
public:
    A(int x):a(x){};	//利用初始化列表初始化
}
```



#### **常成员函数**

1、定义常成员函数的时候，在函数后加const

2、常成员函数只能访问，不得修改类中的任何数据成员

```C
class A
{
    int a =10;
public:
    int getValue() const;
}
```



#### 修饰形参

```C
void function1(const int val);	//val在函数中不能变
void function2(const char* val);//修饰char，所指的内容为常量
void function3(char* const val);//修饰指针，参数指针为常指针
void function4(const int& val);	//引用参数在函数内为常量
```



#### **修饰函数的返回值**

```C
const int function5();	//返回一个常数
const int* function6();	//返回一个指向常量的指针，使用：const int *p = function6();
int const function7();	//返回一个常指针，使用:int* const p = function7();
```



#### 去常量指针





 **a[i]==i[a]==\*(i+a)==\*(a+i)**

这个汇编是怎样的形式？



### 指针与引用

#### 相同点

1. 都是地址的概念，指针指向某一内存、它的内容是所指内存的地址；引用则是某块内存的别名。
2. 从内存分配上看，两者都占内存，程序为指针会分配内存，一般是4个字节；而引用的本质是指针常量，指向对象不能变，但指向对象的值可以变。两者都是地址概念，所以本身都会占用内存。

#### 区别

1. 指针是实体，而引用是别名。
2. 指针和引用的自增（++）运算符意义不同，指针是对内存地址自增，而引用是对值的自增。
3. 引用使用时无需解引用(*)，指针需要解引用；（关于解引用大家可以看看这篇博客，传送门）。
4. 引用只能在定义时被初始化一次，之后不可变；指针可变。
5. 引用不能为空，指针可以为空。
6. “sizeof 引用”得到的是所指向的变量(对象)的大小，而“sizeof 指针”得到的是指针本身的大小，在32位系统指针变量一般占用4字节内存。

#### 转换

- **引用转指针**：对引用取地址，所得的地址为引用所指向的地址

  ```c
  int a = 20;
  int& b = a;
  int* p1 = &b;
  int* p2 = &a;
  cout << p1 << endl << p2;
  ```

  ```C
  009AFEA0
  009AFEA0
  ```

- **指针转引用**：把指针用*就可以转换成对象，可以用在引用参数当中。



### 指针是什么？

1. 野指针是指向不可用内存的指针，当指针被创建时，指针不可能自动指向NULL，这时，默认值是随机的，此时的指针成为野指针。

2. 当指针被free或delete释放掉时，如果没有把指针设置为NULL，则会产生野指针，因为释放掉的仅仅是指针指向的内存，并没有把指针本身释放掉。

3. 第三个造成野指针的原因是指针操作超越了变量的作用范围。



### 智能指针

- 通过一个类，将原本的类包裹起来，用外层类的构造和析构函数帮助它自动释放对象，然后再通过运算符重载等操作，使得整个包裹的类像一个指针（例如`->`,`*`,`bool`）
- 注意，直接赋值的话，其实是个浅拷贝，所以当其中一个析构之后，另外一个就会错误。为了避免这个问题，换成深拷贝

**1、unique_ptr**

- [Unique_ptr](https://docs.microsoft.com/zh-cn/cpp/standard-library/unique-ptr-class?view=msvc-160)不共享其指针。 不能将其复制到另一个，而是 `unique_ptr` 通过值传递给函数，也不能在需要进行复制的任何 c + + 标准库算法中使用。 只能移动 `unique_ptr`。 这意味着，内存资源所有权将转移到另一 `unique_ptr`，并且原始 `unique_ptr` 不再拥有此资源。![ç§»å¨å¯ä¸_ptr çæææ](https://docs.microsoft.com/zh-cn/cpp/cpp/media/unique_ptr.png?view=msvc-160)

**2、shared_ptr**

- `shared_ptr` 类型是 C++ 标准库中的一个智能指针，是为多个所有者可能必须管理对象在内存中的生命周期的方案设计的。 在您初始化一个 `shared_ptr` 之后，您可复制它，按值将其传入函数参数，然后将其分配给其他 `shared_ptr` 实例。 所有实例均指向同一个对象，并共享对一个“控制块”（每当新的 `shared_ptr` 添加、超出范围或重置时增加和减少引用计数）的访问权限。 当引用计数达到零时，控制块将删除内存资源和自身。![å±äº«æéå³ç³»å¾](https://docs.microsoft.com/zh-cn/cpp/cpp/media/shared_ptr.png?view=msvc-160)

**3、weak_ptr**

- weak_ptr允许你共享但不拥有某对象，一旦最末一个拥有该对象的智能指针失去了所有权，任何weak_ptr都会自动成空（empty）

### 五种内存分配区域

#### 栈区

```
存放函数参数、局部变量等
```

#### 堆区

```
一般有程序员分配和释放，若没有释放，则就在程序结束的时候由操作系统回收。
```

#### 全局/静态区

```
全局变量和静态变量的存储是放在一块的，初始化的全局变量和初始化的静态变量在一块区域，未初始化的全局变量和未初始化的静态变量在相邻的另一块区域，程序结束后由操作系统回收。
```



#### 文字常量区

```
存放常量值，如常量字符串等，不允许修改，程序结束后由操作系统回收。
```



#### 程序代码区

```
存放函数体的二进制代码。
```



### 堆的申请

1. malloc

   ```C
   char *Ptr = NULL; 
   Ptr = (char *)malloc(100 * sizeof(char)); 
   //Ptr[i]....
   free(Ptr);
   Ptr = NULL;
   ```

   注：malloc函数分配完内存后需注意：

   a. 检查是否分配成功（若分配成功，返回内存的首地址；分配不成功，返回NULL。可以通过if语句来判断）

   b. 清空内存中的数据（malloc分配的空间里可能存在垃圾值，用memset或bzero 函数清空内存）

   ```C
   //s是 需要置零的空间的起始地址； n是 要置零的数据字节个数。
   void bzero（void *s, int n）;
   // 如果要清空空间的首地址为p，value为值，size为字节数。
   void memset(void *start, int value, int size);
   ```

   

2. new

   ```C
   int *p = new int[5];
   delete[] p;
   p = NULL;
   ```

   



### 字节对齐

- 对齐跟数据在内存中的位置有关。如果一个变量的内存地址正好位于它长度的整数倍，他就被称做自然对齐。譬如`short int`的字节长度为2，则存放在的内存地址应该为2的整数倍。
- struct和union都要考虑字节对齐，class也是

```C
class AAA
{
	long num;  //4
	char* name;	//4     x64的时候为8
	short int data;	//2
	char ha;	//1
	short ba[5]; //10
};
```

1、X86`sizeof(AAA)=24`，4+4+2+1+`1(补齐)`+10+`2(补齐)`

2、x64`sizeof(AAA)=32`，4+`4(补齐)`+8+2+1+`1(补齐)`+10+`2(补齐)`