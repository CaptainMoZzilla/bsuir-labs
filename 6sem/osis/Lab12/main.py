import time
import threading
from threading import Thread, Lock

from PyQt5 import QtWidgets, QtGui,QtCore
from design import Ui_MainWindow
import random
import sys

class mywindow(QtWidgets.QMainWindow):

    def __init__(self):
        super(mywindow, self).__init__()
        self.mutex = threading.Lock()
        self.semaphore = threading.Semaphore()
        
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        
        self.ui.pushButton.clicked.connect(self.start_threads)

    def set_mutext_color(self, color):
        self.mutex.acquire()
        try:
    
            self.ui.mutex_label.setStyleSheet(f"background-color:{color};")
            time.sleep(0.1)        
        finally:
            self.mutex.release()    

    def set_semaphor_color(self, color):
        self.semaphore.acquire()
        try:
            self.ui.semaphor_label.setStyleSheet(f"background-color:{color};")
            time.sleep(0.1)        
        finally:
            self.semaphore.release()

    def start_mutext(self, color):
        while True:
            self.set_mutext_color(color)
            time.sleep(0.2)        

    def start_semaphor(self, color):
        while True:
            self.set_semaphor_color(color)
            time.sleep(0.1)        


    def start_threads(self):
        threading.Thread(target=self.start_mutext, args=('#0000FF', )).start()
        threading.Thread(target=self.start_mutext, args=('#ffff00',)).start()
        threading.Thread(target=self.start_mutext, args=('#000000', )).start()

        threading.Thread(target=self.start_semaphor, args=('#ffff00', )).start()
        threading.Thread(target=self.start_semaphor, args=('#0000FF', )).start()
        threading.Thread(target=self.start_semaphor, args=('#000000', )).start()


app = QtWidgets.QApplication([])
application = mywindow()
application.show() 
sys.exit(app.exec())