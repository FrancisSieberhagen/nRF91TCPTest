#!/usr/bin/env python3

import datetime
import socket

HOST = '0.0.0.0'    # Standard loopback interface address 
PORT = 42501        # Port to listen on (non-privileged ports are > 1023)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    while True:
      conn, addr = s.accept()
      with conn:
        print('Connected by', addr)
        while True:
            data = conn.recv(1024)
            if not data:
                break
            msg = data.decode("utf-8").strip()
            tstr = datetime.datetime.now().isoformat()[0:len("2019-09-12T11:25:41")]
            print('%s\t%s\t[%s]' % (tstr, addr, msg))
            conn.sendall(data)
