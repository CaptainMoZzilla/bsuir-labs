import sys
import time
import msvcrt

import schedule

line = ''
def job():
    with open('./data.txt', 'w') as f:
        f.write(line)


schedule.every(20).seconds.do(job)

while True:
    x = msvcrt.getch()    
    x = x.decode('utf8')
    line += x
    schedule.run_pending()