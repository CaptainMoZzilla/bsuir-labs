import time
import hashlib 
import sys

from PyQt5 import QtWidgets, QtGui,QtCore
from PyQt5.QtWidgets import QMessageBox

from login import Ui_MainWindow as LoginUi
from register import Ui_MainWindow as RegisterUi
from main import Ui_MainWindow as MainUi

from defender import is_login_safe,\
                     is_password_safe

from database import add_user,\
                     is_login_exist,\
                     get_user_role,\
                     is_user_exist,\
                     get_all_users

class RegisterWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super(RegisterWindow, self).__init__()
        self.ui = RegisterUi()
        self.ui.setupUi(self)
        self.ui.register_button.clicked.connect(self.on_register_button_cliced)
    

    def on_register_button_cliced(self):
        login = self.ui.login_label.text()
        password = self.ui.password_label.text()
        cofirm = self.ui.confirm_label.text()

        if not is_login_safe(login):
            QMessageBox.about(self, "Incorrect login", "Логин может иметь только числа, буквы, '@', '.'\n"
                                    "Длина не должна превышать 40 символов")
            return

        if not is_password_safe(password):
            QMessageBox.about(self, "Incorrect password", "Длина не должна превышать 40 символов")
            return

        if cofirm != password:
            QMessageBox.about(self, "Incorrect password", "Пароли не совпадают")
            return
        
        if is_login_exist(login):
            QMessageBox.about(self, "Incorrect login", "Такой пользователь уже существует")
            return

        add_user([login, hashlib.md5(password.encode()).hexdigest(), 'user'])
        self.close()
        self.login_window = LoginWindow()
        self.login_window.show()


class LoginWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super(LoginWindow, self).__init__()
        
        self.ui = LoginUi()
        self.ui.setupUi(self)
        self.ui.register_button.clicked.connect(self.register_button_clicked)
        self.ui.enter_button.clicked.connect(self.enter_button_clicked)
        self.counter = 0
        self.time = None

    def register_button_clicked(self):
        self.close()
        self.register_window = RegisterWindow()
        self.register_window.show()
        
    def enter_button_clicked(self):
        login = self.ui.login_label.text()
        password = self.ui.password_label.text()
        
        if self.time is None and self.counter >= 5:
            self.time = time.time() + 20
            QMessageBox.about(self, "Limit", "Слишком много попыток, подождите 20 секунд")
            return
        elif self.time is not None:
            if time.time() < self.time:
                QMessageBox.about(self, "Limit", "Слишком много попыток, подождите 20 секунд")
                return
            else:
                self.time = None
                self.counter = 0

        self.counter += 1
        if not is_login_safe(login):
            QMessageBox.about(self, "Incorrect login", "Логин может иметь только числа, буквы, '@', '.'\n"
                                    "Длина не должна превышать 40 символов")
            return

        if not is_password_safe(password):
            QMessageBox.about(self, "Incorrect password", "Длина не должна превышать 40 символов")
            return

        if not is_user_exist(login, hashlib.md5(password.encode()).hexdigest()):
            QMessageBox.about(self, "Incorrect login", "Неправильный логин или пароль")
            return
        self.counter = 0
        self.time = None
        
        self.close()
        self.main_window = MainWindow(login, hashlib.md5(password.encode()).hexdigest())
        self.main_window.show()


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self, login, password_hash):
        super(MainWindow, self).__init__()    
        self.ui = MainUi()
        self.ui.setupUi(self)

        self.role = get_user_role(login, password_hash)
        self.ui.role_label.setText(f'Role: {self.role[0]}')

        if self.role[0] != 'admin':
            self.ui.users_button.setEnabled(False)
        else:
            self.ui.users_button.clicked.connect(self.button_clicked)

    def button_clicked(self):
        users = get_all_users()
        self.ui.users_label.setText('Users:\n' +
                                    'LOGIN     PASSWORD             ROLE\n' + 
                                    '\n'.join([' '.join(u[1:]) for u in users]))


app = QtWidgets.QApplication([])
application = LoginWindow()
application.show() 

sys.exit(app.exec())