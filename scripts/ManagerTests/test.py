import socket
from time import sleep

#s = socket.socket()
#s.connect(("localhost", 8085))
#s.send( "YOLO TEST" )
#print( "Sending YOLO TEST" )
#s.close()


for i in range(5000):
    s = socket.socket()
    s.connect(("localhost", 8085))
    s.send( "YOLO "+str(i) )
    sleep(1)
    print( "SENDING YOLO "+str(i) )
    s.close()

#s = socket.socket()
#s.connect(("localhost", 8085))
#s.send( "create/KySQUUylQ0WsAjApHtgrwU3HLb0fiFQAEOm4tGIt5KoHZwMYRYyjfDJAA33q" )
#print( "SENDING create/KySQUUylQ0WsAjApHtgrwU3HLb0fiFQAEOm4tGIt5KoHZwMYRYyjfDJAA33q" )
#s.close()
'''
s = socket.socket()
s.connect(("localhost", 8085))
s.send( "__KILL_YOURSELF__" )
s.close()
'''
