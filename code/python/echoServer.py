import socketserver
import sys

class MyTCPHandler(socketserver.BaseRequestHandler):
    """
    The request handler class for the echo server.

    It is instantiated once per connection to the server, and must
    override the handle() method to implement communication to the
    client.
    
    The 'echo server' and the 'echo client' must be launched from different consoles... 
    otherwise, at least in Windows, you'll get a nice [WinError 10061] 
    """

class MyTCPHandler(socketserver.StreamRequestHandler):

    def handle(self):
        # self.rfile is a file-like object created by the handler;
        # we can now use e.g. readline() instead of raw recv() calls
        self.data = self.rfile.readline().strip()
        print("{} wrote:".format(self.client_address[0]))
        print(self.data)
        # Likewise, self.wfile is a file-like object used to write back
        # to the client
        self.wfile.write(self.data.upper())

if __name__ == "__main__":
    HOST, PORT = "localhost", 9999

    # Create the server, binding to localhost on port 9999
    with socketserver.TCPServer((HOST, PORT), MyTCPHandler) as server:
        # Activate the server; this will keep running until you
        # interrupt the program with Ctrl-C
        try:
            server.serve_forever()
        except:
            print("something went wrong...")
            server.close()
            print("bye bye")
            sys.exit()
