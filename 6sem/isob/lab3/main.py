import socket
from random import randint
from tqdm import tqdm

def passive_scan(return_open=True):
    open_ports = []
    sock = socket.socket()
    for portNumber in range(2220, 4444):
        try:
            sock.connect(('localhost', portNumber))
            print('[*] Port', portNumber, '/tcp','is open')
            return portNumber
        except:
            print(portNumber, ' is closed')
            continue
    if return_open:
        return open_ports


def full_flood(host, port, counter):
	for _ in tqdm(range(counter)):
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
		try:
			s.connect((host, port))
		except Exception as ex:
			continue

full_flood('localhost', passive_scan(), 100)
