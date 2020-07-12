import sys

from PyQt5.QtGui import QColor, QIcon
from PyQt5.QtWidgets import (QWidget, QPushButton, QLineEdit,
                             QInputDialog, QApplication, QFrame, QColorDialog, QTextEdit, QAction, QFileDialog)


class Example(QWidget):

    def __init__(self):
        super().__init__()
        self.le = None
        self.frm = None
        self.text_edit = None
        self.init_ui_input_dialog()

    def init_ui_color_dialog(self):
        """显示一个用于选择颜色值的对话框"""
        col = QColor(0, 0, 0)  # 初始化QFrame的颜色为黑色

        btn = QPushButton('Dialog', self)
        btn.move(20, 20)
        btn.clicked.connect(self.show_color_dialog)

        self.frm = QFrame(self)
        self.frm.setStyleSheet("QWidget { background-color: %s }" % col.name())
        self.frm.setGeometry(130, 22, 100, 100)

        self.setGeometry(300, 300, 250, 180)
        self.setWindowTitle('Color dialog')
        self.show()

    def init_ui_input_dialog(self):
        """用户点击按钮显示一个输入框，用户输入信息会显示在文本框中"""
        btn = QPushButton('Dialog', self)
        btn.move(20, 20)
        btn.clicked.connect(self.show_dialog)

        self.le = QLineEdit(self)
        self.le.move(130, 22)

        self.setGeometry(300, 300, 290, 150)
        self.setWindowTitle('Input dialog')
        self.show()

    def show_dialog(self):
        text, ok = QInputDialog.getText(self, 'Input Dialog', 'Enter your name:')

        if ok:
            self.le.setText(str(text))

    def show_color_dialog(self):
        """当颜色值有效时，我们通过样式表(style sheet)来改变背景颜色"""
        col = QColorDialog.getColor()

        if col.isValid():
            self.frm.setStyleSheet("QWidget { background-color: %s }" % col.name())


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
