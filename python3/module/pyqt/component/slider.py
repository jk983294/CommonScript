import sys
from PyQt5.QtWidgets import (QWidget, QSlider,
                             QLabel, QApplication)
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QPixmap


class Example(QWidget):

    def __init__(self):
        super().__init__()
        self.label = None
        self.init_ui()

    def init_ui(self):
        sld = QSlider(Qt.Horizontal, self)
        sld.setFocusPolicy(Qt.NoFocus)
        sld.setGeometry(30, 40, 100, 30)
        sld.valueChanged[int].connect(self.change_value)

        self.label = QLabel(self)
        self.label.setPixmap(QPixmap('audio.ico'))
        self.label.setGeometry(160, 40, 80, 30)

        self.setGeometry(300, 300, 280, 170)
        self.setWindowTitle('QSlider')
        self.show()

    def change_value(self, value):
        """模拟了一个音量控制。通过拖动滑块来改变标签上的图像"""
        if value == 0:
            self.label.setPixmap(QPixmap('audio.ico'))
        elif 0 < value <= 30:
            self.label.setPixmap(QPixmap('min.ico'))
        elif 30 < value < 80:
            self.label.setPixmap(QPixmap('med.ico'))
        else:
            self.label.setPixmap(QPixmap('max.ico'))


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
