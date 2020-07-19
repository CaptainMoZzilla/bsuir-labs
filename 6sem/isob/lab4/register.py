# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'register.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(308, 330)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(50, 50, 47, 13))
        self.label.setObjectName("label")
        self.label_2 = QtWidgets.QLabel(self.centralwidget)
        self.label_2.setGeometry(QtCore.QRect(50, 100, 47, 13))
        self.label_2.setObjectName("label_2")
        self.label_3 = QtWidgets.QLabel(self.centralwidget)
        self.label_3.setGeometry(QtCore.QRect(50, 150, 81, 21))
        self.label_3.setObjectName("label_3")
        self.register_button = QtWidgets.QPushButton(self.centralwidget)
        self.register_button.setGeometry(QtCore.QRect(90, 220, 121, 41))
        self.register_button.setObjectName("register_button")
        self.login_label = QtWidgets.QLineEdit(self.centralwidget)
        self.login_label.setGeometry(QtCore.QRect(140, 50, 113, 20))
        self.login_label.setObjectName("login_label")
        self.password_label = QtWidgets.QLineEdit(self.centralwidget)
        self.password_label.setGeometry(QtCore.QRect(140, 100, 113, 20))
        self.password_label.setEchoMode(QtWidgets.QLineEdit.Password)
        self.password_label.setObjectName("password_label")
        self.confirm_label = QtWidgets.QLineEdit(self.centralwidget)
        self.confirm_label.setGeometry(QtCore.QRect(140, 150, 113, 20))
        self.confirm_label.setEchoMode(QtWidgets.QLineEdit.Password)
        self.confirm_label.setObjectName("confirm_label")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 308, 21))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.label.setText(_translate("MainWindow", "Login"))
        self.label_2.setText(_translate("MainWindow", "Password"))
        self.label_3.setText(_translate("MainWindow", "Confirm"))
        self.register_button.setText(_translate("MainWindow", "Register"))
