#!/bin/bash
# 编译写进程和读进程
gcc write_process.c -o write_process
gcc read_process.c -o read_process
gcc clean.c -o clean
# 启动多个读写进程
./write_process
for i in {1..10}; do
    ./write_process&
    ./read_process&
done
# 等待所有进程结束
wait
#关闭共享内存
./clean
wait
# 清理编译生成的可执行文件
rm write_process read_process clean
