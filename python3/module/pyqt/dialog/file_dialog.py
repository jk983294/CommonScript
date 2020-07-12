import sys

from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import (QApplication, QTextEdit, QAction, QFileDialog, QMainWindow)


class Example(QMainWindow):

    def __init__(self):
        super().__init__()
        self.le = None
        self.frm = None
        self.text_edit = None
        self.init_ui_file_dialog()

    def init_ui_file_dialog(self):
        self.text_edit = QTextEdit()
        self.setCentralWidget(self.text_edit)
        self.statusBar()

        open_file = QAction(QIcon('open.png'), 'Open', self)
        open_file.setShortcut('Ctrl+O')
        open_file.setStatusTip('Open new File')
        open_file.triggered.connect(self.show_file_dialog)

        menu_bar = self.menuBar()
        file_menu = menu_bar.addMenu('&File')
        file_menu.addAction(open_file)

        self.setGeometry(300, 300, 350, 300)
        self.setWindowTitle('File dialog')
        self.show()

    def show_file_dialog(self):
        fname = QFileDialog.getOpenFileName(self, 'Open file', '/home')
        if fname[0]:
            f = open(fname[0], 'r')

            with f:
                data = f.read()
                self.text_edit.setText(data)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
