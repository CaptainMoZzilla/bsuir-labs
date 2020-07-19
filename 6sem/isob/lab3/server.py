import socket

class TestServer:
    def __init__(self):
        self.main_socket = socket.socket()
        self.main_socket.bind(('localhost', 2222))
        self.open_connections = []

    def start(self):
        self.main_socket.listen(1)
        while True:
            connection, address = self.main_socket.accept()
            print(f'Message from: {address}')
            client_request = connection.recv(1024)
            if address not in set(self.open_connections):
                self.open_connections.append(address)

            if len(self.open_connections) > 100:
                raise Exception('To many active connection')


TestServer().start()