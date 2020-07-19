import json
from des2 import encrypt, decrypt

def encrypt_first_message(message, password):
    # TODO: Добавить дес для времени только без смены ключа
    enc_time = encrypt(str(message['time']), password)
    message['time'] = enc_time
    return json.dumps(message).encode()

def decrypt_first_message(message, password):
    # TODO: Добавить дес и оно должно возвращать оригинальны месседж с временем 
    message['time'] = float(decrypt(message['time'], password)) 
    return message

def load_from_request(message):
    # TODO: для извлечения json
    return json.loads(message.decode())

def encrypt_message_with_tgt(message, user_password, kdc_password):
    # TODO: Зашифровать tgt ключом kdc, зашифровать время и ключ сесси ключом пользователя     
    message['tgt'] = encrypt(json.dumps(message['tgt']), kdc_password)
    message['time'] = encrypt(str(message['time']), user_password)
    message['session_key'] = encrypt(str(message['session_key']), user_password)
    return json.dumps(message).encode()

def decrypt_message_with_tgt(message, user_password):
    # TODO: Расшифровываем время и session key, tgt не трогаем 
    message = json.loads(message.decode())
    message['time'] =  float(decrypt(message['time'], user_password)) 
    message['session_key'] =  decrypt(message['session_key'], user_password)
    return message

def encrypt_user_message_with_tgt(message, session_key):
    # TODO: Шифруем время с помощью session key больше ничего не трогаем 
    message['time'] =  encrypt(str(message['time']), session_key)
    return json.dumps(message).encode()

def decrypt_user_message_with_tgt(message, kdc_password):
    # TODO: Расшифровываем tgt ключом kdc для tgs, а затем из tgt достаем
    # ключ сессии и им расшифровываем время
    message = json.loads(message.decode())
    message['tgt'] = json.loads(decrypt(message['tgt'], kdc_password))
    message['time'] = float(decrypt(message['time'], message['tgt']['session_key']))
    return message

def encrypt_kcs_user_ticket(message, tgs_key, session_key):
    # TODO: Шифруем билет сервера ключом сервера(tgs_key), а все вместе сессионным
    # ключом сессии
    message['server_ticket'] = encrypt(json.dumps(message['server_ticket']), tgs_key)
    message['username'] = encrypt(message['username'], session_key)
    message['target_server'] = encrypt(message['target_server'], session_key)
    message['start_time'] = encrypt(str(message['start_time']), session_key)
    message['end_time'] = encrypt(str(message['end_time']), session_key)
    message['kcs_key'] = encrypt(message['kcs_key'], session_key)
    
    return json.dumps(message).encode()

def decrypt_kcs_user_ticket(message, session_key):
    # TODO: Расшифровываем билет пользователя и всё остальное ключом сессии
    # билет сервера остается зашифрованным
    message = json.loads(message.decode())
    message['username'] = decrypt(message['username'], session_key)
    message['target_server'] = decrypt(message['target_server'], session_key)
    message['start_time'] = decrypt(str(message['start_time']), session_key)
    message['end_time'] = decrypt(str(message['end_time']), session_key)
    message['kcs_key'] = decrypt(message['kcs_key'], session_key)
    return message

def encrypt_target_server_ticket(message, kcs_key):
    # TODO: Зашифровать время ключом kcs, билет сервера не трогать
    message['time'] = encrypt(str(message['time']), kcs_key)
    return json.dumps(message).encode()

def decrypt_target_server_ticket(message, tgs_key):
    # TODO: Расшифровываем билет сервера ключом tgs
    # а затем kcs ключом расшифровываем время
    message = json.loads(message.decode()) 
    message['server_ticket'] = json.loads(decrypt(message['server_ticket'], tgs_key))
    message['time'] = encrypt(message['time'], message['server_ticket']['kcs_key'])
    return message
