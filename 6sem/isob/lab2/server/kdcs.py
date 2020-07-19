import socket
import random
import time

import sys
sys.path.append('..')

from encrypt import load_from_request,\
                    decrypt_first_message,\
                    encrypt_message_with_tgt        
from config import DEFAULT_USERS,\
                   KDC_PASSWORD,\
                   KDC_SERVER_PORT,\
                   KDC_SERVER_NAME,\
                   KDC_SERVER_TICKET_PERIOD


class KDCS:
    def __init__(self):
        self.main_socket = socket.socket()
        self.main_socket.bind(('localhost', KDC_SERVER_PORT))
        self.users = DEFAULT_USERS
        self.password = KDC_PASSWORD

    def __create_tgt(self, username, session_key, target_server):
        return {
            'session_key': session_key,
            'username': username,
            'target_server': target_server,
            'end_time': time.time() + 10000000
        }

    def __create_message_with_tgt(self, username, user_time, session_key, target_server):
        return {
            'time': user_time,
            'session_key': session_key,
            'tgt': self.__create_tgt(username, session_key, target_server)
        }

    def __create_session_key(self):
        return ''.join([str(random.randint(1, 10)) for _ in range(10)])

    def start(self):
        self.main_socket.listen(1)
        while True:
            connection, address = self.main_socket.accept()
            print(f'KDC@Init message from: {address}')

            while True:
                client_request = connection.recv(1000000)
                if not client_request:
                    break

                #############################################
                ## First request
                #############################################
                encrypted_message = load_from_request(client_request)
                username = encrypted_message['username']

                if username not in self.users:
                    print(f'KDC@There is no such user')
                    break

                user_password = self.users[username]
                
                decrypted_message = decrypt_first_message(encrypted_message, user_password)
                user_time = decrypted_message['time'] # Нужно только расшифрованное время
                target_server = decrypted_message['target_server']

                if time.time() - decrypted_message['time'] > KDC_SERVER_TICKET_PERIOD:
                    print('KDC@Time limit')
                    break

                session_key = self.__create_session_key()
                print(f'KDC@Session key: {session_key}')

                message_with_tgt = self.__create_message_with_tgt(username, user_time, session_key, target_server)
                
                kdc_encrypted_message = encrypt_message_with_tgt(message_with_tgt, user_password, self.password)
                connection.send(kdc_encrypted_message)

KDCS().start()