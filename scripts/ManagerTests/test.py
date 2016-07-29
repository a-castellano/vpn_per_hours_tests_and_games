import socket
from time import sleep

#s = socket.socket()
#s.connect(("localhost", 8085))
#s.send( "YOLO TEST" )
#print( "Sending YOLO TEST" )
#s.close()

request = "create/KySQUUylQ0WsAjApHtgrwU3HLb0fiFQAEOm4tGIt5KoHZwMYRYyjfDJAA33q";

for i in range(10000):
    s = socket.socket()
    s.connect(("localhost", 8085))
    s.send( request )
    sleep(1.5)
    print( "SENDING {} - {}".format( request, i ))
    s.close()

s = socket.socket()
s.connect(("localhost", 8085))
s.send( "__KILL_YOURSELF__" )
s.close()
