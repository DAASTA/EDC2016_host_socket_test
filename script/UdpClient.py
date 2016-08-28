# python 2.7 

# Created by wxk14, 2016.8
#  simple udp test

import socket

if "__main__"==__name__:
    port=30000
    host='127.0.0.1'
    address = (host, port)
    s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

    while True:
        line = raw_input();
        line = line + '\0'
        s.sendto(line,address)
        sss = s.recv(1024)
        print sss
        for i in range(len(sss)):
            print hex(ord(sss[i])), ' ',
        print ''

    s.close()