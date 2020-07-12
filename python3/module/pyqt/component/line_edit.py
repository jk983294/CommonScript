import sys
from PyQt5.QtWidgets import (QWidget, QLabel, QLineEdit, QApplication)


class Example(QWidget):
    def __init__(self):
        super().__init__()
        self.lbl = None
        self.init_ui()

    def init_ui(self):
        self.lbl = QLabel(self)
        qle = QLineEdit(self)

        qle.move(60, 100)
        self.lbl.move(60, 40)

        qle.textChanged[str].connect(self.on_text_changed)

        self.setGeometry(300, 300, 280, 170)
        self.setWindowTitle('QLineEdit')
        self.show()

    def on_text_changed(self, text):
        """在QLineEdit中输入的文字会实时显示在QLabel控件中"""
        self.lbl.setText(text)
        self.lbl.adjustSize()  # 将QLabel控件的尺寸调整为文本的长度


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
