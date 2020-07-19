import socket
import random
import time

import sys
sys.path.append('..')

from encrypt import decrypt_user_message_with_tgt,\
                    encrypt_kcs_user_ticket
from config import KDC_PASSWORD,\
                   TICKET_GRANTING_SERVER_KEY,\
                   TICKET_GRANTING_SERVER_NAME,\
                   TICKET_GRANTING_SERVER_PORT

class TGS:
    def __init__(self):
        self.main_socket = socket.socket()
        self.main_socket.bind(('localhost', TICKET_GRANTING_SERVER_PORT))

        self.kdc_password = KDC_PASSWORD
        self.tgs_password = TICKET_GRANTING_SERVER_KEY
    
    def __create_kcs_key(self):
        return ''.join([str(random.randint(1, 10)) for _ in range(10)])

    def __create_kcs_ticket(self, username, target_server, kcs_key):
        return {
            'username': username,
            'target_server': target_server,
            'start_time': time.time(),
            'end_time': time.time() + 50000000000000000,
            'kcs_key': kcs_key
        }

    def __create_user_kcs_ticket(self, username, target_server, kcs_key):
        user_ticket = self.__create_kcs_ticket(username, target_server, kcs_key)
        user_ticket['server_ticket'] = user_ticket.copy()
        return user_ticket

    def start(self):
        self.main_socket.listen(1)
        while True:
            connection, address = self.main_socket.accept()
            print(f'TGS@TGT message from: {address}')
            while True:
                client_request = connection.recv(1000000)
                if not client_request:
                    break
            
                decrypted_user_message = decrypt_user_message_with_tgt(client_request, self.kdc_password)
                tgt = decrypted_user_message['tgt']

                if time.time() > tgt['end_time']:
                    print('TGS@Time limit')
                    break

                username = tgt['username']
                target_server = tgt['target_server']
                session_key = tgt['session_key']

                print(f'TGS@Session_key: {session_key}, User time:{decrypted_user_message["time"]}')

                kcs_key = self.__create_kcs_key()
                print(f'TGS@KCS key: {session_key}')

                kcs_ticket = self.__create_user_kcs_ticket(username, target_server, kcs_key)
                encrypte_kcs_ticket = encrypt_kcs_user_ticket(kcs_ticket, self.tgs_password, session_key)
            
                connection.send(encrypte_kcs_ticket)

TGS().start()