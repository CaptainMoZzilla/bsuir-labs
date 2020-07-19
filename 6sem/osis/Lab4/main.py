import sys
import msvcrt

while True:
    x = msvcrt.getch()
    if x == '\r'.encode():
        break
    
    if x == ' '.encode():
        continue
    
    x = x.decode('utf8')
    sys.stdout.write(x)