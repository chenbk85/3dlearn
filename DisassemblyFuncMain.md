![http://3dlearn.googlecode.com/files/main_disassembly.png](http://3dlearn.googlecode.com/files/main_disassembly.png)
上图错误修正:最后一行的分析提示应该是"EAX清零"，真是指鹿为马啊!

### 重点提示 ###
以上逐行分析了一次函数创建和恢复现场的汇编过程.

  * 堆栈空间的创建和恢复
在进入调用点之前(也就是第一行push ebp),原始的堆栈空间是BP到SP表示的内存空间。在当前函数里，将BP-SP均向下平移，紧接原来的空间创建了当前使用的堆栈空间(这里是C0H字节),使用EDI-ECX-EAX-REP STOS组合来初始化这个空间。调用前的栈顶是当前函数的基址，这个关系在当前调用过程中一直未被修改，则最后将当前的基址可以重新设为调用前的栈顶(倒数第三行)。至于为什么不push-pop，可能是编译器小技巧吧。


### References ###
  * 寄存器的常用含义还有那些？
http://bbs.pediy.com/showthread.php?t=29791

  * 各寄存器作用
http://blog.csdn.net/shentao17792/article/details/5556315

  * Where the top of the stack is on x86
http://eli.thegreenplace.net/2011/02/04/where-the-top-of-the-stack-is-on-x86/