# EDC2016 host - socket test

电设上位机 - Windows C++ 通讯文件

- socket
- 串口

- main.cpp
    - 一个简单的命令行串口助手
    - main.cpp同时是一个udp的socket服务器，能够将收到的串口信息通过socket分享给其他进程。

## 编译

- VS

功能均通过Windows API实现，因此只适用于Windows系统。

另外注意，项目需要选择使用Unicode字符集：

- 项目->属性->项目默认值->公共语言运行时支持->使用Unicode字符集

## Socket

- SocketServer(port, function): 建立UDP服务器，监听本地port端口，并设置字符串处理函数function自动处理收到的字符串并返回回复的字符串。
    - run(): 启动服务器，新建线程进行循环监听。注意这里可能出现的线程安全问题。
    - stop(): 终止服务器。
- SocketClient(port, ip="127.0.0.1"): 建立UDP客户端
    - send(MyString): 发送信息到指定端口。
    - MyString sendAndRecv(MyString): 发送信息并立即接受返回信息到echo。此函数是堵塞的，默认等待时间为20ms。

## Serial Port

- SerialPortProtol(header_list, length): 简单的串口协议。header_list是可以接受的字符串头；length是协议规定的字符串长度。
- SerialPort(com, baud_rate, protol): 开启串口。给出串口号，波特率，串口协议。
    - send(MyString): 发送字符串。
    - receive(): 接受一次信息，并返回符合串口协议的所有字符串。   
