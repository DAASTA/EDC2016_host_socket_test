// Created by wxk14, 2016.8
//   test for the `socket` and `serial port`

#include"communication/my_string.hpp"
#include"communication/socket.hpp"
#include"communication/serial_port.hpp"
#include"communication/time_stamp.hpp"

#include<cstdio>
#include<conio.h>
#include<iostream>
#include<windows.h>

const char* IP_ADDRESS = "127.0.0.1";
const int PORT = 30000;

MyString shared_data("");

MyString function(MyString s_in)
{
    return MyString(TimeStamp::getTimeStamp()) + MyString(" ") + shared_data;
}

int main(int argc, char* argv[])
{
    SocketServer socket_server(30000, function);
    socket_server.run();

    char tail[3] = { 0x0d, 0x0a, 0x00 };
    SerialPortProtol protol(5, tail);

    SerialPort port(15, 115200, protol);
    
    while (true)
    {
        std::vector<MyString> list = port.receive();
        for (int i = 0; i < list.size(); ++i) 
            printf("%s %s\n", TimeStamp::getTimeStamp().c_str(), list[i].hex_str());
        if (list.size() > 0) shared_data = list[0];

        if (_kbhit()) {
            char ch = _getch();
            if (ch == ' ') {
                printf("\n\n%s === 暂停: 等待输入 ===\n", TimeStamp::getTimeStamp().c_str());
                //system("pause");
                printf("输入要发送的字符(ASCII): \n");
                char buffer[256];
                std::cin.getline(buffer, 256);
                port.send(MyString(buffer));
                printf("%s === 运行中 - 正在持续接受数据，按空格键暂停 ===\n\n", TimeStamp::getTimeStamp().c_str());
            }
        }

        Sleep(50);
    }
    
}
