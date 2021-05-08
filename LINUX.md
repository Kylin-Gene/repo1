### Linux中断

1. 现在的Linux中断不能嵌套，在处理中断A时，中断B不能打断，即使中断优先级更高

   ```
   ？？？以前的软件中断分为FIQ、IRQ 所以能够中断嵌套？
   ```

   

2. 为了解决上面那个问题，可以将中断拆分为：上半部、下半部![image-20210506114615239](C:\Users\13535\AppData\Roaming\Typora\typora-user-images\image-20210506114615239.png)

3. 中断下半部的实现方法有很多种，主要有：tasklet(小任务)、work queue(工作队列)

4. 软件中断能被打断吗？





## 驱动问题

### 如何编写驱动、驱动调用的具体过程，编程中使用的具体结构体内容，举例如何编写一个驱动

1. 如何编写

2. 调用的具体过程

3. 编程中使用的具体结构体内容

   ```tex
   struct file_operations 
   struct class
   
   ```

   

4. 举例如何写一个驱动

   ```tex
   以一个LED驱动为例，先定义一个file_operations结构体，接着编写init函数，在init函数中完成对管脚的映射，register_chrdev字符设备的注册，class_create类的注册，class_device_create在类下面注册一个设备。exit函数中完成字符设备的卸载，类的卸载，内存空间的释放。在open函数中完成硬件管脚的初始化，在write函数中完成点灯操作。
   ```

   ```tex
   	举一个LED驱动的例子，先定义一个file_operations结构体，然后在入口函数里对该结构体进行字符设备的注册，当然，要先实现file_operations里面一些用到的函数，例如open函数中完成硬件的一些初始化，然后用class_create为该设备创建一个类注册到内核中，接着就能用device_create在/dev目录下创建相应的设备节点。最后在exit函数中完成字符设备的卸载，类的卸载，内存空间的释放。
   	至于对硬件的初始化，我不喜欢和驱动程序写在一个文件里，我会将驱动程序分为上下两层，上层就是硬件无关的一些操作，下层就是硬件相关的，我们可以在上层抽象出一个结构体，里面成员是函数指针的，然后由下层提供初始化和输入输出等一些硬件的操作给这个结构体，这样的话就能将硬件的操作分离开来，以后想要移植到换别的硬件的时候，就只要修改下层的代码就可以了。
   ```

   



### 为什么存在总线？总线如何配对？如何利用总线编写驱动程序？

1. **为什么存在总线？**
   引入platform_device/platform_driver,可以将“资源”与“驱动”分离开来。虽然代码稍微复杂了一点，但是易于扩展。冗余代码太多，修改引脚时设备端的代码需要重新编译。
2. **匹配规则：**
   1）先比较：platform_device.device_override和platform_driver.name *Driver name to force a match*,强制用name选择某个platform_driver
   2）然后比较：platform_device.name和platform_driver.id_table[i].name。
   id_table是“platform_device_id”指针，表示该drv支持若干个device，它里面
   列出了各个 device 的{.name, .driver_data}，其中的“name”表示该 drv 支持的设备的名字，driver_data是些提供给该 device 的私有数据
   3）最后比较：platform_device.name和platform_driver.driver.name。
   platform_driver.id_table 可能为空，这时可以根据 platform_driver.driver.name 来寻找同名的 platform_device。
3. **如何利用总线编写驱动程序？**
   1）分配/设置/注册platform_device结构体：在里面定义所用资源，指定设备名字。
   2）分配/设置/注册platform_driver结构体：在其中的probe函数里，分配/设置/注册file_operations结构体，并从platform_device中确实所用硬件资源。指定platform_driver的名字。





### 为什么存在设备树？设备树是如何实现的？如何利用设备树来编写驱动？

1. 通过配置文件——设备树来定义“资源”。虽然代码稍微复杂，但是易于扩展。无冗余代码，修改引脚时只需要修改dts文件并编译得到dtb，将其传给内核，无需重新编译内核/驱动
2. 内核会动态地解析这些配置文件，uboot会把dtb文件传给内核，然后内核解析dtb文件，把每一个节点都转换为device_node结构体。对于某些device_node结构体（没有disable？），会被转换为platform_device结构体
   **这样的会被转换**
   A：根节点下含有compatible属性的子节点。
   B：含有特定compatible属性的节点的子节点。"simple-bus","simple-mfd","isa","arm,amba-bus"。
   C：*IIC、SPI节点下的子节点不会转换为platform_device*
3. 简单来说，驱动要求设备树节点提供什么，我们就得按着这要求去写设备树。设备树要有compatible属性，要与platform_driver中的of_match_table里的其中一项compatible一致，这样才对应的上。
   **设备树指定资源，platform_driver获得资源**：：驱动程序中，可以从platform_device中得到device_node,再用of_property_read_u32得到属性值





## arm架构的问题

### 什么是CPSR、SPSR？什么时候用到

```tex
CPSR是当前程序状态寄存器，存储的是当前程序的状态，比如上下文的一些寄存器内容，程序运行的话就要用到CPSR。SPSR为备份的程序状态寄存器，主要是中断发生时用来存储CPSR的值的。
```









