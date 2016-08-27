// Created by wxk14, 2016.8
//   test for the `socket` and `serial port`

#include"socket.hpp"
#include"serial_port.hpp"
#include"time_stamp.hpp"

#include<cstdio>
#include<windows.h>

const char* IP_ADDRESS = "127.0.0.1";
const int PORT = 30000;

string Q, R, S;

char* function(char* s_out, const char* s_in)
{
    SYSTEMTIME sys;
    GetLocalTime(&sys);

    sprintf(s_out, "%s echo: %s \n %02X %02X ", getTimeStamp().c_str(), s_in, (unsigned char)S[7], (unsigned char)S[6]);

    return s_out;
}

int main(int argc, char* argv[])
{
    SocketServer socket_server(30000, function);
    socket_server.run();

    vector<string> head_list;
    head_list.push_back("UQ"); // 0x 55 51
    head_list.push_back("UR"); // 0x 55 52
    head_list.push_back("US"); // 0x 55 53

    SerialPortProtol protol(head_list, 11);
    SerialPort port(3, 9600, protol);

    while (true)
    {
        vector<string> list = port.receive();
        for (int i = 0; i < list.size(); ++i) {
            for (int j = 0; j < protol.getLength(); ++j) printf("%02X ", (unsigned char)list[i][j]);
            switch ((unsigned char)list[i][1])
            {
            case 'Q':
                Q = list[i];
                break;
            case 'R':
                R = list[i];
                break;
            case 'S':
                S = list[i];
                break;
            }
            printf("\n");
        }
        Sleep(50);
    }
}
