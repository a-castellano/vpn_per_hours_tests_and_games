#!/usr/bin/env python
# -*- coding: utf-8 -*-

# client.py
# Álvaro Castellano Vela - 08/04/2016

import socket
from random import randint

def sendRequest(ip, port, domain, destination, action):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((ip, port))
    try:
        message = domain + "|##|" + destination + "|##|" + action
        sock.sendall(message)
        response = sock.recv(1024)
        print "Received: {}".format(response)
    finally:
        sock.close()


ip = "127.0.0.1"
port = 8745

dest = "23.45.67.32"

actions = ["ADD", "DELETE"]

for i in range(20):
    domain = "example-" + str(i) + ".windmaker.net"
    print "Sending: {} to {}:".format(domain, dest)
    sendRequest(ip, port, domain, dest, actions[1])
