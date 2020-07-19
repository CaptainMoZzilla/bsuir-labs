import time
import threading

from PyQt5 import QtWidgets, QtGui,QtCore
from design import Ui_MainWindow
import random
import sys

class mywindow(QtWidgets.QMainWindow):

    def __init__(self):
        super(mywindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        
        self.ui.label.setFont(
            QtGui.QFont('SansSerif', 30)
        )
 
        self.ui.label.setGeometry(
            QtCore.QRect(10, 10, 200, 200)
        ) # изменить геометрию ярлыка
        self.ui.pushButton.clicked.connect(self.move_label)
    
    def _move_second_label(self):
        while True:       
            x = self.ui.label.x()
            y = self.ui.label.y()

            rand_x = random.randint(-4, 4)
            rand_y = random.randint(-4, 4)

            self.ui.label.move(x + rand_x, y + rand_y)
            time.sleep(0.1)
    
    def _move_first_label(self):
        while True:       
            x = self.ui.label_2.x()
            y = self.ui.label_2.y()

            rand_x = random.randint(-8, 8)
            rand_y = random.randint(-8, 8)

            self.ui.label_2.move(x + rand_x, y + rand_y)
            time.sleep(0.1)

    def _move_third_label(self):
        while True:       
            x = self.ui.label_2.x()
            y = self.ui.label_2.y()

            rand_x = random.randint(-10, 10)
            rand_y = random.randint(-10, 10)

            self.ui.label_3.move(x + rand_x, y + rand_y)
            time.sleep(0.1)

    def move_label(self):
        threading.Thread(target=(self._move_first_label)).start()
        threading.Thread(target=(self._move_second_label)).start()
        threading.Thread(target=(self._move_third_label)).start()
        

app = QtWidgets.QApplication([])
application = mywindow()
application.show()
 
sys.exit(app.exec())