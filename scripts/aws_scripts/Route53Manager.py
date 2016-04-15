#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Route53Manager.py
# Álvaro Castellano Vela - 07/04/2016

import threading
import SocketServer

import signal
import sys

import Queue

from random import randint
from time import sleep

import route53

QueueOfRouteRequests = Queue.Queue()
Lock = threading.Lock()

def signal_handler(signal, frame):
    print('Powering off server')
    server.shutdown()
    server.server_close()
    sys.exit(0)

def processRoute53Request():
    while True:
        if not QueueOfRouteRequests.empty():
            Lock.acquire()
            request = QueueOfRouteRequests.get()
            Lock.release()

            success = False

            while not success:
                try:
                    conn = route53.connect(
                        aws_access_key_id='AKIAIDMPG7XNEGWQ7YJA',
                        aws_secret_access_key='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',
                    )
                    VPNzone = conn.get_hosted_zone_by_id('ZPEB3E12BAWA8')

                    url = request[0]
                    ip = request[1]
                    action = request[2]

                    name_to_match = url + '.'
                    finded = False

                    for record_set in VPNzone.record_sets:
                        if record_set.name == name_to_match:
                            finded = True
                            record_set.delete()
                            if action == "ADD":
                                new_record, change_info = VPNzone.create_a_record(name=name_to_match, values=[str(ip)], )
                            break;

                    if not finded and action == "ADD":
                        new_record, change_info = VPNzone.create_a_record(name=name_to_match, values=[str(ip)], )

                    success = True

                except:
                    success = False

            print "Completed Handle for {}".format(request)


class ThreadedTCPRequestHandler(SocketServer.BaseRequestHandler):
    def handle(self):
        data = self.request.recv(1024)
        processed_data = data.split('|##|')
        if len(processed_data) == 3:
            domain = processed_data[0]
            ip = processed_data[1]
            action = processed_data[2]
            self.request.sendall("OK")
            Lock.acquire()
            QueueOfRouteRequests.put([domain,ip,action])
            Lock.release()
            print data


class ThreadedTCPServer(SocketServer.ThreadingMixIn, SocketServer.TCPServer):
    pass


if __name__ == "__main__":


    signal.signal(signal.SIGINT, signal_handler)
    server = ThreadedTCPServer(("127.0.0.1", 8745), ThreadedTCPRequestHandler)
    ip, port = server.server_address
    print "Listening on {}:{}".format(ip,port)



    server_thread = threading.Thread(target=server.serve_forever)
    server_thread.daemon = True
    server_thread.start()
    print "Server loop running in thread:", server_thread.name

    worker = threading.Thread(target=processRoute53Request)
    worker.setDaemon(True)
    worker.start()

    while True:
        continue

exit(0)
