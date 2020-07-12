import sys
from PyQt5.QtWidgets import (QPushButton, QWidget,  QLineEdit, QApplication)


class Button(QPushButton):
    def __init__(self, title, parent):
        super().__init__(title, parent)

        self.setAcceptDrops(True)  # 接受drop事件

    def dragEnterEvent(self, e):
        """设置可接受的数据类型(在这里是普通文本)"""
        if e.mimeData().hasFormat('text/plain'):
            e.accept()
        else:
            e.ignore()

    def dropEvent(self, e):
        """在drop事件发生时, 改变按钮的文字"""
        self.setText(e.mimeData().text())


class Example(QWidget):
    def __init__(self):
        super().__init__()

        self.init_ui()

    def init_ui(self):
        edit = QLineEdit('', self)
        edit.setDragEnabled(True)  # drag操作的支持
        edit.move(30, 65)

        button = Button("Button", self)
        button.move(190, 65)

        self.setWindowTitle('Simple drag & drop')
        self.setGeometry(300, 300, 300, 150)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    ex.show()
    app.exec_()
