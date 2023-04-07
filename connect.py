#
#   Hello World client in Python
#   Connects REQ socket to tcp://localhost:5555
#   Sends "Hello" to server, expects "World" back
#

import zmq
import time

context = zmq.Context()

#  Socket to talk to server
print("Connecting to server…")
socket = context.socket(zmq.REQ)
socket.connect("tcp://127.0.0.1:5555")

#  Do 10 requests, waiting each time for a response
print('Send "xy" for current position & "s" to exit')
reply = ''
while 'shutdown' not in reply:
    msg = input('msg: ')
    t1 = time.time()
    # Send msg
    socket.send(msg.encode('utf-8'))
    #  Get the reply.
    message = socket.recv()
    reply = message.decode('utf-8')
    t2 = time.time()
    print(f"Received reply '{reply}' in {(t2-t1)*1e6:.3f}us")

