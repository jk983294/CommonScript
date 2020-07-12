import sys

from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QMainWindow, QApplication, QAction, qApp, QTextEdit


class Example(QMainWindow):

    def __init__(self):
        super().__init__()
        self.toolbar = None
        self.init_ui_status_bar()

    def init_ui_status_bar(self):
        text_edit = QTextEdit()
        self.setCentralWidget(text_edit)

        exit_action = QAction(QIcon('exit.png'), '&Exit', self)
        exit_action.setShortcut('Ctrl+Q')
        exit_action.setStatusTip('Exit application')
        exit_action.triggered.connect(qApp.quit)

        menu_bar = self.menuBar()
        file_menu = menu_bar.addMenu('&File')  # 添加菜单
        file_menu.addAction(exit_action)  # 添加事件

        tool_bar_exit_action = QAction(QIcon('exit24.png'), 'Exit', self)
        tool_bar_exit_action.setShortcut('Ctrl+Q')
        tool_bar_exit_action.triggered.connect(qApp.quit)

        self.toolbar = self.addToolBar('Exit')
        self.toolbar.addAction(tool_bar_exit_action)

        status_bar = self.statusBar()
        status_bar.showMessage('Ready')  # show at bottom

        self.setGeometry(300, 300, 250, 150)
        self.setWindowTitle('status bar')
        self.show()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
