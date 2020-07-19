# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'main.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(787, 587)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.users_button = QtWidgets.QPushButton(self.centralwidget)
        self.users_button.setGeometry(QtCore.QRect(30, 240, 91, 51))
        self.users_button.setObjectName("users_button")
        self.users_label = QtWidgets.QLabel(self.centralwidget)
        self.users_label.setGeometry(QtCore.QRect(260, 30, 431, 451))
        self.users_label.setText("")
        self.users_label.setObjectName("users_label")
        self.role_label = QtWidgets.QLabel(self.centralwidget)
        self.role_label.setGeometry(QtCore.QRect(20, 20, 171, 31))
        self.role_label.setObjectName("role_label")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 787, 21))
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
        self.users_button.setText(_translate("MainWindow", "Show users"))
        self.role_label.setText(_translate("MainWindow", "Role: "))
