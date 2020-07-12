import sys
from PyQt5.QtWidgets import (QWidget, QPushButton, QFrame, QApplication)
from PyQt5.QtGui import QColor


class Example(QWidget):

    def __init__(self):
        super().__init__()
        self.col = None
        self.square = None
        self.init_ui()

    def init_ui(self):
        """QPushButton并通过其setCheckable()方法来得到一个ToggleButton"""
        self.col = QColor(0, 0, 0)

        red_button = QPushButton('Red', self)
        red_button.setCheckable(True)
        red_button.move(10, 10)
        red_button.clicked[bool].connect(self.set_color)

        green_button = QPushButton('Green', self)
        green_button.setCheckable(True)
        green_button.move(10, 60)
        green_button.clicked[bool].connect(self.set_color)

        blue_button = QPushButton('Blue', self)
        blue_button.setCheckable(True)
        blue_button.move(10, 110)
        blue_button.clicked[bool].connect(self.set_color)

        self.square = QFrame(self)
        self.square.setGeometry(150, 20, 100, 100)
        self.square.setStyleSheet("QWidget { background-color: %s }" % self.col.name())

        self.setGeometry(300, 300, 280, 170)
        self.setWindowTitle('Toggle button')
        self.show()

    def set_color(self, pressed):
        source = self.sender()

        if pressed:
            val = 255
        else:
            val = 0

        if source.text() == "Red":
            self.col.setRed(val)
        elif source.text() == "Green":
            self.col.setGreen(val)
        else:
            self.col.setBlue(val)

        self.square.setStyleSheet("QFrame { background-color: %s }" % self.col.name())


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
