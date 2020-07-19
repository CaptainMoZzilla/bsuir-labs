import socket
import random
import time

import sys
sys.path.append('..')

from encrypt import decrypt_target_server_ticket
from config import (TICKET_GRANTING_SERVER_KEY,
                   TARGET_SERVICE_PORT,
                   TARGET_SERVER_NAME,)


class TargetServerr:
    def __init__(self):
        self.main_socket = socket.socket()
        self.main_socket.bind(('localhost', TARGET_SERVICE_PORT))
        
        self.tgs_password = TICKET_GRANTING_SERVER_KEY
        self.name = TARGET_SERVER_NAME

    def start(self):
        self.main_socket.listen(1)

        while True:
            connection, address = self.main_socket.accept()
            print(f'TargetServer@Message from: {address}')
            while True:
                client_request = connection.recv(1024)
                if not client_request:
                    break
            
                ticket = decrypt_target_server_ticket(client_request, self.tgs_password)
                
                if ticket['server_ticket']['target_server'] != self.name:
                    print('TargetServer@It\'s not ticket =(')
                    break

                print(f"TargetServer@SUCCESS user:{ticket['server_ticket']['username']}\n"
                      f"KCS_KEY: {ticket['server_ticket']['kcs_key']}")

TargetServerr().start()