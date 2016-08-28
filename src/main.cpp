// Created by wxk14, 2016.8
//   test for the `socket` and `serial port`

#include"my_string.hpp"
#include"socket.hpp"
#include"serial_port.hpp"
#include"time_stamp.hpp"

#include<cstdio>
#include<conio.h>
#include<iostream>
#include<windows.h>

const char* IP_ADDRESS = "127.0.0.1";
const int PORT = 30000;

MyString shared_data("");

MyString function(MyString s_in)
{
    return MyString(getTimeStamp()) + MyString(" ") + shared_data;
}

int main(int argc, char* argv[])
{
    SocketServer socket_server(30000, function);
    socket_server.run();

    //char buffer[20] = { 0x0d, 0x0a, 0x00 };
    //vector<string> head_list;
    //head_list.push_back(buffer);
    //SerialPortProtol protol(head_list, 20);

    SerialPort port(12, 115200/*, protol*/);

    while (true)
    {
        vector<MyString> list = port.receive();
        for (int i = 0; i < list.size(); ++i) 
            printf("%s %s\n", getTimeStamp().c_str(), list[i].c_str());
        if (list.size() > 0) shared_data = list[0];

        if (_kbhit()) {
            char ch = _getch();
            if (ch == ' ') {
                printf("%s === 暂停: 等待输入 ===\n", getTimeStamp().c_str());
                //system("pause");
                printf("输入要发送的字符(ASCII): \n");
                char buffer[256];
                std::cin.getline(buffer, 256);
                port.send(MyString(buffer));
                printf("%s === 运行中 - 正在持续接受数据，按空格键暂停 ===\n", getTimeStamp().c_str());
            }
        }

        Sleep(50);
    }
    
}
