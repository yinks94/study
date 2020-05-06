import os
import socket
import threading
import socketserver

SERVER_HOST = 'localhost'
SERVER_PORT = 0
BUF_SIZE = 1024

def client(ip, port, message):
    """A client to test threading mixin server"""
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((ip, port))
    try:
        #print("[AAA] %s " % message)
        sock.sendall(message.encode())
        response = sock.recv(BUF_SIZE)
        print("Client received : %s" % response)
    finally:
        sock.close()


class ThreadedTCPRequestHandler(socketserver.BaseRequestHandler):
    """An example of threaded TCP request handler"""
    def handle(self):
        data = self.request.recv(1024)
        current_thread = threading.current_thread()
        response = "%s ?  %s" % (current_thread, data)
        self.request.sendall(response.encode())

class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    """NOoting to add here, inherited everyhing  necesssary from parent"""
    pass

if __name__ == '__main__' :
    server = ThreadedTCPServer((SERVER_HOST, SERVER_PORT), ThreadedTCPRequestHandler)

    ip, port = server.server_address
    server_thread = threading.Thread(target=server.serve_forever)
    server_thread.daemon = True
    server_thread.start()
    print("Server loop running on thread : %s" % server_thread.name)

    client(ip, port, "Hello form client1")
    client(ip, port, "Hello form client2")
    client(ip, port, "Hello form client3")
    server.shutdown()








