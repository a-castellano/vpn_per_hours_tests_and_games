import socket
from time import sleep

s = socket.socket()
s.connect(("localhost", 8085))
s.send( "YOLO TEST" )
s.close()



for i in range(10):
    s = socket.socket()
    s.connect(("localhost", 8085))
    s.send( "YOLO "+str(i) )
    s.close()

s = socket.socket()
s.connect(("localhost", 8085))
s.send( "create/KySQUUylQ0WsAjApHtgrwU3HLb0fiFQAEOm4tGIt5KoHZwMYRYyjfDJAA33q" )
s.close()
