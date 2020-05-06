import os
import socket
import threading
import socketserver



SERVER__HOST = 'localhost'
SERVER_PORT = 0
BUF_SIZE = 1024
ECHO_MSG = 'Hello echo server!!'

class ForkedClient():
    """A Client to test forking server"""
    def __init__(self, ip, port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((ip, port))

    def run(self):
        """Client playing with the server"""
        current_process_id = os.getpid()
        print("PID %s Sending echo message to server : %s" % (current_process_id, ECHO_MSG))
        sent_data_length = self.sock.send(ECHO_MSG)
        print("Sent : %d characters, so far.." % sent_data_length)
        response = self.sock.recv(BUF_SIZE)
        print("PID %s received : %s" % (current_process_id, response[5:]))

    def shutdown(self):
        """Cleanup the client  socket"""
        self.sock.close()


class ForkingServerRequestHandler(socketserver.BaseRequestHandler):
    def handle(self):
        data = self.request.recv(BUF_SIZE)
        current_process_id = os.getpid()
        response = '%s : %s' % (current_process_id, data)
        print("Server sending response [current_process_id:data] = [%s]" % response)
        self.request.send(response)
        return

class ForkingServer(socketserver.ForkingMixIn, socketserver.TCPServer):
    """Nothing to add here, inherited everything necessary from parent"""
    pass

def main():
    server = ForkingServer((SERVER__HOST, SERVER_PORT), ForkingServerRequestHandler)
    ip, port = server.server_address
    server_thread = threading.Thread(target=server.serve_forever)
    server_thread.setDaemon(True)
    server_thread.start()
    print("Server loop running PID : %s" % os.getpid())

    client1 = ForkedClient(ip, port)
    client1.run()

    client2 = ForkedClient(ip, port)
    client2.run()


    server.shutdown()
    client1.shutdown()
    client2.shutdown()


if __name__ == '__main__':
    main()
