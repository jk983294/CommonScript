import sys
from PyQt5.QtCore import pyqtSignal, QObject
from PyQt5.QtWidgets import QMainWindow, QApplication


class Communicate(QObject):
    closeApp = pyqtSignal()  # 信号closeApp是Communicate的类属性，它由pyqtSignal()创建


class Example(QMainWindow):

    def __init__(self):
        super().__init__()
        self.c = None
        self.init_ui()

    def init_ui(self):
        self.c = Communicate()
        self.c.closeApp.connect(self.close)  # 自定义closeApp信号连接到QMainWindow的close槽

        self.setGeometry(300, 300, 290, 150)
        self.setWindowTitle('Emit signal')
        self.show()

    def mousePressEvent(self, event):
        self.c.closeApp.emit()  # 点击鼠标时会触发closeApp信号，使程序退出


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
