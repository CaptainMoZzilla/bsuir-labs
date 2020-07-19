import socket
import json
import time
import hashlib 

from encrypt import encrypt_first_message,\
                    decrypt_message_with_tgt,\
                    encrypt_user_message_with_tgt,\
                    decrypt_kcs_user_ticket,\
                    encrypt_target_server_ticket    
from server.config import CLIENT_KDC_SERVER_ADDRESS,\
                          CLIENT_TICKET_GRANTING_SERVER_ADDRESS,\
                          CLIENT_TARGET_SERVER_ADDRESS

class Client:
    def __init__(self):
        self.password = self.usermame = 'default_user'
        self.kdcs_socket = socket.socket()
        self.tgs_socket = socket.socket()
        self.target_socket = socket.socket()

    def __create_kdc_message(self):
        return {
            'username': self.usermame,
            'target_server': 'target_server',
            'time': time.time(),  
        }

    def __create_message_with_tgt(self, time, tgt):
        return {
            'time': time,
            'tgt': tgt
        }

    def __create_target_server_message(self, server_ticket):
        return {
            'time': time.time(),
            'server_ticket': server_ticket
        }

    def start(self):
        self.kdcs_socket.connect(CLIENT_KDC_SERVER_ADDRESS)

        kdc_message = self.__create_kdc_message()
        time_to_check = kdc_message['time']
        self.kdcs_socket.send(encrypt_first_message(kdc_message, self.password))

        kdc_answer = self.kdcs_socket.recv(1000000)
        if not kdc_answer:
            print('USER@MEGA ERROR! AAAAAAAAAAAAAA')
            return

        kdc_answer_decrypted = decrypt_message_with_tgt(kdc_answer, self.password)
        if kdc_answer_decrypted['time'] != time_to_check:
            print('USER@Incorrect time from kdc')
            return
        
        self.kdcs_socket.close()

        #########################################################
        # Let's start with TGS
        #########################################################
        print('USER@Get tgt from kdc')

        tgt = kdc_answer_decrypted['tgt']
        session_key = kdc_answer_decrypted['session_key']
        print(f'USER@Session key: {session_key}')

        self.tgs_socket.connect(CLIENT_TICKET_GRANTING_SERVER_ADDRESS)

        message_with_tgt = self.__create_message_with_tgt(time_to_check, tgt)
        enc_message_with_tgt = encrypt_user_message_with_tgt(message_with_tgt, session_key)

        self.tgs_socket.send(enc_message_with_tgt)

        tgs_answer = self.tgs_socket.recv(2048)
        self.tgs_socket.close()
        print('USER@Get kcs from tgs')

        #########################################################
        # And finally target server
        #########################################################
        decrypted_kcs_ticket = decrypt_kcs_user_ticket(tgs_answer, session_key)

        kcs_key = decrypted_kcs_ticket['kcs_key']    
        print(f'USER@KCS key: {kcs_key}')

        server_ticket = decrypted_kcs_ticket['server_ticket']
        target_server_ticket = self.__create_target_server_message(server_ticket)
        encrypted_target_server_ticket = encrypt_target_server_ticket(target_server_ticket, kcs_key)

        self.target_socket.connect(CLIENT_TARGET_SERVER_ADDRESS)
        self.target_socket.send(encrypted_target_server_ticket)


Client().start()

