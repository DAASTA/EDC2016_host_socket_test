// Created by wxk14, 2016.8
//  serial port at Windows
//
//  - SerialPortProtol(header_list, length): 简单的串口协议。header_list是可以接受的字符串头；length是协议规定的字符串长度。
//  - SerialPort(com, baud_rate, protol): 开启串口。给出串口号，波特率，串口协议。
//      - send(msg, length): 发送字符串及其长度。
//      - receive(): 接受一次信息，并返回符合串口协议的所有字符串。注意，返回的字符串可能在中间出现0x00。

#pragma once

#include"com.hpp"

#include<vector>
#include<string>

using std::vector;
using std::string;

class SerialPortProtol {

public:
    SerialPortProtol(vector<string> header_list, int length) 
        : header_list_(header_list)
        , length_(length)
    {
    }

    ~SerialPortProtol() {
    }

    vector<string> decodeLines(char* line, int& len)
    {
        vector<string> list;
        int offset = 0;
        while (len - offset > length_) {
            if (checkHeader(line + offset)) {
                list.push_back(cutString(line + offset));
                offset += length_;
            }
            else {
                offset += 1;
            }
        }
        for (int i = offset; i < len; ++i) line[i - offset] = line[i];
        len -= offset;

        return list;
    }

    inline int getLength() { return length_; }

private:
    vector<string> header_list_;
    int length_;

    bool checkHeader(const char* line) {
        for (int i = 0; i < header_list_.size(); ++i)
            if (header_list_[i].compare(0, string::npos, line, header_list_[i].length()) == 0)
                return true;
        return false;
    }
    string cutString(const char* line) {
        string s(length_+1,'\0');
        for (int i = 0; i < length_; ++i) s[i] = line[i];
        return s;
    }
};

class SerialPort {
public:
    SerialPort(int com, int baud_rate, SerialPortProtol protol)
        : com_(com)
        , baud_rate_(baud_rate)
        , valid_(false)
        , protol_(protol)
        , total_length(0)
    {
        int result;
        
        // open com device
        result = OpenCOMDevice(com_, baud_rate_);
        if (result != 0) {
            printf("[Error] Failed to open COM%d\n", com_);
            return;
        }

        printf("[Info] COM%d launched.\n", com_);
        valid_ = true;
    }

    ~SerialPort() {
    }

    bool send(const char* msg, int length) {
        SendUARTMessageLength(com_, msg, length);
    }

    vector<string> receive() {
        if (!valid_) {
            vector<string> list;
            printf("[Error] This serial port (com%d) is invalid.\n", com_);
            return list;
        }
        total_length += CollectUARTData(com_, buffer);
        return protol_.decodeLines(buffer, total_length);
    }

    inline bool isValid() { return valid_; }
    
private: 

    SerialPortProtol protol_;

    bool valid_;
    int com_;
    int baud_rate_;
    
    char buffer[8192];
    int total_length;

};
