# Multithreading

## Uthread: switching between threads

为用户级线程系统设计实现上下文切换机制：`user/uthread.c`, `user/uthread_switch.S`。需要制定一个计划来创建线程并保存/恢复寄存器以在线程之间切换。

### Solution

`user/uthread.c: thread_create(), thread_schedule(); user/uthread_switch.S: thread_switch`

两个目标：
1. 确保`thread_schedule()`第一次运行给定线程时，该线程在其自己的堆栈上执行传递给`thread_create()`的函数
2. 确保`thread_switch`保存被切换的线程的寄存器，恢复被切换到的线程的寄存器，并返回到后一个线程的指令中最后离开的点(sp)
   1. 决定在哪里保存/恢复寄存器
   2. 修改`struct thread`来保存寄存器
   3. 在`thread_schedule()`中添加对`thread_switch`的调用
   4. 可以给`thread_switch`传参数

### Implemetation

实现一个用户级别的上下文切换：
1. 首先线程要有自己的上下文结构体context
2. 创建线程时，设置线程的ra和sp寄存器
3. 上下文切换就是保存和加载寄存器，和内核级完全一致

## Using threads

使用哈希表探索线程和锁的并行编程，在WSL下运行（不是qemu），使用`pthread`库，多线程的情况下出现哈希碰撞不能很好的解决

### Solution

给哈希表加锁，两种思路：
1. 每次`put/insert`都给整个哈希表加锁
2. 每次`put/insert`只给对应哈希表的bucket加锁(?)

### Implemetation



## Barrier