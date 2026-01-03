//使用 Intel 语法的 32 位 Windows 汇编代码
#.386 //使用了``.386`` 指令集，这是 32 位 x86 架构
#.model flat,stdcall //使用了``.model flat,stdcall`` 内存模型，这是 Windows 系统特有的
#.stack 4096
#ExitProcess PROTO, dwExitCode:DWORD //使用了``ExitProcess`` Windows API
#.code
#main PROC
#    mov eax, 5
#    add eax, 6

#    INVOKE ExitProcess,0 //使用了``INVOKE`` 指令，这是 MASM 汇编器的指令
#main ENDP
#END main //整个代码结构是 Windows 风格的

//
//  main.s
//  test
//
//  Created by 天塌不惊 on 2026/1/2.
//  MacOS兼容的64位AT&T语法 64位架构（使用x86_64指令集）

.section __TEXT,__text # 使用.section指令定义代码段
.globl _main # 使用.globl _main声明main函数为全局可见
_main: # 入口点：MacOS使用_main而不是main（MacOS要求C函数名前加下划线）
    # 计算 5 + 6
    movl $5, %eax // 操作数顺序：AT&T是"源操作数, 目标操作数"，Intel是"目标操作数, 源操作数"
    addl $6, %eax  # 结果在 %eax 中 (11) 使用AT&T语法：操作数顺序为源，目标，寄存器前加%，立即数前加$
    
    # 将数字转换为ASCII字符串并存储到栈中
    subq $32, %rsp  # 分配足够的栈空间
    movl %eax, %ebx  # 保存结果到 %ebx 指令后缀：AT&T需要指令后缀指定操作数大小（如movl, addl）
    movl $0, %ecx  # 用于计数位数
    movl $10, %edi  # 除数
    
    # 将数字转换为字符并压入栈中（逆序）
    convert_loop:
        movl $0, %edx
        divl %edi  # %eax = 商, %edx = 余数
        addl $48, %edx  # 转换为ASCII
        pushq %rdx  # 保存余数
        incl %ecx  # 位数加1
        cmpl $0, %eax
        jne convert_loop
    
    # 将字符从栈中弹出并存储到输出缓冲区
    movq %rsp, %rsi  # 输出缓冲区地址
    movl $0, %ebx  # 索引
    
    build_string:
        popq %rdx
        movb %dl, (%rsi, %rbx)
        incl %ebx
        loop build_string
    
    movb $'\n', (%rsi, %rbx)  # 添加换行符
    incl %ebx  # 总长度加1
    
    # 输出结果
    movl $0x2000004, %eax  # write syscall
    movl $1, %edi  # stdout
    movl %ebx, %edx  # 字符串长度
    syscall
    
    # 清理栈
    addq $32, %rsp
    
    # 退出程序
    movl $0, %edi
    movl $0x2000001, %eax  # exit syscall
    syscall # 退出系统调用：MacOS使用syscall而不是ExitProcess
